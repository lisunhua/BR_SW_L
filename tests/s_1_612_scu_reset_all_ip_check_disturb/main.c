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

static void verifyCheckScuIs(uint32_t idx,uint32_t index,__IO uint32_t *reg,uint32_t val,bool *sut)
{
    if(idx != index){
        if ((*reg) != val)
            (*sut) = false;
    }
    if(idx == index)
        if ((*reg) == val)
            (*sut) = false;  
    if(!(*sut))
        c_printf("i:%d, idx:%d,reg:%X,val:%X\n",idx,index,(*reg),val);
}

void UartSCUOutput(void)
{
    UART_InitInfo_Type UART_InitStru;
    UART_InitStru.UART_BaudRate     = 921600;
    UART_InitStru.UART_WordLength   = UART_WL_8BITS;
    UART_InitStru.UART_StopBits     = UART_SB_1BIT;
    UART_InitStru.UART_ParityMode   = UART_PM_NONE;
    UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
    UART_InitStru.UART_FIFOMode     = UART_FM_ENABLE;
    UART_InitStru.UART_DMAMode      = UART_DM_MODE_0;
    UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
    UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;
     
    UART_Init(UART0, &UART_InitStru); 
    UART_InterruptSet(UART0,0x01ul<<UART_ERBFI);
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);
}



