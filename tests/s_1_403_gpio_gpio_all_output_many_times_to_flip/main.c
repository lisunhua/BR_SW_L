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
    c_printf("s_1_403_gpio_gpio_all_output_many_times_to_flip case \r\n");
    MCU_Sleep(1);
    {
        GPIO_InitInfo_Type  GPIO_InitStru;
        PADConfig_Type      PAG_InitStru;

        memset(&GPIO_InitStru,0,sizeof(GPIO_InitInfo_Type));
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));

        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
       
        for (PADId_Type pin = PADID0;pin <= PADID5 ;pin++ )
            SystemPADConfig(pin,&PAG_InitStru);
        
        PAG_InitStru.pad_ctl    = PAD_MODE0;
        for (PADId_Type pin = PADID6;pin <= TEST_GPIO_END ;pin++ )
            SystemPADConfig(pin,&PAG_InitStru);
        
        GPIO_InitStru.dir           = GPOP_DIR_OUT;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;
        SystemDevClockCtl(GPIO_CKEn,true);
        SystemDevClockCtl(IFCLK_GPIO_CKEn,true);
        for(GPIO_PinId_Type pin = GPIO_PIN_0;pin <GPIO_PIN_32;pin++)
        {
            GPIO_InitStru.pin = pin;
            GPIO_Init(&GPIO_InitStru);
            GPIO_WriteBit(pin,1);
            MCU_Sleep(1);
            GPIO_WriteBit(pin,0);

        }       
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));  
        SystemPADConfig(PADID0,&PAG_InitStru);
        SystemPADConfig(PADID1,&PAG_InitStru);

    }
    c_printf("s_1_403_gpio_gpio_all_output_many_times_to_flip case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}
















