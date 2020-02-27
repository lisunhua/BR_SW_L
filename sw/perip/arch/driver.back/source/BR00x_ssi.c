/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_ssi.c
 * @brief    This file provides the ssi firmware functions.
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
#include "BR00x_ssi.h"
#include "system_BR00x.h"
#include "BR00x_ssi_if.h"
#include "BR00x_ssi_common.h"


//* SSI control Param*//
static uint32_t SSI_GetCrotrolParams(SSI_TypeDef   *SSIx , SSI_InitInof_Type *SSI_InitStru)
{
    return  ((SSI_InitStru->spi_frame_format<< SSI_CTRLR0_SPI_FRF_POS)|\
                ( SSI_InitStru->frame_format_size_32<< SSI_CTRLR0_DFS_32_POS)|\
                ( SSI_InitStru->frame_format_size_16<< SSI_CTRLR0_DFS_POS)|\
                ( SSI_InitStru->control_farme_size<< SSI_CTRLR0_CFS_POS)|\
                ( SSI_InitStru->operation_mode<< SSI_CTRLR0_SRL_POS)|\
                ( SSI_InitStru->slave_output_enable<< SSI_CTRLR0_SLV_OE_POS)|\
                ( SSI_InitStru->transfer_mode<< SSI_CTRLR0_TMOD_POS)|\
                ( SSI_InitStru->clock_polarity<< SSI_CTRLR0_SCPOL_POS)|\
                ( SSI_InitStru->clock_phase<< SSI_CTRLR0_SCPH_POS)|\
                ( SSI_InitStru->SSI_frame_format<< SSI_CTRLR0_FRF_POS));
}


/**
  * @brief  This function is used to update the frameFormat of the SSI
  *
  * @param  SSIx: pointer to a SSI.
  * @param frame_format : Select the SSI_SpiFrameFormat_Type you want to set
  *
  * @retval None
  */
bool  SSI_UpdateFrameFormat(SSI_TypeDef   *SSIx,SSI_SpiFrameFormat_Type frame_format)
{
    if(!SSIx)
        return false;
    
    SSIx->SSIENR = DISABLE;
    SSI_ClearInterrupt(SSIx);

    if(frame_format)
        SSIx->CTRLR0|=frame_format<<SSI_CTRLR0_SPI_FRF_POS;
    else
        SSIx->CTRLR0 &=SSI_CTRLR0_SPI_FRF_MSK;
    
   SSIx->SSIENR = ENABLE;
   
   return true;
}

/**
  * @brief  This function is used to update the control parameters of the SSI
  *
  * @param  SSIx: pointer to a SSI.
  * @param  SSI_InitStru: pointer to a SSI_InitInfo_Type structure that
  *         contains the configuration information for the specified SSI peripheral.
  *
  * @retval None
  */
void SSI_UpdataControlParams(SSI_TypeDef   *SSIx,SSI_InitInof_Type *SSI_InitStru)
{
    SSIx->SSIENR = DISABLE;
    SSI_ClearInterrupt(SSIx);
    SSIx->CTRLR0 = SSI_GetCrotrolParams(SSIx,SSI_InitStru);
    SSIx->SSIENR = ENABLE;
}


/**
  * @brief Set the transmission mode of SSI through the mode parameter,.
  * @param  SSIx: pointer to a SSI.
  * @param tx_mode : Select the mode you want to set
  * @retval None
  */
bool SSI_SetTransferMode(SSI_TypeDef   *SSIx,SSI_TransferMode_Type tx_mode)
{
    if (!SSIx)
        return false;

    if(((SSIx->CTRLR0 & SSI_CTRLR0_TMOD_MSK) >> \
        SSI_CTRLR0_TMOD_POS )  ==tx_mode)
        return true;
    
    SSIx->SSIENR = DISABLE;
    SSI_ClearInterrupt(SSIx);
    SSIx->CTRLR0 &= ~SSI_CTRLR0_TMOD_MSK;
    for(uint8_t i=0;i<5;i++);
    
    SSIx->CTRLR0 |=tx_mode<<SSI_CTRLR0_TMOD_POS;

   SSIx->SSIENR = ENABLE;      
   return true;
}



/**
  * @brief  Initializes the SSI peripheral according to the specified
  *         parameters in the SSI_InitInfo_Type.
  *
  * @param  SSI_InitStru: pointer to a SSI_InitInfo_Type structure that
  *         contains the configuration information for the specified SSI peripheral.
  * @retval None
  */
void SSI_Init(SSI_TypeDef   *SSIx,SSI_InitInof_Type *SSI_InitStru)
{
    //clear all interrupter 
    SSIx->SSIENR = DISABLE;
    SSI_ClearInterrupt(SSIx);
    SSIx->IMR = DISABLE;
    //NVIC_ClearPendingIRQ(SSI_InitStru->irqn);
    //NVIC_EnableIRQ(SSI_InitStru->irqn);

    SSIx->CTRLR0    = SSI_GetCrotrolParams(SSIx,SSI_InitStru);                               
    SSIx->CTRLR1    = SSI_InitStru->data_frame_num<<SSI_CTRLR1_NDF_POS;
    SSIx->BAUDR     = SSI_InitStru->clock_divider;
    SSIx->IMR       = SSI_InitStru->unmask_interrupt;

     if(SSI_InitStru->dma_rx_en)
        SSIx->DMACR |=0x01;
    else
        SSIx->DMACR &=~0x01;
    
    if(SSI_InitStru->dma_tx_en)
        SSIx->DMACR |=0x02;
    else
        SSIx->DMACR &=~0x02;
    
    SSIx->RXFTLR    = SSI_InitStru->rx_fifo_threshold_level;
    SSIx->TXFTLR    = (SSI_InitStru->tx_fifo_start_fifo_level<<15 | SSI_InitStru->tx_fifo_threshold_level);

    SSIx->DMARDLR = SSI_InitStru->dma_rx_data_level;
    SSIx->DMATDLR = SSI_InitStru->dma_tx_data_level;
        
    SSIx->SER       = 0X0001;
    SSIx->SSIENR    = ENABLE;
    
}


