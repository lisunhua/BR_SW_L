/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_ssi.h
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

#ifndef __BT1051Axx_SSI_H__
#define __BT1051Axx_SSI_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "BR00x_config.h"

#define SSI_STATUS(X)  X->SR
#define SSI_INTERRUPT_STATUS(X)  X->ISR
#define SSI_RAW_INTERRUPT_STATUS(X)  X->RISR

#define SSI_RX_FIFO_LEVEL(X)  X->RXFLR
#define SSI_TX_FIFO_LEVEL(X)  X->TXFLR

#define SSI_SET_INTERRUPT_MASK(X,Y) (X->IMR |= Y) 
#define SSI_CLEAR_INTERRUPT_MASK(X,Y)  (X->IMR &=~Y)


typedef enum
{
    SSI_DATA_FRAME_SIZE_RESERVER1,
    SSI_DATA_FRAME_SIZE_RESERVER2,
    SSI_DATA_FRAME_SIZE_RESERVER3,
    SSI_DATA_FRAME_SIZE_4BIT,
    SSI_DATA_FRAME_SIZE_5BIT,
    SSI_DATA_FRAME_SIZE_6BIT,
    SSI_DATA_FRAME_SIZE_7BIT,
    SSI_DATA_FRAME_SIZE_8BIT,
    SSI_DATA_FRAME_SIZE_9BIT,
    SSI_DATA_FRAME_SIZE_10BIT,
    SSI_DATA_FRAME_SIZE_11BIT,
    SSI_DATA_FRAME_SIZE_12BIT,
    SSI_DATA_FRAME_SIZE_13BIT,
    SSI_DATA_FRAME_SIZE_14BIT,
    SSI_DATA_FRAME_SIZE_15BIT,
    SSI_DATA_FRAME_SIZE_16BIT,
    SSI_DATA_FRAME_SIZE_17BIT,
    SSI_DATA_FRAME_SIZE_18BIT,
    SSI_DATA_FRAME_SIZE_19BIT,
    SSI_DATA_FRAME_SIZE_20BIT,
    SSI_DATA_FRAME_SIZE_21BIT,
    SSI_DATA_FRAME_SIZE_22BIT,
    SSI_DATA_FRAME_SIZE_23BIT,
    SSI_DATA_FRAME_SIZE_24BIT,
    SSI_DATA_FRAME_SIZE_25BIT,
    SSI_DATA_FRAME_SIZE_26BIT,
    SSI_DATA_FRAME_SIZE_27BIT,
    SSI_DATA_FRAME_SIZE_28BIT,
    SSI_DATA_FRAME_SIZE_29BIT,
    SSI_DATA_FRAME_SIZE_30BIT,
    SSI_DATA_FRAME_SIZE_31BIT,
    SSI_DATA_FRAME_SIZE_32BIT
}SSI_DataFarmeSize_Type;


typedef enum
{
    SSI_FRAME_FORMAT_MOTOROLA_SPI,      /*Motorola SPI Frame Format*/
    SSI_FRAME_FORMAT_TI_SSP,            /*Texas Instruments SSP Frame Format */ 
    SSI_FRAME_FORMAT_NSM,               /*National Semiconductors Microwire Frame Format*/ 
    SSI_FRAME_FORMAT_RES                /*Reserved*/ 
}SSI_FrameFormat_Type;

typedef enum 
{
    SSI_CLOCK_TOGGLES_MIDDLE,           /*Serial clock toggles in middle of first data bit*/
    SSI_CLOCK_TOGGLES_START             /*Serial clock toggles at start of first data bit*/
}SSI_SerialClockPhase_Type;

typedef enum
{
    SSI_INACTIVE_STATE_LOW,
    SSI_INACTIVE_STATE_HIGH
}SSI_SerialClockPolarity_Type;

typedef enum
{
    SSI_TRANSMIT_AND_RECEIVE,
    SSI_ONLY_TRANSMIT,
    SSI_ONLY_RECEIVE,
    SSI_EEPROM_READ
}SSI_TransferMode_Type;


typedef enum
{
    SSI_SLAVE_TXD_IS_ENABLE,
    SSI_SLAVE_TXD_IS_DISABLE
}SSI_SlaveOutputEnable_Type;

typedef enum
{
    SSI_NORMAL_MODE,
    SSI_TEST_MODE,
}SSI_ShiftRegisterLoop_Type;

typedef enum
{
    SSI_CONTROL_FRAME_1BIT_WORD,
    SSI_CONTROL_FRAME_2BIT_WORD,
    SSI_CONTROL_FRAME_3BIT_WORD,
    SSI_CONTROL_FRAME_4BIT_WORD,
    SSI_CONTROL_FRAME_5BIT_WORD,
    SSI_CONTROL_FRAME_6BIT_WORD,
    SSI_CONTROL_FRAME_7BIT_WORD,
    SSI_CONTROL_FRAME_8BIT_WORD,
    SSI_CONTROL_FRAME_9BIT_WORD,
    SSI_CONTROL_FRAME_10BIT_WORD,
    SSI_CONTROL_FRAME_11BIT_WORD,
    SSI_CONTROL_FRAME_12BIT_WORD,
    SSI_CONTROL_FRAME_13BIT_WORD,
    SSI_CONTROL_FRAME_14BIT_WORD,
    SSI_CONTROL_FRAME_15BIT_WORD,
    SSI_CONTROL_FRAME_16BIT_WORD,
}SSI_ControlFrameSize_Type;


