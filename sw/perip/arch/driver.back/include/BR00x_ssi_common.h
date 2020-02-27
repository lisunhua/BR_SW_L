/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_ssi_common.h
 * @brief    This file provides  the ssi and ssi  firmware functions.
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

#ifndef __BT1051Axx_SSI_COMMON_H__
#define __BT1051Axx_SSI_COMMON_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "BR00x_config.h"
#include "BR00x_ssi_common.h"
#include "BR00x_ssi.h"

/**
  * @brief  Write to SSI peripheral with byte.
  *
  * @param  SSIx: pointer to a SSI or ssic.
  * @param  data: The data pointer will be write to the SSI fifo or data register.
  * @param  len: The data length.
  * @retval  true(succeed)/false(defeated)
  */

bool SSI_SendData(SSI_TypeDef *SSIx,uint8_t *data,uint16_t len);
bool SSI_SendData32(SSI_TypeDef   *SSIx,uint32_t *data,uint16_t len);



/**
  * @brief   Read from SSI peripheral..
  *
  * @param  SSIx: pointer to a SSI or ssic.
  * @param  data: The data pointer will be read to the SSI fifo or data register.
  * @param  len: The data length.
  * @retval  true(succeed)/false(defeated)
  */

bool SSI_ReadData(SSI_TypeDef *SSIx,uint8_t *data,uint16_t len);
bool SSI_ReadData32(SSI_TypeDef   *SSIx,uint32_t *data,uint16_t len);



/**
  * @brief   Receive from SSI peripheral..
  *
  * @param  SSIx: pointer to a SSI or ssic.
  * @trigger Triggers a write start.
  * @param  data: The data pointer will be read to the SSI fifo or data register.
  * @param  len: The data length.
  * @retval  true(succeed)/false(defeated)
  */
bool SSI_Receive(SSI_TypeDef *SSIx,bool trigger ,uint8_t *data,uint16_t len);


/**
  * @brief   Send to SSI peripheral with byte.
  *
  * @param  SSIx: pointer to a SSI or ssic.
  * @param  data: The data pointer will be read to the SSI fifo or data register.
  * @param  len: The data length.
  * @retval  true(succeed)/false(defeated)
  */
bool SSI_Send(SSI_TypeDef *SSIx,uint8_t *data,uint16_t len);

/**
  * @brief   Transfer from SSI peripheral..
  *
  * @param  SSIx: pointer to a SSI or ssic.
  * @param  tx: The tx pointer will be write to the SSI fifo or data register.
  * @param  tlen: The tx data length.
  * @param  rx: The tx pointer will be read to the SSI fifo or data register.
  * @param  rlen: The rx  data length.
  * @retval true(succeed)/false(defeated)
  */
bool SSI_Transfer(SSI_TypeDef *SSIx,uint8_t *tx,uint16_t tlen,uint8_t *rx,uint16_t rlen);

/**
  * @brief  Direct transfer from SSI peripheral..
  *
  * @param  SSIx: pointer to a SSI or ssic.
  * @param  tx: The tx pointer will be write to the SSI fifo or data register.
  * @param  tlen: The tx data length.
  * @param  rx: The tx pointer will be read to the SSI fifo or data register.
  * @param  rlen: The rx  data length.
  * @retval true(succeed)/false(defeated)
  */
bool SSI_Dirtransfer(SSI_TypeDef *SSIx,uint8_t *tx,uint16_t tlen,uint8_t *rx,uint16_t rlen);



/**
  * @brief  SSI Busy Flag.When set, indicates that a serial transfer is in progress; .
  *            when cleared indicates that the DWC_ssi is idle or disabled
  * @param  SSIx: pointer to a SSI or ssic.
  * @retval  true(Busy)/false(idle)
  */
bool SSI_IsBusy(SSI_TypeDef *SSIx);


/**
  * @brief  Clear Interrupts.
  *       A  read clears the ssi_txo_intr, ssi_rxu_intr, ssi_rxo_intr, and
  *       the ssi_mst_intr interrupts. Writing to this register has no
  *       effect.
  * @param  SSIx: pointer to a SSI or ssic.
  * @retval   just 0
  */
uint32_t  SSI_ClearInterrupt(SSI_TypeDef *SSIx);

