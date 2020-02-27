/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_ssic.c
 * @brief    This file provides the ssic firmware functions.
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
#include "BR00x_ssic.h"
#include "system_BR00x.h"
#include "BR00x_ssic_if.h"

#define MAX_FIFO_DEP   32
static uint32_t  SSIC_XipGetControlCfg(SSIC_XIP_InitInfo_Type *SSIC_XipInitStru);
static uint32_t  SSIC_XipSetSpiControlCfg(SSIC_XIP_InitInfo_Type *SSIC_XipInitStru);
static uint32_t  SSIC_GetControlCfg(SSIC_InitInfo_Type *SSIC_InitStru);

static uint32_t  SSIC_XipGetControlCfg(SSIC_XIP_InitInfo_Type *SSIC_XipInitStru)
{
    return  (((SSIC_XipInitStru->spi_frame_format  <<SSIC_XIP_CTRL_FRF_POS ) & SSIC_XIP_CTRL_FRF_MSK) |
        ((SSIC_XipInitStru->transfer_type <<SSIC_XIP_CTRL_TRANS_TYPE_POS ) & SSIC_XIP_CTRL_TRANS_TYPE_MSK)|
        ((SSIC_XipInitStru->address_length <<SSIC_XIP_CTRL_ADDR_L_POS )& SSIC_XIP_CTRL_ADDR_L_MSK)|
        ((SSIC_XipInitStru->instruction_length <<SSIC_XIP_CTRL_INST_L_POS )& SSIC_XIP_CTRL_INST_L_MSK)|
        ((SSIC_XipInitStru->xip_mode_bit_en <<SSIC_XIP_CTRL_MD_BITS_EN_POS )& SSIC_XIP_CTRL_MD_BITS_EN_MSK)|
        ((SSIC_XipInitStru->wait_cycles <<SSIC_XIP_CTRL_WAIT_CYCLES_POS )& SSIC_XIP_CTRL_WAIT_CYCLES_MSK)|
        ((SSIC_XipInitStru->xip_dfs_hsize_hburst_en <<SSIC_XIP_CTRL_DFS_HC_POS )& SSIC_XIP_CTRL_DFS_HC_MSK)|
        ((SSIC_XipInitStru->xip_spi_ddr_en <<SSIC_XIP_CTRL_DDR_EN_POS )& SSIC_XIP_CTRL_DDR_EN_MSK)|
        ((SSIC_XipInitStru->instruction_ddr_enable <<SSIC_XIP_CTRL_INST_DDR_EN_POS )& SSIC_XIP_CTRL_INST_DDR_EN_MSK)|
        ((SSIC_XipInitStru->read_data_strobe_enable <<SSIC_XIP_CTRL_RXDS_EN_POS )& SSIC_XIP_CTRL_RXDS_EN_MSK)|
        ((SSIC_XipInitStru->xip_instruction_enable <<SSIC_XIP_CTRL_INST_EN_POS )& SSIC_XIP_CTRL_INST_EN_MSK)|
        ((SSIC_XipInitStru->xip_continuous_transfer_enable <<SSIC_XIP_CTRL_CONT_XFER_EN_POS )& SSIC_XIP_CTRL_CONT_XFER_EN_MSK)|
        ((SSIC_XipInitStru->xip_spi_hyerbus_format_enable <<SSIC_XIP_CTRL_XIP_HYPERBUS_EN_POS )& SSIC_XIP_CTRL_XIP_HYPERBUS_EN_MSK)|
        ((SSIC_XipInitStru->xip_rxds_signaling_enable <<SSIC_XIP_CTRL_RXDS_SIG_EN_POS )& SSIC_XIP_CTRL_RXDS_SIG_EN_MSK)|
        ((SSIC_XipInitStru->xip_mode_bit_length <<SSIC_XIP_CTRL_XIP_MB_POS )& SSIC_XIP_CTRL_XIP_MB_MSK)|
        ((SSIC_XipInitStru->xip_pre_fetch_enable <<SSIC_XIP_CTRL_XIP_PREFETCH_EN_POS )& SSIC_XIP_CTRL_XIP_PREFETCH_EN_MSK));
        
        
}


