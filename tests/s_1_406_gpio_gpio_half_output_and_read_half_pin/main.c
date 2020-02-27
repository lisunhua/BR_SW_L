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

#ifdef BR002
    uint16_t All_Pad =13;
    GPIO_PinId_Type Start_PAD   = GPIO_PIN_1;
    GPIO_PinId_Type Mod_PAD     = GPIO_PIN_14;
    GPIO_PinId_Type End_PAD     = GPIO_PIN_26;
#elif  defined(BR003)
    uint16_t All_Pad =14;
    GPIO_PinId_Type Start_PAD   = GPIO_PIN_1;
    GPIO_PinId_Type Mod_PAD     = GPIO_PIN_15;
    GPIO_PinId_Type End_PAD     = GPIO_PIN_28;
#elif  defined(BR005)
    uint16_t All_Pad =9;
    GPIO_PinId_Type Start_PAD   = GPIO_PIN_1;
    GPIO_PinId_Type Mod_PAD     = GPIO_PIN_10;
    GPIO_PinId_Type End_PAD     = GPIO_PIN_18;
#endif

int main (void)
{
    // LOG UART INIT
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_406_gpio_gpio_half_output_and_read_half_pin case \r\n");
    Verrify_SendPinConnect(GPIO_TEST_EN); //set TB
    MCU_Sleep(1);
    {
        GPIO_InitInfo_Type GPIO_Input;
        GPIO_InitInfo_Type GPIO_Output;
        PADConfig_Type     PAG_InitStru;
        
        memset(&GPIO_Input,0,sizeof(GPIO_InitInfo_Type));
        memset(&GPIO_Output,0,sizeof(GPIO_InitInfo_Type));
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        PAG_InitStru.pad_ctl    = PAD_MODE0;
        SystemPADConfig(PADID0,&PAG_InitStru);


        PAG_InitStru.pad_ctl    = PAD_MODE1;
        for (PADId_Type pin = PADID1;pin <= PADID5 ;pin++ )
           SystemPADConfig(pin,&PAG_InitStru);
        
        PAG_InitStru.pad_ctl    = PAD_MODE0;
        for (PADId_Type pin = PADID6;pin <= TEST_GPIO_END ;pin++ )
            SystemPADConfig(pin,&PAG_InitStru);
        
        
        GPIO_Input.dir           = GPOP_DIR_IN;
        GPIO_Input.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_Input.int_en        = DISABLE;
        GPIO_Input.int_unmask    = DISABLE;
        GPIO_Input.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_Input.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_Input.debounce_en   = DISABLE;
        
        GPIO_Output.dir           = GPOP_DIR_OUT;
        GPIO_Output.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_Output.int_en        = DISABLE;
        GPIO_Output.int_unmask    = DISABLE;
        GPIO_Output.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_Output.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_Output.debounce_en   = DISABLE;
        SystemDevClockCtl(GPIO_CKEn,true);
        SystemDevClockCtl(IFCLK_GPIO_CKEn,true);
     
        for(GPIO_PinId_Type pin = Start_PAD;pin <Mod_PAD ;pin++)
        {
            FlagStatus st;
            GPIO_Input.pin = pin;
            GPIO_Output.pin = (GPIO_PinId_Type)(pin + All_Pad);
             
            GPIO_Init(&GPIO_Input);
            GPIO_Init(&GPIO_Output);
            
            GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),1);
            st = GPIO_ReadBit(pin);
            c_printf("GPIO Set Pin[%d],[%d];Get Pin[%d],[%d]\n",
                pin+All_Pad,1,pin,st);
            
            GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),0);
            st = GPIO_ReadBit(pin);
            c_printf("GPIO Set Pin[%d],[%d];Get Pin[%d],[%d]\n",
                pin+All_Pad,0,pin,st);
        } 
        
        GPIO_DeInit();

        for(GPIO_PinId_Type pin = Mod_PAD;pin <= End_PAD;pin++)
        {
            GPIO_Input.pin = pin;
            GPIO_Output.pin = (GPIO_PinId_Type)(pin-All_Pad);
             
            GPIO_Init(&GPIO_Input);
            GPIO_Init(&GPIO_Output);
            
            GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),1);
            c_printf("GPIO Set Pin[%d],[%d];Get Pin[%d],[%d]\n",
                pin-All_Pad,1,pin,GPIO_ReadBit(pin));
            
            GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),0);
            c_printf("GPIO Set Pin[%d],[%d];Get Pin[%d],[%d]\n",
                pin-All_Pad,0,pin,GPIO_ReadBit(pin));
        }      

    }
    c_printf("s_1_406_gpio_gpio_half_output_and_read_half_pin case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}
















