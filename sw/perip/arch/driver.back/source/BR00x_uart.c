/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_uart.c
 * @brief   This file provides all the UART firmware functions.
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

#include "BR00x_uart.h"
#include <stdint.h>

UART_write_handle  UWrite_handle;


void UART_DeInit(UART_TypeDef *UARTx)
{
    #if  defined(BR002)||defined(BR003)
    if (UARTx == UART0) {
        SystemDevRstCtl(UART0_SwRst);
        memset(UART0,0,sizeof(UART_TypeDef));
    }
    else {
        SystemDevRstCtl(UART1_SwRst);
        memset(UART1,0,sizeof(UART_TypeDef));
    }
    #endif

    #if defined(BR005)

    if (UARTx == UART0) {
        SystemDevRstCtl(UART0_PCLK_SwRst);
        SystemDevRstCtl(UART0_SLCK_SwRst);
        memset(UART0,0,sizeof(UART_TypeDef));
    }
    else {
        SystemDevRstCtl(UART1_PCLK_SwRst);
        memset(UART1,0,sizeof(UART_TypeDef));
    }
    #endif
}

void UART_Init(UART_TypeDef *UARTx, UART_InitInfo_Type *UART_InitStruct)
{
    uint32_t BR_div;
    uint32_t fcr_cfg = 0;
    
    if (UARTx->USR & 0x01) {
        //UART is busy now, we can init it!
        return;
    }
    UARTx->IER &= ~(0xFF);
    UARTx->LCR |= 0x01 << 7; //Enable the DLL/DLH to writable
    BR_div = (SystemCoreClock/UART_InitStruct->UART_BaudRate);

    UARTx->DLL =  ((BR_div>>4 ) & 0xFF);
    UARTx->DLH =  ((BR_div>>12) & 0xFF);
    UARTx->DLF =  ((BR_div) & 0xf);
    
    UARTx->LCR &= ~(0x01 << 7); //Disable the DLL/DLH to writable
    UARTx->LCR &= ~(0xFF);
    UARTx->LCR_EXT &= ~(0xFF);
    if (UART_InitStruct->UART_WordLength == UART_WL_9BITS) {
        //Supported  ???
        //UARTx->LCR_EXT |= 0x01 << 0;
    }
    else {
        UARTx->LCR |= UART_InitStruct->UART_WordLength;
    }
    UARTx->LCR |= UART_InitStruct->UART_StopBits << 2;
    if (UART_InitStruct->UART_ParityMode != UART_PM_NONE) {
        UARTx->LCR |= 0x01 << 3;
        //For ODD parity mode, the EPS/Stick Parity have be cleard.
        if (UART_InitStruct->UART_ParityMode == UART_PM_EVEN) {
            UARTx->LCR |= 0x01 << 4;
        }
        else if (UART_InitStruct->UART_ParityMode == UART_PM_STICK_LOG0) {
            UARTx->LCR |= 0x03 << 4;
        }
        else if (UART_InitStruct->UART_ParityMode == UART_PM_STICK_LOG1) {
            UARTx->LCR |= 0x02 << 4;
        }
    }
    UARTx->MCR &= ~(0xFF);
    if (UART_InitStruct->UART_HardwareFlowControl      == UART_FC_DTRDSR) 
         UARTx->MCR |= 0x01;
    else if (UART_InitStruct->UART_HardwareFlowControl == UART_FC_RTSCTS) 
         UARTx->MCR |= 0x02;
    else if (UART_InitStruct->UART_HardwareFlowControl == UART_FC_AUTO_RTSCTS) 
        UARTx->MCR  |= 0x22;
    else if (UART_InitStruct->UART_HardwareFlowControl == UART_FC_RTSCTS_DTRDSR) 
        UARTx->MCR  |= 0x3;
    else if (UART_InitStruct->UART_HardwareFlowControl == UART_FC_AUTO_RTSCTS_DTRDSR) 
        UARTx->MCR  |= 0x23;
    
    UARTx->FCR &= ~(0xFF);
    if (UART_InitStruct->UART_DMAMode == UART_DM_MODE_1) 
        fcr_cfg |= 0x01 << 3;
    
    if (UART_InitStruct->UART_FIFOMode == UART_FM_ENABLE) {
        
        fcr_cfg |= UART_InitStruct->UART_RX_FIFOTriggerMode << 6;
        fcr_cfg |= UART_InitStruct->UART_TX_FIFOTriggerMode << 4;       
    }
    
    fcr_cfg |= 0x03 << 1; //Reset XMIT/RCVR FIFO
    fcr_cfg |= 0x01 << 0;
    UARTx->FCR = fcr_cfg;
}

void UART_InterruptSet(UART_TypeDef *UARTx, uint16_t UART_IntMask)
{
    // UARTx->LCR &= ~(0x01 << 7); //Disable the DLL/DLH to writable    
    UARTx->IER &= ~UART_IntMask;
    UARTx->IER |= UART_IntMask;
}

void UART_WriteByte(UART_TypeDef *UARTx, uint8_t byte)
{
    UARTx->THR = byte;
}

void UART_WriteData(UART_TypeDef *UARTx, uint8_t *data, uint16_t length)
{
    while (length--) {
        while (!(UARTx->LSR & UART_LSR_BIT_THRE))
        {
            if(UWrite_handle)
                UWrite_handle();
        };
        UARTx->THR = *data++;
    }
}

void UART_SetUWriteHandle(UART_write_handle handle)
{
    UWrite_handle = handle;
}

uint8_t UART_ReadByte(UART_TypeDef *UARTx)
{
    return (UARTx->RBR & 0xFF);
}

void  UART_AutoFlow(UART_TypeDef *UARTx,bool En)
{
    if(En)
    {
        UARTx->MCR  |=0x22;  
        UARTx->FCR  |=1<<0;
    }
    else
    {
        UARTx->MCR  &= ~0x22;  
    }
        
}

void  UART_SetRts(UART_TypeDef *UARTx,bool En)
{
    if(En)
    {
        UARTx->MCR  |=0x02;  
    }
    else
    {
        UARTx->MCR  &= ~0x02;  
    }
        
}

FlagStatus UART_LSRCheckBits(UART_TypeDef *UARTx, uint32_t bits)
{
    uint32_t val = UARTx->LSR & 0x1FF;

    if (val & bits) {
        return SET;
    }
    else {
        return RESET;
    }
}

FlagStatus UART_MSRCheckBits(UART_TypeDef *UARTx, uint32_t bits)
{
    uint32_t val = UARTx->MSR;

    if (val & bits) {
        return SET;
    }
    else {
        return RESET;
    }
}

UART_InterID_Tpye UART_GetInterruptID(UART_TypeDef *UARTx)
{
    return (UART_InterID_Tpye)(UARTx->IIR & 0xf);
}

ITStatus UART_GetInterruptStatus(UART_TypeDef *UARTx, uint16_t UART_IntIds)
{
    if (UARTx->IER & UART_IntIds) {
        if (UARTx->IIR & UART_IntIds) {
            return SET;
        }
    }
    return RESET;
}

uint32_t UART_GetStatus(UART_TypeDef *UARTx)
{
    return(UARTx->USR );
}



