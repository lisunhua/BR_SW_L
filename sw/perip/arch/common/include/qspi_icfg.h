/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    br_qspi_iocfg.h
 * @brief    .
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

#ifndef __BR_QSPI_I_CONFIG_H__
#define __BR_QSPI_I_CONFIG_H__

#include "BR00x_config.h"


#if  defined(BR002)||defined(BR003)

typedef enum
{
    QSPI_PIN27 = 27,
    QSPI_PIN28,
    QSPI_PIN29,
    QSPI_PIN30,
    QSPI_PIN31,
    QSPI_PIN32,
    QSPI_PIN33,
    QSPI_PIN34,
    QSPI_PIN_END
}QspiPin_Type;

// typedef enum
// {
//     QSPI_CLK,
//     QSPI_CS,
//     QSPI_D0,
//     QSPI_D1,
//     QSPI_D2,
//     QSPI_D3,
// }QspiPinConfig_Type;

typedef enum
{
    QSPI_CS,
    QSPI_D0,
    QSPI_CLK,
    QSPI_D3,
    QSPI_D2,
    QSPI_D1,
    QSPI_END
}QspiPinConfig_Type;

bool SCUQspiConfig(QspiPin_Type pin,QspiPinConfig_Type tp);

#endif


#endif /*__BR_QSPI_I_CONFIG_H__*/

