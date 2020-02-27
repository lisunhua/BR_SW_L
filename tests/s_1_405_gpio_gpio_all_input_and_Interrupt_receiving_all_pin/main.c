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
    c_printf("s_1_405_gpio_gpio_all_input_and_Interrupt_receiving_all_pin case \r\n");
    MCU_Sleep(1);
    {
        GPIO_InitInfo_Type GPIO_InitStru;
        PADConfig_Type      PAG_InitStru;
        
        memset(&GPIO_InitStru,0,sizeof(GPIO_InitInfo_Type));
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));

        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
       
        //SystemPADConfig(PADID0,&PAG_InitStru);
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        for (PADId_Type pin = PADID1;pin <= PADID5 ;pin++ )
           SystemPADConfig(pin,&PAG_InitStru);
        
        PAG_InitStru.pad_ctl    = PAD_MODE0;
        for (PADId_Type pin = PADID6;pin <= TEST_GPIO_END ;pin++ )
            SystemPADConfig(pin,&PAG_InitStru);
        
        GPIO_InitStru.dir           = GPOP_DIR_IN;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = ENABLE;
        GPIO_InitStru.int_unmask    = ENABLE;
        SystemDevClockCtl(GPIO_CKEn,true);
        SystemDevClockCtl(IFCLK_GPIO_CKEn,true);
        for(GPIO_IntType_Type IntT = GPIO_INTTYPE_LEVEL;IntT<= GPIO_INTTYPE_EDGE;IntT++)
        {
            GPIO_InitStru.int_type      = IntT;
            for(GPIO_IntPolarity_Type IntP = GPIO_INTPOL_ACTIVELOW; IntP<= GPIO_INTPOL_ACTIVEHIGH;IntP++)
            {
                GPIO_InitStru.int_pol       = IntP;
                for(FunctionalState deb = DISABLE;deb<= 1;deb++)
                {
                    GPIO_InitStru.debounce_en   = deb;
                    for(GPIO_PinId_Type pin = GPIO_PIN_0;pin <GPIO_PIN_32;pin++)
                    {
                        FlagStatus st;
                        GPIO_InitStru.pin = pin;
                        GPIO_Init(&GPIO_InitStru);
                        for(uint16_t i=0;i<1000;i++){};
                        st = GPIO_ReadBit(pin);
                        c_printf("GPIO Get Pin[%X],st[%d]\r\n",pin,st);
                    }  
                }
            }
        }
    }
    c_printf("s_1_405_gpio_gpio_all_input_and_Interrupt_receiving_all_pin case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}
















