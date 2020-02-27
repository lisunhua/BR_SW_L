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
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_62d_scu_timers_div case \r\n");
    {
        uint32_t div=0;
        SystemDevClockCtl(TIMER_CKEn ,true);
        SystemDevClockCtl(TIMER0_CKEn,true);
        SystemDevClockCtl(TIMER1_CKEn,true);
        SystemDevClockCtl(TIMER2_CKEn,true);
        SystemDevClockCtl(TIMER3_CKEn,true);
        SystemDevClockCtl(TIMER4_CKEn,true);
        SystemDevClockCtl(TIMER5_CKEn,true);
        SystemDevClockCtl(TIMER6_CKEn,true);
        SystemDevClockCtl(TIMER7_CKEn,true);

        for(SCU_Timers_Type tm = CLK_TM0;tm<=CLK_TM7;tm++)
        {
            for(div=0;div<10000;div+=1111)
            {
                SCU_TimersDiv(tm,div);
                c_printf("SCU TM[%d], div[%d]\n",tm,div); 
            }
        }
    }
	MCU_Sleep(3);
    c_printf("s_1_62d_scu_timers_div case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}















