/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_master.c
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

#include <string.h>
#include <stdlib.h>
#include <stdint.h>


#ifdef BR_DUAL

#include "verify_message.h"
#include "cm_printf.h"
static SocRole  G_SOC_ROLE = SOC_MASTER;

bool GetSocRole(void)
{
    return G_SOC_ROLE;
}
    
void SetSocRole(SocRole role)
{
    G_SOC_ROLE = role;
    cm_printf("SocRole:%s\n",role?"SOC_MASTER":"SOC_SLAVE");    
}

#endif