static uint32_t  SSIC_XipSetSpiControlCfg(SSIC_XIP_InitInfo_Type *SSIC_XipInitStru)
{
    return (((SSIC_XipInitStru->transfer_type<<SSIC_SPI_CTRLR0_TRANS_TYPE_POS) & SSIC_SPI_CTRLR0_TRANS_TYPE_MSK) |
        ((SSIC_XipInitStru->address_length <<SSIC_SPI_CTRLR0_ADDR_L_POS) & SSIC_SPI_CTRLR0_ADDR_L_MSK) |
        ((SSIC_XipInitStru->xip_mode_bit_en<<SSIC_SPI_CTRLR0_XIP_MD_BIT_EN_POS) & SSIC_SPI_CTRLR0_XIP_MD_BIT_EN_MSK) |
        ((SSIC_XipInitStru->instruction_length<<SSIC_SPI_CTRLR0_INST_L_POS) & SSIC_SPI_CTRLR0_INST_L_MSK) |
        ((SSIC_XipInitStru->wait_cycles<< SSIC_SPI_CTRLR0_WAIT_CYCLES_POS) & SSIC_SPI_CTRLR0_WAIT_CYCLES_MSK)|
        ((SSIC_XipInitStru->xip_spi_ddr_en<<SSIC_SPI_CTRLR0_SPI_DDR_EN_POS) & SSIC_SPI_CTRLR0_SPI_DDR_EN_MSK) |
        ((SSIC_XipInitStru->instruction_ddr_enable <<SSIC_SPI_CTRLR0_INST_DDR_EN_POS) & SSIC_SPI_CTRLR0_INST_DDR_EN_MSK) |
        ((SSIC_XipInitStru->read_data_strobe_enable<<SSIC_SPI_CTRLR0_SPI_RXDS_EN_POS) & SSIC_SPI_CTRLR0_SPI_RXDS_EN_MSK) |
        ((SSIC_XipInitStru->xip_dfs_hsize_hburst_en<<SSIC_SPI_CTRLR0_XIP_DFS_HC_POS) & SSIC_SPI_CTRLR0_XIP_DFS_HC_MSK) |
        ((SSIC_XipInitStru->xip_instruction_enable<<SSIC_SPI_CTRLR0_XIP_INST_EN_POS) & SSIC_SPI_CTRLR0_XIP_INST_EN_MSK) |
        ((SSIC_XipInitStru->xip_continuous_transfer_enable<<SSIC_SPI_CTRLR0_SSIC_XIP_CONT_XFER_EN_POS) & SSIC_SPI_CTRLR0_SSIC_XIP_CONT_XFER_EN_MSK)|
        ((SSIC_XipInitStru->spi_data_mask_en<<SSIC_SPI_CTRLR0_SPI_DM_EN_POS) & SSIC_SPI_CTRLR0_SPI_DM_EN_MSK) |
        ((SSIC_XipInitStru->xip_rxds_signaling_enable<<SSIC_SPI_CTRLR0_SPI_RXDS_SIG_EN_POS) & SSIC_SPI_CTRLR0_SPI_RXDS_SIG_EN_MSK) |
        ((SSIC_XipInitStru->xip_mode_bit_length <<SSIC_SPI_CTRLR0_XIP_MBL_POS) & SSIC_SPI_CTRLR0_XIP_MBL_MSK) |
        ((SSIC_XipInitStru->xip_pre_fetch_enable<<SSIC_SPI_CTRLR0_XIP_PREFETCH_EN_POS) & SSIC_SPI_CTRLR0_XIP_PREFETCH_EN_MSK) |
        ((SSIC_XipInitStru->spi_clk_stretch_en<<SSIC_SPI_CTRLR0_CLK_STRETCH_EN_POS) & SSIC_SPI_CTRLR0_CLK_STRETCH_EN_MSK));
        
        
}


