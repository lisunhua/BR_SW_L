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
    // LOG UART INIT
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    {
        uint32_t adr =  0x2000;
        volatile uint32_t *addr = (uint32_t *)adr;
        uint16_t  ram_ksize = 384;
        uint32_t val = 0;
        
        c_printf("Check ROM:0x[%X]-128K*3\n",adr); 
        c_printf("Set ROM\n");
        for(uint32_t i=0;i<((ram_ksize<<8)-(adr/4));i++)
        {
            *addr = i;
            addr++;
        }
        c_printf("Get ROM\n");
        addr = (uint32_t *)adr;
        for(uint32_t i=0;i<((ram_ksize<<8)-(adr/4));i++)
        {
            val = *addr;
            addr++;
            if(val !=i)
            {
                c_printf("ROM:Error![%X],[%p],[%X]\n",i,addr,*addr);
                break;
            }
        }
        c_printf("ROM:Completed!\n");
    }
	MCU_Sleep(3);
    SimulationEnd();

    while(1){     
    };
}
















