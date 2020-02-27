/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    br_qspi_iocfg.c
 * @brief   The file contains QSPI config full mux 
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
#include "BR00x_clock.h"
#include "system_BR00x.h"
#include "qspi_icfg.h"
#include "cm_printf.h"


#if  defined(BR002)||defined(BR003)

#ifdef BR_CONFIG_TB
#include "verify_message.h"
#endif

bool SCUQspiConfig(QspiPin_Type pin,QspiPinConfig_Type tp)
{
    PADConfig_Type  PAG_InitStru;
    uint16_t  funt=0, MAX=6;
#ifdef BR003
    uint16_t  pib= pin-QSPI_PIN29;
#else
    uint16_t  pib= pin-QSPI_PIN27;
#endif
    memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
    //Check parameter
    if(pin < QSPI_PIN27 || pin > QSPI_PIN_END || tp >=QSPI_END)
        return false; 
    //Get Pad_ctl and IO Config
    funt = (tp + pib )>= MAX ? (tp + pib -MAX ): (tp + pib);

    PAG_InitStru.pad_ctl    = (PAD_CTL_MODE_type)funt;
    SystemPADConfig((PADId_Type)(pin),&PAG_InitStru);

#ifdef BR_CONFIG_TB   //Config TB 
    tp = tp==2?0:tp==0?1:tp==1?2:tp==5?3:tp==4?4:5;
    Verrify_SendPinCon(0xE101 + tp*0x100 + pib);
#endif
    return true;
}


// bool SCUQspiConfigback(QspiPin_Type pin,QspiPinConfig_Type tp)
// {
//     PADConfig_Type  PAG_InitStru;
//     uint16_t  funt=0,cfg=0, MAX=6;
  
// #ifdef BR003
//     uint16_t  pib= pin-QSPI_PIN29;
// #else
//     uint16_t  pib= pin-QSPI_PIN27;
// #endif

//     memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
//     //Check parameter
//     if(pin < QSPI_PIN27 || pin > QSPI_PIN_END ||tp > QSPI_D3)
//         return false; 
//     //Get Pad_ctl and IO Config
//     funt = pib > tp ? MAX - pib + tp : tp-pib;   
//     cfg  += tp  > QSPI_CS ? pib >= tp ? pib - tp : MAX + pib - tp : 0;   

//     PAG_InitStru.pad_ctl    = (PAD_CTL_MODE_type)funt;
    
// #ifdef BR_CONFIG_TB
//     //Config TB 
//     Verrify_SendPinCon(0xE101 + tp*0x100 + pib);
// #endif
    
// #ifdef BR002
//     if(tp >= QSPI_D0 )
//         SystemIOConfigQspiOne(cfg,(PadIoConfig_Type)(tp-QSPI_D0));
// #endif
 
//     SystemPADConfig((PADId_Type)(pin),&PAG_InitStru);
    
//     return true;
// }

#endif


