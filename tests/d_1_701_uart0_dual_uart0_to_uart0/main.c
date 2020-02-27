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
#include "cm_printf.h"


int main (void)
{
    LOGUartInit();
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    VerifyDualGetRoleHandler();
    c_printf("d_1_701_uart0_dual_uart0_to_uart0 case \r\n");
    MCU_Sleep(1);
    Verrify_SendPinConnect(DUAL_UART0TO0_PIN_EN);
    Verrify_SendPinConnect(UART1_OUTPUT);
    {
        UART_InitInfo_Type UART_InitStru;
        PADConfig_Type PAD_InitStru;

        memset(&UART_InitStru,0,sizeof(UART_InitInfo_Type));
        memset(&PAD_InitStru, 0,sizeof(PADConfig_Type));
        
        PAD_InitStru.pad_ctl            = PAD_MODE1;       
        SystemPADConfig(PADID15,&PAD_InitStru);
        SystemPADConfig(PADID16,&PAD_InitStru);
        SystemDevClockCtl(UART1_CKEn,true);
        UART_InitStru.UART_BaudRate             = 921600;
        UART_InitStru.UART_WordLength           = UART_WL_8BITS;
        UART_InitStru.UART_StopBits             = UART_SB_1BIT;
        UART_InitStru.UART_ParityMode           = UART_PM_NONE;
        UART_InitStru.UART_HardwareFlowControl  = UART_FC_NONE;
        UART_InitStru.UART_FIFOMode             = UART_FM_ENABLE;
        UART_InitStru.UART_DMAMode              = UART_DM_MODE_0;
        UART_InitStru.UART_TX_FIFOTriggerMode   = UART_TT_EMPTY;
        UART_InitStru.UART_RX_FIFOTriggerMode   = UART_RT_1_CHARACTER;        
        UART_Init(UART1, &UART_InitStru);
    }

    LOGUartInit();
    UART_InterruptSet(UART0,0x01ul);
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);

    {
#if defined(BR_MASTER) || defined(BR_SLAVE)       
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            cm_printf_Uart1("CLT->\n");
            Verify_messageSend(BRCASE_STOP2,true);  
            {
                uint32_t cd=0,va=0;
            MSTART_TEST: 
                Verify_messageGetRData(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    goto MSTART_TEST;

                c_printf("SOC_CLT:master Uart0 to slave Uart0\r\n");
            }
        }  
#endif
      
#ifdef BR_SLAVE   
#ifdef BR_DUAL
        if(!GetSocRole())
#endif    
        {        
            cm_printf_Uart1("SVR->\n");
            Verify_messageSend(BRCASE_STOP1,true); 
            {
                uint32_t cd=0,va=0;
            SSTART_TEST: 
                Verify_messageGetRData(&cd,&va);    
                if(!(cd == BRCASE_STOP2 && va == 1))
                    goto SSTART_TEST;  
                c_printf("SOC_SVR:slave Uart0 to master Uart0\r\n");
            }     
        }
         
#endif
#endif
    }
    MCU_Sleep(5);
    Verrify_SendPinConnect(UART0_OUTPUT);
    c_printf("d_1_701_uart0_dual_uart0_to_uart1 case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}

void UART0_IRQHandler(void)
{ 

    if (UART_LSRCheckBits(UART0, UART_LSR_BIT_DR)) 
    {
        uint8_t data = UART_ReadByte(UART0);
        UART_WriteData(UART1,&data,1);
    }
    if(UART_GetInterruptID(UART0) == BUSY_DETECT)  
    {
        UART_GetStatus(UART0);
    } 
#ifdef BR_FPGA
    if (UART_LSRCheckBits(UART0, UART_LSR_BIT_DR)) 
    {
        uint8_t data = UART_ReadByte(UART0);
        UART0_Handle(data);
        
    }
#endif

}


void UART1_IRQHandler(void)
{ 
    if (UART_LSRCheckBits(UART1, UART_LSR_BIT_DR)) 
    {   
#if (defined(BR_MASTER) || defined(BR_SLAVE))   
        //cm_printf_Uart1("[%X]\n",UART_ReadByte(UART1));       
        uint8_t data = UART_ReadByte(UART1);
        UART_WriteData(UART1,&data,1);       
#else
        uint8_t data = UART_ReadByte(UART1);
        UART_WriteData(UART0,&data,1);   
#endif
    } 
    if(UART_GetInterruptID(UART1) == BUSY_DETECT)  
    {
        UART_GetStatus(UART1);
    }        
}

















