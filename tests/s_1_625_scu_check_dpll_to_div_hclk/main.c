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
    c_printf("s_1_625_scu_check_dpll_to_div_hclk case \r\n");
    c_printf("SCU  App Case29 HCLK Sel DIV\n");
    {

        SCU_HClkSelect(CLK_HCLK_MUX);
        MCU_Sleep(2);
        
        for(SCU_96MDIVCtl_Type clk = CLK_12M ;clk<=CLK_96M;clk++)
        {
            SCU_ClockSelectDivControl(clk);
            c_printf("SCU_ClockSelectDivControl=[%d]\n",clk);
            MCU_Sleep(2);
        }
        MCU_Sleep(2);
        c_printf("SCU HCLK Sel DIV Completed !!\n");


    }

	MCU_Sleep(3);
    c_printf("s_1_625_scu_check_dpll_to_div_hclk case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















