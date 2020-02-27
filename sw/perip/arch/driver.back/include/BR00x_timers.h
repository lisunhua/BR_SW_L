/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_times.h
 * @brief    This file provides all the times firmware functions.
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

#ifndef __BT1051Axx_TIMERS_H__
#define __BT1051Axx_TIMERS_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "BR00x_config.h"


 /*!< Position of TIMER_0N100PWM_EN field. */
#define TIMER_CTLR_TIMER_0N100PWM_EN_Pos (4ul)  
/*!< Bit mask of TIMER_0N100PWM_EN field. */ 
#define TIMER_CTLR_TIMER_0N100PWM_EN_Msk (0x01ul << TIMER_CTLR_TIMER_0N100PWM_EN_Pos) 

 /*!< Position of CTLR_PWM field. */
#define TIMER_CTLR_PWM_Pos (3ul)
/*!< Bit mask of CTLR_PWM field. */ 
#define TIMER_CTLR_PWM_Msk (0x01ul << TIMER_CTLR_PWM_Pos) 

/*!< Position of CTLR_INTMASK field. */
#define TIMER_CTLR_INTMASK_Pos (2ul)
 /*!< Bit mask of CTLR_INTMASK field. */ 
#define TIMER_CTLR_INTMASK_Msk (0x01ul << TIMER_CTLR_INTMASK_Pos)

 /*!< Position of CTLR_MODE field. */
#define TIMER_CTLR_MODE_Pos (1ul)
 /*!< Bit mask of CTLR_MODE field. */ 
#define TIMER_CTLR_MODE_Msk (0x01ul << TIMER_CTLR_MODE_Pos)

 /*!< Position of CTLR_ENABLE_ field. */
#define TIMER_CTLR_ENABLE_Pos (0ul) 
/*!< Bit mask of CTLR_ENABLE_ field. */ 
#define TIMER_CTLR_ENABLE__Msk (0x01ul << TIMER_CTLR_ENABLE_Pos) 



typedef enum
{   
    TM0,
    TM1,
    TM2,
    TM3,
    TM4,
    TM5,
    TM6,
    TM7
}TIMER_Num_Type;


typedef enum
{
    TIMER_PWM_DISABLE,
    TIMER_PWM_ENABLE
}TIMER_Pwm_Type;

typedef enum
{
    TIMER_INTERRUPT_UNMASKED,
    TIMER_INTERRUPT_MASKED
}TIMER_InterruptMask_Type;

typedef enum
{
    TIMER_FREE_RUNNING,
    TIMER_USER_DEFINED
}TIMER_Mode_Type;



typedef enum
{
    TIMER_DISABLE,
    TIMER_ENABLE
}TIMER_Sch_Type;



typedef struct
{
    TIMER_Num_Type  TIMERx;
    uint32_t        TIMER_PwmValue;
    uint32_t        TIMER_LoadValue;

    TIMER_Pwm_Type              TIMER_Pwd;
    TIMER_InterruptMask_Type    TIMER_InterruptMask;
    TIMER_Mode_Type             TIMER_mode;
    TIMER_Sch_Type              TIMER_sch;
    
}TIMER_InitInof_TypeDef;


/**
  * @brief  Deinitializes the TIMERS peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void TIMER_DeInit(void);
/**
  * @brief  Initializes the time  peripheral according to the specified
  *         parameters in the TIMER_InitInof_TypeDef_t.
  * @param  TIMER_InitStaru: pointer to a TIMER_InitInof_TypeDef structure that
  *         contains the configuration information for the specified time  peripheral.
  * @retval None
  */
bool TIMER_Init(TIMER_InitInof_TypeDef *TIMER_InitStaru);


/**
  * @brief  Run Control of the specified timer.
  *
  * @param  TIMERx: A Timer serial number.
  *
  * @retval None
  */
void TIMER_Stop(TIMER_Num_Type TIMERx,bool stu);


/**
  * @brief  Updata of the specified timer.
  *
  * @param  TIMERx: A Timer serial number.
  * @param  val: Updata data
  * @retval None
  */
void TIMER_Updata(TIMER_Num_Type TIMERx,uint32_t val);
/**
  * @brief  Gets the current counter of the specified timer.
  *
  * @param  TIMERx:  A Timer serial number.
  *
  * @retval the valuei s current counter of the specified timer
  */
uint32_t TIMER_GetTimeCurrentValue(TIMER_Num_Type TIMERx);

/**
  * @brief  clear  Reading from this register returns all zeroes (0) and clears the interrupt from .
  *
  * @param  TIMERx:  A Timer serial number.
  *
  * @retval  zeroes (0).
  */
uint32_t TIMER_ClearInterrupt(TIMER_Num_Type TIMERx);

/**
  * @brief  Get  the specified timer interrupt of the specified timer.
  *
  * @param  TIMERx: A Timer serial number.
  * @retval The status of interrupt.
  */
uint32_t TIMERx_InterruptStatus(TIMER_Num_Type TIMERx);


/**
  * @brief  Get  the specified timer interrupt of the specified timers.
  *  Contains the interrupt status of all timers in the component. If a bit of
  * this register is 0, then the corresponding timer interrupt is not active C
  * and the corresponding interrupt could be on either the timer_intr bus or
  * the timer_intr_n bus, depending on the interrupt polarity you have
  * chosen. Similarly, if a bit of this register is 1, then the corresponding
  * interrupt bit has been set in the relevant interrupt bus. In both cases, the
  * status reported is the status after the interrupt mask has been applied.
  * Reading from this register does not clear any active interrupts:
  *             0 C either timer_intr or timer_intr_n is not active after masking
  *             1 C either timer_intr or timer_intr_n is active after masking
  *
  * @retval The State of all timers interrupts.
  */
uint32_t TIMER_GetInterruptAllStatus(void);


/**
  * @brief  clear  the specified timer interrupt.Reading this bit returns all zeroes (0) 
  *            and clears all active interrupts.
  *
  * @retval  all zeroes (0).
  */
uint32_t  TIMER_ClearAllInterrupt(void);

/**
  * @brief  Contains the interrupt status for TimerN.
  *
  * @param  TIMERx:  A Timer serial number.
  *
  * @retval  interrupt status for TimerN, It's only 0 bit effective.
  */
uint32_t TIMER_GetInterruptStatus(TIMER_Num_Type TIMERx);


/**
  * @brief  Contains the raw interrupt status for TimerN.
  *
  * @param  TIMERx:  A Timer serial number.
  *
  * @retval  raw interrupt status for TimerN, It's only 0 bit effective.
  */
uint32_t TIMER_GetRawInterruptStatus(TIMER_Num_Type TIMERx);


#ifdef __cplusplus
}
#endif

#endif /* __BT1051Axx_TIMERS_H__ */

