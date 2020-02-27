/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_soc.h
 * @brief    This file provides  the soc firmware functions.
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

#ifndef __BT1051Axx_SOC_H__
#define __BT1051Axx_SOC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "BR00x_config.h"

typedef enum
{
    VREF_DEFAULT,  /*   */
    VREF_POSITION_20PER,
    VREF_POSITION_10PER,
    VREF_POSITION_30PER,
    VREF_NEGATION_40PER,
    VREF_NEGATION_30PER,
    VREF_NEGATION_20PER,
    VREF_NEGATION_10PER,
    
}SOC_PLL_VREF_Type;

typedef enum
{
    CHARGE_PUMP_OFFSET_1_00UA,  /* default */
    CHARGE_PUMP_OFFSET_1_25UA,
    CHARGE_PUMP_OFFSET_0_05UA,
    CHARGE_PUMP_OFFSET_0_75UA,
    CHARGE_PUMP_OFFSET_2_00UA,
    CHARGE_PUMP_OFFSET_2_25UA,
    CHARGE_PUMP_OFFSET_1_50UA,
    CHARGE_PUMP_OFFSET_1_75UA,
    CHARGE_PUMP_OFFSET_3_00UA,
    CHARGE_PUMP_OFFSET_3_25UA,
    CHARGE_PUMP_OFFSET_2_50UA,
    CHARGE_PUMP_OFFSET_2_75UA,
    CHARGE_PUMP_OFFSET_4_00UA,
    CHARGE_PUMP_OFFSET_4_25UA,
    CHARGE_PUMP_OFFSET_3_50UA,
    CHARGE_PUMP_OFFSET_3_75UA,
    
}SOC_PLL_ChargePump_Type;

typedef enum
{
    PRE_SCALER_BIAS_DEFAULT,
    PRE_SCALER_BIAS_NEGATION_10PER,
    PRE_SCALER_BIAS_POSITION_20PER,
    PRE_SCALER_BIAS_POSITION_10PER,
    
}SOC_PLL_PreScalerBias_Type;

typedef enum
{
    BIAS_DEFAULT,
    BIAS_NEGATION_30PER1,
    BIAS_NEGATION_30PER,
    BIAS_NEGATION_60PER,
    BIAS_NEGATION_15PER,
    BIAS_NEGATION_40PER1,
    BIAS_NEGATION_40PER,
    BIAS_NEGATION_70PER,
    
}SOC_PLL_BandWidth_Type;

typedef enum
{
    VOC_BIAS_20UA,
    VOC_BIAS_12UA,
    VOC_BIAS_32UA,
    VOC_BIAS_24UA,
    VOC_BIAS_52UA,
    VOC_BIAS_44UA,
    VOC_BIAS_64UA,
    VOC_BIAS_56UA,
}SOC_PLL_VCO_Type;

typedef enum
{
    PLL_16M_AFC_CLOCK,
    PLL_32M_AFC_CLOCK,
}SOC_PLL_AFC_Type;






/**
  * @brief  PMU Band gap enable or disable.
  * @param  status:0: enable(default)/1: disable
  * @retval None
  */
void SOC_PmuBandGap(bool status);
/**
  * @brief  Low power digital LDO enable or disable.
  * @param  status:0: enable(default)/1: disable
  * @retval None
  */
void SOC_LowPowerDLDO(bool status);
/**
  * @brief  DCDC function enable or bypass.
  * @param  status:0: bypass(default)/1: normal function
  * @retval None
  */
void SOC_DcdcForm(bool status);
/**
  * @brief  Battery detect enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_BatteryDetect(bool status);
/**
  * @brief  DCDC over load and short protection enable or disable.
  * @param  status:0: enable/1: disable(default)
  * @retval None
  */
void SOC_DcdcProtection(bool status);

/**
  * @brief  VDT in DCDC enable or disable.
  * @param  status:0: enable(default)/1: disable
  * @retval None
  */
void SOC_VdtInDcdc(bool status);

