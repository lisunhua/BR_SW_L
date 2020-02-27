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
    c_printf("s_1_304_scu_sacn_padcfg case \r\n");
    {
        PADConfig_Type      PAG_InitStru;
        for(int8_t set = 0;set<=1;set++)
        {
            PAG_InitStru.set =set;
            for(PAD_CTL_IE_type ie = PAD_IE_DISABLE;ie<=PAD_IE_ENABLE;ie++)
            {
                PAG_InitStru.ie =ie;       
                for(PAD_CTL_OEN_type oen = PAD_OEN_ENABLE; oen<=PAD_OEN_DISABLE;oen++)
                {
                    PAG_InitStru.oen =oen;
                    for(PAD_CTL_REN_type ren = PAD_REN_ENABLE;ren<=PAD_REN_DISABLE;ren++)
                    {
                        PAG_InitStru.ren=ren;
                        for(PAD_CTL_MODE_type mode = PAD_MODE0;mode<= PAD_MODE7;mode++)
                        {
                            PAG_InitStru.pad_ctl    = mode;
                            for(PADId_Type pad = PADID0; pad<PADID33;pad++)
                                SystemPADConfig(pad,&PAG_InitStru);
                        } 
                    }
                }
            }
        }

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE0;
        SystemPADConfig(PADID0,&PAG_InitStru);        
        c_printf("SCU IO MUX complete\n");


    }

	MCU_Sleep(3);
    c_printf("s_1_304_scu_sacn_padcfg case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}















