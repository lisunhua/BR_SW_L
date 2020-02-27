/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR1051Axx_wdt_if.h
 * @brief   This file provides all the wdt register parameter.
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

#ifndef __BT1051Axx_WDT_IF_H__
#define __BT1051Axx_WDT_IF_H__


/* Peripheral: wdt */
/* Description: watchdog. */

/* Register: WDT_CR  */
/* Description:  Control Register. */
/*bit 0 :WDT enable*/
#define BR_WDT_WDT_CR_WDT_EN_Pos (0ul) /*!< Position of WDT_EN field. */
#define BR_WDT_WDT_CR_WDT_EN_Msk (0x01ul << BR_WDT_WDT_CR_WDT_EN_Pos) /*!< Bit mask of WDT_EN field. */

/*bit 1 :Response mode.*/
#define BR_WDT_WDT_CR_RMOD_Pos (1ul) /*!< Position of RMOD field. */
#define BR_WDT_WDT_CR_RMOD_Msk (0x01ul << BR_WDT_WDT_CR_RMOD_Pos) /*!< Bit mask of RMOD field. */

/*bit 2-4 :Reset pulse length*/
#define BR_WDT_WDT_CR_RPL_Pos (2ul) /*!< Position of RPL field. */
#define BR_WDT_WDT_CR_RPL_Msk (0x03ul << BR_WDT_WDT_CR_RPL_Pos) /*!< Bit mask of RPL field. */

/* Register: WDT_TORR */
/* Description:  Timeout Range Register. */
/*bit 0-3 :TOP : Timeout period.*/
#define BR_WDT_WDT_TORR_TOP_Pos (0ul) /*!< Position of TOP field. */
#define BR_WDT_WDT_TORR_TOP_Msk (0x0ful << BR_WDT_WDT_TORR_TOP_Pos) /*!< Bit mask of TOP field. */

/*bit 4-7 :TOP_INIT : Timeout period for initialization.*/
#define BR_WDT_WDT_TORR_TOP_INIT_Pos (4ul) /*!< Position of TOP_INIT field. */
#define BR_WDT_WDT_TORR_TOP_INIT_Msk (0x0ful << BR_WDT_WDT_TORR_TOP_INIT_Pos) /*!< Bit mask of TOP_INIT field. */




#ifdef __cplusplus
}
#endif

#endif /* __BT1051Axx_WDT_H__ */

