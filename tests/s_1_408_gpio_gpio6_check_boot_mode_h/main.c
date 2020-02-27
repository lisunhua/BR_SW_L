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

#ifdef BR005 
#define  TEST_GPIO_END  PADID20
#elif  defined(BR003)
#define  TEST_GPIO_END  PADID28
#endif

int main (void)
{
    // LOG UART INIT
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_408_gpio_gpio6_check_boot_mode_h case \r\n");
    MCU_Sleep(1);
    {
        GPIO_InitInfo_Type GPIO_InitStru;    
        PADConfig_Type      PAG_InitStru;

        memset(&GPIO_InitStru,0,sizeof(GPIO_InitInfo_Type));
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        PAG_InitStru.pad_ctl        = PAD_MODE0;
        SystemPADConfig(PADID6,&PAG_InitStru);

        GPIO_InitStru.dir           = GPOP_DIR_IN;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;
        SystemDevClockCtl(GPIO_CKEn,true);
        SystemDevClockCtl(IFCLK_GPIO_CKEn,true);
        GPIO_Init(&GPIO_InitStru);

        GPIO_WriteBit(GPIO_PIN_6,1);


        MCU_Sleep(1);

        if(GPIO_ReadBit(GPIO_PIN_6) == SET){
            c_printf("BOOT GPIO6 Check is True,Need Into Boot Mode \r\n");
        }else
            c_printf("BOOT GPIO6 Check is False, Not Need Into Boot Mode \r\n");

    }
    c_printf("s_1_408_gpio_gpio6_check_boot_mode_h case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}
















