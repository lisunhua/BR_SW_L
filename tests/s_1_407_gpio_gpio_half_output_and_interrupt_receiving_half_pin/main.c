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
#endif
#ifdef BR003
    uint16_t All_Pad =14;
    GPIO_PinId_Type Start_PAD   = GPIO_PIN_1;
    GPIO_PinId_Type Mod_PAD     = GPIO_PIN_15;
    GPIO_PinId_Type End_PAD     = GPIO_PIN_28;
#endif
#ifdef BR005
    uint16_t All_Pad =9;
    GPIO_PinId_Type Start_PAD   = GPIO_PIN_1;
    GPIO_PinId_Type Mod_PAD     = GPIO_PIN_10;
    GPIO_PinId_Type End_PAD     = GPIO_PIN_18;
#endif

static uint8_t GPIOInterrup_Flag[32]={\
    0,0,0,0,0,0,0,0,0,0,\
    0,0,0,0,0,0,0,0,0,0,\
    0,0,0,0,0,0,0,0,0,0,\
    0,0} ;


int main (void)
{
    // LOG UART INIT
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_407_gpio_gpio_half_output_and_interrupt_receiving_half_pin case \r\n");
    Verrify_SendPinConnect(GPIO_TEST_EN);
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
        for (PADId_Type pin = PADID1; pin <= PADID5 ; pin++ )
           SystemPADConfig(pin,&PAG_InitStru);
        
        PAG_InitStru.pad_ctl    = PAD_MODE0;
        for (PADId_Type pin = PADID6;pin <= TEST_GPIO_END ;pin++ )
            SystemPADConfig(pin,&PAG_InitStru);

        
        GPIO_Output.dir             = GPOP_DIR_OUT;
        GPIO_Output.mode            = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_Output.int_en          = DISABLE;
        GPIO_Output.int_unmask      = DISABLE;
        GPIO_Output.int_type        = GPIO_INTTYPE_LEVEL;
        GPIO_Output.int_pol         = GPIO_INTPOL_ACTIVELOW;
        GPIO_Output.debounce_en     = DISABLE;
        
        GPIO_Input.dir              = GPOP_DIR_IN;
        GPIO_Input.mode             = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_Input.int_en           = ENABLE;
        GPIO_Input.int_unmask       = ENABLE;
        SystemDevClockCtl(GPIO_CKEn,true);
        SystemDevClockCtl(IFCLK_GPIO_CKEn,true);

        for(GPIO_IntType_Type IntT = GPIO_INTTYPE_LEVEL;IntT<= GPIO_INTTYPE_EDGE;IntT++)
        {
            GPIO_Input.int_type      = IntT;
            for(GPIO_IntPolarity_Type IntP = GPIO_INTPOL_ACTIVELOW; IntP<= GPIO_INTPOL_ACTIVEHIGH;IntP++)
            {
                GPIO_Input.int_pol       = IntP;
                for(FunctionalState deb = DISABLE;deb<= 1;deb++)
                {
                    GPIO_Input.debounce_en   = deb;
                   
                    GPIO_DeInit();
                    c_printf("GPIO config deb[%d] p[%d],D[%d]\r\n",deb,IntP,IntT);
                    for(GPIO_PinId_Type pin = Start_PAD;pin <Mod_PAD;pin++)
                    {
                        GPIO_Input.pin = pin;
                        GPIO_Output.pin = (GPIO_PinId_Type)(pin + All_Pad);
                        
                        NVIC_ClearPendingIRQ((IRQn_Type)(GPIO0_IRQn+pin));
                        NVIC_EnableIRQ((IRQn_Type)(GPIO0_IRQn+pin));
                        
                        GPIOInterrup_Flag[pin] = 0;
                        
                        GPIO_Init(&GPIO_Input);
                        GPIO_Init(&GPIO_Output);
                        
                        if(IntT == GPIO_INTTYPE_LEVEL)
                            if(IntP == GPIO_INTPOL_ACTIVELOW)
                                GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),0);
                            else
                                GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),1);     
                         else
                         {
                            if(IntP == GPIO_INTPOL_ACTIVELOW)
                            {
                                GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),1);
                                GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),0);
                            }
                            else
                            {
                                GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),0);
                                GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),1);
                            }
                         }

                        c_printf("GPIO Get Pin[%d] p[%d],D[%d]\r\n",pin,IntP,IntT);
                        while(GPIOInterrup_Flag[pin]==0);
                        
                    }  
                    
                    GPIO_DeInit();
                    
                    for(GPIO_PinId_Type pin = Mod_PAD;pin <=End_PAD;pin++)
                    {
                        GPIO_Input.pin = pin;
                        GPIO_Output.pin = (GPIO_PinId_Type)(pin - All_Pad);
                        
                        NVIC_ClearPendingIRQ((IRQn_Type)(GPIO0_IRQn+pin));
                        NVIC_EnableIRQ((IRQn_Type)(GPIO0_IRQn+pin));
                        
                        GPIOInterrup_Flag[pin] = 0;
                        
                        GPIO_Init(&GPIO_Input);
                        GPIO_Init(&GPIO_Output);
                        
                        if(IntT == GPIO_INTTYPE_LEVEL)
                            if(IntP == GPIO_INTPOL_ACTIVELOW)
                                GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),0);
                            else
                                GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),1);     
                         else
                         {
                            if(IntP == GPIO_INTPOL_ACTIVELOW)
                            {
                                GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),1);
                                GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),0);
                            }
                            else
                            {
                                GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),0);
                                GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),1);
                            }
                         }                   
                        c_printf("GPIO Get Pin[%d] p[%d],D[%d]\r\n",pin,IntP,IntT);
                        while(GPIOInterrup_Flag[pin]==0);                       
                    }  
                }
            }
        }

    }
    c_printf("s_1_407_gpio_gpio_half_output_and_interrupt_receiving_half_pin case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}



void GPIO0_IRQHandler(void)
{
    c_printf("GPIO0:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_0);
    GPIOInterrup_Flag[0] = 1;
    NVIC_DisableIRQ(GPIO0_IRQn);
}
void GPIO1_IRQHandler(void)
{
    c_printf("GPIO1:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_1);
    GPIOInterrup_Flag[1] = 1;
    NVIC_DisableIRQ(GPIO1_IRQn);
}
void GPIO2_IRQHandler(void)
{
    c_printf("GPIO2:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_2);
    GPIOInterrup_Flag[2] = 1;
    NVIC_DisableIRQ(GPIO2_IRQn);
}
void GPIO3_IRQHandler(void)
{
    c_printf("GPIO3:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_3);
    GPIOInterrup_Flag[3] = 1;
    NVIC_DisableIRQ(GPIO3_IRQn);
}
void GPIO4_IRQHandler(void)
{
    c_printf("GPIO4:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_4);
    GPIOInterrup_Flag[4] = 1;
    NVIC_DisableIRQ(GPIO4_IRQn);
}
void GPIO5_IRQHandler(void)
{
    c_printf("GPIO5:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_5);
    GPIOInterrup_Flag[5] = 1;
    NVIC_DisableIRQ(GPIO5_IRQn);
}
void GPIO6_IRQHandler(void)
{
    c_printf("GPIO6:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_6);
    GPIOInterrup_Flag[6] = 1;
    NVIC_DisableIRQ(GPIO6_IRQn);
}
void GPIO7_IRQHandler(void)
{
    c_printf("GPIO7:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_7);
    GPIOInterrup_Flag[7] = 1;
    NVIC_DisableIRQ(GPIO7_IRQn);
}
void GPIO8_IRQHandler(void)
{
    c_printf("GPIO8:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_8);
    GPIOInterrup_Flag[8] = 1;
    NVIC_DisableIRQ(GPIO8_IRQn);
}
void GPIO9_IRQHandler(void)
{
    c_printf("GPIO9:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_9);
    GPIOInterrup_Flag[9] = 1;
    NVIC_DisableIRQ(GPIO9_IRQn);
}
void GPIO10_IRQHandler(void)
{
    c_printf("GPIO10:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_10);
    GPIOInterrup_Flag[10] = 1;
    NVIC_DisableIRQ(GPIO10_IRQn);
}
void GPIO11_IRQHandler(void)
{
    c_printf("GPIO11:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_11);
    GPIOInterrup_Flag[11] = 1;
    NVIC_DisableIRQ(GPIO11_IRQn);
}
void GPIO12_IRQHandler(void)
{
    c_printf("GPIO12:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_12);
    GPIOInterrup_Flag[12] = 1;
    NVIC_DisableIRQ(GPIO12_IRQn);
}
void GPIO13_IRQHandler(void)
{
    c_printf("GPIO13:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_13);
    GPIOInterrup_Flag[13] = 1;
    NVIC_DisableIRQ(GPIO13_IRQn);
}
void GPIO14_IRQHandler(void)
{
    c_printf("GPIO14:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_14);
    GPIOInterrup_Flag[14] = 1;
    NVIC_DisableIRQ(GPIO14_IRQn);
}
void GPIO15_IRQHandler(void)
{
    c_printf("GPIO15:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_15);
    GPIOInterrup_Flag[15] = 1;
    NVIC_DisableIRQ(GPIO15_IRQn);
}
void GPIO16_IRQHandler(void)
{
    c_printf("GPIO16:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_16);
    GPIOInterrup_Flag[16] = 1;
    NVIC_DisableIRQ(GPIO16_IRQn);
}
void GPIO17_IRQHandler(void)
{
    c_printf("GPIO17:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_17);
    GPIOInterrup_Flag[17] = 1;
    NVIC_DisableIRQ(GPIO17_IRQn);
}
void GPIO18_IRQHandler(void)
{
    c_printf("GPIO18:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_18);
    GPIOInterrup_Flag[18] = 1;
    NVIC_DisableIRQ(GPIO18_IRQn);
}
void GPIO19_IRQHandler(void)
{
    c_printf("GPIO19:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_0);
    GPIOInterrup_Flag[19] = 1;
    NVIC_DisableIRQ(GPIO19_IRQn);
}
void GPIO20_IRQHandler(void)
{
    c_printf("GPIO20:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_20);
    GPIOInterrup_Flag[20] = 1;
    NVIC_DisableIRQ(GPIO20_IRQn);
}
void GPIO21_IRQHandler(void)
{
    c_printf("GPIO21:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_21);
    GPIOInterrup_Flag[21] = 1;
    NVIC_DisableIRQ(GPIO21_IRQn);
}
void GPIO22_IRQHandler(void)
{
    c_printf("GPIO22:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_22);
    GPIOInterrup_Flag[22] = 1;
    NVIC_DisableIRQ(GPIO22_IRQn);
}
void GPIO23_IRQHandler(void)
{
    c_printf("GPIO23:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_23);
    GPIOInterrup_Flag[23] = 1;
    NVIC_DisableIRQ(GPIO23_IRQn);
}
void GPIO24_IRQHandler(void)
{
    c_printf("GPIO24:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_24);
    GPIOInterrup_Flag[24] = 1;
    NVIC_DisableIRQ(GPIO24_IRQn);
}
void GPIO25_IRQHandler(void)
{
    c_printf("GPIO25:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_25);
    GPIOInterrup_Flag[25] = 1;
    NVIC_DisableIRQ(GPIO25_IRQn);
}
void GPIO26_IRQHandler(void)
{
    c_printf("GPIO26:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_26);
    GPIOInterrup_Flag[26] = 1;
    NVIC_DisableIRQ(GPIO26_IRQn);
}
void GPIO27_IRQHandler(void)
{
    c_printf("GPIO27:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_27);
    GPIOInterrup_Flag[27] = 1;
    NVIC_DisableIRQ(GPIO27_IRQn);
}
void GPIO28_IRQHandler(void)
{
    c_printf("GPIO28:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_28);
    GPIOInterrup_Flag[28] = 1;
    NVIC_DisableIRQ(GPIO28_IRQn);
}
void GPIO29_IRQHandler(void)
{
    c_printf("GPIO29:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_29);
    GPIOInterrup_Flag[29] = 1;
    NVIC_DisableIRQ(GPIO29_IRQn);
}

void GPIO30_IRQHandler(void)
{
    c_printf("GPIO30:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_30);
    GPIOInterrup_Flag[30] = 1;
    NVIC_DisableIRQ(GPIO30_IRQn);
}
void GPIO31_IRQHandler(void)
{
    c_printf("GPIO31:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_31);
    GPIOInterrup_Flag[1] = 1;
    NVIC_DisableIRQ(GPIO31_IRQn);
}

















