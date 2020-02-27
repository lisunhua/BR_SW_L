/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_register_handle.h
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

#ifndef __VERIFY_REGISTER_HANDLE
#define __VERIFY_REGISTER_HANDLE

#include "BR00x_config.h"

typedef  struct 
{
    bool rd;
    bool wt;
    uint16_t  regid;
    uint32_t  attr;
    volatile  uint32_t *reg;
}RegisterCell;

bool Verify_RegisterHandle(const RegisterCell *regList,uint16_t sz,uint16_t idx);
bool Verify_RegisterUARTHandle(const RegisterCell *regList,uint16_t sz ,volatile uint32_t *reg,bool log,uint16_t idx);
bool Verify_RegisterDAMHandle(const RegisterCell *regList,uint16_t sz,uint16_t idx);
#endif 

