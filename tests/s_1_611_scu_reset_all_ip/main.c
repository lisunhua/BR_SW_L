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


static void verifyCheckScu(uint32_t idx,__IO uint32_t *reg,uint32_t val)
{
    *reg = val;
    SCU->SW_RST |=0x01<<idx;
    c_printf("SCU Reset:%d ",idx);
    if(*reg==val)
        c_printf(" False \n");
    else
        c_printf(" true \n"); 
}

void UartSCUOutput(void)
{
    UART_InitInfo_Type UART_InitStru;
    UART_InitStru.UART_BaudRate = 921600;
    UART_InitStru.UART_WordLength = UART_WL_8BITS;
    UART_InitStru.UART_StopBits = UART_SB_1BIT;
    UART_InitStru.UART_ParityMode = UART_PM_NONE;
    UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
    UART_InitStru.UART_FIFOMode = UART_FM_ENABLE;
    UART_InitStru.UART_DMAMode = UART_DM_MODE_0;
    UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
    UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;
     
    UART_Init(UART0, &UART_InitStru); 
    UART_InterruptSet(UART0,0x01ul<<UART_ERBFI);
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);
}


int main (void)
{
    uint32_t idx=0;
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_611_scu_reset_all_ip case \r\n");
    {
        SCU->CLK_EN= 0XFFFFFFFF;
        SCU->CLK_DIV = 0x005500aa;
        while(UART_GetStatus(UART0)& 0x01);
        SCU->SW_RST |=0x01<<0;
        for(uint16_t i=0;i<100;i++);
        SCU->CLK_EN= 0xFFFFFFFF;
        c_printf("SCU Reset:%d ",idx);
        if(SCU->CLK_DIV ==0x005500aa)
            c_printf(" False \n");
        else
            c_printf(" true \n");
        
        verifyCheckScu(1,&GPIO->DR0,0x005500aa);
        verifyCheckScu(2,&WDT->CR,0xE);
        verifyCheckScu(3,&RTC->CLR,0x005500aa);
        
        while(UART_GetStatus(UART0)& 0x01){};        
        {
        
            bool u0Ret = true;
            UART0->DLF = 0xe;
            SCU->SW_RST |=0x01<<4;
            
            if(UART0->DLF)
                u0Ret = false;
            
            UartSCUOutput();
            c_printf("\r\nReset UART0 [%s]\r\n",u0Ret? "true" : "false");
        }
        
        verifyCheckScu(5,&UART1->DLF,0xe);
        
        SPIM1->SSIENR = DISABLE;
        SPIM1->IMR = DISABLE;
        verifyCheckScu(6,&SPIM1->BAUDR,0x80);
        c_printf("Reset SPIM1:[%X]",SPIM1->BAUDR);

        SPIS1->SSIENR = DISABLE;
        SPIS1->IMR = DISABLE;
        verifyCheckScu(7,&SPIS1->TXFTLR,0x5);
        
        verifyCheckScu(8,&I2SM->CCR,0xF);
        verifyCheckScu(9,&I2SS->I2S_Ch.RCR,1);
        
        verifyCheckScu(10,&TIMERS->TIMER[0].LOAD_COUNT,0x005500aa);
        verifyCheckScu(10,&TIMERS->TIMER[1].LOAD_COUNT,0x005500aa);
        verifyCheckScu(10,&TIMERS->TIMER[2].LOAD_COUNT,0x005500aa);
        verifyCheckScu(10,&TIMERS->TIMER[3].LOAD_COUNT,0x005500aa);
        verifyCheckScu(10,&TIMERS->TIMER[4].LOAD_COUNT,0x005500aa);
        verifyCheckScu(10,&TIMERS->TIMER[5].LOAD_COUNT,0x005500aa);
        verifyCheckScu(10,&TIMERS->TIMER[6].LOAD_COUNT,0x005500aa);
        verifyCheckScu(10,&TIMERS->TIMER[7].LOAD_COUNT,0x005500aa);        
        verifyCheckScu(11,&I2C0->IC_TAR,0x88);
        
//        verifyCheckScu(12,&QDEC->DR0,0x005500aa);
	//flash_cache
        verifyCheckScu(12,&FC->CCR,0x60);
        verifyCheckScu(13,&FC->CCR,0x1234);		//added for check RF resetn(no rf register only check rf_resetn waveform)

        verifyCheckScu(14,&BB->BB_CTL[0],0x005500aa);
        verifyCheckScu(15,&BB->BB_CTL[2],0x005500aa);

        verifyCheckScu(16,&DMA->CHR[0].SAR,0x123);
       
        SPIM0->SSIENR = DISABLE;
        SPIM0->IMR = DISABLE;
        verifyCheckScu(17,&SPIM0->BAUDR,0x80);    
							//bit18 is dummy
        verifyCheckScu(19,&USB->GUSBCFG,1);
        verifyCheckScu(20,&USB->GUSBCFG,1);

        verifyCheckScu(21,&TIMERS->TIMER[0].LOAD_COUNT,0x3654);
        verifyCheckScu(22,&TIMERS->TIMER[1].LOAD_COUNT,0x3654);
        verifyCheckScu(23,&TIMERS->TIMER[2].LOAD_COUNT,0x3654);
        verifyCheckScu(24,&TIMERS->TIMER[3].LOAD_COUNT,0x3654);
        verifyCheckScu(25,&TIMERS->TIMER[4].LOAD_COUNT,0x3654);
        verifyCheckScu(26,&TIMERS->TIMER[5].LOAD_COUNT,0x3654);
        verifyCheckScu(27,&TIMERS->TIMER[6].LOAD_COUNT,0x3654);
        verifyCheckScu(28,&TIMERS->TIMER[7].LOAD_COUNT,0x3654);        verifyCheckScu(29,&BB->BB_CTL[1],0x1111a);    
        verifyCheckScu(30,&GPIO->DR0,0x45643);    
    }

	MCU_Sleep(3);
    c_printf("s_1_611_scu_reset_all_ip case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















