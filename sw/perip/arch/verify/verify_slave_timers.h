/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_timers.h
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

#ifndef __VERIFY_SLAVE_TIMERS_
#define __VERIFY_SLAVE_TIMERS_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

bool cmd_VerifyRegisterTimersCase1(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyRegisterTimersCase2(uint32_t cmd, uint8_t *param_line,uint16_t len);

bool cmd_VerifyAppTimersCase1(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppTimersCase2(uint32_t cmd, uint8_t *param_line,uint16_t len);
bool cmd_VerifyAppTimersCase3(uint32_t cmd, uint8_t *param_line,uint16_t len);
    
#endif //__VERIFY_SLAVE_TIMER_

