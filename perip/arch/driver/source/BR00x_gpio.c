/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_gpio.c
 * @brief    This file provides the GPIO firmware functions.
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * @date    14. Augest 2018
 * @version V1.0.0
 * @author  Asher
*/
#include "BR00x_gpio.h"
#include "system_BR00x.h"
#include <stdlib.h>
#include <string.h>

#define GPIO_CAL_PORT(X)  (X-32)

void GPIO_DeInit(void)
{
#if  defined(BR002)||defined(BR003)
    SystemDevRstCtl(GPIO_SwRst);
#endif

#if  defined(BR005)
    SystemDevRstCtl(GPIO_PCLK_SwRst);
    SystemDevRstCtl(IFCLK_GPIO_SwRst);
#endif
    //memset(GPIO, 0, sizeof(GPIO_TypeDef));
}

void GPIO_Init(GPIO_InitInfo_Type *GPIO_InitStru)
{
    if (!IS_VAILD_PIN(GPIO_InitStru->pin)) {
        return;
    }
    if (GPIO_InitStru->pin < 0x20) {
      //  GPIO->DR0 |= 1 << GPIO_InitStru->pin;
        GPIO->DDR0 |= GPIO_InitStru->dir << GPIO_InitStru->pin;
        GPIO->CTL0 |= GPIO_InitStru->mode << GPIO_InitStru->pin;
        GPIO->IE |= GPIO_InitStru->int_en << GPIO_InitStru->pin;
        if (GPIO_InitStru->int_en) {
            if(GPIO_InitStru->int_unmask){
                GPIO->IM &=  ~(0x01<< GPIO_InitStru->pin);
            }else{
                GPIO->IM |=  0x01<< GPIO_InitStru->pin;
            }
            GPIO->ITL |= GPIO_InitStru->int_type << GPIO_InitStru->pin;
            GPIO->IP |= GPIO_InitStru->int_pol << GPIO_InitStru->pin;
            GPIO->DB |= GPIO_InitStru->debounce_en << GPIO_InitStru->pin;
        }
    }
    else {
       // GPIO->DR1 |= 1 << GPIO_CAL_PORT(GPIO_InitStru->pin);
        GPIO->DDR1 |= (GPIO_InitStru->dir << GPIO_CAL_PORT(GPIO_InitStru->pin));
        GPIO->CTL1 |= (GPIO_InitStru->mode << GPIO_CAL_PORT(GPIO_InitStru->pin));
    }
}

FlagStatus GPIO_ReadBit(GPIO_PinId_Type GPIO_Pin)
{
    if (!IS_VAILD_PIN(GPIO_Pin)) {
        return RESET;
    }
    if (GPIO_Pin < 0x20) {
        if (GPIO->EXTDR0 & (0x01ul << GPIO_Pin)) {
            return SET;
        }
        else {
            return RESET;
        }
    }
    else {
        if (GPIO->EXTDR1 & (0x01ul << GPIO_CAL_PORT(GPIO_Pin))) {
            return SET;
        }
        else {
            return RESET;
        }
    }
}

void GPIO_WriteBit(GPIO_PinId_Type GPIO_Pin, uint8_t bit_val)
{
    if (!IS_VAILD_PIN(GPIO_Pin)) {
        return;
    }
    if (bit_val) {
        if (GPIO_Pin < 0x20) {
            GPIO->DR0 |= 0x01 << GPIO_Pin;
        }
        else {
            GPIO->DR1 |= 0x01 << GPIO_CAL_PORT(GPIO_Pin);
        }
    }
    else {
        if (GPIO_Pin < 0x20) {
            GPIO->DR0 &= ~(0x01 << GPIO_Pin);
        }
        else {
            GPIO->DR1 &= ~(0x01 << GPIO_CAL_PORT(GPIO_Pin));
        }
    }
}

FlagStatus GPIO_ReadIntBit(GPIO_PinId_Type GPIO_Pin)
{
    if (GPIO_Pin < 0x20) {
        if (GPIO->IS & (0x01 << GPIO_Pin)) {
            return SET;
        }
    }
    return RESET;
}

FlagStatus GPIO_ReadRawIntBit(GPIO_PinId_Type GPIO_Pin)
{
    if (GPIO_Pin < 0x20) {
        if (GPIO->RIS & (0x01 << GPIO_Pin)) {
            return SET;
        }
    }
    return RESET;
}

void GPIO_ClrIntBit(GPIO_PinId_Type GPIO_Pin)
{
    if (GPIO_Pin < 0x20) {
        GPIO->EOI |= 0x01 << GPIO_Pin;
    }
}

