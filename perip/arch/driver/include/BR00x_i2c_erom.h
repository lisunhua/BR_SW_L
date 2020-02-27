/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR1051Axx_i2c_eeprom.h
 * @brief    This file provides all the i2c_eeprom firmware functions.
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

#ifndef __BT1051Axx_I2C_EEPORM_H__
#define __BT1051Axx_I2C_EEPORM_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "BR00x_config.h"



/**
  * @brief  A write operation requires two 8-bit data word addresses 
  *    following the device address word and acknowledgment..
  * @param  addr: The first address of the data writer.
  * @param  data :The data will be write to the eeprom
  * @retval None
  */
void  EEPROM_WriteByte(uint16_t addr ,uint8_t data);

/**
  * @brief A page write is initiated the same way as a byte write, 
  *     but the microcontroller does not send a stop condition after 
  *      the first data word is clocked in .the microcontroller can 
  *     transmit up to 63 more data words
  * @param  addr: The first address of the data writer.
  * @param  data :The data pointer will be write to the FALSH
  * @param  dlen :The data length
  * @retval None
  */
void  EEPROM_WritePage(uint16_t addr ,uint8_t *data,uint16_t dlen);

/**
  * @brief The internal data word address counter maintains the last
  *       address accessed during the last read or write operation,
  *       incremented by one
  * @retval  current data;
  */
uint8_t  EEPROM_ReadCurrentByte(void);

/**
  * @brief  A random read requires a "dummy" byte write sequence to load in the data
  *       word address
  * @param  addr: The first address of the data read.
  * @retval  current data;
  */
uint16_t  EEPROM_ReadByte(uint16_t addr );


/**
  * @brief  Sequential reads are initiated by either a current address read or a random address read
  * @param  addr: The first address of the data writer.
  * @param  data :The number read from addr is stored in this data
  * @param  dlen :The number you need to read
  * @retval None
  */
void EEPROM_SequentialRead(uint16_t addr,uint8_t *data,uint16_t len);




#ifdef __cplusplus
}
#endif

#endif /* __BT1051Axx_I2C_EEPORM_H__ */

