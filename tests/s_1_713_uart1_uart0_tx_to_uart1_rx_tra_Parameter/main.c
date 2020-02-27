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
#elif defined(BR003)
#define UART1_TX  PADID15
#define UART1_RX  PADID16
#endif


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    Verrify_SendPinConnect(UART0_UART1_EN);
    LOGUartInit();
    c_printf("s_1_713_uart1_uart0_tx_to_uart1_rx_tra_Parameter case \r\n");
    MCU_Sleep(1);
    Verrify_SendPinConnect(UART1_OUTPUT);
    {
        UART_InitInfo_Type UART_InitStru;
        PADConfig_Type PAG_InitStru;
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));

        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(UART1_TX,&PAG_InitStru);
        SystemPADConfig(UART1_RX,&PAG_InitStru);
        
        UART_InitStru.UART_ParityMode = UART_PM_NONE;
        UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
        
        UART_InitStru.UART_DMAMode = UART_DM_MODE_0;
        
        SystemDevClockCtl(UART1_CKEn,true);
        
        for(UART_StopBits_Type sbt =UART_SB_1BIT;sbt<=UART_SB_1_5_2BITS;sbt++)
        {
            UART_InitStru.UART_StopBits = sbt;
            for(uint32_t brt=115200;brt<500000;brt+=100000)
            {
                UART_InitStru.UART_BaudRate=brt;
                for(UART_RXFIFOTriggerMode_Type rfm=UART_RT_1_CHARACTER;rfm<=UART_RT_2_LESS;rfm++)
                {
                    UART_InitStru.UART_RX_FIFOTriggerMode = rfm;
                    for(UART_TXFIFOTriggerMode_Type tfm=UART_TT_EMPTY;tfm<=UART_TT_HALF;tfm++)
                    {
                        UART_InitStru.UART_TX_FIFOTriggerMode = tfm;
                        for(UART_FIFOMode_Type fm=UART_FM_ENABLE;fm<=UART_FM_ENABLE;fm++)
                        {
                            UART_InitStru.UART_FIFOMode = fm;
                            for(UART_WordLength_Type wl = UART_WL_8BITS;wl<UART_WL_9BITS;wl++)
                            {
                                UART_InitStru.UART_WordLength = wl;
                                while(UART_GetStatus(UART1)&0x01);
                                UART_Init(UART1, &UART_InitStru);
                                UART_InterruptSet(UART1,0x01ul<<UART_ERBFI);
                                UART_InterruptSet(UART1,0x01ul<<UART_ElSI);
                                
                                NVIC_ClearPendingIRQ(UART1_IRQn);
                                NVIC_EnableIRQ(UART1_IRQn); 
                                cm_printf_Uart1("Uart1->Uart0\r\n");
                                MCU_Sleep(1);
                                while(UART_GetStatus(UART0)& 0x01);        
                                UART_Init(UART0, &UART_InitStru); 
                                c_printf("5689\n");
                            }
                        }
                    }
                }
            }  
        }

    }
    MCU_Sleep(1);
    Verrify_SendPinConnect(UART0_OUTPUT);
    c_printf("s_1_713_uart1_uart0_tx_to_uart1_rx_tra_Parameter case completed \r\n");
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
