typedef enum
{
    STANDARD_SPI_FORMAT = 0,
    DUAL_SPI_FORMAT = 1,
    QUAD_SPI_FORMAT =2,
    QCTAL_SPI_FORMAT =3,
}SSI_SpiFrameFormat_Type;

typedef enum
{
    FIFO_MASK_ALL                   =  0,
    TX_FIFO_EMPTY_UNMASK            = (1<<0),
    TX_FIFO_OVERFLOW_UNMASK         = (1<<1),
    RX_FIFO_UNDERFLOW_UNMASK        = (1<<2),
    RX_FIFO_OVERFLOW_UNMASK         = (1<<3),
    RX_FIFO_FULL_UNMASK             = (1<<4),
    TX_FIFO_MULTI_MASTER_UNMASK     = (1<<5),
    XIP_RX_FIFO_OVERFLOW_UNMSAK     = (1<<6),
}SSI_UnMaskInterrupt_Type;

typedef enum
{
    SSI_busy,
    SSI_tx_fifo_not_full,
    SSI_tx_fifo_empty,
    SSI_rx_fifo_not_empty,
    SSI_rx_fifo_full_full,
    SSI_tx_error,
    SSI_data_colliision, /*Data Collision Error */
    
}SSI_Status_Type;


typedef enum
{
    SSI_tx_emty,
    SSI_tx_fifo_overflow,
    SSI_rx_underflow,
    SSI_rx_fifo_overflow,
    SSI_rx_fifo_full,
    SSI_multi_master_contention,/*This bit field is not present if the DW_apb_ssi is configured as a serial-slave device.*/
    xip_rx_fifo_overflow,
    
}SSI_InterruptStatus_Type;

typedef struct
{
    uint16_t    clock_divider;       /*Fsclk_out = Fssi_clk/SCKDV */
    uint32_t    data_frame_num;

    SSI_FrameFormat_Type SSI_frame_format;
    SSI_SerialClockPhase_Type clock_phase;
    SSI_SerialClockPolarity_Type clock_polarity;
    SSI_TransferMode_Type    transfer_mode;
    SSI_SlaveOutputEnable_Type  slave_output_enable;
    SSI_ShiftRegisterLoop_Type operation_mode;
    SSI_ControlFrameSize_Type control_farme_size;

    SSI_DataFarmeSize_Type frame_format_size_16;
    SSI_DataFarmeSize_Type frame_format_size_32;

    SSI_SpiFrameFormat_Type spi_frame_format;
    
    bool dma_rx_en;
    bool dma_tx_en;
    
    uint32_t   unmask_interrupt; 
    
    uint32_t tx_fifo_threshold_level;
    uint32_t tx_fifo_start_fifo_level;
    uint32_t rx_fifo_threshold_level;

    uint32_t dma_rx_data_level;
    uint32_t dma_tx_data_level;
   
}SSI_InitInof_Type;





/**
  * @brief  Initializes the SSI peripheral according to the specified
  *         parameters in the SSI_InitInfo_Type.
  *
  * @param  SSI_InitStru: pointer to a SSI_InitInfo_Type structure that
  *         contains the configuration information for the specified SSI peripheral.
  * @retval None
  */
void SSI_Init(SSI_TypeDef   *SSIx,SSI_InitInof_Type *SSI_InitStru);


/**
  * @brief  This function is used to update the control parameters of the SSI
  *
  * @param  SSIx: pointer to a SSI.
  * @param  SSI_InitStru: pointer to a SSI_InitInfo_Type structure that
  *         contains the configuration information for the specified SSI peripheral.
  *
  * @retval None
  */
void SSI_UpdataControlParams(SSI_TypeDef   *SSIx,SSI_InitInof_Type *SSI_InitStru);

/**
  * @brief Set the transmission mode of SSI through the mode parameter,.
  * @param  SSIx: pointer to a SSI.
  * @param tx_mode : Select the mode you want to set
  * @retval None
  */
bool SSI_SetTransferMode(SSI_TypeDef   *SSIx,SSI_TransferMode_Type tx_mode);

/**
  * @brief  This function is used to update the frameFormat of the SSI
  *
  * @param  SSIx: pointer to a SSI.
  * @param frame_format : Select the SSI_SpiFrameFormat_Type you want to set
  *
  * @retval None
  */
bool  SSI_UpdateFrameFormat(SSI_TypeDef   *SSIx,SSI_SpiFrameFormat_Type frame_format);







#ifdef __cplusplus
}
#endif

#endif /* __BT1051Axx_SSI_H__ */

