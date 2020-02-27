/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_wdt.c
 * @brief    This file provides all the wdt firmware functions.
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
#include "BR00x_wdt.h"
#include "BR00x_wdt_if.h"
#include "system_BR00x.h"
#include <stdint.h>


#define WDT_RESTAET_DATA      0x76


/**
  * @brief  Deinitializes the WDT peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void WDT_DeInit(void)
{
  #if  defined(BR002)||defined(BR003)
    SystemDevRstCtl(WDT_SwRst);
  #endif  

  #if  defined(BR005)
    SystemDevRstCtl(RTC_PCLK_SwRst);
  #endif 
}

/**
  * @brief  Initializes the WDT peripheral according to the specified
  *         parameters in the WDT_InitInfos_Type.
  * @param  WDT_InitStruct: pointer to a WDT_InitInfo_Type structure that
  *         contains the configuration information for the specified wdt peripheral.
  * @retval None
  */
void  WDT_Init(WDT_InitInfo_Type *WDT_InitStruct)
{
    if(WDT_InitStruct->timeout_init_period>15)
    WDT_InitStruct->timeout_init_period = 15;

    if(WDT_InitStruct->timeout_period>15)
    WDT_InitStruct->timeout_period= 15;

    WDT->CR   &= ~BR_WDT_WDT_CR_WDT_EN_Msk;

    WDT->TORR &= ~(BR_WDT_WDT_TORR_TOP_Msk|BR_WDT_WDT_TORR_TOP_INIT_Msk);
    WDT->TORR |= (WDT_InitStruct->timeout_period <<BR_WDT_WDT_TORR_TOP_Pos) |
        (WDT_InitStruct->timeout_init_period << BR_WDT_WDT_TORR_TOP_INIT_Pos) ; 

    WDT->CR &= ~(BR_WDT_WDT_CR_RPL_Msk|BR_WDT_WDT_CR_RMOD_Msk);
    WDT->CR   |= ((WDT_InitStruct->pclk_cycles << BR_WDT_WDT_CR_RPL_Pos) | 
        (WDT_InitStruct->response_mode<< BR_WDT_WDT_CR_RMOD_Pos));
    WDT->CR   |= BR_WDT_WDT_CR_WDT_EN_Msk;

    WDT_CountRestart();
}

/**
  * @brief restart the wdt counter.
  * @param  WDT_InitStruct: pointer to a WDT_InitInfo_Type structure that
  *         contains the configuration information for the specified wdt peripheral.
  * @retval None
  */
void WDT_CountRestart(void)
{
    WDT->CRR |= WDT_RESTAET_DATA;
}


/**
  * @brief Gets the value of the current counter .
  * @retval The value of the counter current
  */
uint32_t  WDT_CounterCurrentValue(void)
{
    return WDT->CCVR;
}


/**
  * @brief Gets the status of the wdt.
  * @retval The interrupt status for the wdt
  */
bool  wdt_InterruptActive(void)
{
    return ((bool)(WDT->STAT & 0x01));
}

/**
  * @brief Clear the interrupt status for the wdt .
  * @retval The value is useless
  */
uint32_t wdt_ClearInterrupt(void)
{
    return (WDT->EIO);
}



