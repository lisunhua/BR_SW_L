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
#include <string.h>
#include "BR00x_uart.h"
#include "BR00x_clock.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"
#include "cm_printf.h"


bool UART0_Rx_flag=0;

int main (void)
{
    bool sut = true;
    LOGUartInit();
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    VerifyDualGetRoleHandler();
    c_printf("d_1_711_uart1_dual_uart1_to_uart1 case \r\n");   
    Verrify_SendPinConnect(DUAL_UART1TO1_PIN_EN);            
    {

#if defined(BR_MASTER) || defined(BR_SLAVE)   

        UART_InitInfo_Type UART_InitStru;
        PADConfig_Type PAG_InitStru;

        memset(&PAG_InitStru, 0,sizeof(PADConfig_Type));
        memset(&UART_InitStru,0,sizeof(UART_InitInfo_Type));
        

        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID15,&PAG_InitStru);
        SystemPADConfig(PADID16,&PAG_InitStru);
       
        UART_InitStru.UART_BaudRate     = 500000;
        UART_InitStru.UART_WordLength   = UART_WL_8BITS;
        UART_InitStru.UART_StopBits     = UART_SB_1BIT;
        UART_InitStru.UART_ParityMode   = UART_PM_NONE;
        UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
        UART_InitStru.UART_FIFOMode     = UART_FM_ENABLE;
        UART_InitStru.UART_DMAMode      = UART_DM_MODE_0;
        UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
        UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;  
           
        SystemDevClockCtl(UART1_CKEn,true);
        
        UART_Init(UART1, &UART_InitStru);
        UART_InterruptSet(UART1,0x01ul<<UART_ERBFI);
        NVIC_ClearPendingIRQ(UART1_IRQn);
        NVIC_EnableIRQ(UART1_IRQn); 
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif  
        {
            Verify_messageSend(BRCASE_STOP2,true);  
            {
                uint32_t cd=0,va=0;

            MSTART_TEST: 
                Verify_messageGetRData(&cd,&va);
                // c_printf("UART1 master[%d]\r\n",sut);
                // c_printf("I2C master:cmd[%x],value[%x]\r\n",cd,va);
                // MCU_Sleep(1);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    goto MSTART_TEST;
                if(sut)   
                    cm_printf_Uart1("SOC_CLT:master Uart1 to slave Uart1\r\n");
            }
        } 
#endif
      
#ifdef BR_SLAVE  
#ifdef BR_DUAL
        if(!GetSocRole())
#endif 
        {        
            Verify_messageSend(BRCASE_STOP1,true); 
            {
                uint32_t cd=0,va=0;

            SSTART_TEST: 
                Verify_messageGetRData(&cd,&va);
                // c_printf("I2C slave:cmd[%x],value[%x]\r\n",cd,va);
                // c_printf("UART1 Slave[%d]\r\n",sut);
                // MCU_Sleep(1);    
                if(!(cd == BRCASE_STOP2 && va == 1))
                    goto SSTART_TEST;
                if(sut)   
                    cm_printf_Uart1("SOC_SVR:slave Uart1 to master Uart1\r\n");
            }     
        }            
#endif
#endif
    }
    Verrify_SendPinConnect(UART0_OUTPUT);
    MCU_Sleep(3);
    c_printf("d_1_711_uart1_dual_uart1_to_uart1 case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}


void UART0_IRQHandler(void)
{ 
#ifdef BR_SLAVE
#ifdef BR_DUAL
    if(!GetSocRole())
#endif 
    {
        if(UART0_Rx_flag)
        {
            if (UART_LSRCheckBits(UART0, UART_LSR_BIT_DR)) 
            {
                uint8_t data = UART_ReadByte(UART0);
                UART_WriteData(UART1,&data,1);
            }
        }
    }
#endif   
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
#if !(defined(BR_MASTER) || defined(BR_SLAVE))   
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



















