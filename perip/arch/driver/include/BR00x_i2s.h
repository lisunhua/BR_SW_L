/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_i2s.c
 * @brief    This file provides all the i2s firmware functions.
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

#ifndef __BT1051Axx_I2S_H__
#define __BT1051Axx_I2S_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "BR00x_config.h"


#define  I2S_CHANNLE_MAPS(X)  (1UL<<X)


typedef enum
{
    I2S_RX_AVAILABLE_DAM,
    I2S_RX_FIFO_OVERRUN,
    I2S_TX_FIFO_EMPTY,
    I2S_TX_FIFO_OVERRUN,
    
}I2S_Interrupt_Type;

typedef enum
{
    CLOCK_CYCLES_16,
    CLOCK_CYCLES_24,
    CLOCK_CYCLES_32,
}I2S_Clock_Type;

typedef enum
{
    NO_CLOCK_GATING,
    GATING_CLOCK_CYCLES_12,
    GATING_CLOCK_CYCLES_16,
    GATING_CLOCK_CYCLES_20,
    GATING_CLOCK_CYCLES_24,
}I2S_ClockGating_Type;


typedef enum
{
    DATA_RX  = 0x01<<0,
    DATA_TX  = 0x01<<1,
    DATA_TX_RX = 0x03,
}I2S_Dircetion_Type;

typedef enum
{
    IGNORE_WORD_LENGTH,
    RESOLUTION_12_BIT,
    RESOLUTION_16_BIT,
    RESOLUTION_20_BIT,
    RESOLUTION_24_BIT,
    RESOLUTION_32_BIT

}I2S_DataResolution_t;

typedef enum
{
    TRIGGER_LEVEL_1,
    TRIGGER_LEVEL_2,
    TRIGGER_LEVEL_3,
    TRIGGER_LEVEL_4,
    TRIGGER_LEVEL_5,
    TRIGGER_LEVEL_6,
    TRIGGER_LEVEL_7,
    TRIGGER_LEVEL_8,
    TRIGGER_LEVEL_9,
    TRIGGER_LEVEL_10,
    TRIGGER_LEVEL_11,
    TRIGGER_LEVEL_12,
    TRIGGER_LEVEL_13,
    TRIGGER_LEVEL_14,
    TRIGGER_LEVEL_15,
    TRIGGER_LEVEL_16

}I2S_InterruptLevel_Type;

typedef struct
{
    bool  tx_fifo_overrun_interrupt_mask;   
    bool  tx_fifo_empty_interrupt_mask;
    bool  rx_fifo_overrun_interrupt_mask;
    bool  rx_dma_available_interrupt_mask;
}I2S_IntCtlMask;

typedef struct
{
    
    I2S_Dircetion_Type dirct_type;

     
    I2S_Clock_Type     clock_type;
    I2S_ClockGating_Type     clock_gating_type;
    I2S_DataResolution_t data_resl_type;
    I2S_InterruptLevel_Type interrupt_level;

    /* false : unmsak  open interrupt,
        true : mask  clean interrupt,
    */   
    I2S_IntCtlMask  IntCtlMask;
    
    
}I2S_InitInof_Type;


/**
  * @brief  Deinitializes the i2s peripheral registers to their default reset values.
  * @param  I2Sx: pointer to a I2S.
  * @retval None
  */

void I2S_DeInit(I2S_TypeDef  *I2Sx);
    
/**
  * @brief  Initializes the I2S peripheral according to the specified
  *         parameters in the I2S_InitInfo_Type.
  * @param  I2Sx: pointer to a I2S.
  * @param  I2S_InitStru: pointer to a I2S_InitInfo_Type structure that
  *         contains the configuration information for the specified I2S peripheral.
  * @retval None
  */
void I2S_Init(I2S_TypeDef *I2Sx , I2S_InitInof_Type  *I2S_InitStru);

/**
  * @brief  The left stereo data received serially from the receive channel input (sdix)
  *
  * @param  I2Sx: pointer to a I2S.
  * @retval Stereo left channel data
  */
