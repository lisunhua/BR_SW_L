/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_spi.c
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

#include "cm_printf.h"
#include "verify_slave_spi.h"
#include "verify_message.h"
#include "verify_register_handle.h"

#include "BR00x_config.h"
#include "BR00x_ssic.h"
#include "BR00x_spi_flash.h"


#ifdef SPI_DEBUG_LOG
#define spiprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define spiprf(format, ...)
#endif


const RegisterCell SPIM0_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,   0x000F77DC,     &SPIM0->CTRLR0},
    {true,  true,   2,   0x000000FF,     &SPIM0->CTRLR1},
//    {true,  true,   3,   0x00000001,     &SPIM0->SSIENR},//Enable Bit Cannot set
    {true,  true,   4,   0x00000007,     &SPIM0->MWCR},//SSIC_IS_MASTER == 1 
    {true,  true,   5,   0x00000001,     &SPIM0->SER},//SSIC_NUM_SLAVES == 1
    {true,  true,   6,   0x0000FFFE,     &SPIM0->BAUDR},
    {true,  true,   7,   0x0000001F,     &SPIM0->TXFTLR},// TX_ABW=4
    {true,  true,   8,   0x0000001F,     &SPIM0->RXFTLR},// TX_ABW=4
    {true,  false,  9,   0x0000001F,     (volatile uint32_t*)&SPIM0->TXFLR}, // TX_ABW=4
    {true,  false,  10,  0x0000001F,     (volatile uint32_t*)&SPIM0->RXFLR}, // TX_ABW=4
    {true,  false,  11,  0x0000007F,     (volatile uint32_t*)&SPIM0->SR},
    {true,  true,   12,  0x0000007F,     &SPIM0->IMR},
    {true,  false,  13,  0x0000007F,     (volatile uint32_t*)&SPIM0->ISR},
    {true,  false,  14,  0x0000007F,     (volatile uint32_t*)&SPIM0->RISR},
    //Read Clear Interrupt
    {true,  false,  15,  0x00000001,     (volatile uint32_t*)&SPIM0->TXOICR},
    {true,  false,  16,  0x00000001,     (volatile uint32_t*)&SPIM0->RXOICR},
    {true,  false,  17,  0x00000001,     (volatile uint32_t*)&SPIM0->RXUICR},
    {true,  false,  18,  0x00000001,     (volatile uint32_t*)&SPIM0->MSTICR},
    {true,  false,  19,  0x00000001,     (volatile uint32_t*)&SPIM0->ICR},
    
    {true,  true,   20,  0x00000003,     (volatile uint32_t*)&SPIM0->DMACR},
    {true,  true,   21,  0x0000001F,     &SPIM0->DMATDLR}, // TX_ABW=4
    {true,  true,   22,  0x0000001F,     &SPIM0->DMARDLR}, // TX_ABW=4
    
    {true,  true,   23,  0xFFFFFFFF,     &SPIM0->DR[0]}, // TX_ABW=4
    {true,  true,   24,  0x000000FF,     &SPIM0->RX_SAMPLE_DLY},//SSIC_HAS_RX_SAMPLE_DELAY=1
    
    {true,  true,   25,  0x0000FBBF,     &SPIM0->SPI_CTRLR0},
    
    {true,  true,   26,  0x0000FFFF,     &SPIM0->XIP_INCR_INST},
    {true,  true,   27,  0x0000FFFF,     &SPIM0->XIP_WRAP_INST},
    {true,  true,   28,  0x00C7F6FF,     &SPIM0->XIP_CTRL},
    {true,  true,   29,  0x00000001,     &SPIM0->XIP_SER},
    {true,  false,  30,  0x00000001,     (volatile uint32_t*)&SPIM0->XRXOICR},
    {true,  true,   31,  0x000000FF,     &SPIM0->XIP_CNT_TIME_OUT},
};

const RegisterCell SPIM1_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,   0x0000F3FC,     &SPIM1->CTRLR0},
    {true,  true,   2,   0x000000FF,     &SPIM1->CTRLR1},
//    {true,  true,   3,   0x00000001,     &SPIM1->SSIENR},//Enable Bit Cannot set
    {true,  true,   4,   0x00000007,     &SPIM1->MWCR},//SSIC_IS_MASTER == 1 
    {true,  true,   5,   0x00000001,     &SPIM1->SER},//SSIC_NUM_SLAVES == 1
    {true,  true,   6,   0x0000FFFE,     &SPIM1->BAUDR},
    {true,  true,   7,   0x00000007,     &SPIM1->TXFTLR},// TX_ABW=2
    {true,  true,   8,   0x00000007,     &SPIM1->RXFTLR},// TX_ABW=2
    {true,  false,  9,   0x00000007,     (volatile uint32_t*)&SPIM1->TXFLR}, // TX_ABW=2
    {true,  false,  10,  0x00000007,     (volatile uint32_t*)&SPIM1->RXFLR}, // TX_ABW=2
    {true,  false,  11,  0x00000007,     (volatile uint32_t*)&SPIM1->SR},
    {true,  true,   12,  0x0000003F,     &SPIM1->IMR},
    {true,  false,  13,  0x0000003F,     (volatile uint32_t*)&SPIM1->ISR},
    {true,  false,  14,  0x0000003F,     (volatile uint32_t*)&SPIM1->RISR},
    //Read Clear Interrupt
    {true,  false,  15,  0x00000001,     (volatile uint32_t*)&SPIM1->TXOICR},
    {true,  false,  16,  0x00000001,     (volatile uint32_t*)&SPIM1->RXOICR},
    {true,  false,  17,  0x00000001,     (volatile uint32_t*)&SPIM1->RXUICR},
    {true,  false,  18,  0x00000001,     (volatile uint32_t*)&SPIM1->MSTICR},
    {true,  false,  19,  0x00000001,     (volatile uint32_t*)&SPIM1->ICR},
    
    {true,  true,   20,  0x00000003,     (volatile uint32_t*)&SPIM1->DMACR},
    {true,  true,   21,  0x00000007,     &SPIM1->DMATDLR}, // TX_ABW=2
    {true,  true,   22,  0x00000007,     &SPIM1->DMARDLR}, // TX_ABW=2
    
    {true,  true,   23,  0xFFFFFFFF,     &SPIM1->DR[0]}, // TX_ABW=2
   
};

