/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_ssc.h
 * @brief    This file provides  the ssic firmware functions.
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * @date    14. Augest 2018
 * @version V1.0.0
 * @author  MEIGER
*/

#ifndef __BT1051Axx_SSIC_H__
#define __BT1051Axx_SSIC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "BR00x_config.h"
#include "BR00x_ssi.h"
#include "BR00x_ssi_common.h"

typedef enum
{
    SSIC_SLAVE_SELECT_TOHHLE_DISABLE,
    SSIC_SLAVE_SELECT_TOHHLE_ENABLE,
   
}SSIC_SlaveSelectToggleEn_Type;

typedef enum
{
    SSIC_SPI_HYPERBUS_DISABLE,
    SSIC_SPI_HYPERBUS_ENABLE,
}SSIC_SpiHyperbusFrameFormatEn_Type;


typedef enum
{
    TT0,            /* Instruction and Address will be sent in Standard SPI Mode.*/
    TT1,            /* Instruction will be sent in Standard SPI Mode and Address will be sent in the mode specified by XIP_CTRL.SPI_FRF. */
    TT2,            /* Both Instruction and Address will be sent in the mode specified by XIP_CTRL.SPI_FRF.*/
    TT3,            /*Reserved */
}SSIC_Transfer_Type;


typedef enum
{
    ADDR_L0,        /* No address */
    ADDR_L4,        /* 4  bit  address length */
    ADDR_L8,        /* 8  bit  address length */
    ADDR_L12,       /* 12 bit  address length */
    ADDR_L16,       /* 16 bit  address length */
    ADDR_L20,       /* 20 bit  address length */
    ADDR_L24,       /* 24 bit  address length */
    ADDR_L28,       /* 28 bit  address length */
    ADDR_L32,       /* 32 bit  address length */
    ADDR_L36,       /* 36 bit  address length */
    ADDR_L40,       /* 40 bit  address length */
    ADDR_L44,       /* 44 bit  address length */
    ADDR_L48,       /* 48 bit  address length */
    ADDR_L52,       /* 52 bit  address length */
    ADDR_L56,       /* 56 bit  address length */
    ADDR_L60,       /* 60 bit  address length */
}SSIC_AddressLength_Tpye;


/*Dual/Quad/Octal mode instruction length in bits.  */
typedef enum
{
    INST_L0,        /* No Instruction*/
    INST_L4,        /* 4 bit Instruction length */
    INST_L8,        /* 8 bit Instruction length */
    INST_L16,       /* 16 bit Instruction length */
}SSIC_InstructionLength_Type;

typedef enum
{
    MBL_2,          /* Mode bits length equal to 2*/
    MBL_4,          /* Mode bits length equal to 4*/
    MBL_8,          /* Mode bits length equal to 8*/
    MBL_16,         /* Mode bits length equal to 16*/
        
}SSIC_XipModeBitsLength_Type;

typedef struct
{
    uint16_t               clock_divider;         /*Fsclk_out = Fssi_clk/SCKDV */

    SSI_DataFarmeSize_Type  frame_format_size;    /*SPI FLASH -> SSI_DATA_FRAME_SIZE_8BIT */
                                                  /*XIP FLASH -> SSI_DATA_FRAME_SIZE_32BIT */
    SSI_FrameFormat_Type ssi_frame_format;
    SSI_SerialClockPhase_Type clock_phase;
    SSI_SerialClockPolarity_Type clock_polarity;
    SSI_TransferMode_Type    transfer_mode;
    SSI_SlaveOutputEnable_Type  slave_output_enable;
    SSI_ShiftRegisterLoop_Type operation_mode;
    SSIC_SlaveSelectToggleEn_Type  slave_select_toggle_en;
    SSI_ControlFrameSize_Type control_farme_size;
   
    SSI_SpiFrameFormat_Type spi_frame_format;
    SSIC_SpiHyperbusFrameFormatEn_Type  spi_hyperbus_en;
    
    uint16_t data_frames_number;
    uint32_t slaves_select;
    uint32_t tx_fifo_threshold_level;
    uint32_t tx_fifo_start_fifo_level;
    uint32_t rx_fifo_threshold_level;

    bool dma_rx_en;
    bool dma_tx_en;

    uint32_t dma_rx_data_level;
    uint32_t dma_tx_data_level;   
    uint32_t unmask_interrupt; 
    
}SSIC_InitInfo_Type;




