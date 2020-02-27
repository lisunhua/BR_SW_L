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
#include "BR00x_ssic.h"
#include "BR00x_spi_flash.h"
#include "verify_message.h"
#include "log_uart_config.h"
#include "qspi_icfg.h"

int main (void)
{
    // LOG UART INIT
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_721_spim0_spim0_tx case \r\n");
    {
        SSIC_InitInfo_Type  SSIC_InitStru ;
  
        memset(&SSIC_InitStru,0,sizeof(SSIC_InitInfo_Type));

        SCUQspiConfig(QSPI_PIN29,QSPI_CLK);
        SCUQspiConfig(QSPI_PIN30,QSPI_CS);
        SCUQspiConfig(QSPI_PIN31,QSPI_D0);
        SCUQspiConfig(QSPI_PIN32,QSPI_D1);
        SCUQspiConfig(QSPI_PIN33,QSPI_D2);
        SCUQspiConfig(QSPI_PIN34,QSPI_D3);

        SSIC_InitStru.clock_divider             = 0x10;

        SSIC_InitStru.frame_format_size         =  SSI_DATA_FRAME_SIZE_8BIT;
        SSIC_InitStru.ssi_frame_format          =  SSI_FRAME_FORMAT_MOTOROLA_SPI ;
        SSIC_InitStru.clock_phase               =  SSI_CLOCK_TOGGLES_MIDDLE ;
        SSIC_InitStru.clock_polarity            =  SSI_INACTIVE_STATE_LOW;
        SSIC_InitStru.transfer_mode             =  SSI_EEPROM_READ;
        SSIC_InitStru.slave_output_enable       =  SSI_SLAVE_TXD_IS_ENABLE;
        SSIC_InitStru.operation_mode            =  SSI_NORMAL_MODE ;
        SSIC_InitStru.slave_select_toggle_en    =  SSIC_SLAVE_SELECT_TOHHLE_DISABLE;
        SSIC_InitStru.control_farme_size        =  SSI_CONTROL_FRAME_1BIT_WORD;
        SSIC_InitStru.spi_frame_format          =  STANDARD_SPI_FORMAT;
        SSIC_InitStru.spi_hyperbus_en           =  SSIC_SPI_HYPERBUS_DISABLE;

        SSIC_InitStru.data_frames_number        = 0;
        SSIC_InitStru.slaves_select             = 1 ;
        SSIC_InitStru.tx_fifo_threshold_level   = 0;
        SSIC_InitStru.tx_fifo_start_fifo_level  = 0;
        SSIC_InitStru.rx_fifo_threshold_level   = 0;
        SSIC_InitStru.dma_rx_data_level         = 0;
        SSIC_InitStru.dma_tx_data_level         = 0;

        SSIC_InitStru.unmask_interrupt = FIFO_MASK_ALL;
        //SystemDevClockCtl(SPIM0_CKEn, ENABLE);
        SystemDevClockCtl(SPIM0_CKEn,true);
        SSIC_Init(&SSIC_InitStru);
        
        c_printf("FLASH id:[%X]",FLASH_ReadManufDeviceId());                       
        {
            uint8_t data[50]={0};
            FLASH_SectorErase(0);
            FLASH_ReadData(0,data,50);
            
            for(uint16_t i=0;i<50;i++)
            {
                if(data[i] !=0xff){
                    c_printf("spim0 Erase false\r\n");
                    break;
                }
            }
            
            for(uint16_t i=0;i<50;i++)
                data[i] = i;
            
            FLASH_PageProgram(0,data,50);
            FLASH_WaitBusy();
            for(uint16_t i=0;i<50;i++)
            {
                if(data[i] !=i){
                    c_printf("spim0 Program false\r\n");
                    break;
                }
            }  
        }    
    }
    c_printf("s_1_721_spim0_spim0_tx case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}















