/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_rtc.h
 * @brief    This file provides all the rtc firmware functions.
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

#ifndef __BT1051Axx_RTC_H__
#define __BT1051Axx_RTC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "BR00x_config.h"



#define RTC_REG_CONFIG(X,Y,Z)    (Y) ? (X |= Z) : (X &= ~Z)
#define RTC_SET_LOAD_COUNTER_VALUE(X)         (RTC->CLR = X)
#define RTC_SET_INTERRUPT_MATCH_VALUE(X)      (RTC->CMR = X)

#define RTC_INTERRUPT_IS_MSAKED   (RTC->MIS&0X01)
#define RTC_RAW_INTERRUPT_STATUS   (RTC->RIS&0X01)


typedef enum
{
    RTC_INTERRUPT_DISABLE,
    RTC_INTERRUPT_ENABLE
}RTC_InterruptSwitch_Type;


typedef struct
{
    uint32_t RTC_StartValue;
    uint32_t RTC_InterruptValue;

    RTC_InterruptSwitch_Type  RTC_Interrpt;

}RTC_InitInfo_Type;


/**
  * @brief  Deinitializes the RTC peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void RTC_DeInit(void);

/**
  * @brief  Initializes the RTC peripheral according to the specified
  *         parameters in the RTC_InitInfo_Type.
  * @param  RTC_InitStruct: pointer to a RTC_InitInfo_Type structure that
  *         contains the configuration information for the specified rtc peripheral.
  * @retval None
  */
void RTC_Init(RTC_InitInfo_Type *RTC_InitStruct);


/**
  * @brief  Set the RTC  peripheral  start work .
  *
  * @param  status: If set to 1, the RTC is enabled. After the RTC is enabled, 
  *     do not write to this bit otherwise the current RTC value is reset to zero.
  * @retval None
  */
void RTC_Run(bool status);

/**
  * @brief  Get the current RTC value. .
  *
  * @retval 32-bit read data register. Reads from
  *  this register return the current value of the RTC
  */
uint32_t  RTC_CurrentValue(void);

/**
  * @brief  Set the RTC  peripheral interrupt enable.
  *
  * @param  status:  true : RTC initerrupt enable
  *                         flase : RTC interrupt disable
  * @retval None
  */
void RTC_InterruptMask(bool status);

/**
  * @brief  clearf the RTC  peripheral interrupt .
  *
  * @param  None
  * @retval None
  */
void  RTC_ClearInterrupt(void);




#ifdef __cplusplus
}
#endif

#endif /* __BT1051Axx_RTC_H__ */