/**
  * @brief   Controls the level of entries (or above) at which the receive/transmit
  *   FIFO controller triggers an interrupt. The FIFO depth is
  *   configurable in the range 0-8/32. ti  is sized to the
  *   number of address bits needed to access the FIFO. If you
  *   attempt to set this value greater than the depth of the FIFO,
  *  this field is not written and retains its current value. When the
  *  number of receive FIFO entries is greater than or equal to
  *  this value + 1, the receive FIFO full interrupt is triggered
  
  * @param  SSIx: pointer to a SSI or ssic.
  * @param  rx_thd:Receive FIFO Threshold
  * @param  tx_thd:Transmit FIFO Threshold
  * @retval  None
  */
void SSI_UpdataReceiveTransmitFifoThreshold(SSI_TypeDef *SSIx,uint16_t rx_thd,uint16_t tx_thd);


/**
  * @brief    this  sets the  number of data frames to be continuously received by the
  *  ssi. The ssi continues to receive serial data until
  *  the number of data frames received is equal to this register
  *  value plus 1, which enables you to receive up to 64 KB of
  *  data in a continuous transfer. When the ssi is 
  *  configured as a serial slave, the transfer continues for as
  *  long as the slave is selected. Therefore, this register serves
  *  no purpose and is not present when the ssi is 
  *  configured as a serial slave.
  *
  * @param  SSIx: pointer to a SSI or ssic.
  * @param  len:Number of Data Frames
  * @retval  None
  */
void SSI_UpdataReceiveNumber(SSI_TypeDef *SSIx,uint16_t len);


/**
  * @brief  The LSB for this field is always set to 0 and is unaffected by a
  *      write operation, which ensures an even value is held in this
  *      register. If the value is 0, the serial output clock (sclk_out) is
  *      disabled. The frequency of the sclk_out is derived from the
  *      following equation:
  *      Fsclk_out = Fssi_clk/SCKDV
  *      where SCKDV is any even value between 2 and 65534. For
  *      example: for Fssi_clk = 3.6864MHz and SCKDV =2
  *      Fsclk_out = 3.6864/2 = 1.8432MHz
  *
  * @param  SSIx: pointer to a SSI or ssic.
  * @param  clock_div :SSI Clock Divider.
  * @retval  None
  */
void SSI_UpdateClock(SSI_TypeDef *SSIx ,uint16_t clock_div);


/**
  * @brief  : the receive data are automatically right-justified by the 
  *     receive logic, with the upper bits of the receive FIFO zero-padded.
  *     You must right-justify transmit data before writing into the
  *     transmit FIFO. The transmit logic ignores the upper unused
  *     bits when transmitting the data
  *     Note: When SSI_SPI_MODE is either set to "Dual" or
  *     "Quad" or "Octal" mode and SPI_FRF is not set to 2'b00.
  *     - DFS value should be multiple of 2 if SPI_FRF = 01,
  *     - DFS value should be multiple of 4 if SPI_FRF = 10,
  *     - DFS value should be multiple of 8 if SPI_FRF = 11. 
  * @param  :SSIx: pointer to a SSI or ssic .
  * @retval :None
  */
void SSI_UpdataDataFarmeSize(SSI_TypeDef   *SSIx, SSI_DataFarmeSize_Type cfg);

/**
  * @brief  :A read clears the ssi_txo_intr, ssi_rxu_intr, ssi_rxo_intr, and
  *             the ssi_mst_intr interrupts. 
  * @param  :SSIx: pointer to a SSI or ssic .
  * @retval :Can only be 0
  */
uint32_t  SSI_ClearInterrupt(SSI_TypeDef *SSIx);

/**
  * @brief  :A read clears the ssi_rxo_intr interrupt.
  * @param  :SSIx: pointer to a SSI or ssic.
  * @retval :Can only be 0
  */
uint32_t SSI_ClearRxFifoOverflowInterrupt(SSI_TypeDef *SSIx);

/**
  * @brief  :A read clears the ssi_rxu_intr interrupt.
  * @param  :SSIx: pointer to a SSI or ssic.
  * @retval :Can only be 0
  */
uint32_t SSI_ClearRxFifoUnderflowInterrupt(SSI_TypeDef *SSIx);

/**
  * @brief  :A read clears the ssi_txo_intr interrupt.
  * @param  :SSIx: pointer to a SSI or ssic.
  * @retval :Can only be 0
  */
uint32_t SSI_ClearTxFifoOverflowInterrupt(SSI_TypeDef *SSIx);


#ifdef __cplusplus
}
#endif

#endif /* __BT1051Axx_SSI_COMMON_H__ */

