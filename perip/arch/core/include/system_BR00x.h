/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    system_BR00xx.h
 * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer Header File for
 *          Device BR00x
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * @date    11-Augest-2018
 * @version V1.0.0
 * @author  Asher
*/

#ifndef __SYSTEM_BR00x_H__
#define __SYSTEM_BR00x_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifdef BR1051Axx 
typedef enum ClockEnableId
{
    UART0_CKEn      = 0, 
    UART1_CKEn      = 1, 
    SPIM0_CKEn      = 2, 
    SPIM1_CKEn      = 3, 
    SPIS1_CKEn      = 4, 
    I2SM_CKEn       = 5,  
    I2SS_CKEn       = 6, 
    I2C0_CKEn       = 7, 
    I2C1_CKEn       = 8, 
    GPIO_CKEn       = 9, 
    WDT_CKEn        = 10, 
    TIMER_CKEn      = 11, 
    SCU_CKEn        = 12, 
    RF_CKEn         = 13, 
    RTC_CKEn        = 14,
    RSV0_CKEn       = 15,
    BB_CKEn         = 16, 
    DMA_CKEn        = 17, 
    RSV1_CKEn       = 18, 
    RSV2_CKEn       = 19, 
    RSV3_CKEn       = 20, 
    TIM1_CKEn       = 21, 
    TIM2_CKEn       = 22, 
    TIM3_CKEn       = 23, 
    TIM4_CKEn       = 24, 
    RSV4_CKEn       = 25, 
    RSV5_CKEn       = 26, 
    RSV6_CKEn, 
    RSV7_CKEn, 
    RSV8_CKEn, 
    RSV9_CKEn, 
    RSV10_CKEn
} CKEnId_Type;


typedef enum SwRstCtrlId {
    UART0_SwRst = 0, 
    UART1_SwRst, 
    SPIM0_SwRst, 
    SPIM1_SwRst, 
    SPIS1_SwRst, 
    I2SM_SwRst, 
    I2SS_SwRst, 
    I2C0_SwRst, 
    I2C1_SwRst, 
    GPIO_SwRst, 
    WDT_SwRst, 
    TIMER_SwRst, 
    SCU_SwRst, 
    RF_SwRst, 
    RTC_SwRst, 
    RSV0_SwRst, 
    BB_SwRst, 
    DMA_SwRst, 
    RSV1_SwRst, 
    RSV2_SwRst, 
    RSV3_SwRst, 
    TIM1_SwRst, 
    TIM2_SwRst, 
    TIM3_SwRst, 
    TIM4_SwRst, 
    RSV4_SwRst, 
    RSV5_SwRst, 
    RSV6_SwRst, 
    RSV7_SwRst, 
    RSV8_SwRst, 
    RSV9_SwRst, 
    RSV10_SwRst
} SwRstId_Type;


#endif

#if defined(BR002)
typedef enum ClockEnableId
{
    SCU_CKEn        = 0, //can`t control
    GPIO_CKEn       = 1, 
    WDT_CKEn        = 2, 
    RTC_CKEn        = 3, 
    UART0_CKEn      = 4, 
    UART1_CKEn      = 5, 
    SPIM1_CKEn      = 6, 
    SPIS1_CKEn      = 7, 
    I2SM_CKEn       = 8, 
    I2SS_CKEn       = 9, 
    TIMER_CKEn      = 10,
    I2C_CKEn        = 11,
    FLASH_CP_CKEn   = 12,
    RF_CKEn         = 13,
    BB_PCKEn        = 14,
    BB_HCKEn        = 15,
    DMA_CKEn        = 16,
    SPIM0_CKEn      = 17,
    CPU_TRACE_CKEn  = 18,
    USB_HCKEn        = 19, 
    USB_XCKEn        = 20,
    
    TIMER0_CKEn      = 21,
    TIMER1_CKEn      = 22,
    TIMER2_CKEn      = 23,
    TIMER3_CKEn      = 24,
    TIMER4_CKEn      = 25,
    TIMER5_CKEn      = 26,
    TIMER6_CKEn      = 27,
    TIMER7_CKEn      = 28,
    

    UART0_SCKEn      = 29    
    FLASH_CH_CKEn    = 30,
    // IFCLK_BB_CKEn    = 29,
    // IFCLK_GPIO_CKEn  = 30,
    END_CKEn         = 31,
  
} CKEnId_Type;


