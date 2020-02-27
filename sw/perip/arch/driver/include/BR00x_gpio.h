/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_gpio.c
 * @brief    This file provides all the GPIO firmware functions.
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
 * @author  Asher
*/

#ifndef __BT1051Axx_GPIO_H__
#define __BT1051Axx_GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "BR00x_config.h"

typedef enum GPIO_PinId {
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15,
    GPIO_PIN_16,
    GPIO_PIN_17,
    GPIO_PIN_18,
    GPIO_PIN_19,
    GPIO_PIN_20,
    GPIO_PIN_21,
    GPIO_PIN_22,
    GPIO_PIN_23,
    GPIO_PIN_24,
    GPIO_PIN_25,
    GPIO_PIN_26,
    GPIO_PIN_27,
    GPIO_PIN_28,
    GPIO_PIN_29,
    GPIO_PIN_30,
    GPIO_PIN_31,
    GPIO_PIN_32,
    GPIO_PIN_33,
    GPIO_PIN_END,
} GPIO_PinId_Type;

typedef enum GPIO_PinDir {
    GPOP_DIR_IN,                                    /*!< Set the pin direction to input */
    GPOP_DIR_OUT                                    /*!< Set the pin direction to output */
} GPIO_PinDir_Type;

typedef enum GPIO_PinMode {
    GPIO_MODE_SOFTWARE,                             /*!< Set pin control mode to software */
    GPIO_MODE_HARDWARE                              /*!< Set pin control mode to hardware */
} GPIO_PinMode_Type;

typedef enum GPIO_IntType {
    GPIO_INTTYPE_LEVEL,                             /*!< Set interrput type to trigger with a level */
    GPIO_INTTYPE_EDGE                               /*!< Set interrput type to trigger with an edge */
} GPIO_IntType_Type;

typedef enum GPIO_IntPolarity {
    GPIO_INTPOL_ACTIVELOW,                          /*!< Set interrupt polarity to low level trigger. */
    GPIO_INTPOL_ACTIVEHIGH                          /*!< Set interrupt polarity to high level trigger. */
} GPIO_IntPolarity_Type;

#define IS_VAILD_PIN(_pin)              (_pin < GPIO_PIN_END)

typedef struct GPIO_InitInfo {
    GPIO_PinId_Type pin;                            /*!< Pin number */
    GPIO_PinDir_Type dir;                           /*!< Pin direction */
    GPIO_PinMode_Type mode;                         /*!< Pin mode */
    FunctionalState int_en;                         /*!< Pin interrupt enable */
    FunctionalState int_unmask;                       /*!< Pin interrput unmask enable */
    GPIO_IntType_Type int_type;                     /*!< Pin interrupt type */
    GPIO_IntPolarity_Type int_pol;                  /*!< Pin interrupt polarity */
    FunctionalState debounce_en;                    /*!< Pin debounce enable */
} GPIO_InitInfo_Type;

/**
  * @brief  Deinitializes the GPIO peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void GPIO_DeInit(void);

/**
  * @brief  Initializes the GPIO peripheral according to the specified
  *         parameters in the GPIO_InitInfo_Type.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitInfo_Type structure that
  *         contains the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_InitInfo_Type *init_info);

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIO_Pin:  specifies the port bit to read.
  *   This parameter can be GPIO_PIN_x where x can be (0..GPIO_PIN_END).
  * @retval The input port pin value.
  */
FlagStatus GPIO_ReadBit(GPIO_PinId_Type pin);
/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIO_Pin: specifies the port bit to be written.
  *   This parameter can be one of GPIO_PIN_x where x can be (0..GPIO_PIN_END).
  * @param  BitVal: specifies the value to be written to the selected bit.
  *   This parameter can be one of the BitAction enum values:
  *     @arg Bit_RESET: to clear the port pin
  *     @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_PinId_Type pin, uint8_t bit_val);

/**
  * @brief  Reads the interrupt status for specified port pin.
  * @param  GPIO_Pin:  specifies the port interrupt status to read.
  *   This parameter can be GPIO_PIN_x where x can be (0..GPIO_PIN_END).
  * @retval The interrupt status for the specified port pin.
  */
FlagStatus GPIO_ReadIntBit(GPIO_PinId_Type pin);

/**
  * @brief  Reads the raw interrupt status for specified port pin.
  * @param  GPIO_Pin:  specifies the port raw interrupt status to read.
  *   This parameter can be GPIO_PIN_x where x can be (0..GPIO_PIN_END).
  * @retval The raw interrupt status for the specified port pin.
  */
FlagStatus GPIO_ReadRawIntBit(GPIO_PinId_Type pin);

/**
  * @brief  Clear the interrupt status for specified port pin.
  * @param  GPIO_Pin:  specifies the port raw interrupt status to clear.
  *   This parameter can be GPIO_PIN_x where x can be (0..GPIO_PIN_END).
  * @retval None
  */
void GPIO_ClrIntBit(GPIO_PinId_Type pin);

#ifdef __cplusplus
}
#endif

#endif /* __BT1051Axx_GPIO_H__ */

