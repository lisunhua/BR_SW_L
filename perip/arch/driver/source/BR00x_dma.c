/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_dma.c
 * @brief   This file provides all the DMA firmware functions.
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * @date    11-Augest-2018
 * @version V1.0.0
 * @author  Asher
*/

#include "BR00x_dma.h"
#include "system_BR00x.h"
#include "cm_printf.h"

void DMA_DeInit(void)
{
#if  defined(BR002)||defined(BR003)
    SystemDevRstCtl(DMA_SwRst);
#endif
    memset(DMA, 0, sizeof(DMA_TypeDef));
}

void DMA_Init(DMA_ChNum_Type ch, DMA_InitInfo_Type *DMA_InitStru)
{
    uint32_t ctl0 = 0;
    uint32_t cfg0 = 0;
    uint32_t cfg1 = 0;
    if (IS_DMA_CHANNEL(ch) == RESET) {
        return;
    }
    DMA->CHR[ch].SAR = DMA_InitStru->src_addr;
    DMA->CHR[ch].DAR = DMA_InitStru->dst_addr;
    DMA->CHR[ch].CTL1 = DMA_InitStru->block_size & 0x0FFF;
    if (DMA_InitStru->src_llp_en == SET) {
        ctl0 |= SET_BITS(1ul, 28);
    }
    if (DMA_InitStru->dst_llp_en == SET) {
        ctl0 |= SET_BITS(1ul, 27);
    }
    ctl0 |= SET_BITS(DMA_InitStru->tt_tc_mode,      20);
    ctl0 |= SET_BITS(DMA_InitStru->src_msize,       14);
    ctl0 |= SET_BITS(DMA_InitStru->dst_msize,       11);
    ctl0 |= SET_BITS(DMA_InitStru->src_inc_mode,    9 );
    ctl0 |= SET_BITS(DMA_InitStru->dst_inc_mode,    7 );
    ctl0 |= SET_BITS(DMA_InitStru->src_trans_w,     4 );
    ctl0 |= SET_BITS(DMA_InitStru->dst_trans_w,     1 );
    if (DMA_InitStru->int_en == SET) {
        ctl0 |= SET_BITS(1ul, 0);
    }
    DMA->CHR[ch].CTL0 = ctl0;

    cfg1 |= SET_BITS(DMA_InitStru->fifo_mode, 1);
    cfg1 |= SET_BITS(DMA_InitStru->fc_mode, 0);
    if (DMA_InitStru->src_hs_sel == DMA_HS_HARDWARE) {
        cfg1 |= (DMA_InitStru->src_per& 0xF)<<7;
    }
    if (DMA_InitStru->dst_hs_sel == DMA_HS_HARDWARE) {
        cfg1 |= (DMA_InitStru->dst_per& 0xF)<<11;
    }
    
    DMA->CHR[ch].CFG1 = cfg1;
    
    if (DMA_InitStru->src_reload_en == SET) {
        cfg0 |= SET_BITS(1ul, 30);
    }
    if (DMA_InitStru->dst_reload_en == SET) {
        cfg0 |= SET_BITS(1ul, 31);
    }
    cfg0 |= SET_BITS((DMA_InitStru->max_abrst & 0x3FF), 20);
    cfg0 |= SET_BITS(DMA_InitStru->src_hs_pol, 19);
    cfg0 |= SET_BITS(DMA_InitStru->dst_hs_pol, 18);
    cfg0 |= SET_BITS(DMA_InitStru->src_hs_sel, 11);
    cfg0 |= SET_BITS(DMA_InitStru->dst_hs_sel, 10);
    if (DMA_InitStru->ch_suspend == SET) {
        cfg0 |= SET_BITS(1ul, 8);
    }
    cfg0 |= SET_BITS(DMA_InitStru->ch_priority, 5);
    DMA->CHR[ch].CFG0 = cfg0;
}

void DMA_Enable(FunctionalState st)
{
    if (st == ENABLE) {
        DMA->MR.CFG = 0x01;
    }
    else {
        DMA->MR.CFG = 0x00;
    }
}

void DMA_EnableCh(DMA_ChNum_Type ch, FunctionalState st)
{
    if (st == ENABLE) {
        DMA->MR.EN = SET_BITS(1ul, ch + DMA_CHANNELS_NUM) | SET_BITS(1ul, ch);
    }
    else {
        DMA->MR.EN = SET_BITS(1ul, ch + DMA_CHANNELS_NUM) | 0x00;
    }
}

FlagStatus DMA_IsFifoEmpty(DMA_ChNum_Type ch)
{
    FlagStatus r;

    if (DMA->CHR[ch].CFG0 & SET_BITS(1ul, 9)/* 9th bit in CFG register */) {
        r = RESET;
    }
    else {
        r = SET;
    }

    return r;
}

void DMA_SuspendEn(DMA_ChNum_Type ch, FunctionalState st)
{
    if (st == SET) {
        DMA->CHR[ch].CFG0 |= SET_BITS(1ul, 8);
    }
    else {
        DMA->CHR[ch].CFG0 &= CLEAR_BITS(1ul, 8);
    }
}

ITStatus DMA_GetIntRawStatus(DMA_ChNum_Type ch, DMA_IntType_Type type)
{
    ITStatus r;

    uint8_t status = *((uint8_t *)(&DMA->IR) + type * 8);

    if (status & SET_BITS(1ul, ch)) {
        r = SET;
    }
    else {
        r = RESET;
    }

    return r;
}

void DMA_SetIntRawStatus(DMA_ChNum_Type ch, DMA_IntType_Type type, FlagStatus flag)
{
    if (flag == SET) {
        *((uint8_t *)(&DMA->IR)  + (type + 0)  * 8) |= SET_BITS(1ul, ch + DMA_CHANNELS_NUM);
    }
    else {
        *((uint8_t *)(&DMA->IR)  + (type + 0)  * 8) &= CLEAR_BITS(1ul, ch + DMA_CHANNELS_NUM);
    }
}

ITStatus DMA_GetIntStatus(DMA_ChNum_Type ch, DMA_IntType_Type type)
{
    ITStatus r;

    uint8_t status = *((uint8_t *)(&DMA->IR) + (type + 5) * 8);

    if (status & SET_BITS(1ul, ch)) {
        r = SET;
    }
    else {
        r = RESET;
    }

    return r;

}

void DMA_SetIntMask(DMA_ChNum_Type ch, DMA_IntType_Type type, FlagStatus flag)
{
    if (flag == SET) {
        *((uint16_t *)(&DMA->IR)  + (type + 10)  * 4) = SET_BITS(1ul, ch + DMA_CHANNELS_NUM) | SET_BITS(1ul, ch);
    }
    else {
        *((uint16_t *)(&DMA->IR)  + (type + 10)  * 4) = SET_BITS(1ul, ch + DMA_CHANNELS_NUM) | 0x00;
    }
}

ITStatus DMA_GetIntMask(DMA_ChNum_Type ch, DMA_IntType_Type type)
{
    ITStatus r;

    uint8_t status = *((uint8_t *)(&DMA->IR) + (type + 10) * 8);

    if (status & SET_BITS(1ul, ch)) {
        r = SET;
    }
    else {
        r = RESET;
    }

    return r;
}

void DMA_ClearInt(DMA_ChNum_Type ch, DMA_IntType_Type type)
{
    *((uint8_t *)(&DMA->IR)  + (type + 15)  * 8) = SET_BITS(1ul, ch);
}