const RegisterCell SPIS1_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,   0x0000F7FC,     &SPIS1->CTRLR0},
//    {true,  true,   2,   0x000000FF,     &SPIS1->CTRLR1},
//    {true,  true,   3,   0x00000001,     &SPIS1->SSIENR},//Enable Bit Cannot set
//    {true,  true,   4,   0x00000007,     &SPIS1->MWCR},//SSIC_IS_MASTER == 0 
//    {true,  true,   5,   0x00000001,     &SPIS1->SER},//SSIC_NUM_SLAVES == 1
//    {true,  true,   6,   0x0000FFFF,     &SPIS1->BAUDR},
    {true,  true,   7,   0x00000007,     &SPIS1->TXFTLR},// TX_ABW=2
    {true,  true,   8,   0x00000007,     &SPIS1->RXFTLR},// TX_ABW=2
    {true,  false,  9,   0x00000007,     (volatile uint32_t*)&SPIS1->TXFLR}, // TX_ABW=2
    {true,  false,  10,  0x00000007,     (volatile uint32_t*)&SPIS1->RXFLR}, // TX_ABW=2
    {true,  false,  11,  0x00000007,     (volatile uint32_t*)&SPIS1->SR},
    {true,  true,   12,  0x0000001F,     &SPIS1->IMR},
    {true,  false,  13,  0x0000001F,     (volatile uint32_t*)&SPIS1->ISR},
    {true,  false,  14,  0x0000001F,     (volatile uint32_t*)&SPIS1->RISR},
    //Read Clear Interrupt
    {true,  false,  15,  0x00000001,     (volatile uint32_t*)&SPIS1->TXOICR},
    {true,  false,  16,  0x00000001,     (volatile uint32_t*)&SPIS1->RXOICR},
    {true,  false,  17,  0x00000001,     (volatile uint32_t*)&SPIS1->RXUICR},
    {true,  false,  18,  0x00000001,     (volatile uint32_t*)&SPIS1->MSTICR},
    {true,  false,  19,  0x00000001,     (volatile uint32_t*)&SPIS1->ICR},
    
    {true,  true,   20,  0x00000003,     (volatile uint32_t*)&SPIS1->DMACR},
    {true,  true,   21,  0x00000007,     &SPIS1->DMATDLR}, // TX_ABW=2
    {true,  true,   22,  0x00000007,     &SPIS1->DMARDLR}, // TX_ABW=2
    
    {true,  true,   23,  0xFFFFFFFF,     &SPIS1->DR[0]}, // TX_ABW=2
   
};




