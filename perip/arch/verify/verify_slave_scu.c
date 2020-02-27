/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_scu.c
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
#include "verify_slave_scu.h"
#include "verify_message.h"
#include "verify_register_handle.h"
#include "BR00x_config.h"

#include "BR00x_uart.h"
#include "BR00x_clock.h"
#include "BR00x_ssi.h"
#include "BR00x_ssic.h"
#include "BR00x_spi_flash.h"
#include "BR00x_timers.h"
#include "BR00x_rtc.h"

#include "qspi_icfg.h"

#if  defined(BR002)||defined(BR003)
#include "BR00x_rom.h"
#endif

#ifdef SCU_DEBUG_LOG
#define scuprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define scuprf(format, ...)
#endif

#if  defined(BR002)||defined(BR003)
  
const RegisterCell SCU_RegList[]=
{
  
//  {read,  write,  Register ID ,register_attr, Register},
  //{true,  true,   1,   0xFFFFFFFF,     &SCU->CLK_EN},//Reserved
    {true,  true,   2,   0xFFFFFFEE,     &SCU->SW_RST}, //bit[0] Reset SCU Cannot Set 
    {true,  true,   3,   0x1FE1FFFF,     &SCU->CLK_CTL},
    {true,  true,   4,   0xFFFFFFFF,     &SCU->CLK_DIV},
//    {true,  true,   5,   0xFFFFFFFF,     &SCU->SYS_CONFIG},
    {true,  false,  6,   0xFFFFFFFF,     (volatile uint32_t*)&SCU->SYS_STATUS},
    {true,  true,   7,   0xFFFFFFFF,     &SCU->SLEEP_EN},
    {true,  false,  8,   0xFFFFFFFF,     (volatile uint32_t*)&SCU->PWR_STATUS},
    {true,  true,   9,   0xFFFFFFFF,     &SCU->DEV_CONFIG},
    {true,  false,  10,  0xFFFFFFFF,     (volatile uint32_t*)&SCU->DEV_STATUS},
    {true,  true,   11,  0xFFFFFFFF,     &SCU->IO_CONFIG},
    {true,  false,  12,  0xFFFFFFFF,     (volatile uint32_t*)&SCU->IO_STATUS},
    {true,  true,   13,  0xFFFFFFFF,     &SCU->CLK_DIV1},
    {true,  true,   14,  0xFFFFFFFF,     &SCU->CLK_DIV2},
    
    {true,  true,   15,  0xFFFFFFFF,     &SCU->ANA_CTL0},
    {true,  true,   16,  0xFFFFFFFF,     &SCU->ANA_CTL1},
    {true,  true,   17,  0xFFFFFFFF,     &SCU->ANA_CTL2},
    {true,  true,   18,  0xFFFFFFFF,     &SCU->ANA_CTL3},
    {true,  true,   19,  0xFFFFFFFF,     &SCU->ANA_CTL4},
    {true,  false,  20,  0xFFFFFFFF,     (volatile uint32_t*)&SCU->ANA_STATUS0},
    {true,  false,  21,  0xFFFFFFFF,     (volatile uint32_t*)&SCU->ANA_STATUS1},
    
    {true,  true,  22,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[0]},
    {true,  true,  23,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[1]},
    {true,  true,  24,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[2]},
    {true,  true,  25,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[3]},
    {true,  true,  26,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[4]},
    {true,  true,  27,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[5]},
    {true,  true,  28,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[6]},
    {true,  true,  29,  0x0000FFFF,     (volatile uint32_t*)&SCU->TIMERS_DIV[7]},
  #if 0 
    {true,  true,  26,  0x0000003F,     &SCU->PAD_CFG[0]},
    {true,  true,  27,  0x0000003F,     &SCU->PAD_CFG[1]},
    {true,  true,  28,  0x0000003F,     &SCU->PAD_CFG[2]},
    {true,  true,  29,  0x0000003F,     &SCU->PAD_CFG[3]},
    {true,  true,  30,  0x0000003F,     &SCU->PAD_CFG[4]},
    {true,  true,  31,  0x0000003F,     &SCU->PAD_CFG[5]},
    {true,  true,  32,  0x0000003F,     &SCU->PAD_CFG[6]},
    {true,  true,  33,  0x0000003F,     &SCU->PAD_CFG[7]},
    {true,  true,  34,  0x0000003F,     &SCU->PAD_CFG[8]},
    {true,  true,  35,  0x0000003F,     &SCU->PAD_CFG[9]},
    {true,  true,  36,  0x0000003F,     &SCU->PAD_CFG[10]},
    {true,  true,  37,  0x0000003F,     &SCU->PAD_CFG[11]},
    {true,  true,  38,  0x0000003F,     &SCU->PAD_CFG[12]},
    {true,  true,  39,  0x0000003F,     &SCU->PAD_CFG[13]},
    {true,  true,  40,  0x0000003F,     &SCU->PAD_CFG[14]},
    {true,  true,  41,  0x0000003F,     &SCU->PAD_CFG[15]},
    {true,  true,  42,  0x0000003F,     &SCU->PAD_CFG[16]},
    {true,  true,  43,  0x0000003F,     &SCU->PAD_CFG[17]},
    {true,  true,  44,  0x0000003F,     &SCU->PAD_CFG[18]},
    {true,  true,  45,  0x0000003F,     &SCU->PAD_CFG[19]},
    {true,  true,  46,  0x0000003F,     &SCU->PAD_CFG[20]},
    {true,  true,  47,  0x0000003F,     &SCU->PAD_CFG[21]},
    {true,  true,  48,  0x0000003F,     &SCU->PAD_CFG[22]},
    {true,  true,  49,  0x0000003F,     &SCU->PAD_CFG[23]},
    {true,  true,  50,  0x0000003F,     &SCU->PAD_CFG[24]},
    {true,  true,  51,  0x0000003F,     &SCU->PAD_CFG[25]},
    {true,  true,  52,  0x0000003F,     &SCU->PAD_CFG[26]},
    {true,  true,  53,  0x0000003F,     &SCU->PAD_CFG[27]},
    {true,  true,  54,  0x0000003F,     &SCU->PAD_CFG[28]},
    {true,  true,  55,  0x0000003F,     &SCU->PAD_CFG[29]},
    {true,  true,  56,  0x0000003F,     &SCU->PAD_CFG[30]},
    {true,  true,  57,  0x0000003F,     &SCU->PAD_CFG[31]},
    {true,  true,  58,  0x0000003F,     &SCU->PAD_CFG[32]},
    {true,  true,  59,  0x0000003F,     &SCU->PAD_CFG[33]},
    {true,  true,  60,  0x0000003F,     &SCU->PAD_CFG[34]},
    {true,  true,  61,  0x0000003F,     &SCU->PAD_CFG[35]},
    {true,  true,  62,  0x0000003F,     &SCU->PAD_CFG[36]},
    {true,  true,  63,  0x0000003F,     &SCU->PAD_CFG[37]},
    {true,  true,  64,  0x0000003F,     &SCU->PAD_CFG[38]},
    {true,  true,  65,  0x0000003F,     &SCU->PAD_CFG[39]},
    
#endif

};



/***********************************************************
                        Register
************************************************************/
bool cmd_VerifyRegisterSCUCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    scuprf("scu Register case1\r\n");
    verify_SendCid(cmd,&idx);

//scu->clk_en
//scu->sw_rst
//
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&WDT->CR,0x1e);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&WDT->CR);
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyRegisterSCUCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    scuprf("SCU Reg case2\r\n");
    verify_SendCid(cmd,&idx);
    sut =Verify_RegisterHandle(SCU_RegList,sizeof(SCU_RegList),idx);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;

}



/***********************************************************
                        APP
************************************************************/


void UartSCUOutput(void)
{
#ifdef  DEBUG_LOG
    UART_InitInfo_Type UART_InitStru;
    UART_InitStru.UART_BaudRate             = 500000;
    UART_InitStru.UART_WordLength           = UART_WL_8BITS;
    UART_InitStru.UART_StopBits             = UART_SB_1BIT;
    UART_InitStru.UART_ParityMode           = UART_PM_NONE;
    UART_InitStru.UART_HardwareFlowControl  = UART_FC_NONE;
    UART_InitStru.UART_FIFOMode             = UART_FM_ENABLE;
    UART_InitStru.UART_DMAMode              = UART_DM_MODE_0;
    UART_InitStru.UART_TX_FIFOTriggerMode   = UART_TT_EMPTY;
    UART_InitStru.UART_RX_FIFOTriggerMode   = UART_RT_1_CHARACTER;
     
    UART_Init(UART0, &UART_InitStru); 
    UART_InterruptSet(UART0,0x01ul<<UART_ERBFI);
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);
#endif  

}

static void verifyCheckScu(uint32_t idx,__IO uint32_t *reg,uint32_t val)
{
        
    *reg = val;
    SCU->SW_RST |=0x01<<idx;
    scuprf("SCU Reset:%d ",idx);
    if(*reg==val)
        scuprf(" False \n");
    else
        scuprf(" true \n");
        
        
}

bool cmd_VerifyAppSCUCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    scuprf("SCU  App Reset Test case1\r\n");
    verify_SendCid(cmd,&idx);
    SCU->CLK_EN= 0XFFFFFFFF;
    {

        SCU->CLK_DIV = 0x005500aa;
        while(UART_GetStatus(UART0)& 0x01);
        SCU->SW_RST |=0x01<<0;
        for(uint16_t i=0;i<100;i++);
        scuprf("SCU Reset:%d ",idx);
        SCU->CLK_EN= 0xFFFFFFFF;
        if(SCU->CLK_DIV ==0x005500aa)
            scuprf(" False \n");
        else
            scuprf(" true \n");
        
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
            scuprf("\r\nReset UART0 [%s]\r\n",u0Ret? "true" : "false");
        }
        
        verifyCheckScu(5,&UART1->DLF,0xe);
        
        SPIM1->SSIENR = DISABLE;
        SPIM1->IMR = DISABLE;
        verifyCheckScu(6,&SPIM1->BAUDR,0x80);
        scuprf("Reset SPIM1:[%X]",SPIM1->BAUDR);

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
//        verifyCheckScu(13,&rf,0x1234);

        verifyCheckScu(14,&BB->BB_CTL[0],0x005500aa);
        verifyCheckScu(15,&BB->BB_CTL[2],0x005500aa);

        verifyCheckScu(16,&DMA->CHR[0].SAR,0x123);
       
        SPIM0->SSIENR = DISABLE;
        SPIM0->IMR = DISABLE;
        verifyCheckScu(17,&SPIM0->BAUDR,0x80);    
        verifyCheckScu(19,&USB->GUSBCFG,1);

        verifyCheckScu(21,&TIMERS->TIMER[0].LOAD_COUNT,0x3654);
        verifyCheckScu(22,&TIMERS->TIMER[1].LOAD_COUNT,0x3654);
        verifyCheckScu(23,&TIMERS->TIMER[2].LOAD_COUNT,0x3654);
        verifyCheckScu(24,&TIMERS->TIMER[3].LOAD_COUNT,0x3654);
        verifyCheckScu(25,&TIMERS->TIMER[4].LOAD_COUNT,0x3654);
        verifyCheckScu(26,&TIMERS->TIMER[5].LOAD_COUNT,0x3654);
        verifyCheckScu(27,&TIMERS->TIMER[6].LOAD_COUNT,0x3654);
        verifyCheckScu(28,&TIMERS->TIMER[7].LOAD_COUNT,0x3654);    
        verifyCheckScu(29,&BB->BB_CTL[1],0x1111a);    
        verifyCheckScu(30,&GPIO->DR0,0x45643);    
    }
    MCU_Sleep(3);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



