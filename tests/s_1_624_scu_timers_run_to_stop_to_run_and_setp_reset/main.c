/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file main.c
 * @brief Main program entry
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * @date    14. Augest 2019
 * @version V1.0.0
 * @author  MEIGER
*/

#include <stdio.h>
#include "BR00x_uart.h"
#include "BR00x_clock.h"
#include "BR00x_timers.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_624_scu_timers_run_to_stop_to_run_and_setp_reset case \r\n");

    {
        TIMER_InitInof_TypeDef TIMER_InitStru;
        TIMER_InitStru.TIMER_PwmValue       = 0;
        TIMER_InitStru.TIMER_LoadValue      = (3*(SystemCoreClock/1000));
        TIMER_InitStru.TIMER_InterruptMask  = TIMER_INTERRUPT_MASKED;
        TIMER_InitStru.TIMER_mode           = TIMER_USER_DEFINED;
        TIMER_InitStru.TIMER_Pwd            = TIMER_PWM_DISABLE;
        TIMER_InitStru.TIMER_sch            = TIMER_ENABLE;
        c_printf("Mode User\r\n");
        SystemDevClockCtl(TIMER_CKEn,true);
        for(TIMER_Num_Type tm = TM0; tm <= TM7; tm++)
        {
            TIMER_InitStru.TIMERx= tm;
            TIMER_Init(&TIMER_InitStru); 
            
            c_printf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            c_printf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
            c_printf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
            SCU->SW_RST |=0x01<<(21+tm);
            c_printf("Reset\r\n");
            c_printf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            c_printf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
            c_printf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
            c_printf("\r\n"); 
        }
    }

	MCU_Sleep(3);
    c_printf("s_1_624_scu_timers_run_to_stop_to_run_and_setp_reset case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















