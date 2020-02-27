/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_rtc.c
 * @brief    This file provides the rtc firmware functions.
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
 * @author  MEIGER
*/
#include <stdbool.h>
#include "BR00x_rtc.h"
#include "system_BR00x.h"


void RTC_DeInit(void)
{
  #if  defined(BR002)||defined(BR003)
    SystemDevRstCtl(RTC_SwRst);
  #endif 

  #if  defined(BR005)
    SystemDevRstCtl(RTC_PCLK_SwRst);
  #endif

    memset(RTC, 0, sizeof(DMA_TypeDef));
}



/**
  * @brief  Initializes the RTC peripheral according to the specified
  *         parameters in the RTC_InitInfo_Type.
  * @param  RTC_InitStruct: pointer to a RTC_InitInfo_Type structure that
  *         contains the configuration information for the specified rtc peripheral.
  * @retval None
  */
void RTC_Init(RTC_InitInfo_Type *RTC_InitStruct)
{
    RTC_Run(false);
    
    RTC_SET_LOAD_COUNTER_VALUE(RTC_InitStruct->RTC_StartValue);
    RTC_SET_INTERRUPT_MATCH_VALUE(RTC_InitStruct->RTC_InterruptValue);

    if(RTC_InitStruct->RTC_Interrpt)
        RTC_InterruptMask(true);
    else
        RTC_InterruptMask(false);
    
    RTC_Run(true);
       
}


/**
  * @brief  Get the current RTC value. .
  *
  * @retval 32-bit read data register. Reads from
  *  this register return the current value of the RTC
  */
uint32_t  RTC_CurrentValue(void)
{
    return RTC->DR;
}


/**
  * @brief  Set the RTC  peripheral  start work .
  *
  * @param  status: If set to 1, the RTC is enabled. After the RTC is enabled, 
  *     do not write to this bit otherwise the current RTC value is reset to zero.
  * @retval None
  */


void RTC_Run(bool status)
{
    RTC->CCR  = status;
}

/**
  * @brief  Set the RTC  peripheral interrupt enable.
  *
  * @param  status:  true : RTC initerrupt enable
  *                         flase : RTC interrupt disable
  * @retval None
  */
void RTC_InterruptMask(bool status)
{
     RTC->IMSC  = status;
}


/**
  * @brief  clearf the RTC  peripheral interrupt .
  *
  * @param  None
  * @retval None
  */
void  RTC_ClearInterrupt(void)
{
    RTC->ICR = 0x01;
}





