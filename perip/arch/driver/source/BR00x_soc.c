/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_soc.c
 * @brief    This file provides the example firmware functions.
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
#include "string.h"
#include "BR00x_soc.h"
#include "system_BR00x.h"

/* Register configuration function */
#define SET_REG(X,Y,Z) {\
    if(Y){\
        X |= 1ul<<Z;\
    }else\
        X &= ~(1ul<<Z);\
}


/**
  * @brief  PMU Band gap enable or disable.
  * @param  status:0: enable(default)/1: disable
  * @retval None
  */
void SOC_PmuBandGap(bool status)
{
    SET_REG(SOC->EN_SW,status,0);
}

/**
  * @brief  Low power digital LDO enable or disable.
  * @param  status:0: enable(default)/1: disable
  * @retval None
  */
void SOC_LowPowerDLDO(bool status)
{
    SET_REG(SOC->EN_SW,status,1);
}


/**
  * @brief  DCDC function enable or bypass.
  * @param  status:0: bypass(default)/1: normal function
  * @retval None
  */
void SOC_DcdcForm(bool status)
{
    SET_REG(SOC->EN_SW,status,2);
}

/**
  * @brief  Battery detect enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_BatteryDetect(bool status)
{
    SET_REG(SOC->EN_SW,status,3);
}

/**
  * @brief  DCDC over load and short protection enable or disable.
  * @param  status:0: enable/1: disable(default)
  * @retval None
  */
void SOC_DcdcProtection(bool status)
{
    SET_REG(SOC->EN_SW,status,4);
}

/**
  * @brief  VDT in DCDC enable or disable.
  * @param  status:0: enable(default)/1: disable
  * @retval None
  */
void SOC_VdtInDcdc(bool status)
{
    SET_REG(SOC->EN_SW,status,5);
}

/**
  * @brief  32K crystal oscillator enable and disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_Xo33K(bool status)
{
    SET_REG(SOC->EN_SW,status,6);
}

/**
  * @brief  TRV enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_TRV(bool status)
{
    SET_REG(SOC->EN_SW,status,8);
}


/**
  * @brief  Digital LDO power supply in TRV enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_DigPowerInTrv(bool status)
{
    SET_REG(SOC->EN_SW,status,9);
}

/**
  * @brief  TRV BG enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_TRV_BG(bool status)
{
    SET_REG(SOC->EN_SW,status,10);
}

/**
  * @brief  LDO for PLL enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_LDO_PLL(bool status)
{
    SET_REG(SOC->EN_SW,status,11);
}


/**
  * @brief  LDO for RX modules enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_LDO_RX(bool status)
{
    SET_REG(SOC->EN_SW,status,12);
}

/**
  * @brief  LDO for TX modules enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_LDO_TX(bool status)
{
    SET_REG(SOC->EN_SW,status,13);
}

/**
  * @brief  LDO for IF modules enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_LDO_IF(bool status)
{
    SET_REG(SOC->EN_SW,status,14);
}

/**
  * @brief  LDO for PA enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_LDO_PA(bool status)
{
    SET_REG(SOC->EN_SW,status,15);
}

/**
  * @brief  LDO for VCO enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_LDO_VCO(bool status)
{
    SET_REG(SOC->EN_SW,status,16);
}

/**
  * @brief  16M crystal oscillator enable and disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_XO16M(bool status)
{
    SET_REG(SOC->EN_SW,status,17);
}


/**
  * @brief  Digital PLL enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_DPLL(bool status)
{
    SET_REG(SOC->EN_SW,status,18);
}

/**
  * @brief  TX DAC and low pass filter for BLE enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_BLE_DAC(bool status)
{
    SET_REG(SOC->EN_SW,status,20);
}

/**
  * @brief  PLL enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_PLL(bool status)
{
    SET_REG(SOC->EN_SW,status,21);
}


/**
  * @brief  TX PA enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_TX_PLL(bool status)
{
    SET_REG(SOC->EN_SW,status,22);
}

/**
  * @brief  RX LNA enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_RX_LNA(bool status)
{
    SET_REG(SOC->EN_SW,status,23);
}

/**
  * @brief  RX Mixer enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_RX_MIX(bool status)
{
    SET_REG(SOC->EN_SW,status,24);
}

/**
  * @brief  PLL TX buffer enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_TXBuffer(bool status)
{
    SET_REG(SOC->EN_SW,status,25);
}


/**
  * @brief  RX BPF enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_TX_BPF(bool status)
{
    SET_REG(SOC->EN_SW,status,26);
}

/**
  * @brief  RX limit and RSSI enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_RxLimitAndRSSI(bool status)
{
    SET_REG(SOC->EN_SW,status,27);
}

/**
  * @brief  AGC enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_AGC(bool status)
{
    SET_REG(SOC->EN_SW,status,28);
}

/**
  * @brief  SAR ADC enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_SAR_ADC(bool status)
{
    SET_REG(SOC->EN_SW,status,29);
}

/**
  * @brief  Battery detect enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_BattertDect(bool status)
{
    SET_REG(SOC->EN_SW,status,30);
}

/***************************************************************************************
****************************************************************************************/

