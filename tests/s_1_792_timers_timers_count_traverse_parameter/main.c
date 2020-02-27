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



#define     SEC(X)      (X*SystemCoreClock)
#define     MSEC(X)     (X*SystemCoreClock/1000)
#define     USEC(X)     (X*SystemCoreClock/1000000)

static uint8_t  timer_Int=0;

int main (void)
{
    // LOG UART INIT
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_792_timers_timers_count_traverse_parameter case \r\n");
    {
        TIMER_InitInof_TypeDef TIMER_InitStru;
        TIMER_InitStru.TIMER_PwmValue = 0;
        TIMER_InitStru.TIMER_LoadValue= MSEC(10);
        TIMER_InitStru.TIMER_InterruptMask= TIMER_INTERRUPT_UNMASKED;
        TIMER_InitStru.TIMER_mode= TIMER_USER_DEFINED;
        TIMER_InitStru.TIMER_Pwd= TIMER_PWM_DISABLE;
        TIMER_InitStru.TIMER_sch= TIMER_ENABLE;
        c_printf("Mode User\r\n");
        
        SystemDevClockCtl(TIMER_CKEn,true); 
        
        for(TIMER_Num_Type tm = TM0; tm <= TM7; tm++)
        {
            TIMER_InitStru.TIMERx= tm;
            for(uint32_t i=3;i<6;i++)
            {
                TIMER_InitStru.TIMER_LoadValue= MSEC(i);
                timer_Int=0;
                NVIC_ClearPendingIRQ((IRQn_Type)(TIMER1_IRQn+tm));
                NVIC_EnableIRQ((IRQn_Type)(TIMER0_IRQn+tm));
                TIMER_Init(&TIMER_InitStru);
                c_printf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
                while(timer_Int<3);//There may be a problem
                TIMER_Stop(tm,false);
                NVIC_DisableIRQ((IRQn_Type)(TIMER0_IRQn+tm));
               
            }
        }
        
        
        c_printf("Mode Free\r\n");
        TIMER_InitStru.TIMER_mode= TIMER_FREE_RUNNING;
        for(TIMER_Num_Type tm = TM0; tm <= TM7; tm++)
        {
            TIMER_InitStru.TIMERx= tm;
            uint32_t tme= MSEC(3);
            TIMER_InitStru.TIMER_LoadValue= tme;
            timer_Int=0;
            NVIC_ClearPendingIRQ((IRQn_Type)(TIMER1_IRQn+tm));
            NVIC_EnableIRQ((IRQn_Type)(TIMER0_IRQn+tm));
            TIMER_Init(&TIMER_InitStru);
            c_printf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            
            while(!timer_Int);//There may be a problem
            c_printf("stop\r\n");
            TIMER_Stop(tm,false);
            c_printf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            c_printf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            c_printf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            TIMER_Stop(tm,true);
            c_printf("Run\r\n");
            c_printf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            c_printf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            c_printf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            
            
            
            TIMER_Stop(tm,false);
            NVIC_DisableIRQ((IRQn_Type)(TIMER0_IRQn+tm));

        }

    }
    c_printf("s_1_792_timers_timers_count_traverse_parameter case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}



void TIMER0_IRQHandler(void)    
{     
    c_printf("TIMER0_IRQ \r\n"); 
    TIMER_ClearInterrupt(TM0);   
    TIMER_ClearAllInterrupt();
    timer_Int++;

}  
void TIMER1_IRQHandler(void)    
{     
    TIMER_ClearInterrupt(TM1);
    c_printf("TIMER1_IRQ\r\n");
    timer_Int++;    
}  
void TIMER2_IRQHandler(void)    
{     
    TIMER_ClearInterrupt(TM2);
    c_printf("TIMER2_IRQ\r\n"); 
    timer_Int++;
}  
void TIMER3_IRQHandler(void)    
{     
    TIMER_ClearInterrupt(TM3);
    c_printf("TIMER3_IRQ\r\n"); 
    timer_Int++;
}  
void TIMER4_IRQHandler(void)    
{   
    TIMER_ClearInterrupt(TM4);
    c_printf("TIMER4_IRQ\r\n"); 
    timer_Int++;
}  
void TIMER5_IRQHandler(void)    
{     
    TIMER_ClearInterrupt(TM5);
    c_printf("TIMER5_IRQ\r\n"); 
    timer_Int++;
}  
void TIMER6_IRQHandler(void)    
{     
    TIMER_ClearInterrupt(TM6);
    c_printf("TIMER6_IRQ\r\n"); 
    timer_Int++;
}  
void TIMER7_IRQHandler(void)    
{     
    c_printf("TIMER7_IRQ\r\n"); 

    TIMER_ClearInterrupt(TM7);
    TIMER_ClearAllInterrupt(); 
    timer_Int++;    
}
