void VerifyResetHandle(uint16_t idx)
{
    bool sut = true;
    uint32_t uart0reg = UART0->DLF; 
    c_printf("Reset[ %d ] \n",idx);    
    
    SCU->CLK_DIV    = 0x005500aa;
    GPIO->DR0       = 0x005500aa;
    WDT->CR         = 0xE;
    RTC->CLR        = 0x005500aa;
 
    UART1->DLF      = 0xe;
  
    SPIM1->SSIENR   = DISABLE;
    SPIM1->IMR      = DISABLE;
    SPIM1->BAUDR    = 0x80;

    SPIS1->SSIENR   = DISABLE;
    SPIS1->IMR      = DISABLE;
    SPIS1->TXFTLR   = 0x5;
    
    I2SM->CCR       = 0xF;
    I2SS->I2S_Ch.RCR= 1;
    //timers
    I2C0->IC_TAR    = 0x88;
    FC->CCR         = 0x60;
    //RF
    BB->BB_CTL[0]   = 0x1234;
    BB->BB_CTL[1]   = 0x1234;
    
    DMA->CHR[0].SAR = 0x123;  
    
    SPIM0->SSIENR   = DISABLE;
    SPIM0->IMR      = DISABLE;
    SPIM0->BAUDR    = 0x80;
    USB->GINTMSK      = 0x66;
    
    TIMERS->TIMER[0].LOAD_COUNT = 0x005500aa;
    TIMERS->TIMER[1].LOAD_COUNT = 0x005500aa;
    TIMERS->TIMER[2].LOAD_COUNT = 0x005500aa;
    TIMERS->TIMER[3].LOAD_COUNT = 0x005500aa;
    TIMERS->TIMER[4].LOAD_COUNT = 0x005500aa;
    TIMERS->TIMER[5].LOAD_COUNT = 0x005500aa;
    TIMERS->TIMER[6].LOAD_COUNT = 0x005500aa;
    TIMERS->TIMER[7].LOAD_COUNT = 0x005500aa;
    
    uart0reg = 0xe;
       
    if(idx==4)
    {
        while(UART_GetStatus(UART0)&0x01);
        UART0->DLF = 0xe;
        SCU->SW_RST |=0x01<<idx;
        uart0reg = UART0->DLF;
        while(UART_GetStatus(UART0)&0x01);
        UartSCUOutput();       
    }
    else if(idx == 0)
    {
         SCU->SW_RST |=0x01<<idx;
         for(uint16_t j=0;j<100;j++);
         SCU->CLK_EN= 0xFFFFFFFF;
    }
    else
        SCU->SW_RST |=0x01<<idx;
   

    verifyCheckScuIs(idx,0,&SCU->CLK_DIV,0x005500aa,&sut);
    verifyCheckScuIs(idx,1,&GPIO->DR0,0x005500aa,&sut);
    verifyCheckScuIs(idx,2,&WDT->CR  ,0xE,&sut);
    verifyCheckScuIs(idx,3,&RTC->CLR,0x005500aa,&sut);
    verifyCheckScuIs(idx,4,&uart0reg,0xe,&sut);
    verifyCheckScuIs(idx,5,&UART1->DLF,0xe,&sut);
    verifyCheckScuIs(idx,6,&SPIM1->BAUDR,0x80,&sut);
    verifyCheckScuIs(idx,7,&SPIS1->TXFTLR,0x5,&sut);
    verifyCheckScuIs(idx,8,&I2SM->CCR,0xF,&sut);
    verifyCheckScuIs(idx,9,&I2SS->I2S_Ch.RCR,1,&sut);
    
    verifyCheckScuIs(idx,10,&TIMERS->TIMER[0].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,10,&TIMERS->TIMER[1].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,10,&TIMERS->TIMER[2].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,10,&TIMERS->TIMER[3].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,10,&TIMERS->TIMER[4].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,10,&TIMERS->TIMER[5].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,10,&TIMERS->TIMER[6].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,10,&TIMERS->TIMER[7].LOAD_COUNT,0x005500aa,&sut);
    
    
    verifyCheckScuIs(idx,11,&I2C0->IC_TAR,0x88,&sut);
    verifyCheckScuIs(idx,12,&FC->CCR,0x60,&sut);
    //verifyCheckScuIs(idx,13,&I2C0->IC_TAR,0x1234,&sut);
 //13:rf_pclk
    verifyCheckScuIs(idx,14,&BB->BB_CTL[0],0x1234,&sut);
    //verifyCheckScuIs(idx,15,&I2C0->IC_TAR,0x1234,&sut);
 //15:bb_hclk
    verifyCheckScuIs(idx,16,&DMA->CHR[0].SAR,0x123,&sut);
    
    verifyCheckScuIs(idx,17,&SPIM0->BAUDR,0x80,&sut);
    verifyCheckScuIs(idx,19,&USB->GINTMSK,0x66,&sut);
//    verifyCheckScuIs(idx,20,&USB->GUSBCFG,1,&sut);

    verifyCheckScuIs(idx,21,&TIMERS->TIMER[0].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,22,&TIMERS->TIMER[1].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,23,&TIMERS->TIMER[2].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,24,&TIMERS->TIMER[3].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,25,&TIMERS->TIMER[4].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,26,&TIMERS->TIMER[5].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,27,&TIMERS->TIMER[6].LOAD_COUNT,0x005500aa,&sut);
    verifyCheckScuIs(idx,28,&TIMERS->TIMER[7].LOAD_COUNT,0x005500aa,&sut);
//      
    verifyCheckScuIs(idx,29,&BB->BB_CTL[1],0x1234,&sut);
    verifyCheckScuIs(idx,30,&GPIO->DR0,0x005500aa,&sut);
    c_printf("sut:%s \n",sut?"true":"false");
      
    if(!sut){
        c_printf("Re:SCU[%X],GPIO[%X],wdt[%X],rtc[%X],UART0[%X],UART1[%X],SPIM1[%X],SPIS1[%X]\n",
        SCU->CLK_DIV,GPIO->DR0,WDT->CR,RTC->CLR,uart0reg,UART1->DLF,SPIM1->BAUDR,SPIS1->TXFTLR);
        c_printf("i2sm[%X],i2ss[%X],i2c[%X],RF[],BB[%x],dma[%X],SPIM0[%x],usb[%x],FC[%x]\n",
        I2SM->CCR,I2SS->I2S_Ch.RCR,I2C0->IC_TAR,BB->BB_CTL[0],DMA->CHR[0].SAR,SPIM0->BAUDR,&USB->GINTMSK,FC->CCR);
        c_printf("tm0[%X],tm1[%X],tm2[%X],tm3[%X],tm4[%X],tm5[%X],tm6[%X],tm7[%X]\n",
        TIMERS->TIMER[0].LOAD_COUNT,TIMERS->TIMER[1].LOAD_COUNT,TIMERS->TIMER[2].LOAD_COUNT,TIMERS->TIMER[3].LOAD_COUNT,
        TIMERS->TIMER[4].LOAD_COUNT,TIMERS->TIMER[5].LOAD_COUNT,TIMERS->TIMER[6].LOAD_COUNT,TIMERS->TIMER[7].LOAD_COUNT);      
    }
             
}


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_612_scu_reset_all_ip_check_disturb case \r\n");

    {
        uint32_t ctlReset = 0x1FE1FFFF;
        SCU->CLK_EN = 0xffffffff;
        
        for(uint16_t i = 0;i<32;i++)
        {
            if(ctlReset >> i & 0x01ul)
                VerifyResetHandle(i);
        }
    }

	MCU_Sleep(3);
    c_printf("s_1_612_scu_reset_all_ip_check_disturb case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