/***********************************************************
                        Register
************************************************************/
bool cmd_VerifyRegisterSPIM0Case2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    spiprf("spim0 Register case1\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(SPIM0_CKEn,true);
    SPIM0->SSIENR = DISABLE;
    SSI_ClearInterrupt(SPIM0);
    SPIM0->IMR = DISABLE;
    NVIC_ClearPendingIRQ(SPIM0_IRQn);
    
    sut =Verify_RegisterHandle(SPIM0_RegList,sizeof(SPIM0_RegList),idx);

    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyRegisterSPIM1Case2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    spiprf("spim1 Register case1\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(SPIM1_CKEn,true);
    SPIM1->SSIENR = DISABLE;
    sut =Verify_RegisterHandle(SPIM1_RegList,sizeof(SPIM1_RegList),idx);
    
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyRegisterSPIS1Case2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    spiprf("spis1 Register case1\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(SPIS1_CKEn,true);
    SPIS1->SSIENR = DISABLE;
    sut =Verify_RegisterHandle(SPIS1_RegList,sizeof(SPIS1_RegList),idx);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


/***********************************************************
                        APP
************************************************************/

bool cmd_VerifyAppSPIM0Case1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    spiprf("spim0 App case1\r\n");
    verify_SendCid(cmd,&idx);

    {
        SSIC_InitInfo_Type  SSIC_InitStru ;
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

        SSIC_InitStru.data_frames_number =0;
        SSIC_InitStru.slaves_select = 1 ;
        SSIC_InitStru.tx_fifo_threshold_level =0;
        SSIC_InitStru.tx_fifo_start_fifo_level =0;
        SSIC_InitStru.rx_fifo_threshold_level =0;
        SSIC_InitStru.dma_rx_data_level = 0;
        SSIC_InitStru.dma_tx_data_level = 0;

        SSIC_InitStru.unmask_interrupt = FIFO_MASK_ALL;
        //SystemDevClockCtl(SPIM0_CKEn, ENABLE);
        SystemDevClockCtl(SPIM0_CKEn,true);
        SSIC_Init(&SSIC_InitStru);
        
        spiprf("FLASH id:[%X]",FLASH_ReadManufDeviceId());                       
        {
            uint8_t data[50]={0};
            FLASH_SectorErase(0);
            FLASH_ReadData(0,data,50);
            
            for(uint16_t i=0;i<50;i++)
            {
                if(data[i] !=0xff)
                    sut =false;
            }
            
            for(uint16_t i=0;i<50;i++)
                data[i] = i;
            
            FLASH_PageProgram(0,data,50);
            FLASH_WaitBusy();
            for(uint16_t i=0;i<50;i++)
            {
                if(data[i] !=i)
                    sut =false;
            }  
        }    
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


#define XIP_QUAD_SPIx

bool cmd_VerifyAppSPIM0Case2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    uint16_t Fid = 0 ;
    spiprf("spim0 App xip case2\r\n");
    verify_SendCid(cmd,&idx);

    {
        SSIC_InitInfo_Type  SSIC_InitStru ;
        SSIC_XIP_InitInfo_Type SSIC_XipInitStru;
        
        SSIC_InitStru.clock_divider     = 0x10;

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

        SSIC_InitStru.data_frames_number =0;
        SSIC_InitStru.slaves_select = 1 ;
        SSIC_InitStru.tx_fifo_threshold_level =0;
        SSIC_InitStru.tx_fifo_start_fifo_level =0;
        SSIC_InitStru.rx_fifo_threshold_level =0;
        SSIC_InitStru.dma_rx_data_level = 0;
        SSIC_InitStru.dma_tx_data_level = 0;

        SSIC_InitStru.unmask_interrupt = FIFO_MASK_ALL;
        //SystemDevClockCtl(SPIM0_CKEn, ENABLE);
        SystemDevClockCtl(SPIM0_CKEn,true);
        SSIC_Init(&SSIC_InitStru);
        Fid = FLASH_ReadManufDeviceId();
        spiprf("FLASH id:[%X]\r\n",Fid);
        {
            uint8_t data[50]={0};
            FLASH_SectorErase(0);
            FLASH_ReadData(0,data,50);

            for(uint16_t i=0;i<50;i++)
            {
                if(data[i] !=0xff)
                    sut =false;
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

        SSIC_InitStru.data_frames_number =0;
        SSIC_InitStru.slaves_select = 1 ;
        SSIC_InitStru.tx_fifo_threshold_level =0;
        SSIC_InitStru.tx_fifo_start_fifo_level =0;
        SSIC_InitStru.rx_fifo_threshold_level =0;
        SSIC_InitStru.dma_rx_data_level = 0;
        SSIC_InitStru.dma_tx_data_level = 0;

        SSIC_InitStru.unmask_interrupt = FIFO_MASK_ALL;
        //SystemDevClockCtl(SPIM0_CKEn, ENABLE);

        SSIC_Init(&SSIC_InitStru);
        
#ifdef XIP_QUAD_SPI       
        SSIC_XipInitStru.spi_frame_format = QUAD_SPI_FORMAT;
#else
        SSIC_XipInitStru.spi_frame_format = DUAL_SPI_FORMAT;
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
            spiprf("spim0 ROM:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
                *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);   
        }
        
        {

            volatile uint8_t  *addr     = (uint8_t  *)SPI_FLASH_BASE;
            volatile uint16_t *addr16   = (uint16_t *)SPI_FLASH_BASE;
            volatile uint32_t *addr32   = (uint32_t *)SPI_FLASH_BASE;
                        
            FC->CCR=0;
            for(uint16_t i=0;i<100;i++);
            spiprf("spim0 XIP:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
               *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);
            
            FC->CCR=1;
            for(uint16_t i=0;i<100;i++);
            spiprf("spim0 XIP:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
                *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);      

        }    
#endif        
    }
    
    for(uint16_t i=0;i<1000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyAppSPIM0Case3(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint16_t Fid = 0 ;
    uint32_t idx=0;
    spiprf("spim0 App xip case3 \r\n");
    verify_SendCid(cmd,&idx);

    {
        SSIC_InitInfo_Type  SSIC_InitStru ;
        SSIC_XIP_InitInfo_Type SSIC_XipInitStru;
        
        SSIC_InitStru.clock_divider     = 0x10;

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

        SSIC_InitStru.data_frames_number =0;
        SSIC_InitStru.slaves_select = 1 ;
        SSIC_InitStru.tx_fifo_threshold_level =0;
        SSIC_InitStru.tx_fifo_start_fifo_level =0;
        SSIC_InitStru.rx_fifo_threshold_level =0;
        SSIC_InitStru.dma_rx_data_level = 0;
        SSIC_InitStru.dma_tx_data_level = 0;

        SSIC_InitStru.unmask_interrupt = FIFO_MASK_ALL;
        //SystemDevClockCtl(SPIM0_CKEn, ENABLE);
        SystemDevClockCtl(SPIM0_CKEn,true);
        SSIC_Init(&SSIC_InitStru);
        Fid = FLASH_ReadManufDeviceId();
        spiprf("FLASH id:[%X]\r\n",Fid);
        {
            uint8_t data[50]={0};
            FLASH_SectorErase(0);
            FLASH_ReadData(0,data,50);

            for(uint16_t i=0;i<50;i++)
            {
                if(data[i] !=0xff)
                    sut =false;
            }

            for(uint16_t i=0;i<50;i++)
                data[i] = i;

            FLASH_PageProgram(0,data,50);
            FLASH_WaitBusy();
        }
#ifndef XIP_QUAD_SPI       
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
#ifndef XIP_QUAD_SPI
        SSIC_InitStru.spi_frame_format          =  QUAD_SPI_FORMAT;
#else
        SSIC_InitStru.spi_frame_format          =  DUAL_SPI_FORMAT;
#endif
        SSIC_InitStru.spi_hyperbus_en           =  SSIC_SPI_HYPERBUS_DISABLE;

        SSIC_InitStru.data_frames_number =0;
        SSIC_InitStru.slaves_select = 1 ;
        SSIC_InitStru.tx_fifo_threshold_level =0;
        SSIC_InitStru.tx_fifo_start_fifo_level =0;
        SSIC_InitStru.rx_fifo_threshold_level =0;
        SSIC_InitStru.dma_rx_data_level = 0;
        SSIC_InitStru.dma_tx_data_level = 0;

        SSIC_InitStru.unmask_interrupt = FIFO_MASK_ALL;
        //SystemDevClockCtl(SPIM0_CKEn, ENABLE);

        SSIC_Init(&SSIC_InitStru);
        
#ifndef XIP_QUAD_SPI       
        SSIC_XipInitStru.spi_frame_format = QUAD_SPI_FORMAT;
#else
        SSIC_XipInitStru.spi_frame_format = DUAL_SPI_FORMAT;
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

#ifndef XIP_QUAD_SPI
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
        {
#if  defined(BR002)||defined(BR003)
            
            {
                volatile uint8_t  *addr     = (uint8_t  *)CODE_ROM_BASE;
                volatile uint16_t *addr16   = (uint16_t *)CODE_ROM_BASE;
                volatile uint32_t *addr32   = (uint32_t *)CODE_ROM_BASE;
                spiprf("spim0 ROM:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
                    *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);
                
            }
            FC->CCR=0;
            for(uint16_t i=0;i<100;i++){};
                
            {
                volatile uint8_t  *addr     = (uint8_t  *)SPI_FLASH_BASE;
                volatile uint16_t *addr16   = (uint16_t *)SPI_FLASH_BASE;
                volatile uint32_t *addr32   = (uint32_t *)SPI_FLASH_BASE;
            
                spiprf("spim0 XIP:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
                    *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);
            }
            FC->CCR=1;
            for(uint16_t i=0;i<100;i++){};
            {
                volatile uint8_t  *addr     = (uint8_t  *)SPI_FLASH_BASE;
                volatile uint16_t *addr16   = (uint16_t *)SPI_FLASH_BASE;
                volatile uint32_t *addr32   = (uint32_t *)SPI_FLASH_BASE;
            
                spiprf("spim0 XIP:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
                    *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);
            }
             FC->CCR=0x41;
            for(uint16_t i=0;i<100;i++){};
            {
                volatile uint8_t  *addr     = (uint8_t  *)SPI_FLASH_BASE;
                volatile uint16_t *addr16   = (uint16_t *)SPI_FLASH_BASE;
                volatile uint32_t *addr32   = (uint32_t *)SPI_FLASH_BASE;
            
                spiprf("spim0 XIP:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
                    *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);
            }
             FC->CCR=0x61;
            for(uint16_t i=0;i<100;i++){};
            {
                volatile uint8_t  *addr     = (uint8_t  *)SPI_FLASH_BASE;
                volatile uint16_t *addr16   = (uint16_t *)SPI_FLASH_BASE;
                volatile uint32_t *addr32   = (uint32_t *)SPI_FLASH_BASE;
            
                spiprf("spim0 XIP:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
                    *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);
            }
            
#endif
        }        
    }
    
    for(uint16_t i=0;i<1000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyAppSPIM1Case1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    spiprf("spim1 App case1\r\n");
    verify_SendCid(cmd,&idx);

    {
        SSI_InitInof_Type SSI_InitStru ;       
        PADConfig_Type PAG_InitStru;
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID11,&PAG_InitStru);
        SystemPADConfig(PADID12,&PAG_InitStru);
        SystemPADConfig(PADID13,&PAG_InitStru);
        SystemPADConfig(PADID14,&PAG_InitStru);
        
        PAG_InitStru.pad_ctl    = PAD_MODE2;
        
        SystemPADConfig(PADID7,&PAG_InitStru);
        SystemPADConfig(PADID8,&PAG_InitStru);
        SystemPADConfig(PADID9,&PAG_InitStru);
        SystemPADConfig(PADID10,&PAG_InitStru);

        SSI_InitStru.clock_divider          = 0x10;
        SSI_InitStru.SSI_frame_format       = SSI_FRAME_FORMAT_MOTOROLA_SPI;
        SSI_InitStru.clock_phase            = SSI_CLOCK_TOGGLES_MIDDLE;
        SSI_InitStru.clock_polarity         = SSI_INACTIVE_STATE_LOW;
        SSI_InitStru.transfer_mode          = SSI_TRANSMIT_AND_RECEIVE;
        SSI_InitStru.slave_output_enable    = SSI_SLAVE_TXD_IS_DISABLE;
        SSI_InitStru.operation_mode         = SSI_NORMAL_MODE;

        SSI_InitStru.control_farme_size     = SSI_CONTROL_FRAME_8BIT_WORD;
        SSI_InitStru.frame_format_size_16   = SSI_DATA_FRAME_SIZE_8BIT;
        /* SSI_InitStru.frame_format_size_32 = SSI_DATA_FRAME_SIZE_8BIT;*/ /* suppout only 16it */

        SSI_InitStru.spi_frame_format       = STANDARD_SPI_FORMAT;

        SSI_InitStru.data_frame_num         = 6;

        SSI_InitStru.unmask_interrupt       = RX_FIFO_FULL_UNMASK;

        // SSI_InitStru.unmask_interrupt    = (TX_FIFO_OVERFLOW_UNMASK|\
        // RX_FIFO_UNDERFLOW_UNMASK|\
        //RX_FIFO_OVERFLOW_UNMASK|
        // RX_FIFO_FULL_UNMASK|
        // TX_FIFO_MULTI_MASTER_UNMASK|\
        // XIP_RX_FIFO_OVERFLOW_UNMSAK) ;
        SystemDevClockCtl(SPIM1_CKEn,true);
        SSI_Init(SPIM1 ,&SSI_InitStru);
        {
            uint8_t data[8] = {0x69,0x55,0x23,0x89,0x67,0x54};
            SSI_SendData(SPIM1,&data[0],6);
            spiprf("ssi send data: ");
            for (uint16_t i=0;i<6;i++)
            {
                spiprf("%X ,",data[i]);
            }
            spiprf("\r\n");     
        }    
    }
    
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyDualAppSPI1Case1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    spiprf("spim/s1 Dual App case1\r\n");
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);
    
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        SSI_InitInof_Type SSI_InitStru ;
        PADConfig_Type PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif 
        PAG_InitStru.pad_ctl    = PAD_MODE1;
#endif
#ifdef BR_SLAVE
#ifdef BR_DUAL
        if(!GetSocRole())
#endif        
        PAG_InitStru.pad_ctl    = PAD_MODE2;
#endif
        SystemPADConfig(PADID11,&PAG_InitStru);
        SystemPADConfig(PADID12,&PAG_InitStru);
        SystemPADConfig(PADID13,&PAG_InitStru);
        SystemPADConfig(PADID14,&PAG_InitStru);
        

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
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                if(sut)   
                {
                    uint8_t data[8] = {0x69,0x55,0x23,0x89,0x67,0x54};
                    SSI_SendData(SPIM1,&data[0],6);
                    spiprf("spim Send:");
                    for (uint16_t i=0;i<6;i++)
                    {
                        spiprf("%X,",data[i]);
                    }
                    spiprf("\r\n");  
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
            spiprf("SPIS1 Ok\n");     
            Verify_messageSend(BRCASE_STOP1,true);        
        }
#endif   
#endif 

    }
   
    MCU_Sleep(10);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyDualAppSPI1Case2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    spiprf("spim/s1 Dual App 2\r\n");
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        
        SSI_InitInof_Type SSI_InitStru ;
        PADConfig_Type PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_DISABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_DISABLE;
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif 
        PAG_InitStru.pad_ctl    = PAD_MODE1;
#endif
#ifdef BR_SLAVE 
#ifdef BR_DUAL
        if(!GetSocRole())
#endif 
        PAG_InitStru.pad_ctl    = PAD_MODE2;
#endif
        SystemPADConfig(PADID11,&PAG_InitStru);
        SystemPADConfig(PADID12,&PAG_InitStru);
        SystemPADConfig(PADID13,&PAG_InitStru);
        SystemPADConfig(PADID14,&PAG_InitStru);

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
                                                
            SSI_InitStru.transfer_mode              = SSI_ONLY_TRANSMIT;     
            SSI_InitStru.tx_fifo_threshold_level    = 5;
            SSI_InitStru.tx_fifo_start_fifo_level   = 0;
            SSI_InitStru.rx_fifo_threshold_level    = 5;
            
            SSI_Init(SPIS1 ,&SSI_InitStru);
            NVIC_ClearPendingIRQ(SPIS1_IRQn);
            NVIC_EnableIRQ(SPIS1_IRQn);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                if(sut)   
                {
                    uint8_t data[8] = {0x69,0x55,0x23,0x89,0x67,0x54};
                    SSI_SendData(SPIS1,&data[0],6);
                    spiprf("spis Send:");
                    for (uint16_t i=0;i<6;i++)
                    {
                        spiprf("%X,",data[i]);
                    }
                    spiprf("\r\n");     
                    Verify_messageSend(BRCASE_STOP2,true);                 
                }
            }
        }
#endif
#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif 
        {
            SSI_InitStru.unmask_interrupt   = ( TX_FIFO_OVERFLOW_UNMASK|\
                                                RX_FIFO_UNDERFLOW_UNMASK|\
                                                RX_FIFO_OVERFLOW_UNMASK|
                                                RX_FIFO_FULL_UNMASK|
                                                TX_FIFO_MULTI_MASTER_UNMASK|\
                                                XIP_RX_FIFO_OVERFLOW_UNMSAK) ;
            
            SSI_InitStru.tx_fifo_threshold_level    = 5;
            SSI_InitStru.tx_fifo_start_fifo_level   = 0;
            SSI_InitStru.rx_fifo_threshold_level    = 5;
            SSI_InitStru.data_frame_num             = 5;
            SSI_InitStru.transfer_mode              = SSI_ONLY_RECEIVE;
            
            SSI_Init(SPIM1 ,&SSI_InitStru);
            NVIC_ClearPendingIRQ(SPIM1_IRQn);
            NVIC_EnableIRQ(SPIM1_IRQn);
            spiprf("SPIM1 Ok\n");     
            Verify_messageSend(BRCASE_STOP1,true);  
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                if(sut)  
                {
                    spiprf("SPIM1 read\n");  
                    uint8_t data[1]; /* Start Spim1 Read*/
                    SSI_SendData(SPIM1,data,1); 
                }                
            }
        }

#endif
#endif           
    }
    
    MCU_Sleep(10);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyDualAppSPI1Case3(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    spiprf("spim/s1 Dual App 3\r\n");
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);
    {
#if defined(BR_MASTER) || defined(BR_SLAVE)
        SSI_InitInof_Type SSI_InitStru ;
        PADConfig_Type PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_DISABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_DISABLE;
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif 
        PAG_InitStru.pad_ctl    = PAD_MODE1;
#endif
#ifdef BR_SLAVE
#ifdef BR_DUAL
        if(!GetSocRole())
#endif         
        PAG_InitStru.pad_ctl    = PAD_MODE2;
#endif
        SystemPADConfig(PADID11,&PAG_InitStru);
        SystemPADConfig(PADID12,&PAG_InitStru);
        SystemPADConfig(PADID13,&PAG_InitStru);
        SystemPADConfig(PADID14,&PAG_InitStru);

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
        //SSI_InitStru.unmask_interrupt       = RX_FIFO_FULL_UNMASK;
        
        SSI_InitStru.unmask_interrupt   = ( TX_FIFO_OVERFLOW_UNMASK|\
                                            RX_FIFO_UNDERFLOW_UNMASK|\
                                            RX_FIFO_OVERFLOW_UNMASK|
                                            RX_FIFO_FULL_UNMASK|
                                            TX_FIFO_MULTI_MASTER_UNMASK|\
                                            XIP_RX_FIFO_OVERFLOW_UNMSAK) ;
        
        SSI_InitStru.data_frame_num         = 0;
        
        SSI_InitStru.transfer_mode          = SSI_TRANSMIT_AND_RECEIVE;     
        SSI_InitStru.tx_fifo_threshold_level    = 5;
        SSI_InitStru.tx_fifo_start_fifo_level   = 0;
        SSI_InitStru.rx_fifo_threshold_level    = 5;
      
        
#ifdef BR_SLAVE
#ifdef BR_DUAL
        if(!GetSocRole())
#endif 
        {
            SSI_Init(SPIS1 ,&SSI_InitStru);
            NVIC_ClearPendingIRQ(SPIS1_IRQn);
            NVIC_EnableIRQ(SPIS1_IRQn);
            spiprf("SPIS1 Ok\n"); 
            Verify_messageSend(BRCASE_STOP2,true); 
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                if(sut)   
                {
                    uint8_t data[8] = {0x69,0x55,0x23,0x89,0x67,0x54};
                    SSI_SendData(SPIS1,&data[0],6);
                    spiprf("spis Send:");
                    for (uint16_t i=0;i<6;i++)
                    {
                        spiprf("%X,",data[i]);
                    }
                    spiprf("\r\n");                    
                }
            }
        }
#endif
#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif 
        {
            SSI_Init(SPIM1 ,&SSI_InitStru);
            NVIC_ClearPendingIRQ(SPIM1_IRQn);
            NVIC_EnableIRQ(SPIM1_IRQn);
            spiprf("SPIM1 Ok\n");     
            Verify_messageSend(BRCASE_STOP1,true);  
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                if(sut)   
                {
                    uint8_t data[8] = {0x11,0x22,0x33,0x44,0x55,0x66};
                    SSI_SendData(SPIM1,&data[0],6);
                    spiprf("spim Send:");
                    for (uint16_t i=0;i<6;i++)
                    {
                        spiprf("%X,",data[i]);
                    }
                    spiprf("\r\n");                    
                }
            }
        }