#define XIP_QUID

bool cmd_VerifyAppSCUCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    uint32_t Fid=0;
    SCU_SPIM0ClkSelect(CLK_SPIM0_104M);
    MCU_Sleep(1);
    scuprf("SCU  App Remap FLASH Test case2\r\n");
    verify_SendCid(cmd,&idx);
    {
        SSIC_InitInfo_Type  SSIC_InitStru ;
        SSIC_XIP_InitInfo_Type SSIC_XipInitStru;
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
        SSIC_InitStru.slaves_select             = 1;
        SSIC_InitStru.tx_fifo_threshold_level   = 0;
        SSIC_InitStru.tx_fifo_start_fifo_level  = 0;
        SSIC_InitStru.rx_fifo_threshold_level   = 0;
        SSIC_InitStru.dma_rx_data_level         = 0;
        SSIC_InitStru.dma_tx_data_level         = 0;

        SSIC_InitStru.unmask_interrupt          = FIFO_MASK_ALL;
        
        
        SystemDevClockCtl(SPIM0_CKEn,true);
        SSIC_Init(&SSIC_InitStru);
        
        Fid = FLASH_ReadManufDeviceId();
        SSIC_InitStru.clock_divider             =  0x6;
        scuprf("SCU Fid:[%X],%d\r\n",Fid,SSIC_InitStru.clock_divider);
#ifdef XIP_QUID           
        FLASH_EnableEQI(true); 
        scuprf("SCU quid Fid:[%X],%d\r\n",Fid,SSIC_InitStru.clock_divider );
#else
        FLASH_EnableEQI(false); 
        scuprf("SCU dual Fid:[%X],%d\r\n",Fid,SSIC_InitStru.clock_divider );
#endif       
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
 #ifdef XIP_QUID        
        SSIC_XipInitStru.spi_frame_format               = QUAD_SPI_FORMAT;
 #else
        SSIC_XipInitStru.spi_frame_format               = DUAL_SPI_FORMAT;
 #endif
        SSIC_XipInitStru.transfer_type                  = TT0;
        SSIC_XipInitStru.address_length                 = ADDR_L24;
        SSIC_XipInitStru.instruction_length             = INST_L8;
        SSIC_XipInitStru.wait_cycles                    = 0x8; /*Wait cycles in Dual/Quad/Octal mode between control frames transmit and data reception. Specified as number of SPI clock cycles.*/
        SSIC_XipInitStru.xip_mode_bit_en                = false;
        SSIC_XipInitStru.xip_dfs_hsize_hburst_en        = false;
        SSIC_XipInitStru.xip_spi_ddr_en                 = false;
        SSIC_XipInitStru.instruction_ddr_enable         = false;
        SSIC_XipInitStru.read_data_strobe_enable        = false;
        SSIC_XipInitStru.xip_instruction_enable         = true;
        SSIC_XipInitStru.xip_continuous_transfer_enable = true;
        SSIC_XipInitStru.xip_spi_hyerbus_format_enable  = false;
        SSIC_XipInitStru.xip_rxds_signaling_enable      = false; /*Enable rxds signaling during address and command phase of Hypebus transfer*/

        SSIC_XipInitStru.xip_mode_bit_length            = MBL_2;

        /*Enables XIP pre-fetch functionality in DWC_ssi. Once
        enabled DWC_ssi will pre-fetch data frames from next
        contigous location, to reduce the latency for the upcoming
        contiguous transfer. If the next XIP request is not contigous
        then pre-fetched bits will be discarded.*/
        SSIC_XipInitStru.xip_pre_fetch_enable           = false;
      
#ifdef XIP_QUID        
        SSIC_XipInitStru.xip_inst_transfer_opcode       = 0x6b;     //QUAD_SPI_FORMAT
#else
        SSIC_XipInitStru.xip_inst_transfer_opcode       = 0x3b;     //
#endif

        SSIC_XipInitStru.xip_wrap_transfer_opcode       = 0;
        SSIC_XipInitStru.slaves_enbale_mask             = 1;
        SSIC_XipInitStru.spi_clk_stretch_en             = 0;
        SSIC_XipInitStru.spi_data_mask_en               = 0;
        SSIC_XipInitStru.xip_time_out                   = 50;
        scuprf("XIP/Remap to FLASH\r\n");
        
        SSIC_XipInit(&SSIC_XipInitStru);
        FC->CCR=0x1;
        for(uint16_t i=0;i<100;i++){};	
        {
            volatile uint8_t  *addr     = (uint8_t  *)SPI_FLASH_BASE;
            volatile uint16_t *addr16   = (uint16_t *)SPI_FLASH_BASE;
            volatile uint32_t *addr32   = (uint32_t *)SPI_FLASH_BASE;
            scuprf("SCU fc XIP:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
                *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);
        }

        for(uint16_t i=0;i<1000;i++){};
            SCU->SYS_CONFIG = 2;
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyAppSCUCase3(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    scuprf("SCU  App Remap Ram Test case1\r\n");
    verify_SendCid(cmd,&idx);
    {
        volatile uint8_t  *addr     = (uint8_t  *)CODE_SRAM_BASE1;
        for(uint16_t i=0;i<sizeof(ram_data);i++)
        {
            *(addr +i) = ram_data[i];
        } 
        
#ifdef BR_FPGA
        for(uint32_t i=0;i<10000000;i++){};
#endif
                       
        SCU->SYS_CONFIG = 1;
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyAppSCUCase4(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    //uint32_t idx=0;
    scuprf("SCU  IO MUX SCAN\n");
    //verify_SendCid(cmd,&idx);
    for(uint32_t i=0;i<1000;i++){};
        
    {
        PADConfig_Type      PAG_InitStru;
        for(int8_t set = 0;set<=1;set++)
        {
            PAG_InitStru.set =set;
            for(PAD_CTL_IE_type ie = PAD_IE_DISABLE;ie<=PAD_IE_ENABLE;ie++)
            {
                PAG_InitStru.ie =ie;       
                for(PAD_CTL_OEN_type oen = PAD_OEN_ENABLE; oen<=PAD_OEN_DISABLE;oen++)
                {
                    PAG_InitStru.oen =oen;
                    for(PAD_CTL_REN_type ren = PAD_REN_ENABLE;ren<=PAD_REN_DISABLE;ren++)
                    {
                        PAG_InitStru.ren=ren;
                        for(PAD_CTL_MODE_type mode = PAD_MODE0;mode<= PAD_MODE7;mode++)
                        {
                            PAG_InitStru.pad_ctl    = mode;
                            for(PADId_Type pad = PADID0; pad<PADID33;pad++)
                                SystemPADConfig(pad,&PAG_InitStru);
                        } 
                    }
                }
            }
        }

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE0;
        SystemPADConfig(PADID0,&PAG_InitStru);        
        scuprf("SCU  IO MUX complete\n");
    }
    
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool SystemDevClockGet(CKEnId_Type id)
{
		uint32_t reg = SCU->CLK_EN;
		if(reg &= (0x01ul << id))
			return true;
		else
			return false;      
}


uint8_t clock_str[][20]={"SCU_CKEn","GPIO_CKEn","WDT_CKEn","RTC_CKEn","UART0_CKEn","UART1_CKEn","SPIM1_CKEn",\
"SPIS1_CKEn","I2SM_CKEn","I2SS_CKEn","TIMER_CKEn","I2C_CKEn","QDEC_CKEn","RF_CKEn","BB_CKEn","DMA_CKEn",\
"SPIM0_CKEn","CPU_TRACE_CKEn","USB_CKEn"};       

bool cmd_VerifyAppSCUCase5(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0,pin=0;
    verify_SendCid(cmd,&idx);
    SCU->CLK_EN = 0xffffffff;
    scuprf("SCU clock ctrl En/Dis \n");    
    {
        for(CKEnId_Type clk = (CKEnId_Type)0; clk < (CKEnId_Type)32; clk++)
        {
            SystemDevClockCtl(clk,false);

            scuprf("clock[%d]=[%d]\n",clk,SystemDevClockGet(clk));
            sut = Verify_SendAppStep(BRCASE_STOP1+pin,1);pin++;
            if(!sut)
                break;
        
            SystemDevClockCtl(clk,true);

            scuprf("clock[%d]=[%d]\n",clk,SystemDevClockGet(clk));
            sut = Verify_SendAppStep(BRCASE_STOP1+pin,1);pin++;
            if(!sut)
                break;

        }

        scuprf("SCU clock complete\n");
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}




bool cmd_VerifyAppSCUCase6(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    uint32_t step=0;
	SCU->CLK_EN = 0xffffffff;
    verify_SendCid(cmd,&idx);
    scuprf("SCU clock Select\n");    
    {
       
        /***SCU_ClockSelectDivControl**********************************/
        if(sut)
            for(SCU_96MDIVCtl_Type clk = CLK_12M ;clk<=CLK_96M;clk++)
            {
                SCU_ClockSelectDivControl(clk);
                scuprf("SCU_ClockSelectDivControl=[%d]\n",clk);
                sut = Verify_SendAppStep(BRCASE_STOP1+step,SCU->CLK_CTL);step++;
                if(!sut)
                            break;
            }
        SCU_ClockSelectDivControl(CLK_12M);
        /***SCU_SPIM0ClkSelect**********************************/
        if(sut)
            for(SCU_SPIM0Select_Type clk = CLK_HCLK_MAIN ;clk<=CLK_SPIM0_104M;clk++)
            {
                SCU_SPIM0ClkSelect(clk);
                scuprf("SCU_SPIM0ClkSelect=[%d]\n",clk);
                sut = Verify_SendAppStep(BRCASE_STOP1+step,SCU->CLK_CTL);step++;
                if(!sut)
                    break;
            }
        SCU_SPIM0ClkSelect(CLK_HCLK_MAIN);
        /***SCU_32KClkSelect**********************************/
        if(sut)
            for(SCU_32KSelect_Type clk = CLK_RCO_32K ;clk<=clk_DIV_32K;clk++)
            {
                SCU_32KClkSelect(clk);
                scuprf("SCU_32KClkSelect=[%d]\n",clk);
                sut = Verify_SendAppStep(BRCASE_STOP1+step,SCU->CLK_CTL);step++;
                if(!sut)
                    break;
            }
        SCU_32KClkSelect(CLK_RCO_32K);

        /***SCU_USBClkSelect**********************************/
        if(sut)
            for(SCU_USBSelect_Type clk = CLK_RCO_48M ;clk<=CLK_DIV_48M;clk++)
            {
                SCU_USBClkSelect(clk);
                scuprf("Div 13M_control=[%d]\n",clk);
                sut = Verify_SendAppStep(BRCASE_STOP1+step,SCU->CLK_CTL);step++;
                if(!sut)
                    break;
            }
        SCU_USBClkSelect(CLK_RCO_48M); 

        /***SCU_HCLK_ClkSelect**********************************/
        if(sut)
            for(SCU_HclkSelect_Type hclk = CLK_OSC26m; hclk<=CLK_32K_MUX_HCLK; hclk++)
            {
                SCU_HClkSelect(hclk);
                for(uint16_t i=0;i<10;i++){};
                sut = Verify_SendAppStep(BRCASE_STOP1+step,SCU->CLK_CTL);step++;

            }  
        SCU_HClkSelect(CLK_OSC26m);
            
        if(sut)
        {
            SCU_UART0ClkSelect(CLK_OSC_26M);
            MCU_Sleep(1);
        }
        SCU_UART0ClkSelect(CLK_PCLK);
        
        if(sut)
        {
            SCU_BB_MEM_ADC_ClkSelect(1);
            MCU_Sleep(1);
        }
        SCU_BB_MEM_ADC_ClkSelect(0);
         if(sut)
            for(uint32_t clk = 0; clk<=3; clk++)
            {
                SCU_RF_ADC_ClkSelect(clk);
                MCU_Sleep(1);

            }
        
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyAppSCUCase7(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    uint32_t div=0;
	SCU->CLK_EN = 0xffffffff;
    verify_SendCid(cmd,&idx);
    scuprf("SCU clock DIV\n");    
    {
        
    for(div=0;div<1000;div+=111)
    {
        SCU_SPI1Div(div);
        scuprf("SCU SPI1 DIV[%d]\n",div); 
    }

    for(div=0;div<1000;div+=111)
    {
        SCU_32KDiv(div);
        scuprf("SCU 32K DIV[%d]\n",div);
    }

    for(div=0;div<1000;div+=111)
    {
        SCU_WdtDiv(div);
        scuprf("SCU WDT DIV [%d]\n",div); 
    }

    for(div=0;div<1000;div+=111)
    {
        SCU_I2SDiv(div);
        scuprf("SCU I2S DIV[%d]\n",div);  
    }

    for(div=0;div<0x10000;div+=1111)
    {
        SCU_RTCDiv(div);
        scuprf("SCU RTC DIV[%d]\n",div);
    }

    scuprf("SCU clock complete\n");
    }
    
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyAppSCUCase8(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    uint32_t div=0;
	
    SystemDevClockCtl(TIMER_CKEn ,true);
    SystemDevClockCtl(TIMER0_CKEn,true);
    SystemDevClockCtl(TIMER1_CKEn,true);
    SystemDevClockCtl(TIMER2_CKEn,true);
    SystemDevClockCtl(TIMER3_CKEn,true);
    SystemDevClockCtl(TIMER4_CKEn,true);
    SystemDevClockCtl(TIMER5_CKEn,true);
    SystemDevClockCtl(TIMER6_CKEn,true);
    SystemDevClockCtl(TIMER7_CKEn,true);
    verify_SendCid(cmd,&idx);
    scuprf("SCU Timers DIV\n");    
    {
        for(SCU_Timers_Type tm = CLK_TM0;tm<=CLK_TM7;tm++)
        {
            for(div=0;div<10000;div+=1111)
            {
                SCU_TimersDiv(tm,div);
                scuprf("SCU TM[%d], div[%d]\n",tm,div); 
            }
        }
      scuprf("SCU clock complete\n");
    }
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyAppSCUCase9(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    uint32_t step=0;
	
    verify_SendCid(cmd,&idx);
    scuprf("SCU pclk Select\n");    
    {
        /***SCU_PClkSelect**********************************/
        if(sut)
        for(SCU_PclkSelect_Type clk = HCLK_DIV_2_PCLK ;clk<=HCLK_2_PLCK;clk++)
        {
            SCU_PClkSelect(clk);
            MCU_Sleep(1);
                sut = Verify_SendAppStep(BRCASE_STOP1+step,SCU->CLK_CTL);step++;
            if(!sut)
            break;
        }
        SCU_PClkSelect(HCLK_DIV_2_PCLK);
        MCU_Sleep(1);
        scuprf("SCU clock complete\n");
    }
    
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyAppSCUCase10(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint16_t Fid = 0 ;
    uint32_t idx=0;
    scuprf("SCU App QSPI Full Mux new \r\n");
    verify_SendCid(cmd,&idx);
    {
        SSIC_InitInfo_Type  SSIC_InitStru ;
        SSIC_XIP_InitInfo_Type SSIC_XipInitStru; 
        
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

        SSIC_InitStru.unmask_interrupt          = FIFO_MASK_ALL;
        SystemDevClockCtl(SPIM0_CKEn,true);
        SSIC_Init(&SSIC_InitStru);
        Fid = FLASH_ReadManufDeviceId();
        scuprf("FLASH id:[%X]\r\n",Fid);
        
#ifndef XIP_QUAD_SPI       
        FLASH_EnableEQI(true);
#else
        FLASH_EnableEQI(false);
#endif     
        {
            uint8_t data[10]={0xab,0x89,0x67,0x45};
            FLASH_PageProgram(0,data,4);
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
#ifndef XIP_QUAD_SPI
        SSIC_InitStru.spi_frame_format          =  QUAD_SPI_FORMAT;
#else
        SSIC_InitStru.spi_frame_format          =  DUAL_SPI_FORMAT;
#endif
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
        
#ifndef XIP_QUAD_SPI       
        SSIC_XipInitStru.spi_frame_format       = QUAD_SPI_FORMAT;
#else
        SSIC_XipInitStru.spi_frame_format       = DUAL_SPI_FORMAT;
#endif       
        
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

#ifndef XIP_QUAD_SPI
        SSIC_XipInitStru.xip_inst_transfer_opcode   = 0x6b;     //QUAD_SPI_FORMAT
#else
        SSIC_XipInitStru.xip_inst_transfer_opcode   = 0x3b;   //DUAL_SPI_FORMAT
#endif
        SSIC_XipInitStru.xip_wrap_transfer_opcode   = 0;
        SSIC_XipInitStru.slaves_enbale_mask         = 1;
        SSIC_XipInitStru.spi_clk_stretch_en         = 0;
        SSIC_XipInitStru.spi_data_mask_en           = 0;
        SSIC_XipInitStru.xip_time_out               = 50; 
        SSIC_XipInit(&SSIC_XipInitStru);
        for(uint16_t indx =0;indx<6;indx++)
        {
#if  defined(BR002)||defined(BR003)
            switch(indx)
            {
                case 0:
                    SCUQspiConfig(QSPI_PIN29,QSPI_CLK);
                    SCUQspiConfig(QSPI_PIN30,QSPI_CS);
                    SCUQspiConfig(QSPI_PIN31,QSPI_D0);
                    SCUQspiConfig(QSPI_PIN32,QSPI_D1);
                    SCUQspiConfig(QSPI_PIN33,QSPI_D2);
                    SCUQspiConfig(QSPI_PIN34,QSPI_D3);
                    break;
                case 1:
                    SCUQspiConfig(QSPI_PIN30,QSPI_CLK);
                    SCUQspiConfig(QSPI_PIN31,QSPI_CS);
                    SCUQspiConfig(QSPI_PIN32,QSPI_D0);
                    SCUQspiConfig(QSPI_PIN33,QSPI_D1);
                    SCUQspiConfig(QSPI_PIN34,QSPI_D2);
                    SCUQspiConfig(QSPI_PIN29,QSPI_D3);
                    break;
                case 2:
                    SCUQspiConfig(QSPI_PIN31,QSPI_CLK);
                    SCUQspiConfig(QSPI_PIN32,QSPI_CS);
                    SCUQspiConfig(QSPI_PIN33,QSPI_D0);
                    SCUQspiConfig(QSPI_PIN34,QSPI_D1);
                    SCUQspiConfig(QSPI_PIN29,QSPI_D2);
                    SCUQspiConfig(QSPI_PIN30,QSPI_D3);
                    break;
                case 3:
                    SCUQspiConfig(QSPI_PIN32,QSPI_CLK);
                    SCUQspiConfig(QSPI_PIN33,QSPI_CS);
                    SCUQspiConfig(QSPI_PIN34,QSPI_D0);
                    SCUQspiConfig(QSPI_PIN29,QSPI_D1);
                    SCUQspiConfig(QSPI_PIN30,QSPI_D2);
                    SCUQspiConfig(QSPI_PIN31,QSPI_D3);
                    break;
                case 4:
                    SCUQspiConfig(QSPI_PIN33,QSPI_CLK);
                    SCUQspiConfig(QSPI_PIN34,QSPI_CS);
                    SCUQspiConfig(QSPI_PIN29,QSPI_D0);
                    SCUQspiConfig(QSPI_PIN30,QSPI_D1);
                    SCUQspiConfig(QSPI_PIN31,QSPI_D2);
                    SCUQspiConfig(QSPI_PIN32,QSPI_D3);
                    break;
                case 5:
                    SCUQspiConfig(QSPI_PIN34,QSPI_CLK);
                    SCUQspiConfig(QSPI_PIN29,QSPI_CS);
                    SCUQspiConfig(QSPI_PIN30,QSPI_D0);
                    SCUQspiConfig(QSPI_PIN31,QSPI_D1);
                    SCUQspiConfig(QSPI_PIN32,QSPI_D2);
                    SCUQspiConfig(QSPI_PIN33,QSPI_D3);
                    break;
            }	
            {
                volatile uint8_t  *addr     = (uint8_t  *)SPI_FLASH_BASE;
                volatile uint16_t *addr16   = (uint16_t *)SPI_FLASH_BASE;
                volatile uint32_t *addr32   = (uint32_t *)SPI_FLASH_BASE;
                scuprf("spim0 XIP:u8[%2X][%2X][%2X][%2X],u16[%4X][%4X],u32[%8X]\r\n",\
                    *(addr+0),*(addr+1),*(addr+2),*(addr+3),*addr16,*(addr16+1),*addr32);
            }
#endif
        }        
    }
	
    for(uint16_t i=0;i<1000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



void ScuOutput(void)
{
    UART_InitInfo_Type UART_InitStru;
    UART_InitStru.UART_BaudRate = 1200;
    UART_InitStru.UART_WordLength = UART_WL_8BITS;
    UART_InitStru.UART_StopBits = UART_SB_1BIT;
    UART_InitStru.UART_ParityMode = UART_PM_NONE;
    UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
    UART_InitStru.UART_FIFOMode = UART_FM_ENABLE;
    UART_InitStru.UART_DMAMode = UART_DM_MODE_0;
    UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
    UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;
    UART_Init(UART0, &UART_InitStru); 
    
}

void  delay_ms(uint32_t clk,uint32_t timer)
{
    uint32_t cot= clk/10000;
    for(uint16_t k=0;k<timer;k++)
        for(uint32_t i = 0; i<cot;i++)
        {}
}



void verify_clk_reg(__IO uint32_t *reg,uint32_t val, bool *rut,uint32_t *val_fl,uint32_t *idx)
{
    uint32_t  buff = 0;
    (*reg)= val;
    for(uint16_t k=0;k<50;k++);
    buff = (*reg);
    if(buff != val)
    {
        (*rut) = false;
    }
    if(*rut)
        (*val_fl)|=0x01ul<<(*idx);
    else
        (*rut)=true;  
    (*idx)++;
}
void verify_clk_reg_dely(__IO uint32_t *reg,uint32_t val, bool *rut,uint32_t *val_fl,uint32_t *idx)
{
    uint32_t  buff = 0;
    (*reg)= val;
    for(uint16_t k=0;k<10;k++);
    buff = (*reg);
    for(uint16_t k=0;k<10;k++);
    if(buff != val)
    {
        *rut =false;
    }
    if(*rut)
        (*val_fl)|=0x01ul<<(*idx);
    else
        (*rut)=true;  
    (*idx)++;
}

 
    
bool  verify_clk_rw_IP(uint32_t *step,bool *sut,uint32_t cot)
{    
    bool  rut =true;
    uint32_t val_fl = 0;
    uint32_t bit_t  = 0;
    SCU->SEND_DATA = cot;

/*0*/verify_clk_reg(&GPIO->DR0,0x005500aa,&rut,&val_fl,&bit_t);
/*1*/verify_clk_reg(&GPIO->DR0,0x01,&rut,&val_fl,&bit_t);
/*2*/verify_clk_reg(&SCU->PAD_CFG[0],0xb,&rut,&val_fl,&bit_t);
/*3*/verify_clk_reg(&SCU->PAD_CFG[0],0x01,&rut,&val_fl,&bit_t);
/*4*/verify_clk_reg(&WDT->TORR,0x06,&rut,&val_fl,&bit_t);
/*5*/verify_clk_reg(&WDT->TORR,0x01,&rut,&val_fl,&bit_t);
/*6*/verify_clk_reg(&RTC->CLR ,0x518,&rut,&val_fl,&bit_t);
/*7*/verify_clk_reg(&RTC->CLR ,0x01,&rut,&val_fl,&bit_t);
/*8*/verify_clk_reg(&UART1->DLF ,0xe,&rut,&val_fl,&bit_t);
/*9*/verify_clk_reg(&UART1->DLF ,0x01,&rut,&val_fl,&bit_t);
    SPIM1->SSIENR   = DISABLE;
    SPIM1->IMR      = DISABLE;
/*10*/verify_clk_reg(&SPIM1->BAUDR ,0x80,&rut,&val_fl,&bit_t);
/*11*/verify_clk_reg(&SPIM1->BAUDR ,2,&rut,&val_fl,&bit_t);
    SPIS1->SSIENR   = DISABLE;
    SPIS1->IMR      = DISABLE;
/*12*/verify_clk_reg(&SPIS1->TXFTLR ,0x5,&rut,&val_fl,&bit_t);
/*13*/verify_clk_reg(&SPIS1->TXFTLR ,0x01,&rut,&val_fl,&bit_t);
/*14*/verify_clk_reg(&I2SM->CCR ,0xF,&rut,&val_fl,&bit_t);
/*15*/verify_clk_reg(&I2SM->CCR ,0x01,&rut,&val_fl,&bit_t);
/*16*/verify_clk_reg(&I2SS->I2S_Ch.RCR ,2,&rut,&val_fl,&bit_t);
/*17*/verify_clk_reg(&I2SS->I2S_Ch.RCR ,0x01,&rut,&val_fl,&bit_t);
/*18*/verify_clk_reg(&I2C0->IC_TAR ,2,&rut,&val_fl,&bit_t);
/*19*/verify_clk_reg(&I2C0->IC_TAR ,0x01,&rut,&val_fl,&bit_t);
/*20*/verify_clk_reg(&DMA->CHR[0].SAR ,0x123,&rut,&val_fl,&bit_t);
/*21*/verify_clk_reg(&DMA->CHR[0].SAR ,0x01,&rut,&val_fl,&bit_t);
    SPIM0->SSIENR = DISABLE;
    SSI_ClearInterrupt(SPIM0);
    SPIM0->IMR = DISABLE;
/*22*/verify_clk_reg_dely(&SPIM0->TXFTLR ,6,&rut,&val_fl,&bit_t);
/*23*/verify_clk_reg_dely(&SPIM0->TXFTLR ,0x01,&rut,&val_fl,&bit_t);

/*24*/verify_clk_reg(&TIMERS->TIMER[0].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
/*25*/verify_clk_reg(&TIMERS->TIMER[0].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
/*26*/verify_clk_reg(&TIMERS->TIMER[1].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
/*27*/verify_clk_reg(&TIMERS->TIMER[1].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
/*28*/verify_clk_reg(&TIMERS->TIMER[2].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
/*29*/verify_clk_reg(&TIMERS->TIMER[2].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
/*30*/verify_clk_reg(&TIMERS->TIMER[3].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
/*31*/verify_clk_reg(&TIMERS->TIMER[3].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);

///*0*/verify_clk_reg(&TIMERS->TIMER[4].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
///*0*/verify_clk_reg(&TIMERS->TIMER[4].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
///*0*/verify_clk_reg(&TIMERS->TIMER[5].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
///*0*/verify_clk_reg(&TIMERS->TIMER[5].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
///*0*/verify_clk_reg(&TIMERS->TIMER[6].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
///*0*/verify_clk_reg(&TIMERS->TIMER[6].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
///*0*/verify_clk_reg(&TIMERS->TIMER[7].LOAD_COUNT ,0x005500aa,&rut,&val_fl,&bit_t);
///*0*/verify_clk_reg(&TIMERS->TIMER[7].LOAD_COUNT ,0x01,&rut,&val_fl,&bit_t);
   
    *sut = Verify_SendAppStep(*step,val_fl);
    
    (*step)+=1;
    return (*sut);
}


//PCLK  Not Need Case
bool cmd_VerifyAppSCUCase11(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;	
#ifndef ONLY_NO_UVM 
     uint32_t step=0;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    {
        /***SCU_HPCLKClkSelect**********************************/  
        if(sut)
        {
            SCU_PClkSelect(HCLK_2_PLCK);
            for(uint16_t i=0;i<10;i++){};
            for(SCU_HclkSelect_Type hclk = CLK_OSC26m; hclk<=CLK_32K_MUX_HCLK; hclk++)
            {
                SCU_HClkSelect(hclk);
                for(uint16_t i=0;i<10;i++){};
                sut = Verify_SendAppStep(BRCASE_STOP1+step,SCU->CLK_CTL);step++;  
            }  
            
            step = 0x30;
            uint32_t cot=0x11110000;
            SCU->SEND_DATA = cot;cot++;
            SCU_PClkSelect(HCLK_DIV_2_PCLK);            
            SCU_HClkSelect(CLK_OSC26m);
            SCU_PClkPreSelect(HCLK_2_PLCK_PRE);
            delay_ms(26000000ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 1
                goto SCUCase11_VERIFY_END;
            cot++;
            
            SCU_PClkPreSelect(HCLK_DIV02);
            delay_ms(26000000ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 2
                goto SCUCase11_VERIFY_END;
            cot++;
            
            SCU_PClkPreSelect(HCLK_DIV04);
            delay_ms(26000000ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 3
                goto SCUCase11_VERIFY_END;
            cot++;
            
            SCU_PClkPreSelect(HCLK_DIV08);
            delay_ms(26000000ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 4
                goto SCUCase11_VERIFY_END;
            cot++;
            SCU_PClkPreSelect(HCLK_DIV16);
            delay_ms(26000000ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 5
                goto SCUCase11_VERIFY_END;
            cot++;
            
            SCU_HClkSelect(CLK_HCLK_MUX);
            SCU_PClkPreSelect(HCLK_2_PLCK_PRE);
            delay_ms(13000000ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 6
                goto SCUCase11_VERIFY_END;
            cot++;
            SCU_PClkPreSelect(HCLK_DIV02);
            delay_ms(13000000ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 7
                goto SCUCase11_VERIFY_END;
            cot++;
            SCU_PClkPreSelect(HCLK_DIV04);
            delay_ms(13000000ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 8
                goto SCUCase11_VERIFY_END;
            cot++;
            SCU_PClkPreSelect(HCLK_DIV08);
            delay_ms(13000000ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 9
                goto SCUCase11_VERIFY_END;
            cot++;
            SCU_PClkPreSelect(HCLK_DIV16);
            delay_ms(13000000ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 10
                goto SCUCase11_VERIFY_END;
            cot++;
            
            SCU_HClkSelect(CLK_32K_MUX_HCLK);
            SCU_PClkPreSelect(HCLK_2_PLCK_PRE);
            delay_ms(32768ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 11
                goto SCUCase11_VERIFY_END;
            cot++;
            SCU_PClkPreSelect(HCLK_DIV02);
            delay_ms(32768ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 12
                goto SCUCase11_VERIFY_END;
            cot++;
            SCU_PClkPreSelect(HCLK_DIV04);
            delay_ms(32768ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 13
                goto SCUCase11_VERIFY_END;
            cot++;
            SCU_PClkPreSelect(HCLK_DIV08);
            delay_ms(32768ul,1);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 14
                goto SCUCase11_VERIFY_END;
            cot++;
            SCU_PClkPreSelect(HCLK_DIV16);
            if(!verify_clk_rw_IP(&step,&sut,cot))//####### 15
                goto SCUCase11_VERIFY_END;
            cot++;
        }      
        SCU->SEND_DATA = 0x22222222;
    }
SCUCase11_VERIFY_END:    
    Verify_SendCResult(BRCASE_RESULT,sut);
#endif
    return sut;
}


bool cmd_VerifyAppSCUCase12(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    verify_SendCid(cmd,&idx);
    scuprf("SCU pclk 26M [%ld]\n",SystemCoreClock); 
    SystemCoreClock = 32768;	
    scuprf("SCU pclk 32.768k [%ld]\n",SystemCoreClock);  
    while(UART_GetStatus(UART0)& 0x01){};
    for(uint16_t i=0;i<1000;i++){};
    {
			/***SCU_PClkSelect**********************************/
			SCU_HClkSelect(CLK_32K_MUX_HCLK);
            for(uint16_t i=0;i<100;i++){};
			ScuOutput();
			scuprf("67890\n");

    }
    while(UART_GetStatus(UART0)& 0x01){};
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyAppSCUCase13(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;

    verify_SendCid(cmd,&idx);
    scuprf("SCU pclk 13M [%ld]\n",SystemCoreClock); 
    SystemCoreClock = 13000000;	
    scuprf("SCU pclk 13M [%ld]\n",SystemCoreClock);
    for(uint16_t i=0;i<5000;i++){};
		
	
    {
			/***SCU_PClkSelect**********************************/
			SCU_PClkSelect(HCLK_DIV_2_PCLK);
            for(uint16_t i=0;i<100;i++){};
            SCU_PClkPreSelect(HCLK_DIV04);
			ScuOutput();
			scuprf("1234567890\n");
			scuprf("1234567890\n");
			scuprf("1234567890\n");

    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyAppSCUCase14(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t Fid=0;
    //uint32_t idx=0;
    //verify_SendCid(cmd,&idx);
    scuprf("SCU XIP Sacn MEM\r\n");
    {
        SSIC_InitInfo_Type  SSIC_InitStru ;
        SSIC_XIP_InitInfo_Type SSIC_XipInitStru;
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
        SSIC_InitStru.tx_fifo_threshold_level 	= 0;
        SSIC_InitStru.tx_fifo_start_fifo_level  = 0;
        SSIC_InitStru.rx_fifo_threshold_level   = 0;
        SSIC_InitStru.dma_rx_data_level = 0;
        SSIC_InitStru.dma_tx_data_level = 0;

        SSIC_InitStru.unmask_interrupt = FIFO_MASK_ALL;
        SystemDevClockCtl(SPIM0_CKEn,true);
        SSIC_Init(&SSIC_InitStru);
        
        Fid = FLASH_ReadManufDeviceId();
        scuprf("SCU Fid:[%X]\r\n",Fid);
         
        FLASH_EnableEQI(true); 
 
        SSIC_InitStru.clock_divider             =  0x2;
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
      
        SSIC_XipInitStru.spi_frame_format               = QUAD_SPI_FORMAT;

        SSIC_XipInitStru.transfer_type                  = TT0;
        SSIC_XipInitStru.address_length                 = ADDR_L24;
        SSIC_XipInitStru.instruction_length             = INST_L8;
        SSIC_XipInitStru.wait_cycles                    = 0x8; /*Wait cycles in Dual/Quad/Octal mode between control frames transmit and data reception. Specified as number of SPI clock cycles.*/
        SSIC_XipInitStru.xip_mode_bit_en                = false;
        SSIC_XipInitStru.xip_dfs_hsize_hburst_en        = false;
        SSIC_XipInitStru.xip_spi_ddr_en                 = false;
        SSIC_XipInitStru.instruction_ddr_enable         = false;
        SSIC_XipInitStru.read_data_strobe_enable        = false;
        SSIC_XipInitStru.xip_instruction_enable         = true;
        SSIC_XipInitStru.xip_continuous_transfer_enable = true;
        SSIC_XipInitStru.xip_spi_hyerbus_format_enable  = false;
        SSIC_XipInitStru.xip_rxds_signaling_enable      = false; /*Enable rxds signaling during address and command phase of Hypebus transfer*/

        SSIC_XipInitStru.xip_mode_bit_length            = MBL_2;

        /*Enables XIP pre-fetch functionality in DWC_ssi. Once
        enabled DWC_ssi will pre-fetch data frames from next
        contigous location, to reduce the latency for the upcoming
        contiguous transfer. If the next XIP request is not contigous
        then pre-fetched bits will be discarded.*/
        SSIC_XipInitStru.xip_pre_fetch_enable           = false;

        SSIC_XipInitStru.xip_inst_transfer_opcode       = 0x6b;     //QUAD_SPI_FORMAT

        SSIC_XipInitStru.xip_wrap_transfer_opcode       = 0;
        SSIC_XipInitStru.slaves_enbale_mask             = 1;
        SSIC_XipInitStru.spi_clk_stretch_en             = 0;
        SSIC_XipInitStru.spi_data_mask_en               = 0;
        SSIC_XipInitStru.xip_time_out                   = 50;
        SSIC_XipInit(&SSIC_XipInitStru);	
        FC->CCR	=	0x61;
        {

            volatile uint32_t *addr32   = (uint32_t *)SPI_FLASH_BASE;
            uint32_t val = 0;
            uint32_t rom_ksize = 1024;

            scuprf("Get ROM\n");
            for(uint32_t i=0;i<(rom_ksize<<8);i++)
            {
                val = *addr32;
                addr32++;
            }
            scuprf("XIP G Completed ! [%X]\n",val);
        }

       
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}







bool cmd_VerifyAppSCUCase15(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint16_t Fid = 0 ;
    uint32_t idx=0;
    scuprf("SCU App QSPI All Full Mux new\r\n");
    verify_SendCid(cmd,&idx);
	
    {
        SSIC_InitInfo_Type  SSIC_InitStru ;
        SSIC_XIP_InitInfo_Type SSIC_XipInitStru;
			
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
        scuprf("FLASH id:[%X]\r\n",Fid);
              
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
        scuprf("spim0 QSPI:clk[%d],cs[%d],d0[%d],d1[%d],d2[%d],d3[%d]\r\n",clk,cs,d0,d1,d2,d3);
#if  defined(BR002)||defined(BR003)				
						
        {
            volatile uint32_t *addr32   = (uint32_t *)SPI_FLASH_BASE;
            uint32_t data0 = *(addr32+0);
            uint32_t data1 = *(addr32+1);
            scuprf("spim0 XIP:u32[%8X],[%8X]\r\n",data0,data1);
            if(data0 != 0xa5dac5ba || data1 != 0x55aa55aa)
            {
                sut =false;
                scuprf("XIP Full Mux Error");
                goto QSPI_FULLMUXEMD;
            }
        

        }
#endif 
        }}}}}}}}}}}
				
    }		
QSPI_FULLMUXEMD:
    for(uint16_t i=0;i<1000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyAppSCUCase16(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
	
    verify_SendCid(cmd,&idx);
    scuprf("SCU ANA Clock Reg\n"); 
    {
			
			scuprf("[%X]\n",SCU->ANA_CTL0);
			scuprf("[%X]\n",SCU->ANA_CTL1);
			scuprf("[%X]\n",SCU->ANA_CTL2);
			scuprf("[%X]\n",SCU->ANA_CTL3);
			scuprf("[%X]\n",SCU->ANA_CTL4);
//			scuprf("[%X]\n",SCU->ANA_STATUS0);
//			scuprf("[%X]\n",SCU->ANA_STATUS1);

    }
    for(uint16_t i =0 ;i<5000;i++);
		
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


#define SetAnaReg(x,y,z)  y?(x |= 0x01ul<<z ):(x &= ~(0x01ul<<z)) 

bool cmd_VerifyAppSCUCase17(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
	SCU->CLK_EN = 0xffffffff;
    verify_SendCid(cmd,&idx);
    scuprf("SCU ANA Clock Reg\n"); 
    {
			{
				scuprf("[%X]\n",SCU->ANA_CTL0);
				scuprf("[%X]\n",SCU->ANA_CTL1);
				scuprf("[%X]\n",SCU->ANA_CTL2);
				scuprf("[%X]\n",SCU->ANA_CTL3);
				scuprf("[%X]\n",SCU->ANA_CTL4);
			}
//############ANA_CTL0############################################				
			uint32_t ctl = 0xFFFFF800;
			uint32_t setd= 0x0FFF80F0;
			
			for(uint16_t idx=0;idx<32;idx++)
			{
				if((ctl>>idx & 0x01))
				{
					if((setd>>idx & 0x01))
					{
						scuprf("ANA_CTL0[%X],[%d]\n",idx,0);
						SetAnaReg(SCU->ANA_CTL0,0,idx);
						scuprf("ANA_CTL0[%X],[%d]\n",idx,1);
						SetAnaReg(SCU->ANA_CTL0,1,idx);
					}
					else
					{
						scuprf("ANA_CTL0[%X],[%d]\n",idx,1);
						SetAnaReg(SCU->ANA_CTL0,1,idx);
						scuprf("ANA_CTL0[%X],[%d]\n",idx,0);
						SetAnaReg(SCU->ANA_CTL0,0,idx);
					}
				}
				
			}
//############ANA_CTL1############################################			
			 //ctl = 0xFCC79FFF;
			ctl = 0xFFFFFFFF; 
            setd= 0x89942452;
			
			for(uint16_t idx=0;idx<32;idx++)
			{
				if((ctl>>idx & 0x01))
				{
					if((setd>>idx & 0x01))
					{
						scuprf("ANA_CTL1[%X],[%d]\n",idx,0);
						SetAnaReg(SCU->ANA_CTL1,0,idx);
						scuprf("ANA_CTL1[%X],[%d]\n",idx,1);
						SetAnaReg(SCU->ANA_CTL1,1,idx);
					}
					else
					{
						scuprf("ANA_CTL1[%X],[%d]\n",idx,1);
						SetAnaReg(SCU->ANA_CTL1,1,idx);
						scuprf("ANA_CTL1[%X],[%d]\n",idx,0);
						SetAnaReg(SCU->ANA_CTL1,0,idx);
					}
				}
				
			}
//############ANA_CTL2############################################				
			 //ctl = 0xFFFFF01F;
             ctl = 0xFFFFFFFF;
			 setd= 0x0F20AAA4;
			
			for(uint16_t idx=0;idx<32;idx++)
			{
				if((ctl>>idx & 0x01))
				{
					if((setd>>idx & 0x01))
					{
						scuprf("ANA_CTL2[%X],[%d]\n",idx,0);
						SetAnaReg(SCU->ANA_CTL2,0,idx);
						scuprf("ANA_CTL2[%X],[%d]\n",idx,1);
						SetAnaReg(SCU->ANA_CTL2,1,idx);
					}
					else
					{
						scuprf("ANA_CTL2[%X],[%d]\n",idx,1);
						SetAnaReg(SCU->ANA_CTL2,1,idx);
						scuprf("ANA_CTL2[%X],[%d]\n",idx,0);
						SetAnaReg(SCU->ANA_CTL2,0,idx);
					}
				}
				
			}
//############ANA_CTL3############################################				
			 //ctl = 0x1FFFFFFF;
             ctl = 0xFFFFFFFF;
			 setd= 0x08608238;
			
			for(uint16_t idx=0;idx<32;idx++)
			{
				if((ctl>>idx & 0x01))
				{
					if((setd>>idx & 0x01))
					{
						scuprf("ANA_CTL3[%X],[%d]\n",idx,0);
						SetAnaReg(SCU->ANA_CTL3,0,idx);
						scuprf("ANA_CTL3[%X],[%d]\n",idx,1);
						SetAnaReg(SCU->ANA_CTL3,1,idx);
					}
					else
					{
						scuprf("ANA_CTL3[%X],[%d]\n",idx,1);
						SetAnaReg(SCU->ANA_CTL3,1,idx);
						scuprf("ANA_CTL3[%X],[%d]\n",idx,0);
						SetAnaReg(SCU->ANA_CTL3,0,idx);
					}
				}
				
			}
//############ANA_CTL4############################################				
			 //ctl = 0xFFFFFFF8;
             ctl = 0xFFFFFFFF;
			 setd= 0x92722800;
			
			for(uint16_t idx=0;idx<32;idx++)
			{
				if((ctl>>idx & 0x01))
				{
					if((setd>>idx & 0x01))
					{
						scuprf("ANA_CTL4[%X],[%d]\n",idx,0);
						SetAnaReg(SCU->ANA_CTL4,0,idx);
						scuprf("ANA_CTL4[%X],[%d]\n",idx,1);
						SetAnaReg(SCU->ANA_CTL4,1,idx);
					}
					else
					{
						scuprf("ANA_CTL4[%X],[%d]\n",idx,1);
						SetAnaReg(SCU->ANA_CTL4,1,idx);
						scuprf("ANA_CTL4[%X],[%d]\n",idx,0);
						SetAnaReg(SCU->ANA_CTL4,0,idx);
					}
				}	
			}			
    }
		{
				scuprf("[%X]\n",SCU->ANA_CTL0);
				scuprf("[%X]\n",SCU->ANA_CTL1);
				scuprf("[%X]\n",SCU->ANA_CTL2);
				scuprf("[%X]\n",SCU->ANA_CTL3);
				scuprf("[%X]\n",SCU->ANA_CTL4);
	  }
		
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyAppSCUCase18(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
	
    verify_SendCid(cmd,&idx);
    scuprf("SCU IO STATUS Reg Read\n"); 
    {
        uint32_t status=0;
        scuprf("IO S[%X]\n",status);
        
        for(MessagaConnectEn_Type md = TMODE_0; md<=TMODE_5;md++)
        {
            Verrify_SendPinConnect(md);
            Verrify_SendPinConnect(TMODE_DIS);
            Verrify_SendPinConnect(TMODE_EN);
            scuprf("TMode[%d]\n",md-TMODE_0); 
            scuprf("TMode En\n");
            status= SCU->IO_STATUS;
            scuprf("IO S[%X],FUNC[%s],MB[%s],SC[%s],BS[%s]\n",
            status,
            (status>>7 & 0x01)?"true":"false",
            (status>>4 & 0x01)?"true":"false",
            (status>>5 & 0x01)?"true":"false",
            (status>>6 & 0x01)?"true":"false");
        }

    }	
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}




#define SetDIVReg(x,y,z)  y?(x |= 0x01ul<<z ):(x &= ~(0x01ul<<z)) 
bool cmd_VerifyAppSCUCase19(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
	
    SCU->CLK_EN = 0xffffffff;
    verify_SendCid(cmd,&idx);
    scuprf("SCU SCAN Reg\n"); 
    {
//############ANA_CTL0############################################				
			uint32_t ctl = 0xFFFFFFFF;
			for(uint16_t idx=0;idx<32;idx++){
				if((ctl>>idx & 0x01)){
                    SetDIVReg(SCU->CLK_DIV,1,idx);
                    SetDIVReg(SCU->CLK_DIV,0,idx);
				}
            }
            for(uint16_t idx=0;idx<32;idx++){
				if((ctl>>idx & 0x01)){
                    SetDIVReg(SCU->CLK_DIV1,1,idx);
                    SetDIVReg(SCU->CLK_DIV1,0,idx);
				}
            }
            for(uint16_t idx=0;idx<32;idx++){
				if((ctl>>idx & 0x01)){
                    SetDIVReg(SCU->CLK_DIV2,1,idx);
                    SetDIVReg(SCU->CLK_DIV2,0,idx);
				}
            }
            
            for(uint16_t tm=0;tm<8;tm++){
                for(uint16_t idx=0;idx<16;idx++){
                    if((ctl>>idx & 0x01)){
                        SetDIVReg(SCU->TIMERS_DIV[tm],1,idx);
                        SetDIVReg(SCU->TIMERS_DIV[tm],0,idx);
                    }
                }
            }
            
            for(uint16_t tm=0;tm<33;tm++){
                for(uint16_t idx=0;idx<32;idx++){
                    if((ctl>>idx & 0x01)){
                        SetDIVReg(SCU->PAD_CFG[tm],1,idx);
                        SetDIVReg(SCU->PAD_CFG[tm],0,idx);
                    }
                }
            } 
            
            for(uint16_t idx=0;idx<32;idx++){
				if((ctl>>idx & 0x01)){
                    SetDIVReg(SCU->READ_DATA,1,idx);
                    SetDIVReg(SCU->READ_DATA,0,idx);
				}
            }

            for(uint16_t idx=0;idx<32;idx++){
				if((ctl>>idx & 0x01)){
                    SetDIVReg(SCU->READ_CMD,1,idx);
                    SetDIVReg(SCU->READ_CMD,0,idx);
				}
            }
            
	  }
	scuprf("SCU SCAN DIV Complete\n"); 	
    Verify_SendCResult(BRCASE_RESULT,sut);
      
    for(uint16_t idx=0;idx<32;idx++){
        if((0xffffffff>>idx & 0x01)){
            SetDIVReg(SCU->SEND_CMD,1,idx);
            SetDIVReg(SCU->SEND_CMD,0,idx);
        }
    }
    return sut;
}


bool cmd_VerifyAppSCUCase20(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
	
    verify_SendCid(cmd,&idx);
    scuprf("SCU TIMER RESET\n"); 
    {
        TIMER_InitInof_TypeDef TIMER_InitStru;
        TIMER_InitStru.TIMER_PwmValue       = 0;
        TIMER_InitStru.TIMER_LoadValue      = (3*(SystemCoreClock/1000));
        TIMER_InitStru.TIMER_InterruptMask  = TIMER_INTERRUPT_MASKED;
        TIMER_InitStru.TIMER_mode           = TIMER_USER_DEFINED;
        TIMER_InitStru.TIMER_Pwd            = TIMER_PWM_DISABLE;
        TIMER_InitStru.TIMER_sch            = TIMER_ENABLE;
        scuprf("Mode User\r\n");
        SystemDevClockCtl(TIMER_CKEn,true);
        for(TIMER_Num_Type tm = TM0; tm <= TM7; tm++)
        {
            TIMER_InitStru.TIMERx= tm;
            TIMER_Init(&TIMER_InitStru); 
            
            scuprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            scuprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
            scuprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
            SCU->SW_RST |=0x01<<(21+tm);
            scuprf("Reset\r\n");
            scuprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            scuprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
            scuprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
            scuprf("\r\n");
          
        }
        
    }
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
    
}



bool cmd_VerifyAppSCUCase21(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    verify_SendCid(cmd,&idx);
    
    PADConfig_Type PAG_GPIO;
    memset(&PAG_GPIO,0,sizeof(PADConfig_Type));
    PAG_GPIO.set        = true;
    PAG_GPIO.ie         = PAD_IE_ENABLE;
    PAG_GPIO.oen        = PAD_OEN_DISABLE;
    PAG_GPIO.pad_ctl    = PAD_MODE0;
    PAG_GPIO.ren        = PAD_REN_ENABLE,
    SystemPADConfig(PADID30,&PAG_GPIO);

    scuprf("SCU PMU 21\n"); 
    {
        scuprf("Start PMU Test\n");       
        while(UART_GetStatus(UART0)&0x01);
        for(uint16_t i=0;i<1000;i++){};
        SCU_32KClkSelect(CLK_RCO_32K);      
        SCU_HClkSelect(CLK_32K_MUX_HCLK);
        SCU->ANA_CTL0   = 0xC0200000;
        SCU->SLEEP_EN   = 0xffffffff;
    }   
    while(sut); 
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;  
}

bool cmd_VerifyAppSCUCase22(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;	
    verify_SendCid(cmd,&idx);
    scuprf("SCU PMU 22\n"); 
    {
        PADConfig_Type PAG_GPIO;
        memset(&PAG_GPIO,0,sizeof(PADConfig_Type));
        PAG_GPIO.set        = true;
        PAG_GPIO.ie         = PAD_IE_ENABLE;
        PAG_GPIO.oen        = PAD_OEN_DISABLE;
        PAG_GPIO.pad_ctl    = PAD_MODE0;
        PAG_GPIO.ren        = PAD_REN_ENABLE,
        SystemPADConfig(PADID30,&PAG_GPIO);
             
        scuprf("Start PMU Test,RTC 10MS\n");       
        while(UART_GetStatus(UART0)&0x01);
        for(uint16_t i=0;i<1000;i++){};
        SCU_32KClkSelect(CLK_RCO_32K);      
        SCU_HClkSelect(CLK_32K_MUX_HCLK);
        for(uint16_t i=0;i<100;i++){};
            
        {
            RTC_InitInfo_Type RTC_InitStru;               
            RTC_InitStru.RTC_Interrpt = RTC_INTERRUPT_ENABLE ;
            RTC_InitStru.RTC_InterruptValue   = (10*32);
            RTC_InitStru.RTC_StartValue  = 0;
            SystemDevClockCtl(RTC_CKEn,true);
            RTC_Init(&RTC_InitStru);
            NVIC_EnableIRQ(RTC_IRQn);
        }
         SCU->ANA_CTL0   = 0xC0200000;
         SCU->SLEEP_EN   = 0xffffffff;
    }
    while(sut);

    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
    
}

//void VerifyResetHandle(uint16_t idx)
//{
//    uint32_t uart0reg = UART0->DLF; 
//    scuprf("Reset[ %d ] \n",idx);    
//    
//    SCU->CLK_DIV    = 0x005500aa;
//    GPIO->DR0       = 0x005500aa;
//    WDT->CR         = 0xE;
//    RTC->CLR        = 0x005500aa;
// 
//    UART1->DLF      = 0xe;
//  
//    SPIM1->SSIENR   = DISABLE;
//    SPIM1->IMR      = DISABLE;
//    SPIM1->BAUDR    = 0x80;

//    SPIS1->SSIENR   = DISABLE;
//    SPIS1->IMR      = DISABLE;
//    SPIS1->TXFTLR   = 0x5;
//    
//    I2SM->CCR       = 0xF;
//    I2SS->I2S_Ch.RCR= 1;
//    I2C0->IC_TAR    = 0x1234;
//    DMA->CHR[0].SAR = 0x123;  
//    
//    SPIM0->SSIENR   = DISABLE;
//    SSI_ClearInterrupt(SPIM0);
//    SPIM0->IMR      = DISABLE;
//    SPIM0->BAUDR    = 0x80;
//  
//    TIMERS->TIMER[0].LOAD_COUNT = 0x005500aa;
//    TIMERS->TIMER[1].LOAD_COUNT = 0x005500aa;
//    TIMERS->TIMER[2].LOAD_COUNT = 0x005500aa;
//    TIMERS->TIMER[3].LOAD_COUNT = 0x005500aa;
//    TIMERS->TIMER[4].LOAD_COUNT = 0x005500aa;
//    TIMERS->TIMER[5].LOAD_COUNT = 0x005500aa;
//    TIMERS->TIMER[6].LOAD_COUNT = 0x005500aa;
//    TIMERS->TIMER[7].LOAD_COUNT = 0x005500aa;
//  
//    scuprf("SCU[%X],GPIO[%X],wdt[%X],rtc[%X],UART0[%X],UART1[%X],SPIM1[%X],SPIS1[%X]\n",
//    SCU->CLK_DIV,GPIO->DR0,WDT->CR,RTC->CLR,uart0reg,UART1->DLF,SPIM1->BAUDR,SPIS1->TXFTLR);
//    scuprf("i2sm[%X],i2ss[%X],i2c[%X],RF[],BB[],dma[%X],SPIM0[%x]\n",
//    I2SM->CCR,I2SS->I2S_Ch.RCR,I2C0->IC_TAR,DMA->CHR[0].SAR,SPIM0->BAUDR);
//    scuprf("tm0[%X],tm1[%X],tm2[%X],tm3[%X],tm4[%X],tm5[%X],tm6[%X],tm7[%X]\n",
//    TIMERS->TIMER[0].LOAD_COUNT,TIMERS->TIMER[1].LOAD_COUNT,TIMERS->TIMER[2].LOAD_COUNT,TIMERS->TIMER[3].LOAD_COUNT,
//    TIMERS->TIMER[4].LOAD_COUNT,TIMERS->TIMER[5].LOAD_COUNT,TIMERS->TIMER[6].LOAD_COUNT,TIMERS->TIMER[7].LOAD_COUNT);      
//      
//    if(idx==4)
//    {
//        while(UART_GetStatus(UART0)&0x01);
//        UART0->DLF = 0xe;
//        SCU->SW_RST |=0x01<<idx;
//        uart0reg = UART0->DLF;
//        while(UART_GetStatus(UART0)&0x01);
//        UartSCUOutput();       
//    }
//    else if(idx == 0)
//    {
//         SCU->SW_RST |=0x01<<idx;
//         for(uint16_t j=0;j<100;j++);
//         SCU->CLK_EN= 0xFFFFFFFF;
//    }
//    else
//        SCU->SW_RST |=0x01<<idx;
//     
//    for(uint16_t j=0;j<100;j++);
//    
//    scuprf("Re:SCU[%X],GPIO[%X],wdt[%X],rtc[%X],UART0[%X],UART1[%X],SPIM1[%X],SPIS1[%X]\n",
//    SCU->CLK_DIV,GPIO->DR0,WDT->CR,RTC->CLR,uart0reg,UART1->DLF,SPIM1->BAUDR,SPIS1->TXFTLR);
//    scuprf("i2sm[%X],i2ss[%X],i2c[%X],RF[],BB[],dma[%X],SPIM0[%x]\n",
//    I2SM->CCR,I2SS->I2S_Ch.RCR,I2C0->IC_TAR,DMA->CHR[0].SAR,SPIM0->BAUDR);
//    scuprf("tm0[%X],tm1[%X],tm2[%X],tm3[%X],tm4[%X],tm5[%X],tm6[%X],tm7[%X]\n",
//    TIMERS->TIMER[0].LOAD_COUNT,TIMERS->TIMER[1].LOAD_COUNT,TIMERS->TIMER[2].LOAD_COUNT,TIMERS->TIMER[3].LOAD_COUNT,
//    TIMERS->TIMER[4].LOAD_COUNT,TIMERS->TIMER[5].LOAD_COUNT,TIMERS->TIMER[6].LOAD_COUNT,TIMERS->TIMER[7].LOAD_COUNT);      
//}


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
        scuprf("i:%d, idx:%d,reg:%X,val:%X\n",idx,index,(*reg),val);
}

void VerifyResetHandle(uint16_t idx)
{
    bool sut = true;
    uint32_t uart0reg = UART0->DLF; 
    scuprf("Reset[ %d ] \n",idx);    
    
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
    verifyCheckScuIs(idx,14,&BB->BB_CTL[0],0x1234,&sut);
    //verifyCheckScuIs(idx,15,&I2C0->IC_TAR,0x1234,&sut);
    verifyCheckScuIs(idx,16,&DMA->CHR[0].SAR,0x123,&sut);
    
    verifyCheckScuIs(idx,17,&SPIM0->BAUDR,0x80,&sut);
    verifyCheckScuIs(idx,19,&USB->GINTMSK,0x66,&sut);
//    verifyCheckScuIs(idx,20,&USB->GUSBCFG,1,&sut);

//    verifyCheckScuIs(idx,21,&TIMERS->TIMER[0].LOAD_COUNT,0x005500aa,&sut);
//    verifyCheckScuIs(idx,22,&TIMERS->TIMER[1].LOAD_COUNT,0x005500aa,&sut);
//    verifyCheckScuIs(idx,23,&TIMERS->TIMER[2].LOAD_COUNT,0x005500aa,&sut);
//    verifyCheckScuIs(idx,24,&TIMERS->TIMER[3].LOAD_COUNT,0x005500aa,&sut);
//    verifyCheckScuIs(idx,25,&TIMERS->TIMER[4].LOAD_COUNT,0x005500aa,&sut);
//    verifyCheckScuIs(idx,26,&TIMERS->TIMER[5].LOAD_COUNT,0x005500aa,&sut);
//    verifyCheckScuIs(idx,27,&TIMERS->TIMER[6].LOAD_COUNT,0x005500aa,&sut);
//    verifyCheckScuIs(idx,28,&TIMERS->TIMER[7].LOAD_COUNT,0x005500aa,&sut);
//      
    verifyCheckScuIs(idx,29,&BB->BB_CTL[1],0x1234,&sut);
    verifyCheckScuIs(idx,30,&GPIO->DR0,0x005500aa,&sut);
    scuprf("sut:%s \n",sut?"true":"false");
      
    if(!sut){
        scuprf("Re:SCU[%X],GPIO[%X],wdt[%X],rtc[%X],UART0[%X],UART1[%X],SPIM1[%X],SPIS1[%X]\n",
        SCU->CLK_DIV,GPIO->DR0,WDT->CR,RTC->CLR,uart0reg,UART1->DLF,SPIM1->BAUDR,SPIS1->TXFTLR);
        scuprf("i2sm[%X],i2ss[%X],i2c[%X],RF[],BB[%x],dma[%X],SPIM0[%x],usb[%x],FC[%x]\n",
        I2SM->CCR,I2SS->I2S_Ch.RCR,I2C0->IC_TAR,BB->BB_CTL[0],DMA->CHR[0].SAR,SPIM0->BAUDR,&USB->GINTMSK,FC->CCR);
        scuprf("tm0[%X],tm1[%X],tm2[%X],tm3[%X],tm4[%X],tm5[%X],tm6[%X],tm7[%X]\n",
        TIMERS->TIMER[0].LOAD_COUNT,TIMERS->TIMER[1].LOAD_COUNT,TIMERS->TIMER[2].LOAD_COUNT,TIMERS->TIMER[3].LOAD_COUNT,
        TIMERS->TIMER[4].LOAD_COUNT,TIMERS->TIMER[5].LOAD_COUNT,TIMERS->TIMER[6].LOAD_COUNT,TIMERS->TIMER[7].LOAD_COUNT);      
    }
             
}

bool cmd_VerifyAppSCUCase23(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    scuprf("SCU  App Reset case 23\n");
    verify_SendCid(cmd,&idx);
    SCU->CLK_EN = 0xffffffff;
    {
        uint32_t ctlReset = 0x1FE1FFFF;
        for(uint16_t i = 0;i<32;i++)
        {
            if(ctlReset >> i & 0x01ul)
                VerifyResetHandle(i);
        } 
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyAppSCUCase24(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    scuprf("SCU  App SWD Switch case 24\n");
    verify_SendCid(cmd,&idx);
    SCU->CLK_EN = 0xffffffff;
    {
        PADConfig_Type PAG_InitStru;
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        
        
        for(uint16_t md = PAD_MODE3;md<PAD_MODE6;md++)
        {
            PAG_InitStru.pad_ctl    = md;
            SystemPADConfig(PADID4,&PAG_InitStru);
            SystemPADConfig(PADID5,&PAG_InitStru);
            scuprf("SCU  App SWD MD:%d Switch  1\n",md);
            scuprf("SCU  App SWD MD:%d Switch  2\n",md);
            scuprf("SCU  App SWD MD:%d Switch  3\n",md);
            MCU_Sleep(3);
        }
        
        PAG_InitStru.pad_ctl    = 0;
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        scuprf("SCU  App SWD MD:%d Switch  1\n",0);


        
    }
    MCU_Sleep(5);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyAppSCUCase25(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    PADConfig_Type PAG_InitStru;
    scuprf("SCU  App Case25 ,Test Mode 3-5\n");
    verify_SendCid(cmd,&idx);
    {
 
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        for(uint16_t md = PAD_MODE3;md<PAD_MODE6;md++)
        {
            PAG_InitStru.pad_ctl    = md;

            for(PADId_Type pad_id = PADID0; pad_id<PADID29; pad_id++)
                SystemPADConfig(pad_id,&PAG_InitStru);
           
            MCU_Sleep(2);
        }
            
    }
    PAG_InitStru.pad_ctl    = 0;
    SystemPADConfig(PADID0,&PAG_InitStru);
    scuprf("SCU Test Mode 3-5,completed\n");
    MCU_Sleep(5);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyAppSCUCase26(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    scuprf("SCU  App Case26 CM core Reset\n");
    verify_SendCid(cmd,&idx);
    {
 
       MCU_Sleep(3);
       NVIC_CoreReset();
            
    }
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyAppSCUCase27(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    scuprf("SCU  App Case27 CM Reset\n");
    verify_SendCid(cmd,&idx);
    {
 
       MCU_Sleep(3);
       NVIC_SystemReset();
            
    }
    
    MCU_Sleep(2);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

SCU_TypeDef SCUDefaultValue = {
    .CLK_EN     =0xFFFFFFFF,                   /*!< Offset: 0x000  */  
    .SW_RST     =0x0,                   /*!< Offset: 0x004  */
    .CLK_CTL    =0x0,                   /*!< Offset: 0x008  */
    .CLK_DIV    =0x0,                   /*!< Offset: 0x00c  */
    .SYS_CONFIG =0x0,                   /*!< Offset: 0x010  */
    .SYS_STATUS =0x0,                   /*!< Offset: 0x014  */
    .SLEEP_EN   =0x0,                   /*!< Offset: 0x018  */
    .PWR_STATUS =0x1,                   /*!< Offset: 0x01c  */
    .DEV_CONFIG =0x20000,                   /*!< Offset: 0x020  */
    .DEV_STATUS =0x0,                   /*!< Offset: 0x024  */
    .IO_CONFIG  =0x0,                   /*!< Offset: 0x028  */
    .IO_STATUS  =0x0,                   /*!< Offset: 0x02c  */
    .CLK_DIV1   =0x0,                   /*!< Offset: 0x030  */
    .CLK_DIV2   =0x0,                   /*!< Offset: 0x034  */
    
    .SEND_CMD   =0x0,                  /*!< Offset: 0x038  */
    .SEND_DATA  =0x0,                  /*!< Offset: 0x03C  */
    .READ_CMD   =0x0,                  /*!< Offset: 0x040  */
    .READ_DATA  =0x0,                  /*!< Offset: 0x044  */
    .ANA_CTL0   =0x0FFF80F0,                  /*!< Offset: 0x048  */
    .ANA_CTL1   =0x89942452,                  /*!< Offset: 0x04C  */
    .ANA_CTL2   =0x0F20AAA4,                  /*!< Offset: 0x050  */
    .ANA_CTL3   =0x2C608238,                  /*!< Offset: 0x054  */
    .ANA_CTL4   =0x92722800,                  /*!< Offset: 0x058  */
    .ANA_STATUS0   =0x0,               /*!< Offset: 0x05C  */
    .ANA_STATUS1   =0x0,               /*!< Offset: 0x060  */
    
    /*!< Offset: 0x064-0X70 */
    .TIMERS_DIV[0] =0x0,.TIMERS_DIV[1] =0x0,.TIMERS_DIV[2] =0x0,.TIMERS_DIV[3] =0x0,
    .TIMERS_DIV[4] =0x0,.TIMERS_DIV[5] =0x0,.TIMERS_DIV[6] =0x0,.TIMERS_DIV[7] =0x0,
    /*!< Offset: 0X74-0x114 */ 
    .PAD_CFG[0]=0x0,.PAD_CFG[8 ]=0x0,.PAD_CFG[16]=0x0,.PAD_CFG[24]=0x0,.PAD_CFG[32]=0x0,
    .PAD_CFG[1]=0x0,.PAD_CFG[9 ]=0x0,.PAD_CFG[17]=0x0,.PAD_CFG[25]=0x0,.PAD_CFG[33]=0x0,
    .PAD_CFG[2]=0x0,.PAD_CFG[10]=0x0,.PAD_CFG[18]=0x0,.PAD_CFG[26]=0x0,.PAD_CFG[34]=0x0,
    .PAD_CFG[3]=0x0,.PAD_CFG[11]=0x0,.PAD_CFG[19]=0x0,.PAD_CFG[27]=0x0,.PAD_CFG[35]=0x0,
    .PAD_CFG[4]=0x0,.PAD_CFG[12]=0x0,.PAD_CFG[20]=0x0,.PAD_CFG[28]=0x0,.PAD_CFG[36]=0x0,
    .PAD_CFG[5]=0x0,.PAD_CFG[13]=0x0,.PAD_CFG[21]=0x0,.PAD_CFG[29]=0x0,.PAD_CFG[37]=0x0,
    .PAD_CFG[6]=0x0,.PAD_CFG[14]=0x0,.PAD_CFG[22]=0x0,.PAD_CFG[30]=0x0,.PAD_CFG[38]=0x0,
    .PAD_CFG[7]=0x0,.PAD_CFG[15]=0x0,.PAD_CFG[23]=0x0,.PAD_CFG[31]=0x0,.PAD_CFG[39]=0x0,
    
    .BB_WAKEUP_MASK_L=0x0,             /*!< Offset: 0X118 */
    .BB_WAKEUP_MASK_H=0x0,             /*!< Offset: 0X11c */
    .BB_WAKEUP_MASK_SEL=0x0            /*!< Offset: 0X120 */

};

bool cmd_VerifyAppSCUCase28(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    scuprf("SCU  App Case28 Check Scu Default value\n");
    verify_SendCid(cmd,&idx);
    {
        volatile uint32_t *addr1 = (uint32_t *)SCU;
        volatile uint32_t *addr2 = (uint32_t *)&SCUDefaultValue;

        for(uint32_t i=0;i<sizeof((uint32_t *)SCU);i++)
        {
            if((*addr1) != (*addr2))
            {
                scuprf("SCU Default Error; addr:%X\n",addr1);
                sut = false;
                break;
            }
            addr1++;
            addr2++;
        }
        
        SCU->SW_RST |=0x01;
        
        for(uint32_t i=0;i<sizeof((uint32_t *)SCU);i++)
        {
            if((*addr1) != (*addr2))
            {
                scuprf("ReSCU Default Error; addr:%X\n",addr1);
                sut = false;
                break;
            }
            addr1++;
            addr2++;
        }      
    }
    
    MCU_Sleep(2);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyAppSCUCase29(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    scuprf("SCU  App Case29 HCLK Sel DIV\n");
    verify_SendCid(cmd,&idx);
    {
        SCU_HClkSelect(CLK_HCLK_MUX);
        MCU_Sleep(2);
        
        for(SCU_96MDIVCtl_Type clk = CLK_12M ;clk<=CLK_96M;clk++)
        {
            SCU_ClockSelectDivControl(clk);
            scuprf("SCU_ClockSelectDivControl=[%d]\n",clk);
            MCU_Sleep(2);
        }
        MCU_Sleep(2);
        scuprf("SCU HCLK Sel DIV Completed !!\n");
    }
    
    MCU_Sleep(2);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyAppSCUCase30(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    scuprf("SCU  App Case30 SCU WP Reg Scan\n");
    verify_SendCid(cmd,&idx);
    {
        uint32_t ctl = 0xFFFFFFFF;
        SCU->BB_WAKEUP_MASK_L = 0;
        scuprf("SCU BB_WAKEUP_MASK_L\n");
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                SetAnaReg(SCU->BB_WAKEUP_MASK_L,1,idx);
                SetAnaReg(SCU->BB_WAKEUP_MASK_L,0,idx);
            }	
        }
        SCU->BB_WAKEUP_MASK_H = 0;
        scuprf("SCU BB_WAKEUP_MASK_H\n");
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                SetAnaReg(SCU->BB_WAKEUP_MASK_H,1,idx);
                SetAnaReg(SCU->BB_WAKEUP_MASK_H,0,idx);
            }	
        }
        scuprf("SCU BB_WAKEUP_MASK_SEL\n");
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                SetAnaReg(SCU->BB_WAKEUP_MASK_SEL,1,idx);
                SetAnaReg(SCU->BB_WAKEUP_MASK_SEL,0,idx);
            }	
        }
        scuprf("SCU IO CONMFIG\n");
        for(uint16_t idx=0;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                SetAnaReg(SCU->IO_CONFIG,1,idx);
                SetAnaReg(SCU->IO_CONFIG,0,idx);
            }	
        }
        scuprf("SCU SYS_CONFIG\n");
        for(uint16_t idx=4;idx<32;idx++)
        {
            if((ctl>>idx & 0x01))
            {
                SetAnaReg(SCU->SYS_CONFIG,1,idx);
                SetAnaReg(SCU->SYS_CONFIG,0,idx);
            }	
        }        
       
        scuprf("SCU BB Reg\n");
        memset((void *)&BB->BB_CTL,0,sizeof(BB->BB_CTL));
        MCU_Sleep(2);
        memset((void *)&BB->BB_CTL,0xFFFFFFFF,sizeof(BB->BB_CTL));
        MCU_Sleep(2);
        memset((void *)&BB->BB_CTL,0,sizeof(BB->BB_CTL));
        
        MCU_Sleep(2);
        scuprf("SCU SYS RST\n");
        SCU->SW_RST =0xFFFFFFFF;   
    }
    
    MCU_Sleep(2);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyAppSCUCase31(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
	
    verify_SendCid(cmd,&idx);
    PADConfig_Type PAG_GPIO;
    memset(&PAG_GPIO,0,sizeof(PADConfig_Type));
    PAG_GPIO.set        = true;
    PAG_GPIO.ie         = PAD_IE_ENABLE;
    PAG_GPIO.oen        = PAD_OEN_DISABLE;
    PAG_GPIO.pad_ctl    = PAD_MODE0;
    PAG_GPIO.ren        = PAD_REN_ENABLE,
    SystemPADConfig(PADID30,&PAG_GPIO);

    scuprf("Test Mode 0 Sleep no WK \n"); 
    { 
        Verrify_SendPinConnect(TMODE_0);
        Verrify_SendPinConnect(TMODE_DIS);
        Verrify_SendPinConnect(TMODE_EN);
        scuprf("IO S[%X]\n",SCU->IO_STATUS);  
        MCU_Sleep(3);
        SCU_32KClkSelect(CLK_RCO_32K);      
        SCU_HClkSelect(CLK_32K_MUX_HCLK);
        for(uint16_t i=0;i<100;i++){};
        SCU->ANA_CTL0   = 0xC0200000;
        SCU->SLEEP_EN   = 0xffffffff; 
    }	
    
    MCU_Sleep(10);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyAppSCUCase32(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
	
    verify_SendCid(cmd,&idx);
    PADConfig_Type PAG_GPIO;
    memset(&PAG_GPIO,0,sizeof(PADConfig_Type));
    PAG_GPIO.set        = true;
    PAG_GPIO.ie         = PAD_IE_ENABLE;
    PAG_GPIO.oen        = PAD_OEN_DISABLE;
    PAG_GPIO.pad_ctl    = PAD_MODE0;
    PAG_GPIO.ren        = PAD_REN_ENABLE,
    SystemPADConfig(PADID30,&PAG_GPIO);

    scuprf("Test Mode 0 Sleep and WK \n"); 
    {
        Verrify_SendPinConnect(TMODE_0);
        Verrify_SendPinConnect(TMODE_DIS);
        Verrify_SendPinConnect(TMODE_EN);
        scuprf("IO S[%X]\n",SCU->IO_STATUS);  
        MCU_Sleep(3);
        SCU_32KClkSelect(CLK_RCO_32K);      
        SCU_HClkSelect(CLK_32K_MUX_HCLK);
        for(uint16_t i=0;i<100;i++){};
            
        {
            RTC_InitInfo_Type RTC_InitStru;               
            RTC_InitStru.RTC_Interrpt = RTC_INTERRUPT_ENABLE ;
            RTC_InitStru.RTC_InterruptValue   = (10*32);
            RTC_InitStru.RTC_StartValue  = 0;
            SystemDevClockCtl(RTC_CKEn,true);
            RTC_Init(&RTC_InitStru);
            NVIC_EnableIRQ(RTC_IRQn);
        }
         SCU->ANA_CTL0   = 0xC0200000;
         SCU->SLEEP_EN   = 0xffffffff;
    }	
    
    MCU_Sleep(10);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



//HCLK Pre Select
uint32_t P_scu_HClkSelect(SCU_HclkSelect_Type st, uint32_t clk)
{
	clk &= ~(0x03<<3);
	clk |=  (st&0x03)<<3;
    return clk;
}

//PCLK Pre Select
uint32_t P_scu_PClkPreSelect(SCU_Pclk_Pre_Select_Type st,uint32_t clk)
{
    clk &= ~(0x0f<<10);
    clk |=  (st&0x0f)<<10;
    return clk;  
}
//96M DIV Select
uint32_t P_scu_ClockSelectDivControl(SCU_96MDIVCtl_Type st,uint32_t clk)
{   
    clk &= ~0x03;
    clk |= st&0x03;
    return clk;
}

bool cmd_VerifyAppSCUCase33(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
	uint32_t step=0x30;
    uint32_t clk;
    verify_SendCid(cmd,&idx);
    scuprf("Simu HCLK96M,PCLK 24M, \n"); 
    {
        SCU_PClkSelect(HCLK_DIV_2_PCLK);
        MCU_Sleep(1); 
        clk = SCU->CLK_CTL;
        clk = P_scu_HClkSelect(CLK_OSC26m,clk);
        clk = P_scu_PClkPreSelect(HCLK_2_PLCK_PRE,clk);
        SCU->CLK_CTL = clk;
        
        MCU_Sleep(1); 
        verify_clk_rw_IP(&step,&sut,0x11110000+idx++);step++;
        MCU_Sleep(1);
        
        clk = SCU->CLK_CTL;
        clk = P_scu_HClkSelect(CLK_HCLK_MUX,clk);
        clk = P_scu_PClkPreSelect(HCLK_DIV04,clk);
        clk = P_scu_ClockSelectDivControl(CLK_96M,clk);
        SCU->CLK_CTL = clk;
        MCU_Sleep(1); 
        verify_clk_rw_IP(&step,&sut,0x11110000+idx++);step++;
        MCU_Sleep(1);

        clk = SCU->CLK_CTL;
        clk = P_scu_HClkSelect(CLK_OSC26m,clk);
        clk = P_scu_PClkPreSelect(HCLK_2_PLCK_PRE,clk);
        SCU->CLK_CTL = clk;
        MCU_Sleep(1); 
        verify_clk_rw_IP(&step,&sut,0x11110000+idx++);step++;
        MCU_Sleep(1);

        clk = SCU->CLK_CTL;
        clk = P_scu_HClkSelect(CLK_HCLK_MUX,clk);
        clk = P_scu_PClkPreSelect(HCLK_DIV08,clk);
        clk = P_scu_ClockSelectDivControl(CLK_96M,clk);
        SCU->CLK_CTL = clk;
        
        MCU_Sleep(1); 
        verify_clk_rw_IP(&step,&sut,0x11110000+idx++);step++;
        MCU_Sleep(1);    
    }	
    
    MCU_Sleep(2);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyAppSCUCase34(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
	uint32_t step=0x30;
    verify_SendCid(cmd,&idx);
    scuprf("HCLK96M,PCLK 24M, \n"); 
    {
        SCU_PClkSelect(HCLK_DIV_2_PCLK);

        
        SCU_HClkSelect(CLK_OSC26m);
        SCU_PClkPreSelect(HCLK_2_PLCK_PRE);
        MCU_Sleep(1); 
        verify_clk_rw_IP(&step,&sut,0x11110000+idx++);step++;
        MCU_Sleep(1);
        SCU_PClkPreSelect(HCLK_DIV04);
        SCU_ClockSelectDivControl(CLK_96M);
        SCU_HClkSelect(CLK_HCLK_MUX);
        
        MCU_Sleep(1); 
        verify_clk_rw_IP(&step,&sut,0x11110000+idx++);step++;
        MCU_Sleep(1);
        SCU_HClkSelect(CLK_OSC26m);
        SCU_PClkPreSelect(HCLK_2_PLCK_PRE);
        
        MCU_Sleep(1); 
        verify_clk_rw_IP(&step,&sut,0x11110000+idx++);step++;
        MCU_Sleep(1);
        SCU_PClkPreSelect(HCLK_DIV08);
        SCU_ClockSelectDivControl(CLK_96M);
        SCU_HClkSelect(CLK_HCLK_MUX);
        
        MCU_Sleep(1); 
        verify_clk_rw_IP(&step,&sut,0x11110000+idx++);step++;
        MCU_Sleep(1);    
    }	
    
    MCU_Sleep(2);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


bool cmd_VerifyAppSCUCase35(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
	uint32_t step=0x30;
    uint32_t clk;
    verify_SendCid(cmd,&idx);
    scuprf("Simu HCLK96M,PCLK 96M,PClkSelect DIV PCLK \n"); 
    {
        SCU_PClkSelect(HCLK_DIV_2_PCLK);
        MCU_Sleep(1); 
        
        clk = SCU->CLK_CTL;
        clk = P_scu_HClkSelect(CLK_HCLK_MUX,clk);
        clk = P_scu_ClockSelectDivControl(CLK_96M,clk);
        clk = P_scu_PClkPreSelect(HCLK_2_PLCK_PRE,clk);
        SCU->CLK_CTL = clk;
        
        MCU_Sleep(1); 
        verify_clk_rw_IP(&step,&sut,0x11110000+idx++);step++;
        MCU_Sleep(1);
        
        
    }	
    
    MCU_Sleep(2);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyAppSCUCase36(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
	uint32_t step=0x30;
    uint32_t clk;
    verify_SendCid(cmd,&idx);
    scuprf("Simu HCLK96M,PCLK 96M,PClkSelect 2 PCLK \n"); 
    {
        SCU_PClkSelect(HCLK_2_PLCK);
        MCU_Sleep(1); 
        
        clk = SCU->CLK_CTL;
        clk = P_scu_HClkSelect(CLK_HCLK_MUX,clk);
        clk = P_scu_ClockSelectDivControl(CLK_96M,clk);
        clk = P_scu_PClkPreSelect(HCLK_2_PLCK_PRE,clk);
        SCU->CLK_CTL = clk;
        
        MCU_Sleep(1); 
        verify_clk_rw_IP(&step,&sut,0x11110000+idx++);step++;
        MCU_Sleep(1);  
    }	
    
    MCU_Sleep(2);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



#endif