typedef enum SwRstCtrlId {
    UART0_SwRst = 0, 
    UART1_SwRst, 
    SPIM0_SwRst, 
    SPIM1_SwRst, 
    SPIS1_SwRst, 
    I2SM_SwRst, 
    I2SS_SwRst, 
    I2C_SwRst, 
    //I2C1_SwRst, 
    res,
    GPIO_SwRst, 
    WDT_SwRst, 
    TIMER_SwRst, 
    SCU_SwRst, 
    RF_SwRst, 
    RTC_SwRst, 
    RSV0_SwRst, 
    BB_SwRst, 
    DMA_SwRst, 
    RSV1_SwRst, 
    RSV2_SwRst, 
    RSV3_SwRst, 
    TIM1_SwRst, 
    TIM2_SwRst, 
    TIM3_SwRst, 
    TIM4_SwRst, 
    RSV4_SwRst, 
    RSV5_SwRst, 
    RSV6_SwRst, 
    RSV7_SwRst, 
    RSV8_SwRst, 
    RSV9_SwRst, 
    RSV10_SwRst
} SwRstId_Type;

#endif


#if defined(BR003)
typedef enum ClockEnableId
{
    SCU_CKEn        = 0, //can`t control
    GPIO_CKEn       = 1, 
    WDT_CKEn        = 2, 
    RTC_CKEn        = 3, 
    UART0_CKEn      = 4, 
    UART1_CKEn      = 5, 
    SPIM1_CKEn      = 6, 
    SPIS1_CKEn      = 7, 
    I2SM_CKEn       = 8, 
    I2SS_CKEn       = 9, 
    TIMER_CKEn      = 10,
    I2C_CKEn        = 11,
    FLASH_CP_CKEn   = 12,
    RF_CKEn         = 13,
    BB_PCKEn        = 14,
    BB_HCKEn        = 15,
    DMA_CKEn        = 16,
    SPIM0_CKEn      = 17,
    CPU_TRACE_CKEn  = 18,
    USB_HCKEn        = 19, 
    USB_XCKEn        = 20,
    
    TIMER0_CKEn      = 21,
    TIMER1_CKEn      = 22,
    TIMER2_CKEn      = 23,
    TIMER3_CKEn      = 24,
    TIMER4_CKEn      = 25,
    TIMER5_CKEn      = 26,
    TIMER6_CKEn      = 27,
    TIMER7_CKEn      = 28,
    

//UART0_SCKEn      = 29    
//FLASH_CH_CKEn    = 30,
    IFCLK_BB_CKEn    = 29,
    IFCLK_GPIO_CKEn  = 30,
    END_CKEn         = 31,
  
} CKEnId_Type;


typedef enum SwRstCtrlId {
    SCU_SwRst = 0,
    GPIO_SwRst,
    WDT_SwRst,
    RTC_SwRst,
    UART0_SwRst,
    UART1_SwRst,
    SPIM1_SwRst,
    SPIS1_SwRst,
    I2SM_SwRst,
    I2SS_SwRst,
    TIMERS_SwRst,
    I2C_SwRst,
    FC_SwRst,
    RF_SwRst,
    BB_SwRst,
    BBHCLK_SwRst,
    DMA_SwRst,
    SPIM0_SwRst,
    CPUT_SwRst,
    USBH_SwRst,
    USBX_SwRst,
    TIMER0_SwRst,
    TIMER1_SwRst,
    TIMER2_SwRst,
    TIMER3_SwRst,
    TIMER4_SwRst,
    TIMER5_SwRst,
    TIMER6_SwRst,
    TIMER7_SwRst,
    IFCLKBB_SwRst,
    IFCLKGPIO_SwRst,
    END_SwRst,

} SwRstId_Type;

#endif


#if defined(BR005)

