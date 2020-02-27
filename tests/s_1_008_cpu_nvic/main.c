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
#include "BR00x_timers.h"
#include "BR00x_rtc.h"

#include "verify_message.h"
#include "log_uart_config.h"

extern unsigned long int SystemCoreClock;
#define SEC(x)      	(x*SystemCoreClock)
#define MEC(x)      	(x*(SystemCoreClock/1000))
#define LMEC(x)     	(x*(32000UL/1000))


void  AppRtcInit(void)
{
	RTC_InitInfo_Type RTC_InitStru;

	memset(&RTC_InitStru, 0 ,sizeof(RTC_InitInfo_Type));
	c_printf("H Clock RTC\r\n");
	RTC_InitStru.RTC_Interrpt 			= RTC_INTERRUPT_ENABLE ;
	RTC_InitStru.RTC_InterruptValue   	= MEC(1);
	RTC_InitStru.RTC_StartValue  		= 0;
	SystemDevClockCtl(RTC_CKEn,true);
	
	RTC_Init(&RTC_InitStru);
	NVIC_SetPriority (RTC_IRQn,1); 
	NVIC_EnableIRQ(RTC_IRQn);

}


void AppTimerInit(void)
{

	TIMER_InitInof_TypeDef TIMER_InitStru;
	memset(&TIMER_InitStru, 0 ,sizeof(TIMER_InitInof_TypeDef));
	
	TIMER_InitStru.TIMERx				= TM0;
	TIMER_InitStru.TIMER_PwmValue 		= 0;
	TIMER_InitStru.TIMER_LoadValue		= MEC(5);
	TIMER_InitStru.TIMER_InterruptMask 	= TIMER_INTERRUPT_UNMASKED;
	TIMER_InitStru.TIMER_mode			= TIMER_USER_DEFINED;
	TIMER_InitStru.TIMER_Pwd 			= TIMER_PWM_DISABLE;
	TIMER_InitStru.TIMER_sch			= TIMER_ENABLE;

	SystemDevClockCtl(TIMER_CKEn,true);
	SystemDevClockCtl(TIMER0_CKEn,true);

	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_SetPriority (TIMER0_IRQn,4); 
	NVIC_EnableIRQ(TIMER0_IRQn);
	TIMER_Init(&TIMER_InitStru);
}



static uint8_t  Tm_IntCount = 0;

int main (void)
{
    // LOG UART INIT
	sysTimeUpdataClk(SystemCoreClock);
	Verrify_SendPinConnect(UART0_OUTPUT);

	__disable_irq();

	LOGUartInit();
	c_printf("Start!!! \r\n");
    NVIC_SetPriorityGrouping(6);

	NVIC->IP[0] = 0xFF ;
	NVIC->IP[1] = 0xFF ;
	NVIC->IP[2] = 0xFF ;
	c_printf("NVIC_IP[%X]\n", NVIC->IP[0]);
	c_printf("NVIC_IP[%X]\n", NVIC->IP[1]);
	c_printf("NVIC_IP[%X]\n", NVIC->IP[2]);

    NVIC_SetPriority (SysTick_IRQn,0);  
    c_printf("NVIC_GP[%X]\n", NVIC_GetPriorityGrouping());



	c_printf("NVIC_sys[%X]\n", NVIC_GetPriority(SysTick_IRQn));
	c_printf("NVIC_rtc[%X]\n", NVIC_GetPriority(RTC_IRQn));
	c_printf("NVIC_tim[%X]\n", NVIC_GetPriority(TIMER0_IRQn));

    AppRtcInit();
    AppTimerInit();
    
	for(uint32_t i =0 ;i<3000 * 5 ;i++){};
	c_printf(" en int!!! \r\n");
    __enable_irq();

	while(Tm_IntCount < 5){

	};

	SimulationEnd();
	while(1){     
	};
}




void RTC_IRQHandler(void)       
{     
	RTC_ClearInterrupt();
	RTC_SET_LOAD_COUNTER_VALUE(0);
	c_printf("RTC_IRQ\r\n");
}  





void TIMER0_IRQHandler(void)    
{     
    TIMER_ClearInterrupt(TM0);   
    TIMER_ClearAllInterrupt();
    c_printf("TIMER0_IRQ into \r\n"); 
    MCU_Sleep(3);
    Tm_IntCount++;
    c_printf("TIMER0_IRQ out\r\n"); 
}