#endif   

#endif        
    }
    
    MCU_Sleep(10);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}





bool cmd_VerifyDualAppSPI1Case4(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    spiprf("spim/s1 Dual App case4 PAD Only TX\r\n");
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);
    
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        SSI_InitInof_Type SSI_InitStru ;
        PADConfig_Type PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif 
        PAG_InitStru.pad_ctl    = PAD_MODE1;
#endif
#ifdef BR_SLAVE
#ifdef BR_DUAL
        if(!GetSocRole())
#endif        
        PAG_InitStru.pad_ctl    = PAD_MODE2;
#endif
        SystemPADConfig(PADID11,&PAG_InitStru);
        SystemPADConfig(PADID12,&PAG_InitStru);
//        SystemPADConfig(PADID13,&PAG_InitStru);
        SystemPADConfig(PADID14,&PAG_InitStru);
        

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
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                if(sut)   
                {
                    uint8_t data[8] = {0x69,0x55,0x23,0x89,0x67,0x54};
                    SSI_SendData(SPIM1,&data[0],6);
                    spiprf("spim Send:");
                    for (uint16_t i=0;i<6;i++)
                    {
                        spiprf("%X,",data[i]);
                    }
                    spiprf("\r\n");  
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
            spiprf("SPIS1 Ok\n");     
            Verify_messageSend(BRCASE_STOP1,true);        
        }