uint32_t  I2S_GetLeftReceiveData(I2S_TypeDef *I2Sx);

/**
  * @brief  The right stereo data received serially from the receive 
  *
  * @param  I2Sx: pointer to a I2S.
  * @retval Stereo right channel data
  */
uint32_t  I2S_GetRightReceiveData(I2S_TypeDef *I2Sx );

/**
  * @brief  Sets left channel data for stereo data channels
  *
  * @param  I2Sx: pointer to a I2S.
  * @param  data: Stereo left channel data
  * @retval None
  */
void  I2S_SetLeftTransmitData(I2S_TypeDef *I2Sx ,uint32_t data);

/**
  * @brief  Sets right channel data for stereo data channels
  *
  * @param  I2Sx: pointer to a I2S.
  * @param  data: Stereo left channel data
  * @retval None
  */
void  I2S_SetRightTransmitData(I2S_TypeDef *I2Sx ,uint32_t data);


/**
  * @brief Receive Channel FIFO Reset.
  *
  * @param  I2Sx: pointer to a I2S.
  * @retval None
  */
void  I2S_ReceiveFifoReset(I2S_TypeDef *I2Sx);


/**
  * @brief Transmit Channel FIFO Reset.
  *
  * @param  I2Sx: pointer to a I2S.
  * @retval None
  */
void  I2S_TransmitFifoReset( I2S_TypeDef *I2Sx );


/**
  * @brief Sets the specified interrupt
  *
  * @param  I2Sx: pointer to a I2S.
  * @param  I2S_InitStru: pointer to a I2S_InitInfo_Type structure that
  *         contains the configuration information for the specified I2S peripheral Interrupt mask.
  * @retval None
  */
void I2S_SetInterruptMask(I2S_TypeDef *I2Sx, I2S_IntCtlMask *IntCtlMask);


/**
  * @brief I2s enabled clock
  *
  * @param  I2Sx: pointer to a I2S.
  * @param  status: true(Enable)/false(disable)
  * @retval None
  */
void I2S_GeneratrClock(I2S_TypeDef *I2Sx,bool status);

/**
  * @brief  Clear the interrupt status for RX_Overrun_Interrupt.
  * @param  I2Sx: pointer to a I2S.
  * @retval  the interrupt status
  */
bool  I2S_ClearRxOverrunInterrupt(I2S_TypeDef *I2Sx);

/**
  * @brief  Clear the interrupt status for RX_Overrun_Interrupt.
  * @param  I2Sx: pointer to a I2S.
  * @retval the interrupt status
  */
bool  I2S_ClearTxOverrunInterrupt(I2S_TypeDef *I2Sx);


/**
  * @brief  Gets an interrupt status of the specified type
  * @param  I2Sx: pointer to a I2S.
  * @param type: Select the I2S_Interrupt_Type you want to set
  * @retval the status the specified interrupt
  */
bool  I2S_GetInterruptStatus(I2S_TypeDef *I2Sx ,I2S_Interrupt_Type type);


/**
  * @brief  Reset Transmitter Block DMA
  * @param  I2Sx: pointer to a I2S.
  * @retval None
  */
void I2S_ResetTxDma(I2S_TypeDef *I2Sx );

/**
  * @brief  Reset Receiver Block DMA
  * @param  I2Sx: pointer to a I2S.
  * @retval None
  */
void I2S_ResetRxDma(I2S_TypeDef *I2Sx );


/**
  * @brief  Get a pointer address for the i2s DMATX 
  * @param  I2Sx: pointer to a I2S.
  * @retval This is the  address of i2s DMA TX 
  */
uint32_t I2S_GetTxDmaPr(I2S_TypeDef *I2Sx);

/**
  * @brief  Get a pointer address for the i2s DMARX 
  * @param  I2Sx: pointer to a I2S.
  * @retval This is the  address of i2s DMA RX 
  */
uint32_t  I2S_GetRxDmaPr(I2S_TypeDef *I2Sx );





#ifdef __cplusplus
}
#endif

#endif /* __BT1051Axx_I2S_H__ */