static uint32_t SSIC_GetControlCfg(SSIC_InitInfo_Type *SSIC_InitStru)
{
    return (((SSIC_InitStru->frame_format_size<< SSIC_CTRLR0_DFS_POS) & SSIC_CTRLR0_DFS_MSK)|
        ((SSIC_InitStru->ssi_frame_format<< SSIC_CTRLR0_FRF_POS)&SSIC_CTRLR0_FRF_MSK)|
        (( SSIC_InitStru->clock_phase<< SSIC_CTRLR0_SCPH_POS)&SSIC_CTRLR0_SCPH_MSK)|
        (( SSIC_InitStru->clock_polarity<< SSIC_CTRLR0_SCPOL_POS)&SSIC_CTRLR0_SCPOL_MSK)|
        (( SSIC_InitStru->transfer_mode<< SSIC_CTRLR0_TMOD_POS)&SSIC_CTRLR0_TMOD_MSK)|
        (( SSIC_InitStru->slave_output_enable<< SSIC_CTRLR0_SLV_OE_POS)&SSIC_CTRLR0_SLV_OE_MSK)|
        (( SSIC_InitStru->operation_mode<< SSIC_CTRLR0_SRL_POS)&SSIC_CTRLR0_SRL_MSK)|
        (( SSIC_InitStru->slave_select_toggle_en<< SSIC_CTRLR0_SSTE_POS)&SSIC_CTRLR0_SSTE_MSK)|
        (( SSIC_InitStru->control_farme_size<< SSIC_CTRLR0_CFS_POS)&SSIC_CTRLR0_CFS_MSK)|
        (( SSIC_InitStru->spi_frame_format<< SSIC_CTRLR0_SPI_FRF_POS)&SSIC_CTRLR0_SPI_FRF_MSK)|
        (( SSIC_InitStru->spi_hyperbus_en<< SSIC_CTRLR0_SPI_HYPERBUS_EN_POS)&SSIC_CTRLR0_SPI_HYPERBUS_EN_MSK));

}


/**
  * @brief Set the transmission mode of SSIC through the mode parameter,.
  *
  * @param tx_mode : Select the mode you want to set
  * @retval None
  */
bool SSIC_SetTransferMode(SSI_TransferMode_Type tx_mode)
{

    if(((SPIM0->CTRLR0 & SSIC_CTRLR0_TMOD_MSK) >> \
        SSIC_CTRLR0_TMOD_POS )  ==tx_mode)
        return true;
    
    SPIM0->SSIENR = DISABLE;
    SSI_ClearInterrupt(SPIM0);
    SPIM0->CTRLR0 &= ~SSIC_CTRLR0_TMOD_MSK;
    for(uint8_t i=0;i<5;i++);
    
    SPIM0->CTRLR0 |=tx_mode<<SSIC_CTRLR0_TMOD_POS;

   SPIM0->SSIENR = ENABLE;      
   return true;
}

/**
  * @brief  Initializes the SSIC peripheral according to the specified
  *         parameters in the SSIC_InitInfo_Type.
  *
  * @param  SSIC_InitStru: pointer to a SSIC_InitInfo_Type structure that
  *         contains the configuration information for the specified SSIC peripheral.
  * @retval None
  */
