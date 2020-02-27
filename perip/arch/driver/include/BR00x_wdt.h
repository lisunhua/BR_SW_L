/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_wdt.h
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

#ifndef __BT1051Axx_WDT_H__
#define __BT1051Axx_WDT_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "BR00x_config.h"
#include <stdint.h>
#include <stdbool.h>

typedef  enum
{
    WDT_2PCLK_CYCLES,
    WDT_4PCLK_CYCLES,
    WDT_8PCLK_CYCLES,
    WDT_16PCLK_CYCLES,
    WDT_32PCLK_CYCLES,
    WDT_64PCLK_CYCLES,
    WDT_128PCLK_CYCLES,
    WDT_256PCLK_CYCLES
}WDT_PclkCycles_Type;

typedef enum
{
    WDT_RESPONSE_RESET,
    WDT_RESPONSE_INTRTRUPT_RESET
}WDT_ResponseMode_Type;

typedef struct 
{
    WDT_PclkCycles_Type pclk_cycles;
    WDT_ResponseMode_Type response_mode;

    /*
    the value is a bit width of timeout ,
    exmaple  :
        tiemeout = 9: time= 9+15   ->
        time = 0x3ff<<15|0xffffff clock
    */
    uint32_t               timeout_period;                  /*!< This value can only be 1 to 15. */
    uint32_t               timeout_init_period;             /*!< This value can only be 1 to 15. */
    /* These bits exist only when the configuration 
    parameter WDT_DUAL_TOP = 1, otherwise, they are fixed at zero.*/
}WDT_InitInfo_Type;



/**
  * @brief  Deinitializes the WDT peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void WDT_DeInit(void);

/**
  * @brief  Initializes the WDT peripheral according to the specified
  *         parameters in the WDT_InitInfos_Type.
  * @param  WDT_InitStruct: pointer to a WDT_InitInfo_Type structure that
  *         contains the configuration information for the specified wdt peripheral.
  * @retval None
  */
void  WDT_Init(WDT_InitInfo_Type *WDT_InitStruct);

/**
  * @brief restart the wdt counter.
  * @param  WDT_InitStruct: pointer to a WDT_InitInfo_Type structure that
  *         contains the configuration information for the specified wdt peripheral.
  * @retval None
  */
void WDT_CountRestart(void);

/**
  * @brief Gets the value of the current counter .
  * @retval The value of the counter current
  */
uint32_t  WDT_CounterCurrentValue(void);

/**
  * @brief Gets the status of the wdt.
  * @retval The interrupt status for the wdt
  */
bool  wdt_InterruptActive(void);

/**
  * @brief Clear the interrupt status for the wdt .
  * @retval The value is useless
  */
uint32_t wdt_ClearInterrupt(void);

#ifdef __cplusplus
}
#endif

#endif /* __BT1051Axx_WDT_H__ */

