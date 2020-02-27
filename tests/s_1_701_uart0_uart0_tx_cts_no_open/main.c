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
#include "BR00x_gpio.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"

#if defined(BR005)
GPIO_PinId_Type TestUartCstPin = GPIO_PIN_19;
#elif defined(BR003)
GPIO_PinId_Type TestUartCstPin = GPIO_PIN_26;
#endif

int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    Verrify_SendPinConnect(GPIO_UART0_EN);
    LOGUartInit();
    c_printf("s_1_701_uart0_uart0_tx_cts_no_open case \r\n");
    {
        GPIO_InitInfo_Type GPIO_InitStru;
        PADConfig_Type PAG_InitStru;

        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        PAG_InitStru.pad_ctl            = PAD_MODE0;       
        SystemPADConfig(TestUartCstPin,&PAG_InitStru);

        memset(&GPIO_InitStru,0,sizeof(GPIO_InitInfo_Type));

        GPIO_InitStru.dir           = GPOP_DIR_OUT;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;
        GPIO_InitStru.pin           = TestUartCstPin;

        SystemDevClockCtl(GPIO_CKEn,true);
        #ifdef BR005
        SystemDevClockCtl(UART0_SCKEn,true);
        #endif
        
        GPIO_Init(&GPIO_InitStru);
        
        GPIO_WriteBit(TestUartCstPin,0);
        c_printf("Start Auto Flow \r\n");
        MCU_Sleep(1);
        //Enable Uart Flow
        UART_AutoFlow(UART0,true);        
        GPIO_WriteBit(TestUartCstPin,1);   
        c_printf("Run Flow \r\n");    

    }
    c_printf("s_1_701_uart0_uart0_tx_cts_no_open case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}