#endif   
#endif 

    }
   
    MCU_Sleep(10);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyDualAppSPI1Case5(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    spiprf("spim/s1 Dual App 5 PAD Only RX\r\n");
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        
        SSI_InitInof_Type SSI_InitStru ;
        PADConfig_Type PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_DISABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_DISABLE;
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif 
        PAG_InitStru.pad_ctl    = PAD_MODE1;
#endif
#ifdef BR_SLAVE 
#ifdef BR_DUAL
        if(!GetSocRole())
#endif 
        PAG_InitStru.pad_ctl    = PAD_MODE2;
#endif
        SystemPADConfig(PADID11,&PAG_InitStru);
        SystemPADConfig(PADID12,&PAG_InitStru);
        SystemPADConfig(PADID13,&PAG_InitStru);
//        SystemPADConfig(PADID14,&PAG_InitStru);

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
                                                
            SSI_InitStru.transfer_mode              = SSI_ONLY_TRANSMIT;     
            SSI_InitStru.tx_fifo_threshold_level    = 5;
            SSI_InitStru.tx_fifo_start_fifo_level   = 0;
            SSI_InitStru.rx_fifo_threshold_level    = 5;
            
            SSI_Init(SPIS1 ,&SSI_InitStru);
            NVIC_ClearPendingIRQ(SPIS1_IRQn);
            NVIC_EnableIRQ(SPIS1_IRQn);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                if(sut)   
                {
                    uint8_t data[8] = {0x69,0x55,0x23,0x89,0x67,0x54};
                    SSI_SendData(SPIS1,&data[0],6);
                    spiprf("spis Send:");
                    for (uint16_t i=0;i<6;i++)
                    {
                        spiprf("%X,",data[i]);
                    }
                    spiprf("\r\n");     
                    Verify_messageSend(BRCASE_STOP2,true);                 
                }
            }
        }
