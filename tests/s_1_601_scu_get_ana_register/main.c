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
    c_printf("s_1_601_scu_get_ana_register case \r\n");

    {
            c_printf("[%X]\n",SCU->ANA_CTL0);
			c_printf("[%X]\n",SCU->ANA_CTL1);
			c_printf("[%X]\n",SCU->ANA_CTL2);
			c_printf("[%X]\n",SCU->ANA_CTL3);
			c_printf("[%X]\n",SCU->ANA_CTL4);
//			c_printf("[%X]\n",SCU->ANA_STATUS0);
//			c_printf("[%X]\n",SCU->ANA_STATUS1);
    }

	MCU_Sleep(3);
    c_printf("s_1_601_scu_get_ana_register case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















