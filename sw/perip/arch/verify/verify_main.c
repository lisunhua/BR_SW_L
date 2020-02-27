/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_main.c
 * @brief
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
#include "cm_printf.h"
#include "verify_slave.h"
#include "verify_message.h"

#ifdef BR1051Axx
#include "data.h"
#endif


#ifdef BR_FPGA
#include "verify_test_bench.h"
extern void tb_SetRunCid(uint32_t id);
extern void tb_Verify_messageInit(void);
#endif 


#define TEST_SCU_REGx

void Uart1DebugOutput(void);

void UartDebugOutput(void);
/**
main
**/
int main(void)
{   
    UartDebugOutput(); 
#if  defined(SINGLE) || defined(BR_DUAL)  
    //Control Tb Connect UART0 ,
    Verrify_SendPinConnect(UART0_OUTPUT);
#endif
    
#ifdef SINGLE    
    cm_printf("Start...[%s]\r\n",__TIME__);
#endif
    
#ifdef BR_FLASE
    cm_printf("Start FLASH...[%s]\r\n",__TIME__);
#endif
    
#ifdef BR1051Axx
    cm_printf("Start...[%d]\r\n",BR1051Adata_buff[1024]);
#endif
    
#ifdef BR_MASTER
    cm_printf("Dual Soc Clt Start...[%s]\r\n",__TIME__);
#endif

#ifdef BR_SLAVE
    cm_printf("Dual Soc Svr Start...[%s]\r\n",__TIME__);
#endif
    
#ifdef TEST_SCU_REG// Test Scu Register mapping problem
    SCU->CLK_DIV1= 0X12345678;
    cm_printf("...[%X]\r\n",SCU->SEND_CMD);
    return 0;
#else
    
#ifdef BR_FPGA
        for(uint32_t i=0;i<10000000;i++){};
#endif
		
#ifdef BR_FPGA
    initTestBanch();
    tb_Verify_messageInit();
#endif
 
    VerifySlaveHandle();
    return 0;
#endif
}


void  delay(uint32_t time)
{
    for(uint32_t i=0;i<time;i++)
        for(uint8_t k=0;k<10;k++)
        {
            
        }
}


void UartDebugOutput(void)
{
#ifdef  DEBUG_LOG
    UART_InitInfo_Type UART_InitStru;
    
    SystemDevClockCtl(UART0_CKEn,true);
       
    UART_InitStru.UART_BaudRate             = 921600;
    UART_InitStru.UART_WordLength           = UART_WL_8BITS;
    UART_InitStru.UART_StopBits             = UART_SB_1BIT;
    UART_InitStru.UART_ParityMode           = UART_PM_NONE;
    UART_InitStru.UART_HardwareFlowControl  = UART_FC_NONE;
    UART_InitStru.UART_FIFOMode             = UART_FM_ENABLE;
    UART_InitStru.UART_DMAMode              = UART_DM_MODE_0;
    UART_InitStru.UART_TX_FIFOTriggerMode   = UART_TT_EMPTY;
    UART_InitStru.UART_RX_FIFOTriggerMode   = UART_RT_1_CHARACTER;
        
    UART_Init(UART0, &UART_InitStru); 
#ifdef BR_FPGA
    UART_InterruptSet(UART0,0x01ul<<UART_ERBFI);
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);
#endif
    
#endif
}

void Uart1DebugOutput(void)
{
#ifdef  DEBUG_LOG
    UART_InitInfo_Type UART_InitStru;
    
    SystemDevClockCtl(UART1_CKEn,true);
    
    UART_InitStru.UART_BaudRate             = 500000;
    UART_InitStru.UART_WordLength           = UART_WL_8BITS;
    UART_InitStru.UART_StopBits             = UART_SB_1BIT;
    UART_InitStru.UART_ParityMode           = UART_PM_NONE;
    UART_InitStru.UART_HardwareFlowControl  = UART_FC_NONE;
    UART_InitStru.UART_FIFOMode             = UART_FM_ENABLE;
    UART_InitStru.UART_DMAMode              = UART_DM_MODE_0;
    UART_InitStru.UART_TX_FIFOTriggerMode   = UART_TT_EMPTY;
    UART_InitStru.UART_RX_FIFOTriggerMode   = UART_RT_1_CHARACTER;
    
    UART_Init(UART1, &UART_InitStru); 
    cm_printf_Uart1("Output UART1\n");
#endif
}

#ifdef BR_FPGA

void UART0_Handle(uint8_t  ch)
{



}

#endif