#endif
#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif 
        {
            SSI_InitStru.unmask_interrupt   = ( TX_FIFO_OVERFLOW_UNMASK|\
                                                RX_FIFO_UNDERFLOW_UNMASK|\
                                                RX_FIFO_OVERFLOW_UNMASK|
                                                RX_FIFO_FULL_UNMASK|
                                                TX_FIFO_MULTI_MASTER_UNMASK|\
                                                XIP_RX_FIFO_OVERFLOW_UNMSAK) ;
            
            SSI_InitStru.tx_fifo_threshold_level    = 5;
            SSI_InitStru.tx_fifo_start_fifo_level   = 0;
            SSI_InitStru.rx_fifo_threshold_level    = 5;
            SSI_InitStru.data_frame_num             = 5;
            SSI_InitStru.transfer_mode              = SSI_ONLY_RECEIVE;
            
            SSI_Init(SPIM1 ,&SSI_InitStru);
            NVIC_ClearPendingIRQ(SPIM1_IRQn);
            NVIC_EnableIRQ(SPIM1_IRQn);
            spiprf("SPIM1 Ok\n");     
            Verify_messageSend(BRCASE_STOP1,true);  
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                if(sut)  
                {
                    spiprf("SPIM1 read\n");  
                    uint8_t data[1]; /* Start Spim1 Read*/
                    SSI_SendData(SPIM1,data,1); 
                }                
            }
        }

