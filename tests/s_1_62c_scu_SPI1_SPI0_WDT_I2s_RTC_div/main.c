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
    uint32_t div=0;
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_62c_scu_SPI1_SPI0_WDT_I2s_RTC_div case \r\n");
    {

        SCU->CLK_EN = 0xffffffff;
        for(div=0;div<1000;div+=111)
        {
            SCU_SPI1Div(div);
            c_printf("SCU SPI1 DIV[%d]\n",div); 
        }

        for(div=0;div<1000;div+=111)
        {
            SCU_32KDiv(div);
            c_printf("SCU 32K DIV[%d]\n",div);
        }

        for(div=0;div<1000;div+=111)
        {
            SCU_WdtDiv(div);
            c_printf("SCU WDT DIV [%d]\n",div); 
        }

        for(div=0;div<1000;div+=111)
        {
            SCU_I2SDiv(div);
            c_printf("SCU I2S DIV[%d]\n",div);  
        }

        for(div=0;div<0x10000;div+=1111)
        {
            SCU_RTCDiv(div);
            c_printf("SCU RTC DIV[%d]\n",div);
        }
    }

	MCU_Sleep(3);
    c_printf("s_1_62c_scu_SPI1_SPI0_WDT_I2s_RTC_div case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}















