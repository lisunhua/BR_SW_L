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


/***********************************************************
                        APP
************************************************************/
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
    bool sut = true;
    LOGUartInit();
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    VerifyDualGetRoleHandler();
    
    SystemDevClockCtl(I2SM_CKEn,true);
    SystemDevClockCtl(I2SS_CKEn,true);

    c_printf("d_1_775_i2s_i2sm_to_i2ss_pin_17_20_no_config_rx case \r\n");
    MCU_Sleep(1);
    Verrify_SendPinConnect(DUAL_I2S_17TO20_PIN_EN);
    {
        #if    defined(BR_MASTER) || defined(BR_SLAVE)
        I2S_InitInof_Type   I2S_InitStru;
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE3;

        SystemPADConfig(PADID23,&PAG_InitStru);
        SystemPADConfig(PADID24,&PAG_InitStru);
        SystemPADConfig(PADID25,&PAG_InitStru);
//        SystemPADConfig(PADID26,&PAG_InitStru);
        
        I2S_InitStru.clock_gating_type      =  NO_CLOCK_GATING;
        I2S_InitStru.clock_type             =  CLOCK_CYCLES_32;
        I2S_InitStru.data_resl_type         =  RESOLUTION_32_BIT;
        I2S_InitStru.interrupt_level        =  TRIGGER_LEVEL_1;
        
#ifdef BR_SLAVE  
#ifdef BR_DUAL
        if(!GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_RX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  false;//Enable
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  false;//Enable
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true; //Disable
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  false;//Enable
            
            SCU->IO_CONFIG &=~0x20;
            
            SystemDevClockCtl(I2SS_CKEn,true);
            
            I2S_Init(I2SS, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SS_IRQn);
            NVIC_EnableIRQ(I2SS_IRQn);
            Verify_messageSend(BRCASE_STOP1,true);
            c_printf("I2S slave\n"); 
        }            
#endif


#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            I2S_InitStru.dirct_type= DATA_TX;
            I2S_InitStru.IntCtlMask.rx_dma_available_interrupt_mask     =  true;
            I2S_InitStru.IntCtlMask.rx_fifo_overrun_interrupt_mask      =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_empty_interrupt_mask        =  true;
            I2S_InitStru.IntCtlMask.tx_fifo_overrun_interrupt_mask      =  true;

            SystemDevClockCtl(I2SM_CKEn,true);
            
            SCU->IO_CONFIG |=0x20;
            I2S_Init(I2SM, &I2S_InitStru);
            NVIC_ClearPendingIRQ(I2SM_IRQn);
            NVIC_EnableIRQ(I2SM_IRQn);
            {
                uint32_t cd=0,va=0;
                // Verify_messageReceive(&cd,&va);
                MRE_TEST: 
                Verify_messageGetRData(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    // sut =false;
                    goto MRE_TEST;
                c_printf("I2S master[%d]\r\n",sut);
                if(sut)   
                     i2sm_SendData();
            }
        }
            
#endif      
#endif    
      
    }
	MCU_Sleep(20);
    c_printf("d_1_775_i2s_i2sm_to_i2ss_pin_17_20_no_config_rx case completed \r\n");
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

void I2SS_IRQHandler(void)      
{     
    c_printf("I2SS_IRQ\n"); 
    if( I2S_GetInterruptStatus(I2SS,I2S_RX_AVAILABLE_DAM))
    {
        c_printf("SRX_ADAM r[%X],l[%X]\n",\
            I2S_GetRightReceiveData(I2SS),\
            I2S_GetLeftReceiveData(I2SS));       
    }
    if( I2S_GetInterruptStatus(I2SS,I2S_RX_FIFO_OVERRUN))
    {
        I2S_ClearRxOverrunInterrupt(I2SS);
        c_printf("RX_OVERRUN\r\n");
    }
    if( I2S_GetInterruptStatus(I2SS,I2S_TX_FIFO_EMPTY))
    {
        {
            I2S_IntCtlMask  IntCtlMask;
            IntCtlMask.rx_dma_available_interrupt_mask    =  false;
            IntCtlMask.rx_fifo_overrun_interrupt_mask     =  true;
            IntCtlMask.tx_fifo_empty_interrupt_mask       =  true;
            IntCtlMask.tx_fifo_overrun_interrupt_mask     =  true;
            I2S_SetInterruptMask(I2SS,&IntCtlMask);
        }
        c_printf("TX_EMPTY\r\n");
    }
    if( I2S_GetInterruptStatus(I2SS,I2S_TX_FIFO_OVERRUN))
    {
        I2S_ClearTxOverrunInterrupt(I2SS);
        c_printf("TX_OVERRUN\r\n");
    }
   
}   


