#endif
#endif           
    }
    
    MCU_Sleep(10);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyDualAppSPI1Case6(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    spiprf("spim/s1 Dual App case6 PAD Only TX\r\n");
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);
    
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        SSI_InitInof_Type SSI_InitStru ;
        PADConfig_Type PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
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
        PAG_InitStru.pad_ctl    = PAD_MODE1;
#endif
        SystemPADConfig(PADID7,&PAG_InitStru);
        SystemPADConfig(PADID8,&PAG_InitStru);
//        SystemPADConfig(PADID9,&PAG_InitStru);
        SystemPADConfig(PADID10,&PAG_InitStru);
        

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
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                if(sut)   
                {
                    uint8_t data[8] = {0x69,0x55,0x23,0x89,0x67,0x54};
                    SSI_SendData(SPIM1,&data[0],6);
                    spiprf("spim Send:");
                    for (uint16_t i=0;i<6;i++)
                    {
                        spiprf("%X,",data[i]);
                    }
                    spiprf("\r\n");  
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
            spiprf("SPIS1 Ok\n");     
            Verify_messageSend(BRCASE_STOP1,true);        
        }
#endif   
#endif 

    }
   
    MCU_Sleep(10);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyDualAppSPI1Case7(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    spiprf("spim/s1 Dual App 7 PAD Only RX\r\n");
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);
    {
#if (defined(BR_MASTER) || defined(BR_SLAVE))
        
        SSI_InitInof_Type SSI_InitStru ;
        PADConfig_Type PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_DISABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_DISABLE;
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
        PAG_InitStru.pad_ctl    = PAD_MODE1;
#endif
        SystemPADConfig(PADID7,&PAG_InitStru);
        SystemPADConfig(PADID8,&PAG_InitStru);
        SystemPADConfig(PADID9,&PAG_InitStru);
//        SystemPADConfig(PADID10,&PAG_InitStru);

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
                                                
            SSI_InitStru.transfer_mode              = SSI_ONLY_TRANSMIT;     
            SSI_InitStru.tx_fifo_threshold_level    = 5;
            SSI_InitStru.tx_fifo_start_fifo_level   = 0;
            SSI_InitStru.rx_fifo_threshold_level    = 5;
            
            SSI_Init(SPIS1 ,&SSI_InitStru);
            NVIC_ClearPendingIRQ(SPIS1_IRQn);
            NVIC_EnableIRQ(SPIS1_IRQn);
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                if(sut)   
                {
                    uint8_t data[8] = {0x69,0x55,0x23,0x89,0x67,0x54};
                    SSI_SendData(SPIS1,&data[0],6);
                    spiprf("spis Send:");
                    for (uint16_t i=0;i<6;i++)
                    {
                        spiprf("%X,",data[i]);
                    }
                    spiprf("\r\n");     
                    Verify_messageSend(BRCASE_STOP2,true);                 
                }
            }
        }
#endif
#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif 
        {
            SSI_InitStru.unmask_interrupt   = ( TX_FIFO_OVERFLOW_UNMASK|\
                                                RX_FIFO_UNDERFLOW_UNMASK|\
                                                RX_FIFO_OVERFLOW_UNMASK|
                                                RX_FIFO_FULL_UNMASK|
                                                TX_FIFO_MULTI_MASTER_UNMASK|\
                                                XIP_RX_FIFO_OVERFLOW_UNMSAK) ;
            
            SSI_InitStru.tx_fifo_threshold_level    = 5;
            SSI_InitStru.tx_fifo_start_fifo_level   = 0;
            SSI_InitStru.rx_fifo_threshold_level    = 5;
            SSI_InitStru.data_frame_num             = 5;
            SSI_InitStru.transfer_mode              = SSI_ONLY_RECEIVE;
            
            SSI_Init(SPIM1 ,&SSI_InitStru);
            NVIC_ClearPendingIRQ(SPIM1_IRQn);
            NVIC_EnableIRQ(SPIM1_IRQn);
            spiprf("SPIM1 Ok\n");     
            Verify_messageSend(BRCASE_STOP1,true);  
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                if(sut)  
                {
                    spiprf("SPIM1 read\n");  
                    uint8_t data[1]; /* Start Spim1 Read*/
                    SSI_SendData(SPIM1,data,1); 
                }                
            }
        }

#endif
#endif           
    }
    
    MCU_Sleep(10);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyDualAppSPI1Case8(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    spiprf("spim/s1 Dual App 8\r\n");
    SystemDevClockCtl(SPIM1_CKEn,true);
    SystemDevClockCtl(SPIS1_CKEn,true);
    {
#if defined(BR_MASTER) || defined(BR_SLAVE)
        SSI_InitInof_Type SSI_InitStru ;
        PADConfig_Type PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_DISABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_DISABLE;
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
        PAG_InitStru.pad_ctl    = PAD_MODE1;
#endif
        SystemPADConfig(PADID7,&PAG_InitStru);
        SystemPADConfig(PADID8,&PAG_InitStru);
        SystemPADConfig(PADID9,&PAG_InitStru);
        SystemPADConfig(PADID10,&PAG_InitStru);

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
        //SSI_InitStru.unmask_interrupt       = RX_FIFO_FULL_UNMASK;
        
        SSI_InitStru.unmask_interrupt   = ( TX_FIFO_OVERFLOW_UNMASK|\
                                            RX_FIFO_UNDERFLOW_UNMASK|\
                                            RX_FIFO_OVERFLOW_UNMASK|
                                            RX_FIFO_FULL_UNMASK|
                                            TX_FIFO_MULTI_MASTER_UNMASK|\
                                            XIP_RX_FIFO_OVERFLOW_UNMSAK) ;
        
        SSI_InitStru.data_frame_num         = 0;
        
        SSI_InitStru.transfer_mode          = SSI_TRANSMIT_AND_RECEIVE;     
        SSI_InitStru.tx_fifo_threshold_level    = 5;
        SSI_InitStru.tx_fifo_start_fifo_level   = 0;
        SSI_InitStru.rx_fifo_threshold_level    = 5;
      
        
#ifdef BR_SLAVE
#ifdef BR_DUAL
        if(!GetSocRole())
#endif 
        {
            SSI_Init(SPIS1 ,&SSI_InitStru);
            NVIC_ClearPendingIRQ(SPIS1_IRQn);
            NVIC_EnableIRQ(SPIS1_IRQn);
            spiprf("SPIS1 Ok\n"); 
            Verify_messageSend(BRCASE_STOP2,true); 
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                if(sut)   
                {
                    uint8_t data[8] = {0x69,0x55,0x23,0x89,0x67,0x54};
                    SSI_SendData(SPIS1,&data[0],6);
                    spiprf("spis Send:");
                    for (uint16_t i=0;i<6;i++)
                    {
                        spiprf("%X,",data[i]);
                    }
                    spiprf("\r\n");                    
                }
            }
        }
#endif
#ifdef BR_MASTER 
#ifdef BR_DUAL
        if(GetSocRole())
#endif 
        {
            SSI_Init(SPIM1 ,&SSI_InitStru);
            NVIC_ClearPendingIRQ(SPIM1_IRQn);
            NVIC_EnableIRQ(SPIM1_IRQn);
            spiprf("SPIM1 Ok\n");     
            Verify_messageSend(BRCASE_STOP1,true);  
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                if(sut)   
                {
                    uint8_t data[8] = {0x11,0x22,0x33,0x44,0x55,0x66};
                    SSI_SendData(SPIM1,&data[0],6);
                    spiprf("spim Send:");
                    for (uint16_t i=0;i<6;i++)
                    {
                        spiprf("%X,",data[i]);
                    }
                    spiprf("\r\n");                    
                }
            }
        }
