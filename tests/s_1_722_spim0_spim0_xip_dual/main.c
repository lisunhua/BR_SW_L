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

#define XIP_QUAD_SPIx

int main (void)
{
    uint16_t Fid = 0 ;
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_722_spim0_spim0_xip_dual case \r\n");
    {
        SSIC_InitInfo_Type  SSIC_InitStru ;
        SSIC_XIP_InitInfo_Type SSIC_XipInitStru;
        PADConfig_Type          PAD_InitStru;

        memset(&SSIC_InitStru,0,sizeof(SSIC_InitInfo_Type));
        memset(&SSIC_XipInitStru,0,sizeof(SSIC_XIP_InitInfo_Type));
        memset(&PAD_InitStru,0,sizeof(PADConfig_Type));

        PAD_InitStru.pad_ctl = PAD_MODE0;
        SystemPADConfig(PADID29,&PAD_InitStru);
        SystemPADConfig(PADID30,&PAD_InitStru);
        SystemPADConfig(PADID31,&PAD_InitStru);
        SystemPADConfig(PADID32,&PAD_InitStru);
        SystemPADConfig(PADID33,&PAD_InitStru);
        SystemPADConfig(PADID34,&PAD_InitStru);

        SCUQspiConfig(QSPI_PIN29,QSPI_CLK);
        SCUQspiConfig(QSPI_PIN30,QSPI_CS);
        SCUQspiConfig(QSPI_PIN31,QSPI_D0);
        SCUQspiConfig(QSPI_PIN32,QSPI_D1);
        SCUQspiConfig(QSPI_PIN33,QSPI_D2);
        SCUQspiConfig(QSPI_PIN34,QSPI_D3);

        SSIC_InitStru.clock_divider             =  0x10;
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

        SSIC_InitStru.unmask_interrupt          = FIFO_MASK_ALL;
        //SystemDevClockCtl(SPIM0_CKEn, ENABLE);
        SystemDevClockCtl(SPIM0_CKEn,true);
        SSIC_Init(&SSIC_InitStru);
        Fid = FLASH_ReadManufDeviceId();
        c_printf("FLASH id:[%X]\r\n",Fid);
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
        }
#ifdef XIP_QUAD_SPI       
        FLASH_EnableEQI(true);
#else
        FLASH_EnableEQI(false);
#endif         
        SSIC_InitStru.clock_divider     = 0x2;

        SSIC_InitStru.frame_format_size         =  SSI_DATA_FRAME_SIZE_32BIT;
        SSIC_InitStru.ssi_frame_format          =  SSI_FRAME_FORMAT_MOTOROLA_SPI ;
        SSIC_InitStru.clock_phase               =  SSI_CLOCK_TOGGLES_MIDDLE ;
        SSIC_InitStru.clock_polarity            =  SSI_INACTIVE_STATE_LOW;
        SSIC_InitStru.transfer_mode             =  SSI_EEPROM_READ;
        SSIC_InitStru.slave_output_enable       =  SSI_SLAVE_TXD_IS_ENABLE;
        SSIC_InitStru.operation_mode            =  SSI_NORMAL_MODE ;
        SSIC_InitStru.slave_select_toggle_en    =  SSIC_SLAVE_SELECT_TOHHLE_DISABLE;
        SSIC_InitStru.control_farme_size        =  SSI_CONTROL_FRAME_1BIT_WORD;
#ifdef XIP_QUAD_SPI
        SSIC_InitStru.spi_frame_format          =  QUAD_SPI_FORMAT;
#else
        SSIC_InitStru.spi_frame_format          =  DUAL_SPI_FORMAT;
#endif
        SSIC_InitStru.spi_hyperbus_en           =  SSIC_SPI_HYPERBUS_DISABLE;

        SSIC_InitStru.data_frames_number        = 0;
        SSIC_InitStru.slaves_select             = 1 ;
        SSIC_InitStru.tx_fifo_threshold_level   = 0;
        SSIC_InitStru.tx_fifo_start_fifo_level  = 0;
        SSIC_InitStru.rx_fifo_threshold_level   = 0;
        SSIC_InitStru.dma_rx_data_level         = 0;
        SSIC_InitStru.dma_tx_data_level         = 0;

        SSIC_InitStru.unmask_interrupt          = FIFO_MASK_ALL;
        //SystemDevClockCtl(SPIM0_CKEn, ENABLE);

        SSIC_Init(&SSIC_InitStru);
        
#ifdef XIP_QUAD_SPI       
        SSIC_XipInitStru.spi_frame_format       = QUAD_SPI_FORMAT;
#else
        SSIC_XipInitStru.spi_frame_format       = DUAL_SPI_FORMAT;
#endif       
        
        SSIC_XipInitStru.transfer_type = TT0;
        SSIC_XipInitStru.address_length = ADDR_L24;
        SSIC_XipInitStru.instruction_length = INST_L8;
        SSIC_XipInitStru.xip_mode_bit_en =false;
        SSIC_XipInitStru.wait_cycles = 0x8; /*Wait cycles in Dual/Quad/Octal mode between control frames transmit and data reception. Specified as number of SPI clock cycles.*/
        SSIC_XipInitStru.xip_dfs_hsize_hburst_en =false;
        SSIC_XipInitStru.xip_spi_ddr_en =false;
        SSIC_XipInitStru.instruction_ddr_enable =false;
        SSIC_XipInitStru.read_data_strobe_enable =false;
        SSIC_XipInitStru.xip_instruction_enable =true;
        SSIC_XipInitStru.xip_continuous_transfer_enable =true;
        SSIC_XipInitStru.xip_spi_hyerbus_format_enable =false;
        SSIC_XipInitStru.xip_rxds_signaling_enable  =false; /*Enable rxds signaling during address and command phase of Hypebus transfer*/

        SSIC_XipInitStru.xip_mode_bit_length = MBL_2;

        /*Enables XIP pre-fetch functionality in DWC_ssi. Once
        enabled DWC_ssi will pre-fetch data frames from next
        contigous location, to reduce the latency for the upcoming
        contiguous transfer. If the next XIP request is not contigous
        then pre-fetched bits will be discarded.*/
        SSIC_XipInitStru.xip_pre_fetch_enable=false;

#ifdef XIP_QUAD_SPI
        SSIC_XipInitStru.xip_inst_transfer_opcode = 0x6b;     //QUAD_SPI_FORMAT
#else
        SSIC_XipInitStru.xip_inst_transfer_opcode = 0x3b;   //DUAL_SPI_FORMAT
#endif
        SSIC_XipInitStru.xip_wrap_transfer_opcode = 0;
        SSIC_XipInitStru.slaves_enbale_mask = 1;
        SSIC_XipInitStru.spi_clk_stretch_en = 0;
        SSIC_XipInitStru.spi_data_mask_en = 0;
        SSIC_XipInitStru.xip_time_out = 50;

        //SystemDevClockCtl(SPIM0_CKEn, ENABLE);
        SSIC_XipInit(&SSIC_XipInitStru);
#if  defined(BR002)||defined(BR003)        
        {
            volatile uint8_t  *addr     = (uint8_t  *)CODE_ROM_BASE;
            volatile uint16_t *addr16   = (uint16_t *)CODE_ROM_BASE;
            volatile uint32_t *addr32   = (uint32_t *)CODE_ROM_BASE;
            c_printf("spim0 ROM:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
                *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);   
        }
        
        {

            volatile uint8_t  *addr     = (uint8_t  *)SPI_FLASH_BASE;
            volatile uint16_t *addr16   = (uint16_t *)SPI_FLASH_BASE;
            volatile uint32_t *addr32   = (uint32_t *)SPI_FLASH_BASE;
                        
            FC->CCR=0;
            for(uint16_t i=0;i<100;i++);
            c_printf("spim0 XIP:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
               *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);
            
            FC->CCR=1;
            for(uint16_t i=0;i<100;i++);
            c_printf("spim0 XIP:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
                *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);      

        }    
#endif        
    }
    c_printf("s_1_722_spim0_spim0_xip_dual case completed \r\n");
	MCU_Sleep(3);
    SimulationEnd();
    while(1){     
    };
}