/**
  * @brief  bits to configure sigma delta modulator 
  *     to set fractional divide ratio of feedback divider
  *     Divide ratio=PLL_FRAC[23:0]/223.
  * @param  div:1: Divide ratio
  * @retval None
  */
  
void SOC_PLL_FRAC(uint32_t div)
{ 
    SOC->PLL1 &= ~0xFFFFFFul;
    SOC->PLL1 |= (div &0xFFFFFFul);
}


/**
  * @brief  Bits to configure S counter divide ratio of PLL pre-scaler.
  * @param  div:1: Divide ratio
  * @retval None
  */
  
void SOC_PLL_PreScaler(uint32_t PreScaler)
{ 
    SOC->PLL1 &= ~(0x1Ful<<24);
    SOC->PLL1 |= (PreScaler & 0x1Ful)<<24;
}

/**
  * @brief  PLL RX mode or TX mode selection.
  * @param  status:1: TX mode/0: RX mode(default)
  * @retval None
  */
void SOC_PLL_TxOrRxSelect(bool status)
{
    SET_REG(SOC->PLL1,status,29);
}

/**
  * @brief  PLL Band Calibration Enable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_PLL_BandCal(bool status)
{
    SET_REG(SOC->PLL1,status,30);
}


/**
  * @brief  PLL calibration time configuration.
  * @param  status:1: 16us/0: 8us(default)
  * @retval None
  */
void SOC_PLL_CalTime(bool status)
{
    SET_REG(SOC->PLL1,status,31);
}


/**
  * @brief  Tune VCO control voltage, which is
  *   adopted when VCO calibration is on.
  * @param  pll_verf:voltage type
  * @retval None
  */
void SOC_PLL_VOC_SetCtlVtg(SOC_PLL_VREF_Type pll_verf)
{
    SOC->PLL2 &= ~0x07ul;
    SOC->PLL2 |= pll_verf;
}



/**
  * @brief  Bits to tune PLL charge pump offset current.
  * @param  ChargPump: The type that needs to be set
  * @retval None
  */
void SOC_PLL_SetChargePump(SOC_PLL_ChargePump_Type ChargPump)
{
    SOC->PLL2 &= ~(0xFul<<3);
    SOC->PLL2 |= ChargPump<<3;
}


/**
  * @brief  PLL_CP current offset enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_PLL_CP_Offset(bool status)
{
    SET_REG(SOC->PLL2,status,7);
}

/**
  * @brief  External code to select different VCO tuning curves
  *         Set PLL_FREQ_EXT_EN=1 to make these code effective.
  * @param  div: counter divide
  * @retval None
  */
void SOC_PLL_AFC_Select(uint16_t  cur)
{
    SOC->PLL2 &= ~(0x1Ful<<8);
    SOC->PLL2 |= (cur&0x1Ful)<<8;
}

/**
  * @brief  External code to select VCO tuning curves enable or disable.
  * @param  status:1: enable/0: disable(default)
  * @retval None
  */
void SOC_PLL_ExtCode(bool status)
{
    SET_REG(SOC->PLL2,status,13);
}

/**
  * @brief  Bits to tune pre-scaler bias current.
  * @param  PreScaler: The type that needs to be set
  * @retval None
  */
void SOC_PLL_SetPreScaler(SOC_PLL_PreScalerBias_Type PreScaler)
{
    SOC->PLL2 &= ~(0x3ul<<14);
    SOC->PLL2 |= PreScaler<<14;
}

/**
  * @brief  PLL AFC optimizing between two final VCO tuning curves enable or disable.
  * @param  status:1: enable(default)/0: disable
  * @retval None
  */
void SOC_PLL_AFC_DC(bool status)
{
    SET_REG(SOC->PLL2,status,17);
}