typedef enum ClockEnableId
{
    SCU_CKEn        = 0, //can`t control
    GPIO_CKEn       = 1, 
    WDT_CKEn        = 2, 
    RTC_CKEn        = 3, 
    UART0_CKEn      = 4, 
    UART1_CKEn      = 5, 
    SPIM1_CKEn      = 6, 
    SPIM1_SCKEn     = 7,
    UART0_SCKEn     = 8,
    I2C_CKEn        = 11,
    RF_CKEn         = 13,
    BB_PCKEn        = 14,
    BB_HCKEn        = 15,
    CPU_TRACE_CKEn  = 18,
     
    IFCLK_BB_CKEn   = 29,
    IFCLK_GPIO_CKEn = 30,
  
} CKEnId_Type;




typedef enum SwRstCtrlId {
    GPIO_PCLK_SwRst = 1, 
    WDT_PCLK_SwRst, 
    RTC_PCLK_SwRst, 
    UART0_PCLK_SwRst, 
    UART1_PCLK_SwRst, 
    SPIM1_PCLK_SwRst, 
    SPIM1_SCLK_SwRst, 
    UART0_SLCK_SwRst, 
    

    I2C_PCLK_SwRst   = 11, 
    RF_PCLK_SwRst    = 13, 
    BB_PCLK_SwRst    = 14, 
    BB_SLCK_SwRst    = 15,

    CPU_TRACE_SwRst  = 18,
    IFCLK_BB_SwRst   = 29,
    IFCLK_GPIO_SwRst = 30,
} SwRstId_Type;

#endif

typedef enum PllConfigNum {
    OSC32K      = 0x00,
    OSC16M      = 0x01,
    PLL16M      = 0x02,
    PLL32M      = 0x03,
    PLL64M      = 0x04,
    PLL128M     = 0x05,
} PllConfig_Type;

typedef enum PADId {
    PADID0,
    PADID1,
    PADID2,
    PADID3,
    PADID4,
    PADID5,
    PADID6,
    PADID7,
    PADID8,
    PADID9,
    PADID10,
    PADID11,
    PADID12,
    PADID13,
    PADID14,
    PADID15,
    PADID16,
    PADID17,
    PADID18,
    PADID19,
    PADID20,
    PADID21,
    PADID22,
    PADID23,
    PADID24,
    PADID25,
    PADID26,
    PADID27,
    PADID28,
    PADID29,
    PADID30,
    PADID31,
    PADID32,
    PADID33,
    PADID34,
} PADId_Type;

typedef enum PAD_DevId {
    PAD_ID_GPIO,

    PAD_ID_SPIM0_DATA0 =1,
    PAD_ID_SPIM0_DATA1=2,
    PAD_ID_SPIM0_DATA2=3,
    PAD_ID_SPIM0_DATA3=4,

    PAD_I2C0MS_SCL = 5,
    PAD_I2C0MS_SDA =6,
    PAD_I2C1MS_SCL =7,
    PAD_I2C1MS_SDA =8,

    PAD_GPIO_B0 = 9,
    PAD_GPIO_B1 =10,

    PAD_SWD_IO = 11,

    PAD_ID_UART0_TXRX=12,
    PAD_ID_UART0_RTSCTS=13,
    PAD_ID_UART1_TXRX=14,
    PAD_ID_UART1_RTSCTS=15,

    PAD_ID_SPIMS1_SCLK=16,
    PAD_ID_SPIMS1_CSN=17,
    PAD_ID_SPIM1_TXRX=18,
    PAD_ID_SPIS1_TXRX=19,

    PAD_ID_I2SMS_SCLK=20,
    PAD_ID_I2SMS_WS=21,
    PAD_ID_I2SMS_SDOSDI=22,
    PAD_ID_I2SMS_SDISDO=23,

    PAD_ID_SPIM0_SCLK_QDEX_CHA=24,
    PAD_ID_SPIM0_CSN_QDEX_CHB=25,

    PAD_SPI_SLV_DO_SLE = 26,
    PAD_ID_PWM0_SPI_SLV_SCLK=27,
    PAD_ID_PWM1_SPI_SLV_DI=28,
    PAD_ID_PWM2_SPI_SLV_CLK=29,
    PAD_ID_PWM3  =30
} PAD_DevId_type;
    