void SSIC_Init(SSIC_InitInfo_Type *SSIC_InitStru)
{
    SSIC_XipSetEnable(false);
    
    //clear all interrupter 
    SPIM0->SSIENR = DISABLE;
    SSI_ClearInterrupt(SPIM0);
    SPIM0->IMR = DISABLE;
    NVIC_ClearPendingIRQ(SPIM0_IRQn);
    //for(uint16_t i=0;i<500;i++);

    SPIM0->CTRLR0 = SSIC_GetControlCfg(SSIC_InitStru);
                                    
    SPIM0->CTRLR1 = SSIC_InitStru->data_frames_number<<SSIC_CTRLR1_NDF_POS;
    SPIM0->BAUDR = SSIC_InitStru->clock_divider;
    SPIM0->IMR  = SSIC_InitStru->unmask_interrupt;
    
    if(SSIC_InitStru->dma_rx_en)
        SPIM0->DMACR |=0x01;
    else
        SPIM0->DMACR &=~0x01;
    
    if(SSIC_InitStru->dma_tx_en)
        SPIM0->DMACR |=0x02;
    else
        SPIM0->DMACR &=~0x02;
    
    SPIM0->DMARDLR = SSIC_InitStru->dma_rx_data_level;
    SPIM0->DMATDLR = SSIC_InitStru->dma_tx_data_level;
    
    
    SPIM0->RXFTLR =   SSIC_InitStru->rx_fifo_threshold_level;
    SPIM0->TXFTLR =  (SSIC_InitStru->tx_fifo_start_fifo_level<<15 | SSIC_InitStru->tx_fifo_threshold_level);
        
    SPIM0->SER = SSIC_InitStru->slaves_select;
    SPIM0->SSIENR = ENABLE;

}

/**
  * @brief  Initializes the SSIC peripheral according to the specified
  *         parameters in the SSIC_XIP_InitInfo_Type.
  *
  * @param  SSIC_XipInitStru: pointer to a SSIC_XIP_InitInfo_Type structure that
  *         contains the configuration information for the specified SSIC peripheral.
  * @retval None
  */
void SSIC_XipInit(SSIC_XIP_InitInfo_Type *SSIC_XipInitStru)
{   
    SSIC_XipSetEnable(false); 

    SPIM0->SSIENR = DISABLE;
    SPIM0->SPI_CTRLR0  = SSIC_XipSetSpiControlCfg(SSIC_XipInitStru);;

    /**This Register is valid only when SSIC_CONCURRENT_XIP_EN is equal to 1. 
    This register is used to store the control information that the XIP 
    transfer will be using in the concurrent mode.**/
    /** Our IP  SSIC_CONCURRENT_XIP_EN ==1  **/
    SPIM0->XIP_CTRL = SSIC_XipGetControlCfg(SSIC_XipInitStru);
  
    
    SPIM0->XIP_INCR_INST = SSIC_XipInitStru->xip_inst_transfer_opcode;
    SPIM0->XIP_WRAP_INST = SSIC_XipInitStru->xip_wrap_transfer_opcode;
    SPIM0->XIP_SER = SSIC_XipInitStru->slaves_enbale_mask;
    SPIM0->XIP_CNT_TIME_OUT =SSIC_XipInitStru->xip_time_out;
   
    SPIM0->XIP_MODE_BITS = 0;
    SPIM0->SSIENR =ENABLE;
    
    SSIC_XipSetEnable(true); // Enable XIP
}


/**
  * @brief Set the enable state of the SSIC XIP mode.
  *
  * @param status : true (Enable)/ false (Disable)
  * @retval None
  */
void SSIC_XipSetEnable(bool status)
{
    if(status)
        SCU->DEV_CONFIG |= (1<<8);
    else
        SCU->DEV_CONFIG &= ~(1<<8);   
}



/**
  * @brief Get the enable state of the SSIC XIP mode.
  *
  * @param status : true (Enable)/ false (Disable)
  * @retval None
  */
bool SSIC_XipGetEnable(void)
{
   return (((SCU->DEV_CONFIG>>8)&0x01)? true :false);
}


/**
  * @brief  Clear XIP Receive FIFO Overflow Interrupt.
  *
  * @param Nome
  * @retval None
  */
bool  SSIC_XipClrRxOwInterrupt(void)
{
    return (SPIM0->XRXOICR&0x01);
}