/**
  * @brief  Bits to tune PLL bandwidth.
  * @param  Bandwidth:The type that needs to be set 
  * @retval None
  */
void SOC_PLL_SetBandWidth(SOC_PLL_BandWidth_Type Bandwidth)
{
    SOC->PLL2 &= ~(0x7ul<<18);
    SOC->PLL2 |= Bandwidth<<18;
}

/**
  * @brief  Bits to tune current of PLL VCO bias circuit.
  * @param  Pll_voc: The type that needs to be set
  * @retval None
  */
void SOC_PLL_SetVcoBias(SOC_PLL_VCO_Type Pll_voc)
{
    SOC->PLL2 &= ~(0x7ul<<21);
    SOC->PLL2 |= Pll_voc<<21;
}


/**
  * @brief  Bits to configure S counter divide ratio of AFC.
  * @param  div: counter divide
  * @retval None
  */
void SOC_PLL_AFC_ConfigureDivide(uint16_t  div)
{
    SOC->PLL2 &= ~(0x1Ful<<24);
    SOC->PLL2 |= (div&0x1Ful)<<24;
}



/**
  * @brief  PLL AFC calibration target selection.
  * @param  afc_type:1: The type that needs to be set
  * @retval None
  */
void SOC_PLL_AFC_TargetSelet(SOC_PLL_AFC_Type afc_type)
{
    SOC->PLL2 &= ~(0x1ul<<29);
    SOC->PLL2 |= afc_type<<29;
}



/**
  * @brief  PLL gain calibration time configuration.
  * @param  Gain:Gain Calibration 
  * @retval None
  */
void SOC_PLL_GainCalSelet(uint8_t Gain)
{
    SOC->PLL3 &= ~(0x7ul<<0);
    SOC->PLL3 |= (Gain&0x7ul)<<0;
}

/**
  * @brief  PLL_PS_CNT reset select.
  * @param  Auto:0: Not reset / 1: auto reset
  * @retval None
  */
void SOC_PLL_PS_CNT_ResetSelet(bool Auto)
{
    SOC->PLL3 &= ~(0x1ul<<3);
    SOC->PLL3 |= (Auto)<<3;
}

/*PLL_CAL_OPEN_SEL 0 TBF.*/

/**
  * @brief  PLL FBDIV reset signal select.
  * @param  auto:0: internal signal reset;
  *              1: external signal reset;
  * @retval None
  */
void SOC_PLL_FBDIV_ResetSelet(bool signal)
{
    SOC->PLL3 &= ~(0x1ul<<5);
    SOC->PLL3 |= (signal)<<5;
}


/*PLL_FBDIV_RST_EXT 0 PLL FBDIV external reset signal*/


/**
  * @brief  External code to tune DAC reference voltage.
  * @param  level: reference voltage
  * @retval None
  */
void SOC_PLL_ExtCodeVoltage(uint16_t level)
{
    SOC->PLL3 &= ~(0x1ful<<7);
    SOC->PLL3 |= (level&0x1ful)<<7;
}


/**
  * @brief  External reference voltage for modulation enable or disable.
  * @param  Auto:0:  disable (default) / 1: enable
  * @retval None
  */
void SOC_PLL_ExtRefVoltMode(bool status)
{
    SOC->PLL3 &= ~(0x1ul<<12);
    SOC->PLL3 |= (status)<<12;
}


/**
  * @brief  PLL gain calibration enable signal.
  * @param  signal: 0->1:calibration start
  * @retval None
  */
void SOC_PLL_GainCaliStart(bool signal)
{
    SOC->PLL3 &= ~(0x1ul<<13);
    SOC->PLL3 |= (signal)<<13;
}


/**
  * @brief  PLL gain calibration final judgment enable or disable.
  * @param  status: 0:  disable  / 1: enable(default)
  * @retval None
  */
void SOC_PLL_GainCaliFinalJudgment(bool status)
{
    SOC->PLL3 &= ~(0x1ul<<14);
    SOC->PLL3 |= (status)<<14;
}



/**
  * @brief  PLL gain calibration threshold configuration.
  * @param  thrh: gain calibration threshold
  * @retval None
  */
void SOC_PLL_GainCaliThreshold(uint8_t thrh)
{
    SOC->PLL3 &= ~(0xfful<<15);
    SOC->PLL3 |= (thrh&0xff)<<15;
}


/**
  * @brief  PLL test mode enable.
  * @param  status: 0:  disable(default)  / 1: enable
  * @retval None
  */
