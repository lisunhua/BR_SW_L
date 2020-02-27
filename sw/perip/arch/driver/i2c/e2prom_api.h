/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    e2prom_api.h
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

#ifndef __I2C_EEPORM_API_H__
#define __I2C_EEPORM_API_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool eeprom_init(void);
bool eeprom_reset(void);
bool eeprom_byte_write(uint16_t addr, uint8_t data);
bool eeprom_page_write(uint16_t addr, uint8_t *buffer, uint16_t length);  //MAX Size is 64 bytes
bool eeprom_block_write(uint16_t addr, uint8_t *buffer, uint16_t length); //Size is not limited, but the interior needs to wait for the stop condition.
bool eeprom_cur_addr_read(uint8_t *buffer, uint16_t length);
bool eeprom_random_addr_read(uint16_t addr, uint8_t *buffer, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif /* __I2C_EEPORM_API_H__ */

