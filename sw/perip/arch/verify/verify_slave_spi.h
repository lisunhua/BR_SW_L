/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_spi.h
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

#ifndef __VERIFY_SLAVE_SPI_
#define __VERIFY_SLAVE_SPI_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

bool cmd_VerifyRegisterSPIM0Case2(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyRegisterSPIM1Case2(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyRegisterSPIS1Case2(uint32_t cmd, uint8_t *param_line,uint16_t len);

bool cmd_VerifyAppSPIM0Case1(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSPIM0Case2(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSPIM0Case3(uint32_t cmd, uint8_t *param_line,uint16_t len);
//bool cmd_VerifyAppSPIM0Case4(uint32_t cmd, uint8_t *param_line,uint16_t len);

bool cmd_VerifyAppSPIM1Case1(uint32_t cmd, uint8_t *param_line,uint16_t len);

//dual cpu
bool cmd_VerifyDualAppSPI1Case1(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyDualAppSPI1Case2(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyDualAppSPI1Case3(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyDualAppSPI1Case4(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyDualAppSPI1Case5(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyDualAppSPI1Case6(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyDualAppSPI1Case7(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyDualAppSPI1Case8(uint32_t cmd, uint8_t *param_line,uint16_t len);


//bool cmd_VerifyAppSPIS1Case1(uint32_t cmd, uint8_t *param_line,uint16_t len);


#endif //__VERIFY_SLAVE_SPI_