/**
  * @brief  32K crystal oscillator enable and disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_Xo33K(bool status);

/**
  * @brief  TRV enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_TRV(bool status);


/**
  * @brief  Digital LDO power supply in TRV enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_DigPowerInTrv(bool status);

/**
  * @brief  TRV BG enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_TRV_BG(bool status);

/**
  * @brief  LDO for PLL enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_LDO_PLL(bool status);



/**
  * @brief  LDO for RX modules enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_LDO_RX(bool status);

/**
  * @brief  LDO for TX modules enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_LDO_TX(bool status);


/**
  * @brief  LDO for IF modules enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_LDO_IF(bool status);

/**
  * @brief  LDO for PA enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_LDO_PA(bool status);


/**
  * @brief  LDO for VCO enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_LDO_VCO(bool status);

/**
  * @brief  16M crystal oscillator enable and disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_XO16M(bool status);

/**
  * @brief  Digital PLL enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_DPLL(bool status);

/**
  * @brief  TX DAC and low pass filter for BLE enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_BLE_DAC(bool status);

/**
  * @brief  PLL enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_PLL(bool status);
/**
  * @brief  TX PA enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_TX_PLL(bool status);


/**
  * @brief  RX LNA enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_RX_LNA(bool status);

/**
  * @brief  RX Mixer enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_RX_MIX(bool status);

/**
  * @brief  PLL TX buffer enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_TXBuffer(bool status);


/**
  * @brief  RX BPF enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_TX_BPF(bool status);

/**
  * @brief  RX limit and RSSI enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_RxLimitAndRSSI(bool status);

/**
  * @brief  AGC enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_AGC(bool status);
/**
  * @brief  SAR ADC enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_SAR_ADC(bool status);

/**
  * @brief  Battery detect enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_BattertDect(bool status);




/**
  * @brief  Tune VCO control voltage, which is
  *   adopted when VCO calibration is on.
  * @param  pll_verf:voltage type
  * @retval None
  */
void SOC_PLL_VOC_SetCtlVtg(SOC_PLL_VREF_Type pll_verf);
/**
  * @brief  Bits to tune PLL charge pump offset current.
  * @param  ChargPump: The type that needs to be set
  * @retval None
  */
void SOC_PLL_SetChargePump(SOC_PLL_ChargePump_Type ChargPump);

/**
  * @brief  PLL_CP current offset enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_PLL_CP_Offset(bool status);

/**
  * @brief  External code to select different VCO tuning curves
  *         Set PLL_FREQ_EXT_EN=1 to make these code effective.
  * @param  div: counter divide
  * @retval None
  */
void SOC_PLL_AFC_Select(uint16_t  cur);

/**
  * @brief  External code to select VCO tuning curves enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_PLL_ExtCode(bool status);

/**
  * @brief  Bits to tune pre-scaler bias current.
  * @param  PreScaler: The type that needs to be set
  * @retval None
  */
void SOC_PLL_SetPreScaler(SOC_PLL_PreScalerBias_Type PreScaler);


/**
  * @brief  PLL AFC optimizing between two final VCO tuning curves enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_PLL_AFC_DC(bool status);

/**
  * @brief  Bits to tune PLL bandwidth.
  * @param  Bandwidth:The type that needs to be set 
  * @retval None
  */
void SOC_PLL_SetBandWidth(SOC_PLL_BandWidth_Type Bandwidth);



/**
  * @brief  Bits to tune current of PLL VCO bias circuit.
  * @param  Pll_voc: The type that needs to be set
  * @retval None
  */
void SOC_PLL_SetVcoBias(SOC_PLL_VCO_Type Pll_voc);

/**
  * @brief  Bits to configure S counter divide ratio of AFC.
  * @param  div: counter divide
  * @retval None
  */
void SOC_PLL_AFC_ConfigureDivide(uint16_t  div);


/**
  * @brief  PLL AFC calibration target selection.
  * @param  afc_type:1: The type that needs to be set
  * @retval None
  */
void SOC_PLL_AFC_TargetSelet(SOC_PLL_AFC_Type afc_type);



#ifdef __cplusplus
}
#endif

#endif /* __BT1051Axx_SOC_H__ */