typedef struct
{
    SSI_SpiFrameFormat_Type  spi_frame_format;
    SSIC_Transfer_Type transfer_type;
    SSIC_AddressLength_Tpye  address_length;
    SSIC_InstructionLength_Type  instruction_length;
    bool xip_mode_bit_en;
    uint32_t  wait_cycles; /*Wait cycles in Dual/Quad/Octal mode between control frames transmit and 
                                data reception. Specified as number of SPI clock cycles.*/
    bool xip_dfs_hsize_hburst_en;
    bool xip_spi_ddr_en;
    bool instruction_ddr_enable;
    bool read_data_strobe_enable;
    bool xip_instruction_enable;
    bool xip_continuous_transfer_enable;
    bool xip_spi_hyerbus_format_enable;
    bool xip_rxds_signaling_enable; /*Enable rxds signaling during address and command phase of Hypebus transfer*/

    SSIC_XipModeBitsLength_Type  xip_mode_bit_length;
    
    /*Enables XIP pre-fetch functionality in DWC_ssi. Once
    enabled DWC_ssi will pre-fetch data frames from next
    contigous location, to reduce the latency for the upcoming
    contiguous transfer. If the next XIP request is not contigous
    then pre-fetched bits will be discarded.*/
    bool xip_pre_fetch_enable;
 
    uint16_t  xip_inst_transfer_opcode;
    uint16_t  xip_wrap_transfer_opcode;
    uint32_t  slaves_enbale_mask;

    bool spi_clk_stretch_en;
    bool spi_data_mask_en;

    uint8_t   xip_time_out;
    
}SSIC_XIP_InitInfo_Type;


/**
  * @brief  Initializes the SSIC peripheral according to the specified
  *         parameters in the SSIC_InitInfo_Type.
  *
  * @param  SSIC_InitStru: pointer to a SSIC_InitInfo_Type structure that
  *         contains the configuration information for the specified SSIC peripheral.
  * @retval None
  */
void SSIC_Init(SSIC_InitInfo_Type* SSIC_InitStru);

/**
  * @brief  Initializes the SSIC peripheral according to the specified
  *         parameters in the SSIC_XIP_InitInfo_Type.
  *
  * @param  SSIC_XipInitStru: pointer to a SSIC_XIP_InitInfo_Type structure that
  *         contains the configuration information for the specified SSIC peripheral.
  * @retval None
  */
void SSIC_XipInit(SSIC_XIP_InitInfo_Type *SSIC_XipInitStru);

/**
  * @brief  Clear XIP Receive FIFO Overflow Interrupt.
  *
  * @param Nome
  * @retval None
  */
bool  SSIC_XipClrRxOwInterrupt(void);


/**
  * @brief Set the enable state of the SSIC XIP mode.
  *
  * @param status : true (Enable)/ false (Disable)
  * @retval None
  */
void SSIC_XipSetEnable(bool status );


/**
  * @brief Get the enable state of the SSIC XIP mode.
  *
  * @param None
  * @retval status : true (Enable)/ false (Disable)
  */
bool SSIC_XipGetEnable(void);

/**
  * @brief Set the transmission mode of SSIC through the mode parameter,.
  *
  * @param tx_mode : Select the mode you want to set
  * @retval None
  */
bool SSIC_SetTransferMode(SSI_TransferMode_Type tx_mode);


#ifdef __cplusplus
}
#endif

#endif /* __BT1051Axx_SSIC_H__ */

