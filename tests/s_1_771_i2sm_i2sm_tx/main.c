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
#include "BR00x_i2s.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"




void i2sm_SendData(void)
{
    uint32_t data   = 0xaaaaaaa0;
    uint32_t data1  = 0x55555550;
    while(0== I2S_GetInterruptStatus(I2SM,I2S_TX_FIFO_OVERRUN))
    {
        data++;
        data1++;
        I2S_SetLeftTransmitData(I2SM,data);
        I2S_SetRightTransmitData(I2SM,data1);
    }
    {
        I2S_IntCtlMask  IntCtlMask;
        IntCtlMask.rx_dma_available_interrupt_mask    =  false;
        IntCtlMask.rx_fifo_overrun_interrupt_mask     =  false;
        IntCtlMask.tx_fifo_empty_interrupt_mask       =  false;
        IntCtlMask.tx_fifo_overrun_interrupt_mask     =  false;
        I2S_SetInterruptMask(I2SM ,&IntCtlMask);
    }

    I2S_GeneratrClock(I2SM,true);
    
}

void i2ss_SendData(void)
{
    uint32_t data   = 0x66666660;
    uint32_t data1  = 0x99999990;
    while(0== I2S_GetInterruptStatus(I2SS,I2S_TX_FIFO_OVERRUN))
    {
        data++;
        data1++;
        I2S_SetLeftTransmitData(I2SS,data);
        I2S_SetRightTransmitData(I2SS,data1);
    }
    {
        I2S_IntCtlMask  IntCtlMask;
        IntCtlMask.rx_dma_available_interrupt_mask    =  false;
        IntCtlMask.rx_fifo_overrun_interrupt_mask     =  false;
        IntCtlMask.tx_fifo_empty_interrupt_mask       =  false;
        IntCtlMask.tx_fifo_overrun_interrupt_mask     =  false;
        I2S_SetInterruptMask(I2SS ,&IntCtlMask);
    }
}



int main (void)
{
    // LOG UART INIT
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_771_i2sm_i2sm_tx case \r\n");
    {

        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        PAG_InitStru.set        = 0;
       
        PAG_InitStru.pad_ctl    = PAD_MODE2;
        PAG_InitStru.pad_ctl    = PAD_MODE0;
        SystemPADConfig(PADID19,&PAG_InitStru); //interface 1
        SystemPADConfig(PADID20,&PAG_InitStru);
        SystemPADConfig(PADID21,&PAG_InitStru);
        SystemPADConfig(PADID22,&PAG_InitStru);
        
        PAG_InitStru.pad_ctl    = PAD_MODE3;
       // PAG_InitStru.pad_ctl    = PAD_MODE0;
        SystemPADConfig(PADID23,&PAG_InitStru); //interface 2
        SystemPADConfig(PADID24,&PAG_InitStru);
        SystemPADConfig(PADID25,&PAG_InitStru);
        SystemPADConfig(PADID26,&PAG_InitStru);
        
        SCU_I2SDiv(10);
        I2S_InitStru.dirct_type= DATA_TX;
        
        I2S_InitStru.clock_gating_type  =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type         =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type     =  RESOLUTION_32_BIT;
        SCU->IO_CONFIG |=0x10;
        SCU->IO_CONFIG |=0x20;
        I2S_InitStru.interrupt_level    = TRIGGER_LEVEL_1;
        I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;
        I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;
        I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
        I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;

        SystemDevClockCtl(I2SM_CKEn,true);

        I2S_Init(I2SM, &I2S_InitStru);
        NVIC_EnableIRQ(I2SM_IRQn);
        i2sm_SendData();    


    }
    c_printf("s_1_771_i2sm_i2sm_tx case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}



void I2SM_IRQHandler(void)      
{     
    c_printf("I2SM_IRQ\n"); 
    if( I2S_GetInterruptStatus(I2SM,I2S_RX_AVAILABLE_DAM))
    {
        c_printf("MRX_ADAM r[%X],l[%X]\n",\
            I2S_GetRightReceiveData(I2SM),\
            I2S_GetLeftReceiveData(I2SM));
    }
    if( I2S_GetInterruptStatus(I2SM,I2S_RX_FIFO_OVERRUN))
    {
        I2S_ClearRxOverrunInterrupt(I2SM);
        c_printf("RX_OVERRUN\r\n");
    }
    if( I2S_GetInterruptStatus(I2SM,I2S_TX_FIFO_EMPTY))
    {
        {
            I2S_IntCtlMask  IntCtlMask;

            IntCtlMask.rx_dma_available_interrupt_mask    =  false;
            IntCtlMask.rx_fifo_overrun_interrupt_mask     =  true;
            IntCtlMask.tx_fifo_empty_interrupt_mask       =  true;
            IntCtlMask.tx_fifo_overrun_interrupt_mask     =  true;
            I2S_SetInterruptMask(I2SM,&IntCtlMask);

        }
        I2S_GeneratrClock(I2SM,false);
        //i2sm_SendData();
        c_printf("TX_EMPTY\r\n");
    }
    if( I2S_GetInterruptStatus(I2SM,I2S_TX_FIFO_OVERRUN))
    {
        I2S_ClearTxOverrunInterrupt(I2SM);
        c_printf("TX_OVERRUN\r\n");
        I2S_GeneratrClock(I2SM,false);
    }
}    

