void SOC_PLL_TestMode(bool status)
{
    SOC->PLL3 &= ~(0x1ul<<23);
    SOC->PLL3 |= (status&0x1ul)<<23;
}

/**
  * @brief  PLL fast lock enable or disable.
  * @param  status: 0:  disable / 1: enable(default) 
  * @retval None
  */
void SOC_PLL_Fastlock(bool status)
{
    SOC->PLL3 &= ~(0x1ul<<24);
    SOC->PLL3 |= (status&0x1ul)<<24;
}

/**
  * @brief  PLL 16MHz or 32MHz reference frequency selection.
  * @param  selet: 0:16M(default) / 1:32M 
  * @retval None
  */
void SOC_PLL_RefFrequency(bool selet)
{
    SOC->PLL3 &= ~(0x1ul<<25);
    SOC->PLL3 |= (selet&0x1ul)<<25;
}

/**
  * @brief  PLL loop open method selection:.
  * @param selet: 0: PLL open loop manually, 0->1 PLL open the loop
  *               1: PLL open loop automatically after lock in TX mode 
  * @retval None
  */
void SOC_PLL_LoopOpenMethod(bool selet)
{
    SOC->PLL3 &= ~(0x1ul<<26);
    SOC->PLL3 |= (selet&0x1ul)<<26;
}


/**
  * @brief  External voltage to control VCO frequency enable or disable.
  * @param  status: 0:  disable(default) / 1: enable 
  * @retval None
  */
void SOC_PLL_ExtCtlVoltVocFreq(bool status)
{
    SOC->PLL3 &= ~(0x1ul<<27);
    SOC->PLL3 |= (status&0x1ul)<<27;
}
/**
  * @brief  PLL SDM fraction or integer mode selection.
  * @param  status: 0:  Fraction mode (default) / 1:  Integer mode 
  * @retval None
  */
void SOC_PLL_SDM_FractOrInt(bool status)
{
    SOC->PLL3 &= ~(0x1ul<<28);
    SOC->PLL3 |= (status&0x1ul)<<28;
}
/**
  * @brief  PLL lock detect function enable or bypass.
  * @param  status: 0:  normal function(default) / 1: bypass detect function, 
  * @retval None
  */
void SOC_PLL_LockDetect(bool status)
{
    SOC->PLL3 &= ~(0x1ul<<29);
    SOC->PLL3 |= (status&0x1ul)<<29;
}
/**
  * @brief  PLL divider enable or power down.
  * @param  status: 0:  enable(default) / 1: power down 
  * @retval None
  */
void SOC_PLL_DivOrPowerDown(bool status)
{
    SOC->PLL3 &= ~(0x1ul<<30);
    SOC->PLL3 |= (status&0x1ul)<<30;
}
/**
  * @brief  PLL_FBDIV_PD signal bypass or enable.
  * @param  signal: 0:  enable(default) / 
  *                 1: bypass 
  *       PLL_DIV working or not controlled by PLL working mode,
  *       power down when TX mode, enable when RX mode
  * @retval None
  */
void SOC_PLL_FBDIV_Bypass(bool signal)
{
    SOC->PLL3 &= ~(0x1ul<<31);
    SOC->PLL3 |= (signal&0x1ul)<<31;
}



/**
  * @brief  BG Bias adjust for all.
  * @param  bias:   0:-8%
  *                 1: 0%
  *                 2:+8%
  *                 3:+16%
  * @retval None
  */
void SOC_BG_FBiasAdjust(uint8_t bias)
{
    SOC->PM1 &= ~(0x3ul<<0);
    SOC->PM1 |= (bias&0x3ul)<<0;
}

/**
  * @brief  BG bias adjust for all.
  * @param  bias:   0:-7%
  *                 1:-6%
  *                 ...
  *                 7: 0%
  * @retval None
  */
void SOC_BG_CBiasAdjust(uint8_t bias)
{
    SOC->PM1 &= ~(0x7ul<<2);
    SOC->PM1 |= (bias&0x7ul)<<2;
}


/**
  * @brief  Bits to tune output voltage of band gap.
  * @param  bias:   0:1.085V
  *                 1:-6%
  *                 ...
  *                 7: 0%
  * @retval None
  */
void SOC_BG_BandGapVolt(uint16_t volt)
{
    SOC->PM1 &= ~(0x1ful<<5);
    SOC->PM1 |= (volt&0x1ful)<<5;
}







