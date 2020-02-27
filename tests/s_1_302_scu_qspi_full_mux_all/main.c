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

#include "BR00x_uart.h"
#include "BR00x_clock.h"
#include "BR00x_ssi.h"
#include "BR00x_ssic.h"
#include "BR00x_spi_flash.h"
#include "BR00x_timers.h"
#include "BR00x_rtc.h"

#include "qspi_icfg.h"


int main (void)
{
    bool sut = true;
    uint16_t Fid = 0 ;
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_1_302_scu_qspi_full_mux_all case \r\n");

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

			
        FC->CCR=0;
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
        SystemDevClockCtl(SPIM0_CKEn,true);
        SSIC_Init(&SSIC_InitStru);
        Fid = FLASH_ReadManufDeviceId();
        c_printf("FLASH id:[%X]\r\n",Fid);
              
        FLASH_EnableEQI(true);
        {
            uint8_t data[10]={0xba,0xc5,0xda,0xa5,0xaa,0x55,0xaa,0x55,0xaa,0x55};
            FLASH_PageProgram(0,data,10);
            FLASH_WaitBusy();
        }

        SSIC_InitStru.clock_divider             =  0x4;

        SSIC_InitStru.frame_format_size         =  SSI_DATA_FRAME_SIZE_32BIT;
        SSIC_InitStru.ssi_frame_format          =  SSI_FRAME_FORMAT_MOTOROLA_SPI ;
        SSIC_InitStru.clock_phase               =  SSI_CLOCK_TOGGLES_MIDDLE ;
        SSIC_InitStru.clock_polarity            =  SSI_INACTIVE_STATE_LOW;
        SSIC_InitStru.transfer_mode             =  SSI_EEPROM_READ;
        SSIC_InitStru.slave_output_enable       =  SSI_SLAVE_TXD_IS_ENABLE;
        SSIC_InitStru.operation_mode            =  SSI_NORMAL_MODE ;
        SSIC_InitStru.slave_select_toggle_en    =  SSIC_SLAVE_SELECT_TOHHLE_DISABLE;
        SSIC_InitStru.control_farme_size        =  SSI_CONTROL_FRAME_1BIT_WORD;
        SSIC_InitStru.spi_frame_format          =  QUAD_SPI_FORMAT;
        SSIC_InitStru.spi_hyperbus_en           =  SSIC_SPI_HYPERBUS_DISABLE;

        SSIC_InitStru.data_frames_number        =  0;
        SSIC_InitStru.slaves_select             =  1 ;
        SSIC_InitStru.tx_fifo_threshold_level   =  0;
        SSIC_InitStru.tx_fifo_start_fifo_level  =  0;
        SSIC_InitStru.rx_fifo_threshold_level   =  0;
        SSIC_InitStru.dma_rx_data_level         =  0;
        SSIC_InitStru.dma_tx_data_level         =  0;

        SSIC_InitStru.unmask_interrupt          =  FIFO_MASK_ALL;

        SSIC_Init(&SSIC_InitStru);  
        SSIC_XipInitStru.spi_frame_format       = QUAD_SPI_FORMAT;
      
        
        SSIC_XipInitStru.transfer_type          = TT0;
        SSIC_XipInitStru.address_length         = ADDR_L24;
        SSIC_XipInitStru.instruction_length     = INST_L8;
        SSIC_XipInitStru.xip_mode_bit_en        = false;
        SSIC_XipInitStru.wait_cycles            = 0x8; /*Wait cycles in Dual/Quad/Octal mode between control frames transmit and data reception. Specified as number of SPI clock cycles.*/
        SSIC_XipInitStru.xip_dfs_hsize_hburst_en= false;
        SSIC_XipInitStru.xip_spi_ddr_en         = false;
        SSIC_XipInitStru.instruction_ddr_enable = false;
        SSIC_XipInitStru.read_data_strobe_enable= false;
        SSIC_XipInitStru.xip_instruction_enable = true;
        SSIC_XipInitStru.xip_continuous_transfer_enable = true;
        SSIC_XipInitStru.xip_spi_hyerbus_format_enable = false;
        SSIC_XipInitStru.xip_rxds_signaling_enable  = false; /*Enable rxds signaling during address and command phase of Hypebus transfer*/

        SSIC_XipInitStru.xip_mode_bit_length    = MBL_2;
        
        /*Enables XIP pre-fetch functionality in DWC_ssi. Once
        enabled DWC_ssi will pre-fetch data frames from next
        contigous location, to reduce the latency for the upcoming
        contiguous transfer. If the next XIP request is not contigous
        then pre-fetched bits will be discarded.*/
        SSIC_XipInitStru.xip_pre_fetch_enable=false;
        SSIC_XipInitStru.xip_inst_transfer_opcode   = 0x6b;     //QUAD_SPI_FORMAT

        SSIC_XipInitStru.xip_wrap_transfer_opcode   = 0;
        SSIC_XipInitStru.slaves_enbale_mask         = 1;
        SSIC_XipInitStru.spi_clk_stretch_en         = 0;
        SSIC_XipInitStru.spi_data_mask_en           = 0;
        SSIC_XipInitStru.xip_time_out               = 50;
        
        SSIC_XipInit(&SSIC_XipInitStru);
        //FC->CCR=1;
		
//        QspiPin_Type stat_pin  =  ;
        
        for(QspiPin_Type clk= QSPI_PIN29;clk<QSPI_PIN_END;clk++){
        SCUQspiConfig(clk,QSPI_CLK);
        for(QspiPin_Type cs=QSPI_PIN29;cs<QSPI_PIN_END;cs++){
        if(cs !=clk){
        SCUQspiConfig(cs,QSPI_CS);
        for(QspiPin_Type d0=QSPI_PIN29;d0<QSPI_PIN_END;d0++){
        if(d0 != cs  && d0 != clk){
        SCUQspiConfig(d0,QSPI_D0);
        for(QspiPin_Type d1=QSPI_PIN29;d1<QSPI_PIN_END;d1++){
        if(d0 != d1  && d1 != cs  && d1 != clk){
        SCUQspiConfig(d1,QSPI_D1);
        for(QspiPin_Type d2=QSPI_PIN29;d2<QSPI_PIN_END;d2++){
        if(d2 != d0  && d2 != d1  && d2 != cs  && d2 != clk){
        SCUQspiConfig(d2,QSPI_D2);
        for(QspiPin_Type d3=QSPI_PIN29;d3<QSPI_PIN_END;d3++){
        if(d3!=d2 && d3 != d0  && d3 != d1  && d3 != cs  && d3 != clk){
        SCUQspiConfig(d3,QSPI_D3);					
        c_printf("spim0 QSPI:clk[%d],cs[%d],d0[%d],d1[%d],d2[%d],d3[%d]\r\n",clk,cs,d0,d1,d2,d3);
#if  defined(BR002)||defined(BR003)				
						
        {
            volatile uint32_t *addr32   = (uint32_t *)SPI_FLASH_BASE;
            uint32_t data0 = *(addr32+0);
            uint32_t data1 = *(addr32+1);
            c_printf("spim0 XIP:u32[%8X],[%8X]\r\n",data0,data1);
            if(data0 != 0xa5dac5ba || data1 != 0x55aa55aa)
            {
                sut =false;
                c_printf("XIP Full Mux Error");
                goto QSPI_FULLMUXEMD;
            }
        

        }
#endif 
        }}}}}}}}}}}
    }
QSPI_FULLMUXEMD:
	MCU_Sleep(3);
    c_printf("s_1_302_scu_qspi_full_mux_all case completed \r\n");
    SimulationEnd();
    while(1){     
    };
}
















