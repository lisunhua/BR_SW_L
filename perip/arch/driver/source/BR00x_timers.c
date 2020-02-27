/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_timers.c
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
#include "BR00x_timers.h"
#include "system_BR00x.h"

static TIMER_TypeDef  * time_GetTimeAddr(TIMER_Num_Type TIMERx);
static void time_PwmTimeCount(TIMER_Num_Type TIMERx,uint32_t  TIMER_PwmValue);

#define TIMER_RAW_ALL_INTERRUPT_STATUS    TIMERS->RAW_INT_STATUS


/**
  * @brief  The function gets the address of the timer specified.
  * @param  TIMERx: pointer to a time.
  * @retval  the address of the timer specified.
  */
static TIMER_TypeDef  * time_GetTimeAddr(TIMER_Num_Type TIMERx)
{
    return &TIMERS->TIMER[TIMERx];
}


/**
  * @brief  The function sets timer_N_toggle output changes  of the timer specified.
  * @param  TIMERx: pointer to a time.
  * @param  TIMER_PwmValue: Value to be loaded into TimerN when timer_N_toggle output
  *      changes from 0 to 1. This value determines the width of the
  *      HIGH period of the timer_N_toggle output.
  * @retval  the address of the timer specified.
  */
static void time_PwmTimeCount(TIMER_Num_Type TIMERx,uint32_t  TIMER_PwmValue)
{
    switch(TIMERx)
    {
        case TM0: TIMERS->TIMER1_LOAD_COUNT2 = TIMER_PwmValue; break;
        case TM1: TIMERS->TIMER2_LOAD_COUNT2 = TIMER_PwmValue; break;
        case TM2: TIMERS->TIMER3_LOAD_COUNT2 = TIMER_PwmValue; break;
        case TM3: TIMERS->TIMER4_LOAD_COUNT2 = TIMER_PwmValue; break;
        case TM4: TIMERS->TIMER5_LOAD_COUNT2 = TIMER_PwmValue; break;
        case TM5: TIMERS->TIMER6_LOAD_COUNT2 = TIMER_PwmValue; break;
        case TM6: TIMERS->TIMER7_LOAD_COUNT2 = TIMER_PwmValue; break;
        case TM7: TIMERS->TIMER8_LOAD_COUNT2 = TIMER_PwmValue; break;
    }
}



/**
  * @brief  Deinitializes the TIMERS peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void TIMER_DeInit(void)
{
#if  defined(BR002)||defined(BR003)
    SystemDevRstCtl(TIMERS_SwRst);
#endif
    memset(TIMERS,0,sizeof(TIMERS_TypeDef));
}


/**
  * @brief  Initializes the time  peripheral according to the specified
  *         parameters in the TIMER_InitInof_TypeDef_t.
  * @param  TIMER_InitStaru: pointer to a TIMER_InitInof_TypeDef structure that
  *         contains the configuration information for the specified time  peripheral.
  * @retval None
  */
bool TIMER_Init(TIMER_InitInof_TypeDef  *TIMER_InitStaru)
{
    TIMER_TypeDef  * times_t = time_GetTimeAddr(TIMER_InitStaru->TIMERx);
    times_t->CONTROL_REG = 0;     
    times_t->LOAD_COUNT = TIMER_InitStaru->TIMER_LoadValue;
    time_PwmTimeCount(TIMER_InitStaru->TIMERx,TIMER_InitStaru->TIMER_PwmValue);
    times_t->CONTROL_REG =((TIMER_InitStaru->TIMER_Pwd <<TIMER_CTLR_PWM_Pos)  | 
                                 (TIMER_InitStaru->TIMER_InterruptMask <<TIMER_CTLR_INTMASK_Pos) |\
                                 (TIMER_InitStaru->TIMER_mode << TIMER_CTLR_MODE_Pos)|\
                                 (TIMER_InitStaru->TIMER_sch << TIMER_CTLR_ENABLE_Pos));
    return true;
}



void TIMER_Stop(TIMER_Num_Type TIMERx,bool stu)
{
    TIMER_TypeDef  * times_t = time_GetTimeAddr(TIMERx);

    if(stu)
        times_t->CONTROL_REG |=0x01;
    else
        times_t->CONTROL_REG &=~0x01;
}

void TIMER_Updata(TIMER_Num_Type TIMERx,uint32_t val)
{
    TIMER_TypeDef  * times_t = time_GetTimeAddr(TIMERx);
    times_t->LOAD_COUNT = val;
}

/**
  * @brief  Gets the current counter of the specified timer.
  *
  * @param  TIMERx: pointer to a TIMERx.
  *
  * @retval the valuei s current counter of the specified timer
  */
uint32_t TIMER_GetTimeCurrentValue(TIMER_Num_Type TIMERx)
{
    TIMER_TypeDef  * times_t = time_GetTimeAddr(TIMERx);

    return times_t->CURRENT_COUNT;
}


/**
  * @brief  clear  the specified timer interrupt.Reading this bit returns all zeroes (0) 
  *            and clears all active interrupts.
  *
  * @param  TIMERx: pointer to a TIMERx.
  *
  * @retval returns all zeroes (0).
  */
uint32_t TIMER_ClearInterrupt(TIMER_Num_Type TIMERx)
{
    TIMER_TypeDef  * times_t = time_GetTimeAddr(TIMERx);
    return times_t->EOI;
}

/**
  * @brief  Get  the specified timer interrupt.
  *
  * @param  TIMERx: pointer to a TIMERx.
  * @retval The status of interrupts.
  */
uint32_t TIMERx_InterruptStatus(TIMER_Num_Type TIMERx)
{
    TIMER_TypeDef  * times_t = time_GetTimeAddr(TIMERx);
    return times_t->INTSTATUS;
}


uint32_t TIMER_GetInterruptAllStatus(void)
{
    return (TIMERS->INT_STATUS);
}

/**
  * @brief  Contains the interrupt status for TimerN.
  *
  * @param  TIMERx: pointer to a TIMERx.
  *
  * @retval  interrupt status for TimerN, It's only 0 bit effective.
  */
uint32_t TIMER_GetInterruptStatus(TIMER_Num_Type TIMERx)
{
    return ((TIMERS->INT_STATUS >> TIMERx) & 0x01);
}

/**
  * @brief  Contains the raw interrupt status for TimerN.
  *
  * @param  TIMERx: pointer to a TIMERx.
  *
  * @retval  raw interrupt status for TimerN, It's only 0 bit effective.
  */
uint32_t TIMER_GetRawInterruptStatus(TIMER_Num_Type TIMERx)
{
    return ((TIMERS->RAW_INT_STATUS >> TIMERx) & 0x01);
}



/**
  * @brief  clear  the specified timer interrupt.Reading this bit returns all zeroes (0) 
  *            and clears all active interrupts.
  *
  * @param  TIMERx: pointer to a TIMERx.
  *
  * @retval  all zeroes (0).
  */
uint32_t  TIMER_ClearAllInterrupt(void)
{
    return (TIMERS->EOI);
}





