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
#include "BR00x_ssi.h"
#include "BR00x_ssic.h"
#include "BR00x_ssi_common.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "log_uart_config.h"

int main (void)
{
    bool sut = true;
    LOGUartInit();
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    VerifyDualGetRoleHandler();
    
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);

    c_printf("d_1_734_ssi_spim1_to_spis1_pin_11_14_no_config_rx case \r\n");
    Verrify_SendPinConnect(DUAL_SPI1_11TO14_PIN_EN);
    {
        #if (defined(BR_MASTER) || defined(BR_SLAVE))
        SSI_InitInof_Type SSI_InitStru ;
        PADConfig_Type PAG_InitStru;

        memset(&SSI_InitStru,0 ,sizeof(SSI_InitInof_Type));
        memset(&PAG_InitStru,0 ,sizeof(PADConfig_Type));
        
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif 
        PAG_InitStru.pad_ctl    = PAD_MODE2;
#endif
#ifdef BR_SLAVE
#ifdef BR_DUAL
        if(!GetSocRole())
#endif        
        PAG_InitStru.pad_ctl    = PAD_MODE3;
#endif
        SystemPADConfig(PADID15,&PAG_InitStru);
        SystemPADConfig(PADID16,&PAG_InitStru);
//        SystemPADConfig(PADID17,&PAG_InitStru);
        SystemPADConfig(PADID18,&PAG_InitStru);
        

        SSI_InitStru.clock_divider          = 0x10;
        SSI_InitStru.SSI_frame_format       = SSI_FRAME_FORMAT_MOTOROLA_SPI;
        SSI_InitStru.clock_phase            = SSI_CLOCK_TOGGLES_MIDDLE;
        SSI_InitStru.clock_polarity         = SSI_INACTIVE_STATE_LOW;
        
        SSI_InitStru.slave_output_enable    = SSI_SLAVE_TXD_IS_DISABLE;
        SSI_InitStru.operation_mode         = SSI_NORMAL_MODE;

        SSI_InitStru.control_farme_size     = SSI_CONTROL_FRAME_8BIT_WORD;
        SSI_InitStru.frame_format_size_16   = SSI_DATA_FRAME_SIZE_8BIT;
        /* SSI_InitStru.frame_format_size_32 = SSI_DATA_FRAME_SIZE_8BIT;*/ /* suppout only 16it */

        SSI_InitStru.spi_frame_format       = STANDARD_SPI_FORMAT;
        SSI_InitStru.unmask_interrupt       = RX_FIFO_FULL_UNMASK;
        
        SSI_InitStru.data_frame_num         = 0;             
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif 
        {
            SSI_InitStru.transfer_mode          = SSI_ONLY_TRANSMIT;
            
            SSI_Init(SPIM1 ,&SSI_InitStru);
            {
                uint32_t cd=0,va=0;
                // Verify_messageReceive(&cd,&va);
                MASTER_TEST: 
                Verify_messageGetRData(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    // sut =false;
                    goto MASTER_TEST;
                if(sut)   
                {
                    uint8_t data[8] = {0x69,0x55,0x23,0x89,0x67,0x54};
                    SSI_SendData(SPIM1,&data[0],6);
                    c_printf("spim Send:");
                    for (uint16_t i=0;i<6;i++)
                    {
                        c_printf("%X,",data[i]);
                    }
                    c_printf("\r\n");  
                }
            }
        }
#endif
#ifdef BR_SLAVE 
#ifdef BR_DUAL
        if(!GetSocRole())
#endif 
        {
            SSI_InitStru.unmask_interrupt   = ( TX_FIFO_OVERFLOW_UNMASK|\
                                                RX_FIFO_UNDERFLOW_UNMASK|\
                                                RX_FIFO_OVERFLOW_UNMASK|
                                                RX_FIFO_FULL_UNMASK|
                                                TX_FIFO_MULTI_MASTER_UNMASK|\
                                                XIP_RX_FIFO_OVERFLOW_UNMSAK) ;
            
            SSI_InitStru.data_frame_num             = 0;
            SSI_InitStru.tx_fifo_threshold_level    = 5;
            SSI_InitStru.tx_fifo_start_fifo_level   = 0;
            SSI_InitStru.rx_fifo_threshold_level    = 5;
            SSI_InitStru.transfer_mode              = SSI_ONLY_RECEIVE;
            SSI_Init(SPIS1 ,&SSI_InitStru);
            NVIC_ClearPendingIRQ(SPIS1_IRQn);
            NVIC_EnableIRQ(SPIS1_IRQn);
            c_printf("SPIS1 Ok\n");     
            Verify_messageSend(BRCASE_STOP1,true);        
        }
#endif   
#endif 
    }
	MCU_Sleep(10);
    c_printf("d_1_734_ssi_spim1_to_spis1_pin_11_14_no_config_rx case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}



/***************************************************************
***************************************************************/
void  spi_read_data_test(SSI_TypeDef   *SSIx)
{
    uint16_t rx_num;
    uint8_t data[8];
    
    rx_num = SSI_RX_FIFO_LEVEL(SSIx);
    SSI_ReadData(SSIx,&data[0],rx_num);
    
    c_printf("spi :");
    for (uint16_t i=0;i<rx_num;i++)
    {
        c_printf("%X ,",data[i]);
    }
    c_printf("\r\n");  
}

void spi_write_data_test(SSI_TypeDef   *SSIx)
{
    uint8_t data[8] = {0xaa,0x55,0x23,0x89,0x67,0x54};
    c_printf("ssi send data: ");
    for (uint16_t i=0;i<6;i++)
    {
        c_printf("%X ,",data[i]);
    }
    c_printf("\r\n");  
    
    SSI_SendData(SSIx,&data[0],6);
}

void SPIM1_IRQHandler(void)     
{    
    c_printf("SSIM1:");
    if((SSI_INTERRUPT_STATUS(SPIM1) >> SSI_tx_emty) & 0x01)
    {
        c_printf("SSI_tx_emty\r\n");
    }
    if((SSI_INTERRUPT_STATUS(SPIM1) >> SSI_tx_fifo_overflow) & 0x01)
    {
        c_printf("SSI_tx_fifo_overflow\r\n");
        SSI_ClearTxFifoOverflowInterrupt(SPIM1);
    }
    if((SSI_INTERRUPT_STATUS(SPIM1) >> SSI_rx_underflow) & 0x01)
    {
        c_printf("SSI_rx_underflow\r\n");
        SSI_ClearRxFifoUnderflowInterrupt(SPIM1);   
    }
    if((SSI_INTERRUPT_STATUS(SPIM1) >> SSI_rx_fifo_overflow) & 0x01)
    {
        c_printf("SSI_rx_fifo_overflow\r\n");
        SSI_ClearRxFifoOverflowInterrupt(SPIM1);
    }
    if((SSI_INTERRUPT_STATUS(SPIM1) >> SSI_rx_fifo_full) & 0x01)
    {   
        c_printf("SSI_rx_fifo_full\r\n");
        spi_read_data_test(SPIM1);    
    }
    if((SSI_INTERRUPT_STATUS(SPIM1) >> SSI_multi_master_contention) & 0x01)
    {
        c_printf("SSI_multi_master_contention\r\n");
        SSI_ClearInterrupt(SPIM1);
    }
}   




void SPIS1_IRQHandler(void)     
{    
    c_printf("SSIS1:");
    if((SSI_INTERRUPT_STATUS(SPIS1) >> SSI_tx_emty) & 0x01)
    {
        c_printf("SSI_tx_emty\r\n");
    }
    if((SSI_INTERRUPT_STATUS(SPIS1) >> SSI_tx_fifo_overflow) & 0x01)
    {   
        c_printf("SSI_tx_fifo_overflow\r\n");
        SSI_ClearTxFifoOverflowInterrupt(SPIS1);
    }
    if((SSI_INTERRUPT_STATUS(SPIS1) >> SSI_rx_underflow) & 0x01)
    {
        c_printf("SSI_rx_underflow\r\n");
        SSI_ClearRxFifoUnderflowInterrupt(SPIS1);
    }
    if((SSI_INTERRUPT_STATUS(SPIS1) >> SSI_rx_fifo_overflow) & 0x01)
    {
        c_printf("SSI_rx_fifo_overflow\r\n");
        SSI_ClearRxFifoOverflowInterrupt(SPIS1);
    }
    if((SSI_INTERRUPT_STATUS(SPIS1) >> SSI_rx_fifo_full) & 0x01)
    {
        spi_read_data_test(SPIS1);
        //c_printf("SSI_rx_fifo_full\r\n");
    }
    if((SSI_INTERRUPT_STATUS(SPIS1) >> SSI_multi_master_contention) & 0x01)
    {
        c_printf("SSI_multi_master_contention\r\n");
        SSI_ClearInterrupt(SPIS1);
    }
    //SSI_ClearInterrupt(SPIS1);  
}   


















