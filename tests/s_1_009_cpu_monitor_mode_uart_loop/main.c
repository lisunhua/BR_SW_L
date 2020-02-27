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





int main (void)
{
    // LOG UART INIT
	sysTimeUpdataClk(SystemCoreClock);
	Verrify_SendPinConnect(UART0_OUTPUT);
	LOGUartInit();

	//Enable UART0 Interruot
	//UART_InterruptSet(UART0,0x01ul);
	//NVIC_ClearPendingIRQ(UART0_IRQn);
	//NVIC_EnableIRQ(UART0_IRQn);

	Verrify_SendPinConnect(TMODE_0);
	Verrify_SendPinConnect(TMODE_DIS);
	Verrify_SendPinConnect(TMODE_EN);
	{
		c_printf("start...\r\n");
	}
  
	MCU_Sleep(20);
	SimulationEnd();
	while(1){     
	};
}


#if 0

void UART0_IRQHandler(void)
{ 
    if (UART_LSRCheckBits(UART0, UART_LSR_BIT_DR)) 
    {
        uint8_t data = UART_ReadByte(UART0);
        UART_WriteData(UART0,&data,1);
    }
    if(UART_GetInterruptID(UART0) == BUSY_DETECT)  
    {
        UART_GetStatus(UART0);
    } 
}

#endif