#endif   

#endif        
    }
    
    MCU_Sleep(10);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}




/***************************************************************
***************************************************************/
void  spi_read_data_test(SSI_TypeDef   *SSIx)
{
    uint16_t rx_num;
    uint8_t data[8];
    
    rx_num = SSI_RX_FIFO_LEVEL(SSIx);
    SSI_ReadData(SSIx,&data[0],rx_num);
    
    spiprf("spi :");
    for (uint16_t i=0;i<rx_num;i++)
    {
        spiprf("%X ,",data[i]);
    }
    spiprf("\r\n");  
}

void spi_write_data_test(SSI_TypeDef   *SSIx)
{
    uint8_t data[8] = {0xaa,0x55,0x23,0x89,0x67,0x54};
    spiprf("ssi send data: ");
    for (uint16_t i=0;i<6;i++)
    {
        spiprf("%X ,",data[i]);
    }
    spiprf("\r\n");  
    
    SSI_SendData(SSIx,&data[0],6);
}

void SPIM1_IRQHandler(void)     
{    
    spiprf("SSIM1:");
    if((SSI_INTERRUPT_STATUS(SPIM1) >> SSI_tx_emty) & 0x01)
    {
        spiprf("SSI_tx_emty\r\n");
    }
    if((SSI_INTERRUPT_STATUS(SPIM1) >> SSI_tx_fifo_overflow) & 0x01)
    {
        spiprf("SSI_tx_fifo_overflow\r\n");
        SSI_ClearTxFifoOverflowInterrupt(SPIM1);
    }
    if((SSI_INTERRUPT_STATUS(SPIM1) >> SSI_rx_underflow) & 0x01)
    {
        spiprf("SSI_rx_underflow\r\n");
        SSI_ClearRxFifoUnderflowInterrupt(SPIM1);   
    }
    if((SSI_INTERRUPT_STATUS(SPIM1) >> SSI_rx_fifo_overflow) & 0x01)
    {
        spiprf("SSI_rx_fifo_overflow\r\n");
        SSI_ClearRxFifoOverflowInterrupt(SPIM1);
    }
    if((SSI_INTERRUPT_STATUS(SPIM1) >> SSI_rx_fifo_full) & 0x01)
    {   
        spiprf("SSI_rx_fifo_full\r\n");
        spi_read_data_test(SPIM1);    
    }
    if((SSI_INTERRUPT_STATUS(SPIM1) >> SSI_multi_master_contention) & 0x01)
    {
        spiprf("SSI_multi_master_contention\r\n");
        SSI_ClearInterrupt(SPIM1);
    }
}   




void SPIS1_IRQHandler(void)     
{    
    spiprf("SSIS1:");
    if((SSI_INTERRUPT_STATUS(SPIS1) >> SSI_tx_emty) & 0x01)
    {
        spiprf("SSI_tx_emty\r\n");
    }
    if((SSI_INTERRUPT_STATUS(SPIS1) >> SSI_tx_fifo_overflow) & 0x01)
    {   
        spiprf("SSI_tx_fifo_overflow\r\n");
        SSI_ClearTxFifoOverflowInterrupt(SPIS1);
    }
    if((SSI_INTERRUPT_STATUS(SPIS1) >> SSI_rx_underflow) & 0x01)
    {
        spiprf("SSI_rx_underflow\r\n");
        SSI_ClearRxFifoUnderflowInterrupt(SPIS1);
    }
    if((SSI_INTERRUPT_STATUS(SPIS1) >> SSI_rx_fifo_overflow) & 0x01)
    {
        spiprf("SSI_rx_fifo_overflow\r\n");
        SSI_ClearRxFifoOverflowInterrupt(SPIS1);
    }
    if((SSI_INTERRUPT_STATUS(SPIS1) >> SSI_rx_fifo_full) & 0x01)
    {
        spi_read_data_test(SPIS1);
        //spiprf("SSI_rx_fifo_full\r\n");
    }
    if((SSI_INTERRUPT_STATUS(SPIS1) >> SSI_multi_master_contention) & 0x01)
    {
        spiprf("SSI_multi_master_contention\r\n");
        SSI_ClearInterrupt(SPIS1);
    }
    //SSI_ClearInterrupt(SPIS1);  
}   





