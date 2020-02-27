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
#include "cm_printf.h"


#if defined(BR005)
#define UART1_TX  PADID10
#define UART1_RX  PADID11
GPIO_PinId_Type TestUart1CstPin = GPIO_PIN_18;
#elif defined(BR003)
#define UART1_TX  PADID15
#define UART1_RX  PADID16
GPIO_PinId_Type TestUart1CstPin = GPIO_PIN_26;
#endif




void  UART1_Write_handle(void)
{
    for(uint16_t i=0 ;i<800;i++);
    GPIO_WriteBit(TestUart1CstPin,0); 
}



int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    Verrify_SendPinConnect(GPIO_UART1_EN);
    LOGUartInit();
    c_printf("s_1_714_uart1_uart1_flow_control case \r\n");
    {
        GPIO_InitInfo_Type GPIO_InitStru;
        UART_InitInfo_Type UART_InitStru;
        PADConfig_Type PAG_InitStru;
        
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(UART1_TX,&PAG_InitStru);
        SystemPADConfig(UART1_RX,&PAG_InitStru);
        #ifdef BR003
        SystemPADConfig(PADID27,&PAG_InitStru);
        SystemPADConfig(PADID28,&PAG_InitStru);
        #endif
       
        UART_InitStru.UART_BaudRate = 961200;
        UART_InitStru.UART_WordLength = UART_WL_8BITS;
        UART_InitStru.UART_StopBits = UART_SB_1BIT;
        UART_InitStru.UART_ParityMode = UART_PM_NONE;
        UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
        UART_InitStru.UART_FIFOMode = UART_FM_ENABLE;
        UART_InitStru.UART_DMAMode = UART_DM_MODE_0;
        UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
        UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;  
           
        SystemDevClockCtl(UART1_CKEn,true);
        
        UART_Init(UART1, &UART_InitStru);

        GPIO_InitStru.dir           = GPOP_DIR_OUT;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;
        GPIO_InitStru.pin   = TestUart1CstPin;

        PAG_InitStru.pad_ctl    = PAD_MODE0;
        SystemPADConfig((PADId_Type)TestUart1CstPin,&PAG_InitStru);

        SystemDevClockCtl(GPIO_CKEn,true);
        GPIO_Init(&GPIO_InitStru);
        
        GPIO_WriteBit(TestUart1CstPin,0);          
    
        //Enable Uart Flow
        UART_AutoFlow(UART1,true);       
        cm_printf_Uart1("Uart1 Flow\n");
        UART_SetRts(UART1,false);
        for(uint16_t i=0 ;i<800;i++);
        UART_SetRts(UART1,true);
        for(uint16_t i=0 ;i<800;i++);
        GPIO_WriteBit(TestUart1CstPin,1);          
        UART_SetUWriteHandle(UART1_Write_handle);
        cm_printf_Uart1("Test Uart1 Flow \n");        
        c_printf("Test Uart1 Flow \n");  

    }
    c_printf("s_1_714_uart1_uart1_flow_control case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}



void UART1_IRQHandler(void)
{ 
    if (UART_LSRCheckBits(UART1, UART_LSR_BIT_DR)) 
    {   
#if !(defined(BR_MASTER) || defined(BR_SLAVE))   
        uint8_t data = UART_ReadByte(UART1);
        UART_WriteData(UART1,&data,1);       
#else
        uint8_t data = UART_ReadByte(UART1);
        UART_WriteData(log_uart,&data,1);   
#endif
    } 
    if(UART_GetInterruptID(UART1) == BUSY_DETECT)  
    {
        UART_GetStatus(UART1);
    }        
}
