typedef enum PAD_Dir {
    PAD_DIR_BLOCK = 0x00,
    PAD_DIR_IN = 0x01,
    PAD_DIR_OUT = 0x02,
    PAD_DIR_MODE = 0x03
} PAD_Dir_type;

typedef enum PAD_DriveLevel {
    PAD_DL_2MA = 0x00,
    PAD_DL_4MA = 0x01,
    PAD_DL_8MA = 0x02,
    PAD_DL_12MA = 0x03
} PAD_DriveLevel_type;

typedef enum PAD_Speed {
    PAD_SPEED_FAST = 0x00,
    PAD_SPEED_SLOW = 0x01,
} PAD_Speed_type;

typedef enum PAD_PullEn {
    PAD_PE_DISABLE = 0x00,
    PAD_PE_ENABLE = 0x01,
} PAD_PullEn_type;

typedef enum PAD_PullMode {
    PAD_PM_DOWN = 0x00,
    PAD_PM_UP = 0x01,
} PAD_PullMode_type;

typedef enum PAD_InLevelMode {
    PAD_ILM_CMOS = 0x00,
    PAD_ILM_ST = 0x01,                          /*!< Schmitt Trigger */
} PAD_InLevelMode_type;

//typedef struct PADConfig {
//    uint32_t dev_id : 6;
//    uint32_t dir : 2;
//    uint32_t drv_cap : 2;
//    uint32_t speed : 1;
//    uint32_t pull_en : 1;
//    uint32_t pull_mode : 1;
//    uint32_t in_mode : 1;
//    uint32_t reserve : 18;
//} PADConfig_Type;

typedef enum PAD_MODE {
    PAD_MODE0 = 0x00,
    PAD_MODE1 = 0x01,
    PAD_MODE2 = 0x02,
    PAD_MODE3 = 0x03,
    PAD_MODE4 = 0x04,
    PAD_MODE5 = 0x05,
    PAD_MODE6 = 0x06,
    PAD_MODE7 = 0x07,
} PAD_CTL_MODE_type;

typedef enum PAD_IE {
    PAD_IE_DISABLE,
    PAD_IE_ENABLE,
}PAD_CTL_IE_type;

typedef enum PAD_OEN {
    PAD_OEN_ENABLE,
    PAD_OEN_DISABLE,
}PAD_CTL_OEN_type;

typedef enum PAD_REN {
    PAD_REN_ENABLE,
    PAD_REN_DISABLE,
   
}PAD_CTL_REN_type;


typedef struct PADConfig {
    uint32_t set        : 1;
    uint32_t ie         : 1;    //Logic high enable receiver
    uint32_t oen        : 1;    //Logic low enable the transmitter
    uint32_t ren        : 1;    //Logic low enbale the resistor
    uint32_t pad_ctl    : 3;    //Control Mode
    uint32_t unused	    : 25;
} PADConfig_Type;


typedef enum PAD_IOC {
    IO_0,
    IO_1,
    IO_2,
    IO_3
   
}PadIoConfig_Type;


typedef struct IOConfig {
    uint32_t d0         : 3;    
    uint32_t d1         : 3;
    uint32_t d2         : 3;
    uint32_t d3         : 3;
    uint32_t unused	    : 20;
} IOConfig_Type;




//extern unsigned long int SystemFrequency;     /*!< System Clock Frequency (Core Clock)  */
extern unsigned long int SystemCoreClock;       /*!< Processor Clock Frequency            */

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the SystemCoreClock variable.
 */
extern void SystemInit (void);

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
extern void SystemCoreClockUpdate (unsigned long int clock);

void SystemDevClockCtl(CKEnId_Type id, uint8_t enable);
void SystemDevRstCtl(SwRstId_Type id);
void SystemPADConfig(PADId_Type pad_id, PADConfig_Type *config);
void SystemIOConfigQspi(IOConfig_Type *config);
void SystemIOConfigQspiOne(uint32_t config,PadIoConfig_Type io);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_BR00x_H__ */

