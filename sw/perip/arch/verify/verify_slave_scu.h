/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_scu.h
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

#ifndef __VERIFY_SLAVE_SCU_
#define __VERIFY_SLAVE_SCU_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

bool cmd_VerifyRegisterSCUCase1(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyRegisterSCUCase2(uint32_t cmd, uint8_t *param_line,uint16_t len);

bool cmd_VerifyAppSCUCase1(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase2(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase3(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase4(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase5(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase6(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase7(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase8(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase9(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase10(uint32_t cmd, uint8_t *param_line,uint16_t len);
//not 
bool cmd_VerifyAppSCUCase11(uint32_t cmd, uint8_t *param_line,uint16_t len);//b
bool cmd_VerifyAppSCUCase13(uint32_t cmd, uint8_t *param_line,uint16_t len);//d


bool cmd_VerifyAppSCUCase12(uint32_t cmd, uint8_t *param_line,uint16_t len);//c
bool cmd_VerifyAppSCUCase14(uint32_t cmd, uint8_t *param_line,uint16_t len);//e


bool cmd_VerifyAppSCUCase15(uint32_t cmd, uint8_t *param_line,uint16_t len);

bool cmd_VerifyAppSCUCase16(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase17(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase18(uint32_t cmd, uint8_t *param_line,uint16_t len);

bool cmd_VerifyAppSCUCase19(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase20(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase21(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase22(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase23(uint32_t cmd, uint8_t *param_line,uint16_t len);

bool cmd_VerifyAppSCUCase24(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase25(uint32_t cmd, uint8_t *param_line,uint16_t len);

bool cmd_VerifyAppSCUCase26(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase27(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase28(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase29(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase30(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase31(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase32(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase33(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase34(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase35(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppSCUCase36(uint32_t cmd, uint8_t *param_line,uint16_t len);

#endif //__VERIFY_SLAVE_SCU_

