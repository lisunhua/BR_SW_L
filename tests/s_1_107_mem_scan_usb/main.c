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
        volatile uint32_t *addr = (uint32_t *)USB_DFIFODEBUG;
        //uint8_t  ram_32bit      = 128;
        uint16_t  ram_32bit      = 1024;
        uint32_t val            = 0;

        SystemDevClockCtl(USB_HCKEn,true);
        SystemDevClockCtl(USB_XCKEn,true);

        c_printf("Check USB RAM:[0x%X]\n",USB_DFIFODEBUG); 
        c_printf("Set USB RAM\n");

        for(uint32_t i=0;i<ram_32bit;i++)
        {
                *addr = i;
                addr++;
        }

        c_printf("Get USB RAM\n");
        addr = (uint32_t *)USB_DFIFODEBUG;
        for(uint32_t i=0;i<ram_32bit;i++)
        {
            val = *addr;
            addr++;
            if(val !=i)
            {
                c_printf("USB RAM:Error!\n");
                break;
            }
        }
        c_printf("USB RAM:Completed!\n");
    }
	MCU_Sleep(3);
    SimulationEnd();

    while(1){     
    };
}
















