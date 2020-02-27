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
    c_printf("s_1_003_scu_scan_swd_pin case \r\n");

    {
        PADConfig_Type PAG_InitStru;
        SCU->CLK_EN = 0xffffffff;        
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        
        
//        for(uint16_t md = PAD_MODE3;md<PAD_MODE6;md++)
//        {
//            PAG_InitStru.pad_ctl    = md;
//            SystemPADConfig(PADID4,&PAG_InitStru);
//            SystemPADConfig(PADID5,&PAG_InitStru);
//            c_printf("SCU  App SWD MD:%d Switch  1\n",md);
//            c_printf("SCU  App SWD MD:%d Switch  2\n",md);
//            c_printf("SCU  App SWD MD:%d Switch  3\n",md);
//            MCU_Sleep(3);
//        }
        PAG_InitStru.pad_ctl    = PAD_MODE5;			//function5
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        c_printf("SCU  App SWD MD:%d Switch  1\n",PAD_MODE5);

        PAG_InitStru.pad_ctl    = 0;				//function0
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        c_printf("SCU  App SWD MD:%d Switch  1\n",0);
    }

	MCU_Sleep(5);
    c_printf("s_1_003_scu_scan_swd_pin case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















