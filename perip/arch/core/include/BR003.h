/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR003.h
 * @brief   CMSIS Cortex-M3 Core Peripheral Access Layer Header File
 * @note    CMSIS Cortex-M3 Device Peripheral Access Layer Header File. 
 *          This file contains all the peripheral register's definitions, bits 
 *          definitions and memory mapping for BR1051Axx Connectivity line, 
 *          High density, High density value line, Medium density, 
 *          Medium density Value line, Low density, Low density Value line 
 *          and XL-density devices.
 *
 *          The file is the unique include file that the application programmer
 *          is using in the C source code, usually in main.c. This file contains:
 *           - Configuration section that allows to select:
 *              - The device used in the target application
 *              - To use or not the peripherals drivers in application code(i.e. 
 *                code will be based on direct access to peripherals registers 
 *                rather than drivers API), this option is controlled by 
 *                "#define USE_STDPERIPH_DRIVER"
 *              - To change few application-specific parameters such as the HSE 
 *                crystal frequency
 *           - Data structures and the address mapping for all peripherals
 *           - Peripheral's registers declarations and bits definition
 *           - Macros to access peripherals registers hardware
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

#ifndef __BR003_H__
#define __BR003_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdbool.h>
#include <string.h>

/** @addtogroup CM3DS_MPS2_Definitions CM3DS_MPS2 Definitions
  This file defines all structures and symbols for CM3DS_MPS2:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - Peripheral definitions
  @{
*/


/******************************************************************************/
/*                Processor and Core Peripherals                              */
/******************************************************************************/
/** @addtogroup CM3DS_MPS2_CMSIS Device CMSIS Definitions
  Configuration of the Cortex-M3 Processor and Core Peripherals
  @{
*/

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */

typedef enum IRQn
{
    /******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
    NonMaskableInt_IRQn           = -14,                /*!<  2 Cortex-M3 Non Maskable Interrupt                 */
    HardFault_IRQn                = -13,                /*!<  3 Cortex-M3 Hard Fault Interrupt                   */
    MemoryManagement_IRQn         = -12,                /*!<  4 Cortex-M3 Memory Management Interrupt            */
    BusFault_IRQn                 = -11,                /*!<  5 Cortex-M3 Bus Fault Interrupt                    */
    UsageFault_IRQn               = -10,                /*!<  6 Cortex-M3 Usage Fault Interrupt                  */
    SVCall_IRQn                   = -5,                 /*!< 11 Cortex-M3 SV Call Interrupt                      */
    DebugMonitor_IRQn             = -4,                 /*!< 12 Cortex-M3 Debug Monitor Interrupt                */
    PendSV_IRQn                   = -2,                 /*!< 14 Cortex-M3 Pend SV Interrupt                      */
    SysTick_IRQn                  = -1,                 /*!< 15 Cortex-M3 System Tick Interrupt                  */
    /******  BR1051Axx Specific Interrupt Numbers *******************************************************/
    UART0_IRQn                    = 0,
    UART1_IRQn                    = 1,
    DMA_IRQn                      = 2,
    SPIM0_IRQn                    = 3,
    SPIM1_IRQn                    = 4,
    SPIS1_IRQn                    = 5,
    I2C0_IRQn                     = 6,
    I2C1_IRQn                     = 7,
    I2SM_IRQn                     = 8,
    I2SS_IRQn                     = 9,
    RTC_IRQn                      = 10,
    QUID_IRQn                     = 11,
    TIMER0_IRQn                   = 12,
    TIMER1_IRQn                   = 13,
    TIMER2_IRQn                   = 14,
    TIMER3_IRQn                   = 15,
    TIMER4_IRQn                   = 16,
    TIMER5_IRQn                   = 17,
    TIMER6_IRQn                   = 18,
    TIMER7_IRQn                   = 19,
    GPIO0_IRQn                    = 20,
    GPIO1_IRQn                    = 21,
    GPIO2_IRQn                    = 22,
    GPIO3_IRQn                    = 23,
    GPIO4_IRQn                    = 24,
    GPIO5_IRQn                    = 25,
    GPIO6_IRQn                    = 26,
    GPIO7_IRQn                    = 27,
    GPIO8_IRQn                    = 28,
    GPIO9_IRQn                    = 29,
    GPIO10_IRQn                   = 30,
    GPIO11_IRQn                   = 31,
    GPIO12_IRQn                   = 32,
    GPIO13_IRQn                   = 33,
    GPIO14_IRQn                   = 34,
    GPIO15_IRQn                   = 35,
    GPIO16_IRQn                   = 36,
    GPIO17_IRQn                   = 37,
    GPIO18_IRQn                   = 38,
    GPIO19_IRQn                   = 39,
    GPIO20_IRQn                   = 40,
    GPIO21_IRQn                   = 41,
    GPIO22_IRQn                   = 42,
    GPIO23_IRQn                   = 43,
    GPIO24_IRQn                   = 44,
    GPIO25_IRQn                   = 45,
    GPIO26_IRQn                   = 46,
    GPIO27_IRQn                   = 47,
    GPIO28_IRQn                   = 48,
    GPIO29_IRQn                   = 49,
    GPIO30_IRQn                   = 50,
    GPIO31_IRQn                   = 51,
    BLE_HSLOT_IRQn                = 52,
    BLE_RX_IRQn                   = 53,
    BLE_TX_IRQn                   = 54,
    BLE_SLP_IRQn                  = 55,
    BLE_SKIP_IRQn                 = 56,
    BLE_END_IRQn                  = 57,
    BLE_START_IRQn                = 58,
    BLE_CRYPT_IRQn                = 59,
    BLE_ERROR_IRQn                = 60,
    BLE_TIMESTAMP_TGT_IRQn        = 61,
    BLE_GROSSTGTIM_IRQn           = 62,
    BLE_FINETGTIM_IRQn            = 63,
    BLE_SW_IRQn                   = 64
} IRQn_Type;

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M3 Processor and Core Peripherals */
#define __CM3_REV                 0x0201                /*!< Core Revision r2p1                             */
#define __NVIC_PRIO_BITS          3                     /*!< Number of Bits used for Priority Levels        */
#define __Vendor_SysTickConfig    0                     /*!< Set to 1 if different SysTick Config is used   */
#define __MPU_PRESENT             1                     /*!< MPU present or not                             */

/*@}*/ /* end of group CM3DS_MPS2_CMSIS */

#include "core_cm3.h"                                   /* Cortex-M3 processor and core peripherals           */
#include "system_BR00x.h"                           /* CM3DS System include file                      */

/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/
/** @addtogroup CM3DS_MPS2_Peripherals CM3DS_MPS2 Peripherals
  CM3DS_MPS2 Device Specific Peripheral registers structures
  @{
*/

#if defined (__CC_ARM__)
    //#pragma push
    #pragma anon_unions
#elif defined(__ICCARM__)
    #pragma language=extended
#elif defined(__GNUC__)
    /* anonymous unions are enabled by default */
#elif defined(__TMS470__)
    /* anonymous unions are enabled by default */
#elif defined(__TASKING__)
    #pragma warning 586
#else
 /* #warning Not supported compiler type*/
#endif

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
#define SET_BITS(_bits, _off) ((_bits) << (_off))
#define CLEAR_BITS(_bits, _off) (~((_bits) << (_off)))
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;
#define assert_param(expr) ((void)0)

/*-----------------------------------  (SCU) ---------------------------------*/
//typedef struct
//{
//    __IO uint32_t CLK_EN;                       /*!< Offset: 0x000  */  
//    __IO uint32_t SW_RST_CTRL;                  /*!< Offset: 0x004  */
//    __IO uint32_t CLK_SEL;                      /*!< Offset: 0x008  */
//    __IO uint32_t CLK_CONFIG;                   /*!< Offset: 0x00c  */
//    __IO uint32_t SYS_CONFIG;                   /*!< Offset: 0x010  */
//    __I  uint32_t SYS_STATUS;                   /*!< Offset: 0x014  */
//    __IO uint32_t PWR_CONFIG;                   /*!< Offset: 0x018  */
//    __I  uint32_t PWR_STATUS;                   /*!< Offset: 0x01c  */
//    __IO uint32_t DEV_CONFIG;                   /*!< Offset: 0x020  */
//    __I  uint32_t DEV_STATUS;                   /*!< Offset: 0x024  */
//    __IO uint32_t IO_CONFIG;                    /*!< Offset: 0x028  */
//    __I  uint32_t IO_STATUS;                    /*!< Offset: 0x02c  */
//    __IO uint32_t CLK_DIV1;                    /*!< Offset: 0x030  */
//    __IO uint32_t CLK_DIV2;
//    
//    __O  uint32_t SEND_CMD   ;                /*!< Offset: 0x034  */
//    __O  uint32_t SEND_DATA  ;                /*!< Offset: 0x036  */
//    __IO uint32_t READ_CMD   ;                /*!< Offset: 0x038  */
//    __IO uint32_t READ_DATA  ;                /*!< Offset: 0x03c  */
//    
//    __IO uint32_t RESERVED[1];                  /*!< Offset: 0x04c - 0x44 */
//    __IO uint32_t PAD_CFG[34];                  /*!< Offset:   */
//    __I  uint32_t DATA0;
//} SCU_TypeDef;

typedef struct
{
    __IO uint32_t CLK_EN;                       /*!< Offset: 0x000  */  
    __IO uint32_t SW_RST;                       /*!< Offset: 0x004  */
    __IO uint32_t CLK_CTL;                      /*!< Offset: 0x008  */
    __IO uint32_t CLK_DIV;                      /*!< Offset: 0x00c  */
    __IO uint32_t SYS_CONFIG;                   /*!< Offset: 0x010  */
    __I  uint32_t SYS_STATUS;                   /*!< Offset: 0x014  */
    __IO uint32_t SLEEP_EN;                     /*!< Offset: 0x018  */
    __I  uint32_t PWR_STATUS;                   /*!< Offset: 0x01c  */
    __IO uint32_t DEV_CONFIG;                   /*!< Offset: 0x020  */
    __I  uint32_t DEV_STATUS;                   /*!< Offset: 0x024  */
    __IO uint32_t IO_CONFIG;                    /*!< Offset: 0x028  */
    __I  uint32_t IO_STATUS;                    /*!< Offset: 0x02c  */
    __IO uint32_t CLK_DIV1;                     /*!< Offset: 0x030  */
    __IO uint32_t CLK_DIV2;                     /*!< Offset: 0x034  */
    
    __IO uint32_t SEND_CMD  ;                   /*!< Offset: 0x038  */
    __IO uint32_t SEND_DATA  ;                  /*!< Offset: 0x03C  */
    __IO uint32_t READ_CMD   ;                  /*!< Offset: 0x040  */
    __IO uint32_t READ_DATA  ;                  /*!< Offset: 0x044  */
    __IO uint32_t ANA_CTL0   ;                  /*!< Offset: 0x048  */
    __IO uint32_t ANA_CTL1   ;                  /*!< Offset: 0x04C  */
    __IO uint32_t ANA_CTL2   ;                  /*!< Offset: 0x050  */
    __IO uint32_t ANA_CTL3   ;                  /*!< Offset: 0x054  */
    __IO uint32_t ANA_CTL4   ;                  /*!< Offset: 0x058  */
    __I  uint32_t ANA_STATUS0   ;               /*!< Offset: 0x05C  */
    __I  uint32_t ANA_STATUS1   ;               /*!< Offset: 0x060  */
    __IO uint16_t TIMERS_DIV[8] ;               /*!< Offset: 0x064-0X70 */
    __IO uint32_t PAD_CFG[40];                  /*!< Offset: 0X74-0x114 */
    
    __IO uint32_t res; 
    __IO uint32_t BB_WAKEUP_MASK_L;             /*!< Offset: 0X118 */
    __IO uint32_t BB_WAKEUP_MASK_H;             /*!< Offset: 0X11c */
    __IO uint32_t BB_WAKEUP_MASK_SEL;           /*!< Offset: 0X120 */
    
} SCU_TypeDef;


/*-----------------------------------  (QUAD) ---------------------------------*/
typedef struct
{
    __IO uint32_t ENABLE;
    __IO uint32_t SAMPLEPER;
    __IO uint32_t REPORTPER;
    __I   uint32_t SAMPLE;

    __I  uint32_t ACC;
    __I  uint32_t ACCREAD;
    __I  uint32_t ACCDBL;
    __I  uint32_t ACCDBLREAD;

    __IO uint32_t INTENSET;
    __IO uint32_t INTENCLR;
    __IO uint32_t LEDPOL;
    __IO uint32_t LEDPRE;

    __IO uint32_t TASKS;
    __I   uint32_t EVENTS;
    __IO uint32_t SHORTS;
} QUAD_TypeDef;




/*-----------------------------------  (SPI) ---------------------------------*/


typedef struct
{
    __IO uint32_t CTRLR0 ;                      /*!< Offset: 0x000 Control Register 0 (R/W) */  
    __IO uint32_t CTRLR1 ;                      /*!< Offset: 0x004 Control Register 1 (R/W) */ 
    __IO uint32_t SSIENR ;                      /*!< Offset: 0x008 SSI Enable Register (R/W) */
    __IO uint32_t MWCR ;                        /*!< Offset: 0x00C Microwire Control Register (R/W) */
    __IO uint32_t SER ;                         /*!< Offset: 0x010 Slave Enable Register (R/W) */
    __IO uint32_t BAUDR ;                       /*!< Offset: 0x014 Baud Rate Select(R/W) */
    __IO uint32_t TXFTLR ;                      /*!< Offset: 0x018 Transmit FIFO Threshold Level(R/W) */
    __IO uint32_t RXFTLR ;                      /*!< Offset: 0x01C Receive FIFO Threshold Level(R/W) */

    __I  uint32_t TXFLR;                        /*!< Offset: 0x020 Transmit FIFO Level Register(R) */
    __I  uint32_t RXFLR;                        /*!< Offset: 0x024 Receive FIFO Level Register(R) */

    __I  uint32_t SR;                           /*!< Offset: 0x028 Status Register(R) */
    __IO uint32_t IMR;                          /*!< Offset: 0x02C Interrupt Mask Register(R/W) */
    __I  uint32_t ISR;                          /*!< Offset: 0x030 Interrupt  Register(R) */
    __IO uint32_t RISR;                         /*!< Offset: 0x034 Raw Interrupt  Register(R/W) */

    __I  uint32_t TXOICR;                       /*!< Offset: 0x038 Transmit FIFO Overflow Interrupt Clear Register (R) */
    __I  uint32_t RXOICR;                       /*!< Offset: 0x03C Receive FIFO Overflow Interrupt Clear Register (R) */
    __I  uint32_t RXUICR;                       /*!< Offset: 0x040 Receive FIFO Underflow Interrupt Clear Register(R) */
    __I  uint32_t MSTICR;                       /*!< Offset: 0x044 Multi-Master Interrupt Clear Register (R) */
    __I  uint32_t ICR;                          /*!< Offset: 0x048 Interrupt Clear Register (R) */

    __IO uint32_t DMACR;                        /*!< Offset: 0x04C DMA Control Register (R\W) */
    __IO uint32_t DMATDLR;                      /*!< Offset: 0x050 DMA Transmit Data Level (R\W) */
    __IO uint32_t DMARDLR;                      /*!< Offset: 0x054 DMA Receive Data Level (R\W) */

    __I  uint32_t IDR;                          /*!< Offset: 0x058 Identification Register (R) */
    __I  uint32_t VERSION_ID;                   /*!< Offset: 0x05C VERSION_ID (R) */

    __IO uint32_t DR[32];                       /*!< Offset: 0x060 + Data Register x (R/W) */

    __IO uint32_t res[4];                       /*  */

    __IO uint32_t RX_SAMPLE_DLY;                /*!< Offset: 0x0F0 RX Sample Delay Register (R/W) */
    __IO uint32_t SPI_CTRLR0;                   /*!< Offset: 0x0F4 SPI Control Register (R/W) */
    
    union {
        __IO  uint32_t  TXD_DRIVE_EDGE;               /*!< Offset: 0x0F8 RX Sample Delay Register (R/W) */
        __IO uint32_t  DDR_DRIVE_EDGE;
    };
    __IO uint32_t  XIP_MODE_BITS;               /*!< Offset: 0x0FC RX Sample Delay Register (R/W) */

    __IO uint32_t  XIP_INCR_INST;               /*!< Offset: 0x0100  XIP_INCR_INST - XIP INCR transfer opcode (R/W) */
    __IO uint32_t  XIP_WRAP_INST;               /*!< Offset: 0x0104  XIP_WRAP_INST - XIP WRAP transfer opcode (R/W) */
    __IO uint32_t  XIP_CTRL;                    /*!< Offset: 0x010C  XIP_CTRL - XIP Control Register  (R/W) */
    __IO uint32_t  XIP_SER;                     /*!< Offset: 0x0110  Slave Enable Register (R/W) */
    __I  uint32_t  XRXOICR;                     /*!< Offset: 0x0114  XIP Receive FIFO Overflow Interrupt Clear Register(R/W) */
    __IO uint32_t  XIP_CNT_TIME_OUT;            /*!< Offset: 0x0100  XIP time out register for continuous transfers (R/W) */
    // __IO uint32_t  XIP_CNT_TIME_OUT;

} SSI_TypeDef;



/*-----------------------------------  (I2C) ---------------------------------*/
typedef struct
{
    __IO uint32_t  IC_CON;                      /*!< Offset: 0x000 I2C Control (R/W) */  
    __IO uint32_t  IC_TAR;                      /*!< Offset: 0x004 I2C Target Address (R/W) */  
    __IO uint32_t  IC_SAR;                      /*!< Offset: 0x008 I2C Slave Address (R/W) */  
    __IO uint32_t  IC_HS_MADDR;                 /*!< Offset: 0x00C I2C HS Master Mode Code Address */
    __IO uint32_t  DATA_CMD;                    /*!< Offset: 0x010  Rx/Tx Data Buffer and Command */

    union {
    __IO uint32_t  IC_SS_SCL_HCNT;              /*!< Offset: 0x014  Standard speed I2C Clock SCL High Count */
    __IO uint32_t  IC_UFM_SCL_HCNT;             /*!< Offset: 0x014  Ultra-Fast mode I2C Clock High Count Register */

    };

    union {
    __IO uint32_t  IC_SS_SCL_LCNT;              /*!< Offset: 0x018  Standard speed I2C Clock SCL low Count */
    __IO uint32_t  IC_UFM_SCL_LCNT;             /*!< Offset: 0x018 Ultra-Fast mode I2C Clock Low Count Register */
    };

    union {
    __IO uint32_t  IC_FS_SCL_HCNT;              /*!< Offset: 0x01c  Fast Mode and Fast Mode Plus I2C Clock SCL High Count */
    __IO uint32_t  IC_UFM_TBUF_CNT;             /*!< Offset: 0x01c  Ultra-Fast mode TBuf Idle Count Register */
    };


    __IO uint32_t  IC_FS_SCL_LCNT;              /*!< Offset: 0x020  Fast Mode and Fast Mode Plus I2C Clock SCL Low Count */
    __IO uint32_t  IC_HS_SCL_HCNT;              /*!< Offset: 0x024  High speed I2C Clock SCL High Count */
    __IO uint32_t  IC_HS_SCL_LCNT;              /*!< Offset: 0x028  High speed I2C Clock SCL Low Count */
    __I  uint32_t  INTR_STAT;                   /*!< Offset: 0x02C  I2C Interrupt Status */
    __IO uint32_t  INTR_MASK;                   /*!< Offset: 0x030  I2C Interrupt Mask */
    __I  uint32_t  RAW_INTR_STAT;               /*!< Offset: 0x034  I2C Raw Interrupt Status*/
    __IO uint32_t  RX_TL;                       /*!< Offset: 0x038  I2C Receive FIFO Threshold */
    __IO uint32_t  TX_TL;                       /*!< Offset: 0x03C  I2C Transmit FIFO Threshold */

    __I  uint32_t  IC_CLR_INTR;                 /*!< Offset: 0x040  Clear Combined and Individual Interrupts */
    __I  uint32_t  IC_CLR_RX_UNDER;             /*!< Offset: 0x044  Clear RX_UNDER Interrupt */
    __I  uint32_t  IC_CLR_RX_OVER;              /*!< Offset: 0x048  Clear RX_OVER Interrupt */
    __I  uint32_t  IC_CLR_TX_OVER;              /*!< Offset: 0x04C  Clear TX_OVER Interrupt */
    __I  uint32_t  IC_CLR_RD_REQ;               /*!< Offset: 0x050  Clear RD_REQ Interrupt */
    __I  uint32_t  IC_CLR_TX_ABRT;              /*!< Offset: 0x054  Clear TX_ABRT Interrupt */
    __I  uint32_t  IC_CLR_RX_DONE;              /*!< Offset: 0x058  Clear RX_DONE Interrupt */
    __I  uint32_t  IC_CLR_ACTIVITY;             /*!< Offset: 0x05C  Clear ACTIVITY Interrupt */
    __I  uint32_t  IC_CLR_STOP_DET;             /*!< Offset: 0x060  Clear STOP_DET Interrupt */
    __I  uint32_t  IC_CLR_START_DET;            /*!< Offset: 0x064  Clear START_DET Interrupt */
    __I  uint32_t  IC_CLR_GEN_CALL;             /*!< Offset: 0x068  Clear GEN_CALL Interrupt */

    __IO uint32_t  IC_ENABLE;                   /*!< Offset: 0x06C  I2C Enable */
    __I  uint32_t  IC_STATUS;                   /*!< Offset: 0x070  I2C Status register */

    __I  uint32_t  IC_TXFLR;                    /*!< Offset: 0x074  Transmit FIFO Level Register */
    __I  uint32_t  IC_RXFLR;                    /*!< Offset: 0x078  Receive FIFO Level Register */
    __IO uint32_t  SDA_HOLD;                    /*!< Offset: 0x07C  SDA hold time length register */
    __I  uint32_t  TX_ABRT_SOURCE;              /*!< Offset: 0x080  I2C Transmit Abort Status Register */
    __IO uint32_t  SLV_DATA_NACK_ONLY;          /*!< Offset: 0x084 Generate SLV_DATA_NACK Register */

    __IO uint32_t  IC_DMA_CR;                   /*!< Offset: 0x088 DMA Control Register for transmit and receive handshaking interface */
    __IO uint32_t  IC_DMA_TDLR;                 /*!< Offset: 0x08C DMA Transmit Data Level */
    __IO uint32_t  IC_DMA_RDLR;                 /*!< Offset: 0x090 DMA Receive Data Level */
    __IO uint32_t  IC_SDA_SETUP;                /*!< Offset: 0x094 I2C SDA Setup Register */
    __IO uint32_t  IC_ACK_GENERAL_CALL;         /*!< Offset: 0x098 I2C ACK General Call Register */
    __I  uint32_t  IC_ENABLE_STATUS;            /*!< Offset: 0x09c I2C Enable Status Register */

    union {
    __IO uint32_t  FS_SPKLEN;                   /*!< Offset: 0x0A0 ISS and FS spike suppression limit */
    __IO uint32_t  IC_UFM_SPKLEN;               /*!< Offset: 0x0A0 I2C Ultra-Fast mode Spike suppression Register */
    };

    __IO uint32_t  HS_SPKLEN;                   /*!< Offset: 0x0A4 HS spike suppression limit*/
  
    __I  uint32_t  IC_CLR_RESTART_DET;          /*!< Offset: 0x0A8 Clear RESTART_DET Interrupt*/
    __IO uint32_t  IC_SCL_STUCK_AT_LOW_TIMEOUT; /*!< Offset: 0x0AC I2C SCL stuck at low timeout register*/
    __IO uint32_t  IC_SDA_STUCK_AT_LOW_TIMEOUT; /*!< Offset: 0x0B0 I2C SDA stuck at low timeout register*/
    __I  uint32_t  IC_CLR_SCL_STUCK_DET;        /*!< Offset: 0x0B4 Clear SCL Stuck at Low Detect Interrupt Register*/
    __I  uint32_t  resv0;                       /*!< Offset: 0x0B8 I2C Device ID*/
    __IO uint32_t  IC_SMBUS_CLOCK_LOW_SEXT;     /*!< Offset: 0x0BC SMBUS Slave Clock Extend Timeout Register*/
    __IO uint32_t  IC_SMBUS_CLOCK_LOW_MEXT;     /*!< Offset: 0x0C0 SMBUS Master extend clock Timeout Register*/
    __IO uint32_t  IC_SMBUS_THIGH_MAX_IDLE_COUNT;/*!< Offset: 0x0C4 SMBus Thigh MAX Bus-Idle count Register*/
    __I  uint32_t  IC_SMBUS_INTR_STAT;          /*!< Offset: 0x0C8 I2C SMBUS Interrupt Status Register*/
    __IO uint32_t  IC_SMBUS_INTR_MASK;          /*!< Offset: 0x0CC I2C Interrupt Mask Register*/

    __I  uint32_t  IC_SMBUS_INTR_RAW_STATUS;    /*!< Offset: 0x0D0 I2C SMBUS Raw Interrupt Status Register*/
    __O  uint32_t  IC_CLR_SMBUS_INTR;           /*!< Offset: 0x0D4 Clear SMBUS Interrupt Register*/
    __IO uint32_t  IC_SMBUS_UDID_LSB;           /*!< Offset: 0x0D8 SMBUS ARP UDID LSB Register*/
    __IO uint32_t  resv1[6];                    /*!< Offset: 0x0DC ~ 0x0F0 */

}I2C_TypeDef;

/*-----------------------------------  (GPIO) ---------------------------------*/
typedef struct
{
    __IO uint32_t DR0;                          /*!< Offset: 0x000 Port A data register(R/W) */
    __IO uint32_t DDR0;                         /*!< Offset: 0x004 Port A data direction register(R/W) */
    __IO uint32_t CTL0;                         /*!< Offset: 0x008 Port A data source register(R/W) */

    __IO uint32_t DR1 : 2;                      /*!< Offset: 0x00C Port B data register(R/W) */
    __IO uint32_t RESERVED0 : 30;               /*!< Reserved */
    __IO uint32_t DDR1 : 2;                     /*!< Offset: 0x010 Port B data direction register(R/W) */
    __IO uint32_t RESERVED1 : 30;               /*!< Reserved */
    __IO uint32_t CTL1 : 2;                     /*!< Offset: 0x014 Port B data source register(R/W) */
    __IO uint32_t RESERVED2 : 30;               /*!< Reserved */

    __IO uint32_t RESERVED3[6];                 /*!< Reserved */

    __IO uint32_t IE;                           /*!< Offset: 0x030 Interrupt enable register (R/W) */
    __IO uint32_t IM;                           /*!< Offset: 0x034 Interrupt mask register (R/W) */
    __IO uint32_t ITL;                          /*!< Offset: 0x038 Interrupt level register (R/W) */
    __IO uint32_t IP;                           /*!< Offset: 0x03c Interrupt polarity register (R/W) */
    __I  uint32_t IS;                           /*!< Offset: 0x040 Interrupt status of Port A (R) */
    __I  uint32_t RIS;                          /*!< Offset: 0x044 Raw interrupt status of Port A (premasking) (R) */
    __IO uint32_t DB;                           /*!< Offset: 0x048 Debounce enable register (R/W) */

    __O  uint32_t EOI;                          /*!< Offset: 0x04C Port A clear interrupt register (W) */

    __I  uint32_t EXTDR0;                       /*!< Offset: 0x050 External Port A (R)  */
    __I  uint32_t EXTDR1:2;                     /*!< Offset: 0x054 External Port B (R)  */
    __I  uint32_t RESERVED4:30;                 /*!< Offset: 0x054 Reserved */
    __IO uint32_t RESERVED5;                    /*!< Offset: 0x058 Reserved */
    __I  uint32_t RESERVED6;                    /*!< Offset: 0x05C Reserved */

    __IO uint32_t ISS;                          /*!< Offset: 0x060 Level-sensitive synchronization enable register (R/W) */
    __I  uint32_t RESERVED9;                    /*!< Reserved */
    __IO uint32_t IBE;                          /*!< Offset: 0x068 Interrupt both edge type (R) */

    __I  uint32_t RESERVED10;                   /*!< Reserved */
    __I  uint32_t RESERVED11;                   /*!< Reserved */
    __I  uint32_t RESERVED12;                   /*!< Reserved */
} GPIO_TypeDef;


typedef struct
{
    union{
        __I uint32_t LRBR;                      /*!< Offset: 0x020+0X40*0   This specifies the Left Receive Buffer Register..*/
        __O uint32_t LTHR;                      /*!< Offset: 0x020+0X40*0   This specifies the Left Transmit Buffer Register..*/
    };    

    union{
        __I uint32_t RRBR;                      /*!< Offset: 0x024+0X40*0    This specifies the Right Receive Buffer Register*/
        __O uint32_t RTHR;                      /*!< Offset: 0x024+0X40*0    This specifies the Right Transmit Buffer Register..*/
    };

    __IO uint32_t RER;                          /*!< Offset: 0x028+0X40*0    This specifies the Receive Enable Register */
    __IO uint32_t TER;                          /*!< Offset: 0x02C+0X40*0    This specifies the Transmit Enable Register */

    __IO uint32_t RCR;                          /*!< Offset: 0x030+0X40*0    This specifies the Receive Configuration Register. */
    __IO uint32_t TCR;                          /*!< Offset: 0x034+0X40*0    This specifies the Transmit Configuration Register. */

    __I  uint32_t ISR;                          /*!< Offset: 0x038+0X40*0    This specifies the Interrupt Status Register. */
    __IO uint32_t IMR;                          /*!< Offset: 0x03C+0X40*0    This specifies the Interrupt Mask Register */

    __I  uint32_t ROR;                          /*!< Offset: 0x040+0X40*0    This specifies the Receive Overrun Register */
    __I  uint32_t TOR;                          /*!< Offset: 0x044+0X40*0   This specifies the Transmit Overrun Register.*/

    __IO uint32_t RFCR;                         /*!< Offset: 0x048+0X40*0    This specifies the Receive FIFO Configuration Register. */
    __IO uint32_t TFCR;                         /*!< Offset: 0x04C+0X40*0    This specifies the Transmit FIFO Configuration Register. */
   
    __O uint32_t RFF;                          /*!< Offset: 0x050+0X40*0    This specifies the Receive FIFO Flush Register. */
    __O uint32_t TFF;                          /*!< Offset: 0x054+0X40*0    This specifies the Transmit FIFO Flush Register*/

    __IO uint32_t resv1[2] ;                    /*!< Offset: 0x058+0X40*0  - 0x05c+0X40*0 r*/
}I2S_Chn_TypeDef;


/*-----------------------------------  (I2SM) ---------------------------------*/
typedef struct
{
    __IO uint32_t   IER;                        /*!< Offset: 0x000 This register acts as a global enable/disable for i2s (R/W) */
    __IO uint32_t   IRER;                       /*!< Offset: 0x004 This register acts as an enable/disable for the i2s Receiver block (R/W) */
    __IO uint32_t   ITER;                       /*!< Offset: 0x008 I2S Transmitter Block Enable Register (R/W) */
    __IO uint32_t   CER;                        /*!< Offset: 0x00C Clock Enable Register (R/W) */
    __IO uint32_t   CCR;                        /*!< Offset: 0x010 Clock Configuration Register */

    __O uint32_t    RXFFR;                      /*!< Offset: 0x014  This register specifies the Receiver Block FIFO Reset Register */
    __O uint32_t    TXFFR;                      /*!< Offset: 0x018  This register specifies the Transmitter Block FIFO Reset Register.*/
    __I uint32_t    resv00;                     /*Offset: 0x01c */

    I2S_Chn_TypeDef I2S_Ch;                     /*Offset:  */
    
    __I uint32_t    resv001[16*3];              
    __I uint32_t    resv5[40];                  /*!<0x118 - 0x1bc    */

    __I uint32_t    RXDMA;                      /*!< Offset: 0x1C0  Receiver Block DMA Register */
    __O uint32_t    RRXDMA;                     /*!< Offset: 0x1C4  Reset Receiver Block DMA Register */

    __O uint32_t    TXDMA;                      /*!< Offset: 0x1C8  Transmitter Block DMA Register */
    __O uint32_t    RTXDMA;                     /*!< Offset: 0x1CC  Transmitter Receiver Block DMA Register */

    __I uint32_t    resv6[8];
    __I uint32_t    RESERVED0;               
    __I uint32_t    RESERVED1;               
    __I uint32_t    RESERVED2;              
    __I uint32_t    RESERVED3;                 
} I2S_TypeDef;


typedef struct
{
    __IO   uint32_t  LOAD_COUNT;                /*!< Offset: 0x0000 Value to be loaded into TimerN (R/W) */
    __I    uint32_t  CURRENT_COUNT;             /*!< Offset: 0x0004 Current Value of Timer1 (R) */
    __IO   uint32_t  CONTROL_REG;               /*!< Offset: 0x0008 Control Register for Timer1 (R/W) */
    __I    uint32_t  EOI;                       /*!< Offset: 0x000C Clears the interrupt from Timer1 (R) */
    __I    uint32_t  INTSTATUS;                 /*!< Offset: 0x0010 Contains the interrupt status for Timer1 (R) */
} TIMER_TypeDef;

/*-----------------------------------  (TIMERS) ---------------------------------*/
typedef struct
{
    TIMER_TypeDef   TIMER[8];
    
    __I    uint32_t  INT_STATUS;                /*!< Offset: 0x00A0 Contains the interrupt status of all timers in the component.(R) */
    __I    uint32_t  EOI;                       /*!< Offset: 0x00A4 Returns all zeroes (0) and clears all active interrupts (R) */
    __I    uint32_t  RAW_INT_STATUS;            /*!< Offset: 0x00A8 Contains the unmasked interrupt status of all timers in the component. (R) */
    __I    uint32_t  RESERVED1;                 /*!< Offset: 0x00AC (R) */

    __IO   uint32_t  TIMER1_LOAD_COUNT2;        /*!< Offset: 0x00B0 Value to be loaded into Timer1 when toggle output changes from 0 to 1 (R/W) */
    __IO   uint32_t  TIMER2_LOAD_COUNT2;        /*!< Offset: 0x00B4 Value to be loaded into Timer2 when toggle output changes from 0 to 1 (R/W) */
    __IO   uint32_t  TIMER3_LOAD_COUNT2;        /*!< Offset: 0x00B8 Value to be loaded into Timer3 when toggle output changes from 0 to 1 (R/W) */
    __IO   uint32_t  TIMER4_LOAD_COUNT2;        /*!< Offset: 0x00BC Value to be loaded into Timer4 when toggle output changes from 0 to 1 (R/W) */
    __IO   uint32_t  TIMER5_LOAD_COUNT2;        /*!< Offset: 0x00C0 Value to be loaded into Timer5 when toggle output changes from 0 to 1 (R/W) */
    __IO   uint32_t  TIMER6_LOAD_COUNT2;        /*!< Offset: 0x00C4 Value to be loaded into Timer6 when toggle output changes from 0 to 1 (R/W) */
    __IO   uint32_t  TIMER7_LOAD_COUNT2;        /*!< Offset: 0x00C8 Value to be loaded into Timer7 when toggle output changes from 0 to 1 (R/W) */
    __IO   uint32_t  TIMER8_LOAD_COUNT2;        /*!< Offset: 0x00CC Value to be loaded into Timer8 when toggle output changes from 0 to 1 (R/W) */
} TIMERS_TypeDef;


/*-----------------------------------  (RTC) ---------------------------------*/
typedef struct
{
    __I   uint32_t DR;                          /*!< Offset: 0x000 Returns the current RTC value  (R) */
    __IO  uint32_t CMR;                         /*!< Offset: 0x004 Counter Match Register  (R/w) */
    __IO  uint32_t CLR;                         /*!< Offset: 0x008 Counter Load Register  (R/w) */
    __IO  uint32_t CCR;                         /*!< Offset: 0x00C  Control Register  (R/w) */
    __IO  uint32_t IMSC;                        /*!< Offset: 0x010 Interrupt Mask Set or Clear register (R) */
    __I   uint32_t RIS;                         /*!< Offset: 0x014 Raw Interrupt Status (R) */
    __I   uint32_t MIS;                         /*!< Offset: 0x018 Masked Interrupt Status (R) */
    __O   uint32_t ICR;                         /*!< Offset: 0x01c  Interrupt Clear Registerr (W) */
} RTC_TypeDef;

/*-----------------------------------  (WDT) ---------------------------------*/
typedef struct
{
    __IO  uint32_t  CR;                         /*!< Offset: 0x0000   Control Register(W/R) */
    __IO  uint32_t  TORR;                       /*!< Offset: 0x0004   Timeout Range Register(R) */
    __I   uint32_t  CCVR;                       /*!< Offset: 0x0008   Current Counter Value Register(R) */
    __O   uint32_t  CRR;                        /*!< Offset: 0x000C   Counter Restart Register(W) */
    __I   uint32_t  STAT;                       /*!< Offset: 0x0010   Interrupt Status Register(R) */
    __I   uint32_t  EIO;                        /*!< Offset: 0x0014   Interrupt Clear Register (R) */

    __IO  uint32_t  resv1[54];                  /*!< Offset: 0x0018 ~ 0x0E0 */
    __I   uint32_t  COMP_PARAMS_5;              /*!< Offset: 0x00E4   Component Parameters Register 5  (R) */
    __I   uint32_t  COMP_PARAMS_4;              /*!< Offset: 0x00E8   Component Parameters Register 4  (R) */
    __I   uint32_t  COMP_PARAMS_3;              /*!< Offset: 0x00EC   Component Parameters Register 3  (R) */
    __I   uint32_t  COMP_PARAMS_2;              /*!< Offset: 0x00F0   Component Parameters Register 2  (R) */
    __I   uint32_t  COMP_PARAMS_1;              /*!< Offset: 0x00F4   Component Parameters Register 1  (R) */

    __I   uint32_t  COMP_VERSION;               /*!< Offset: 0x00FC   Component Version Register (R) */
    __I   uint32_t  COMP_TYPE;                  /*!< Offset: 0x00FC   Component Type Register (R) */
} WDT_TypeDef;



/*-----------------------------------  (RESV) ---------------------------------*/
typedef struct
{
	__IO uint32_t unrealized ;
} RESV_TypeDef;




#define DMA_CHANNELS_NUM           8

/*
#define DMAH_CH0_MAX_BLK_SIZE_INT   12
#define DMAH_NUM_HS_INT             16
#define LOG2_DMAH_NUM_HS_INT        4
*/

/*-----------------------------------  (DMA) ---------------------------------*/
typedef struct {
    __IO uint32_t  SAR;                         /*!< Offset: 0x000 Channelx  Source Address Register  (R/W) */
    __IO uint32_t  RESERVED0;                   /*!< Offset: 0x004 */
    __IO uint32_t  DAR;                         /*!< Offset: 0x008 Channelx  Destination Address Register  (R/W) */
    __IO uint32_t  RESERVED1;                   /*!< Offset: 0x00C */
    __IO uint32_t  LLP;                         /*!< Offset: 0x010 Channelx  Linked List Pointer  Register  (R/W) */
    __IO uint32_t  RESERVED2;                   /*!< Offset: 0x014 */
    __IO uint32_t  CTL0;                        /*!< Offset: 0x018 Channelx  Control 0 Register Register  (R/W) */
//    __IO uint32_t  CTL1 : 12;                   /*!< Offset: 0x01C Channelx  Control 1 Register Register  (R/W) */
//    __IO uint32_t  RESERVED3 : 20;              /*!< Offset: 0x01C */
    __IO uint32_t  CTL1;   
    __IO uint32_t  SSTAT;                       /*!< Offset: 0x020 Channelx  Source Status Register (R/W) */
    __IO uint32_t  RESERVED4;                   /*!< Offset: 0x024 */
    __IO uint32_t  DSTAT;                       /*!< Offset: 0x028 Channelx  Destination Status Registerr (R/W) */
    __IO uint32_t  RESERVED5;                   /*!< Offset: 0x02C */

    __IO uint32_t  SSTATAR;                     /*!< Offset: 0x030 Channelx  Source Status Address Register (R/W) */
    __IO uint32_t  RESERVED6;                   /*!< Offset: 0x034 */
    __IO uint32_t  DSTATAR;                     /*!< Offset: 0x038 Channelx  Destination Status Address Register (R/W) */
    __IO uint32_t  RESERVED7;                   /*!< Offset: 0x03C */
    __IO uint32_t  CFG0;                        /*!< Offset: 0x040 Channelx  Configuration 0 Register (R/W) */
    __IO uint32_t  CFG1; 
//    __IO uint32_t  CFG1 : 10;                   /*!< Offset: 0x044 Channelx  Configuration 1 Register (R/W) */
//    __IO uint32_t  RESERVED8 : 22;              /*!< Offset: 0x044 */

    __IO uint32_t  RESERVED9;                   /*!< Offset: 0x048 */
    __IO uint32_t  RESERVEDa;                   /*!< Offset: 0x04C */
    __IO uint32_t  RESERVEDb;                   /*!< Offset: 0x050 */
    __IO uint32_t  RESERVEDc;                   /*!< Offset: 0x054 */
} DMA_ChRegDef;

typedef struct {
    __I  uint32_t RST ;                      /*!< Offset: 0x2C0 Raw Status for IntTfr Interrupt (R) */
//    __I  uint32_t RESERVED0 : 24;               /*!< Offset: 0x2C0  */
    __I  uint32_t RESERVED1;                    /*!< Offset: 0x2C4  */
    __I  uint32_t RSB ;                      /*!< Offset: 0x2C8 Raw Status for IntBlock Interrupt (R) */
//    __I  uint32_t RESERVED2 : 24;               /*!< Offset: 0x2C8  */
    __I  uint32_t RESERVED3;                    /*!< Offset: 0x2CC  */
    __I  uint32_t RSST ;                     /*!< Offset: 0x2D0 Raw Status for IntSrcTran Interrupt (R) */
//    __I  uint32_t RESERVED4 : 24;               /*!< Offset: 0x2D0  */
    __I  uint32_t RESERVED5;                    /*!< Offset: 0x2D4  */
    __I  uint32_t RSDT ;                     /*!< Offset: 0x2D8 Raw Status for IntDstTran Interrupt (R) */
//    __I  uint32_t RESERVED6 : 24;               /*!< Offset: 0x2D8  */
    __I  uint32_t RESERVED7;                    /*!< Offset: 0x2DC  */
    __I  uint32_t RSER ;                     /*!< Offset: 0x2E0 Raw Status for IntErr Interrupt (R) */
//    __I  uint32_t RESERVED8 : 24;               /*!< Offset: 0x2E0  */
    __I  uint32_t RESERVED9;                    /*!< Offset: 0x2E4  */

    __I  uint32_t ST ;                       /*!< Offset: 0x2E8  Status for IntTfr Interrupt (R) */
//    __I  uint32_t RESERVEDa : 24;               /*!< Offset: 0x2E8  */
    __I  uint32_t RESERVEDb;                    /*!< Offset: 0x2EC  */
    __I  uint32_t SB ;                       /*!< Offset: 0x2F0  Status for IntBlock Interrupt (R) */
//    __I  uint32_t RESERVEDc : 24;               /*!< Offset: 0x2F0  */
    __I  uint32_t RESERVEDd;                    /*!< Offset: 0x2F4  */
    __I  uint32_t SST ;                      /*!< Offset: 0x2F8  Status for IntSrcTran Interrupt (R) */
//    __I  uint32_t RESERVEDe : 24;               /*!< Offset: 0x2F8  */
    __I  uint32_t RESERVEDf;                    /*!< Offset: 0x2FC  */
    __I  uint32_t SDT ;                      /*!< Offset: 0x300  Status for IntDstTran Interrupt (R) */
//    __I  uint32_t RESERVED10 : 24;              /*!< Offset: 0x300  */
    __I  uint32_t RESERVED11;                   /*!< Offset: 0x304  */
    __I  uint32_t SER ;                      /*!< Offset: 0x308  Status for IntErr Interrupt (R) */
//    __I  uint32_t RESERVED12 : 24;              /*!< Offset: 0x308  */
    __I  uint32_t RESERVED13;                   /*!< Offset: 0x30C  */

    __IO uint32_t MT ;                      /*!< Offset: 0x310  Mask for IntTfr Interrupt (R/W)) */
//    __I  uint32_t RESERVED14 : 16;              /*!< Offset: 0x310  */
    __I  uint32_t RESERVED15;                   /*!< Offset: 0x314  */
    __IO uint32_t MB ;                      /*!< Offset: 0x318  Mask for IntBlock Interrupt (R/W)) */
//    __I  uint32_t RESERVED16 : 16;              /*!< Offset: 0x318  */
    __I  uint32_t RESERVED17;                   /*!< Offset: 0x31C  */
    __IO uint32_t MST ;                     /*!< Offset: 0x320  Mask for IntSrcTran Interrupt (R/W)) */
//    __I  uint32_t RESERVED18 : 16;              /*!< Offset: 0x320  */
    __I  uint32_t RESERVED19;                   /*!< Offset: 0x324  */
    __IO uint32_t MDT ;                     /*!< Offset: 0x328  Mask for IntDstTran Interrupt (R/W)) */
//    __I  uint32_t RESERVED1a : 16;              /*!< Offset: 0x328  */
    __I  uint32_t RESERVED1b;                   /*!< Offset: 0x32C  */
    __IO uint32_t MR ;                      /*!< Offset: 0x330  Mask for IntErr Interrupt (R/W)) */
//    __I  uint32_t RESERVED1c : 16;              /*!< Offset: 0x330  */
    __I  uint32_t RESERVED1d;                   /*!< Offset: 0x334  */

    __O  uint32_t CT ;                       /*!< Offset: 0x338  Clear for IntTfr Interrupt (W)) */
//   __I  uint32_t RESERVED1e : 24;              /*!< Offset: 0x338  */
    __I  uint32_t RESERVED1f;                   /*!< Offset: 0x33C  */
    __O  uint32_t CB ;                       /*!< Offset: 0x340  Clear for IntBlock Interrupt (W)) */
//    __I  uint32_t RESERVED20 : 24;              /*!< Offset: 0x340  */
    __I  uint32_t RESERVED21;                   /*!< Offset: 0x344  */
    __O  uint32_t CST ;                      /*!< Offset: 0x348  Clear for IntSrcTran Interrupt (W)) */
//    __I  uint32_t RESERVED22 : 24;              /*!< Offset: 0x348  */
    __I  uint32_t RESERVED23;                   /*!< Offset: 0x34C  */
    __O  uint32_t CDT ;                      /*!< Offset: 0x350  Clear for IntDstTran Interrupt (W)) */
//    __I  uint32_t RESERVED24 : 24;              /*!< Offset: 0x350  */
    __I  uint32_t RESERVED25;                   /*!< Offset: 0x354  */
    __O  uint32_t CER ;                      /*!< Offset: 0x358  Clear for IntErr Interrupt (W)) */
//    __I  uint32_t RESERVED26 : 24;              /*!< Offset: 0x358  */
    __I  uint32_t RESERVED27;                   /*!< Offset: 0x35C  */

    __I  uint32_t SI ;                       /*!< Offset: 0x360  Status for each interrupt type (W)) */
//    __I  uint32_t RESERVED28 : 28;              /*!< Offset: 0x360  */
    __I  uint32_t RESERVED29;                   /*!< Offset: 0x364  */
} DMA_IntRegDef;

typedef struct {
    __IO uint32_t RSR ;                     /*!< Offset: 0x368  Source Software Transaction Request Register (R/W)) */
//    __I  uint32_t RESERVED0 : 16;               /*!< Offset: 0x39C  */
    __I  uint32_t RESERVED1;                    /*!< Offset: 0x39C  */
    __IO uint32_t RDR ;                     /*!< Offset: 0x370  Destination Software Transaction Request Register (R/W)) */
//    __I  uint32_t RESERVED2 : 16;               /*!< Offset: 0x39C  */
    __I  uint32_t RESERVED3;                    /*!< Offset: 0x39C  */
    __IO uint32_t SRSR ;                    /*!< Offset: 0x378  Single Source Transaction Request Register (R/W)) */
//    __I  uint32_t RESERVED4 : 16;               /*!< Offset: 0x39C  */
    __I  uint32_t RESERVED5;                    /*!< Offset: 0x39C  */
    __IO uint32_t SRDR ;                    /*!< Offset: 0x380  Single Destination Transaction Request Register (R/W)) */
//    __I  uint32_t RESERVED6 : 16;               /*!< Offset: 0x39C  */
    __I  uint32_t RESERVED7;                    /*!< Offset: 0x39C  */
    __IO uint32_t LSR ;                     /*!< Offset: 0x388  Last Source Transaction Request Register (R/W)) */
//    __I  uint32_t RESERVED8 : 16;               /*!< Offset: 0x39C  */
    __I  uint32_t RESERVED9;                    /*!< Offset: 0x39C  */
    __IO uint32_t LDR ;                     /*!< Offset: 0x390  Last Destination Transaction Request Register(R/W)) */
//    __I  uint32_t RESERVEDa : 16;               /*!< Offset: 0x39C  */
    __I  uint32_t RESERVEDb;                    /*!< Offset: 0x39C  */
} DMA_SoftHSRegDef;

typedef struct {
    __IO uint32_t CFG ;                      /*!< Offset: 0x398  DMA Configuration Register (R/W)) */
//    __I  uint32_t RESERVED0 : 31;               /*!< Offset: 0x398  */
    __I  uint32_t RESERVED1;                    /*!< Offset: 0x39C  */
    __IO uint32_t EN ;                      /*!< Offset: 0x3A0  DMA Channel Enable Register (R/W)) */
//    __I  uint32_t RESERVED2 : 16;               /*!< Offset: 0x3A0  */
    __I  uint32_t RESERVED3[21];                /*!< Offset: 0x3A4 */
} DMA_MiscRegDef;

typedef struct {
    DMA_ChRegDef     CHR[DMA_CHANNELS_NUM];
    DMA_IntRegDef    IR;
    DMA_SoftHSRegDef SR;
    DMA_MiscRegDef   MR;
} DMA_TypeDef;


/*------------- Universal Asynchronous Receiver Transmitter (UART) -----------*/
typedef struct {
    union {
        __I   uint32_t  RBR;                    /*!< Offset: 0x000 Receiver Buffer  (R) */
        __O   uint32_t  THR;                    /*!< Offset: 0x000 Transmit Buffer  (R) */
        __IO  uint32_t  DLL;                    /*!< Offset: 0x000 Divisor Low (R/W) */
    };
    union {
        __IO uint32_t  DLH;                     /*!< Offset: 0x004 Divisor High (R/W) */
        __IO uint32_t  IER;                     /*!< Offset: 0x004 Interrupt Enable (R/W) */
    };
    union {
        __I  uint32_t  IIR;                     /*!< Offset: 0x008 Interrupt ID (R) */
        __O  uint32_t  FCR;                     /*!< Offset: 0x008 FIFO Control (W) */
    };
    __IO   uint32_t  LCR;                       /*!< Offset: 0x00C Line Control Register (R/W) */
    __IO   uint32_t  MCR;                       /*!< Offset: 0x010 Modem Control Register (R/W) */
    __I    uint32_t  LSR;                       /*!< Offset: 0x014 Line Status Register (R/W) */
    __I    uint32_t  MSR;                       /*!< Offset: 0x018 Modem Status Register (R/W) */
    __IO   uint32_t  SCR;                       /*!< Offset: 0x01C Scratchpad Register (R/W) */
    __IO   uint32_t  RESERVED0[20];             /*!< Offset: 0x020~0x06C */
    __IO   uint32_t  FAR;                       /*!< Offset: 0x070 FIFO Access Register (R/W) */
    __I    uint32_t  TFR;                       /*!< Offset: 0x074 Transmit FIFO Read (R) */
    __O    uint32_t  RFW;                       /*!< Offset: 0x078 Receive FIFO Write (W) */
    __I    uint32_t  USR;                       /*!< Offset: 0x07C UART Status (R) */

    __IO   uint32_t  TFL;                       /*!< Offset: 0x080 UART Status (R) */
    __IO   uint32_t  RFL;                       /*!< Offset: 0x084 UART Status (R) */
 
    __IO   uint32_t  RESERVED2[7];              /*!< Offset: 0x088 ~ 0x0A0 */
    __IO   uint32_t  HTX;                       /*!< Offset: 0x0A4 Halt TX */
    __O    uint32_t  DMSA;                      /*!< Offset: 0x0A8 DMA Software Ack (W) */
    __IO   uint32_t  RESERVED3[5];              /*!< Offset: 0x0AC ~ 0x0BC */
    __IO   uint32_t  DLF;                       /*!< Offset: 0x0C0 Divisor Latch Fractional Value (R/W) */
    __IO   uint32_t  RAR;                       /*!< Offset: 0x0C4 Receive Addr (R/W) */
    __IO   uint32_t  TAR;                       /*!< Offset: 0x0C8 Transmit Addr (R/W) */
    __IO   uint32_t  LCR_EXT;                   /*!< Offset: 0x0CC Line Extended COntrol (R/W) */
} UART_TypeDef;

/*--------------------------------USB---------------------------------------------*/
typedef struct
{
    //Global Register 
    __IO uint32_t GOTGCTL;                           /*!< Offset: 0x00 (R/W) Control and Status Register*/
    __IO uint32_t GOTGINT;                           /*!< Offset: 0x04 R/W Interrupt Register */
    __IO uint32_t GAHBCFG;                           /*!< Offset: 0x08 R/W AHB Configuration Register */
    __IO uint32_t GUSBCFG;                           /*!< Offset: 0x0c R/W USB Configuration Register */
    __IO uint32_t GRSTCTL;                           /*!< Offset: 0x10 R/W Reset Register */
    __IO uint32_t GINTSTS;                           /*!< Offset: 0x14 R/W Interrupt Register */
    __IO uint32_t GINTMSK;                           /*!< Offset: 0x18 R/W Interrupt Mask Register */
    __I  uint32_t GRXSTSR;                           /*!< Offset: 0x1C R Receive Status Debug Read */
    __I  uint32_t GRXSTSP;                           /*!< Offset: 0x20 R Status Read and Pop Registers */
    __IO uint32_t GRXFSIZ;                           /*!< Offset: 0x24 R/W Receive FIFO Size Register */
    __IO uint32_t GNPTXFSIZ ;                        /*!< Offset: 0x28 R/W Non-Periodic Transmit FIFO Size Register */
    __I  uint32_t GNPTXSTS;                          /*!< Offset: 0x2c R Non-Periodic Transmit FIFO/Queue Status Register */
    __I  uint32_t GI2CCTL;                           /*!< Offset: 0x30 R I2C Access Register */
    __IO uint32_t GPVNDCTL;                          /*!< Offset: 0x34 R/W PHY Vendor Control Register */
    __IO uint32_t GGPIO;                             /*!< Offset: 0x38 R/W General Purpose Input/Output Register */
    __IO uint32_t GUID;                              /*!< Offset: 0x3c R/W User ID Register */
    __I  uint32_t GSNPSID;                           /*!< Offset: 0x40 R Synopsys ID Register */
    __I  uint32_t GHWCFG1;                           /*!< Offset: 0x44 R User HW Config1 Register */
    __I  uint32_t GHWCFG2;                           /*!< Offset: 0x48 R User HW Config2 Register */
    __I  uint32_t GHWCFG3;                           /*!< Offset: 0x4c R User HW Config3 Register */
    __I  uint32_t GHWCFG4;                           /*!< Offset: 0x50 R User HW Config4 Register */
    __IO uint32_t GLPMCFG;                           /*!< Offset: 0x54 R/W Core LPM Configuration Register */
    __IO uint32_t GPWRDN ;                           /*!< Offset: 0x58 R/W Power Down Register */
    __IO uint32_t GDFIFOCFG;                         /*!< Offset: 0x5c R/W DFIFO Software Config Register */
    __IO uint32_t GADPCTL;                           /*!< Offset: 0x60 R/W ADP Timer, Control and Status Register */
    __IO uint32_t resv1[40];
    __IO uint32_t HPTXFSIZ;                          /*!< Offset: 0x100 R/W Host Periodic Transmit FIFO Size Register */

    union {

    __IO uint32_t DPTXFSIZn[15];                         /*!< Offset: 104h + (FIFO_number ¨C 1) * 04h R/W Device Periodic Transmit FIFO-n Size Register */
    __IO uint32_t DIEPTXFn[15];                          /*!< Offset: 104h + (FIFO_number ¨C 1) * 04h R/W Device IN Endpoint Transmit FIFO Size Register: */
    
    };
    //Host Mode Registers 
    __IO uint32_t HCFG;                              /*!< Offset: 0x400 R/W Host Configuration Register */
    __IO uint32_t HFIR;                              /*!< Offset: 0x404 R/W Host Frame Interval Register */
    __I  uint32_t HFNUM;                             /*!< Offset: 0x408 R Host Frame Number/Frame Time Remaining Register */
    __I  uint32_t HPTXSTS;                           /*!< Offset: 0x410 R Host Periodic Transmit FIFO/Queue Status Register */
    __I  uint32_t HAINT;                             /*!< Offset: 0x414 R Host All Channels Interrupt Register */
    __IO uint32_t HAINTMSK;                          /*!< Offset: 0x418 R/W Host All Channels Interrupt Mask Register */
    __IO uint32_t HFLBAddr;                          /*!< Offset: 0x41C R/W  Host Frame List Base Address Register */
    __IO uint32_t HPRT;                              /*!< Offset: 0x440 R/W Host Port Control and Status Register */
    __IO uint32_t HCCHARn;                           /*!< Offset: Channel_number: 0 ¡Ü n ¡Ü 15 Offset: 500h + (Channel_number * 20h) R/W Host Channel-n Characteristics Register */
    __IO uint32_t HCSPLTn;                           /*!< Offset: Channel_number: 0 ¡Ü n ¡Ü 15 Offset: 504h + (Channel_number * 20h) R/W Host Channel-n Split Control Register */
    __IO uint32_t HCINTn;                            /*!< Offset: Channel_number: 0 ¡Ü n ¡Ü 15 Offset: 508h + (Channel_number * 20h) R/W Host Channel-n Interrupt Register */
    __IO uint32_t HCINTMSKn;                         /*!< Offset: Channel_number: 0 ¡Ü n ¡Ü 15 Offset: 50Ch + (Channel_number * 20h) R/W */
    __IO uint32_t HCTSIZn;                           /*!< Offset: 0x510 R/W Host Channel-n Transfer Size Register */
    __IO uint32_t HCDMAn;                            /*!< Offset: 0x514 R/W Host Channel-n DMA Address Register */
    __I  uint32_t HCDMABn;                           /*!< Offset: Channel_number: 0 n 15 ffset: 51Ch + (Channel_number * 20h)  RO  Host Channel-n DMA Buffer Address Register */
    // Device Mode Registers
    __IO uint32_t DCFG;                              /*!< Offset: 0x800 R/W Device Configuration Register */
    __IO uint32_t DCTL;                              /*!< Offset: 0x804 R/W Device Control Register */
    __IO uint32_t DSTS;                              /*!< Offset: 0x808 R Device Status Register */
    __IO uint32_t DIEPMSK;                           /*!< Offset: 0x810 R/W Device IN Endpoint Common Interrupt Mask Register */
    __IO uint32_t DOEPMSK;                           /*!< Offset: 0x814 R/W Device OUT Endpoint Common Interrupt Mask Register */
    __I  uint32_t DAINT;                             /*!< Offset: 0x818 R Device All Endpoints Interrupt Register */
    __IO uint32_t DAINTMSK;                          /*!< Offset: 0x81c R/W Device All Endpoints Interrupt Mask Register */
    __I  uint32_t DTKNQR1;                           /*!< Offset: 0x820 R Device IN Token Sequence Learning Queue Read Register 1 */
    __I  uint32_t DTKNQR2;                           /*!< Offset: 0824h R Device IN Token Sequence Learning Queue Read Register 2 */
    __IO uint32_t DTKNQR3;                           /*!< Offset: 0830h R Device IN Token Sequence Learning Queue Read Register 3 */
    __IO uint32_t DTKNQR4;                           /*!< Offset: 0834h R Device IN Token Sequence Learning Queue Read Register 4 */
    __IO uint32_t DVBUSDIS;                          /*!< Offset: 0x828 R/W Device VBUS Discharge Time Register */
    __IO uint32_t DVBUSPULSE;                        /*!< Offset: 0x82c R/W Device VBUS Pulsing Time Register */
    __IO uint32_t DTHRCTL;                           /*!< Offset: 0x830 R/W Device Threshold Control Register */
    __IO uint32_t DIEPEMPMSK;                        /*!< Offset: 0x834 R/W Device IN Endpoint FIFO Empty Interrupt Mask Register:  */
    __IO uint32_t DEACHINT;                          /*!< Offset: 0x838 R Device Each Endpoint Interrupt Register */
    __IO uint32_t DEACHINTMSK;                       /*!< Offset: 0x83c R/W Device Each Endpoint Interrupt Register Mask */
    __IO uint32_t DIEPEACHMSKn;                      /*!< Offset: 0x840 R/W Device Each In Endpoint-n Interrupt Register */
    __IO uint32_t DOEPEACHMSKn;                      /*!< Offset: 0x880 R/W Device Each Out Endpoint-n Interrupt Register */
    __IO uint32_t DIEPCTL0;                          /*!< Offset: 0x900 R/W Device Control IN Endpoint 0 Control Register */
    __IO uint32_t DOEPCTL0;                          /*!< Offset: 0xb00 R/W Device Control OUT Endpoint 0 Control Register */
    __IO uint32_t DIEPCTLn_DOEPCTLn;                 /*!< Offset: Endpoint_number: 1 ¡Ü n ¡Ü 15 Offset for IN endpoints: 900h + (Endpoint_number * 20h) Offset for OUT endpoints: B00h + (Endpoint_number * 20h) R/W Device Endpoint-n Control Register */
    __IO uint32_t DIEPINTn_DOEPINTn;                 /*!< Offset: Endpoint_number: 0 ¡Ü n ¡Ü 15 Offset for IN endpoints: 908h + (Endpoint_number * 20h) Offset for OUT endpoints: B08h + (Endpoint_number * 20h) R/W Device Endpoint-n Interrupt Register */
    __IO uint32_t DIEPTSIZ0_DOEPTSIZ0;               /*!< Offset: 0x910 R/W Device Endpoint 0 Transfer Size Register */
    __IO uint32_t DIEPTSIZn_DOEPTSIZn;               /*!< Offset: 0x930 R/W Device Endpoint-n Transfer Size Register */
    __IO uint32_t DIEPDMAn_DOEPDMAn;                 /*!< Offset: 0x934 R/W Device Endpoint-n DMA Address Register */
    __I  uint32_t DIEPDMABn_DOEPDMABn;               /*!< Offset: 0x93c R Device Endpoint-n DMA Buffer Address Register */
    __I  uint32_t DTXFSTSn;                          /*!< Offset: 0x938 R Device IN Endpoint Transmit FIFO Status Register */
    //Power and Clock Gating Registers
    __IO uint32_t PCGCCTL;                           /*!< Offset: 0xe00 R/W Power and Clock Gating Control Register */
        
}USB_TypeDef;



/*--------------------------------SCHE ---------------------------------------------*/
typedef struct
{
    __IO uint32_t CCR;                          /*!< Offset: 0x00 SPIM0 Xip Cache (R/W) */
    __IO uint32_t SR;                           /*!< Offset: 0x04 SPIM0 Xip Cache (R/W) */
}FC_TypeDef;


typedef struct {
    // BB Control 1
    __IO uint32_t BB_CTL[10];
    // BB Status 1
    __I  uint32_t BB_RXCAPFULL : 1;
    __I  uint32_t BB_RSV1 : 7;
    __I  uint32_t BB_RXAGC : 8;
    __I  uint32_t BB_TXRAMPSTS : 7;
    __I  uint32_t BB_RSV2 : 9;
    // BB Status 2
    __I  uint32_t BB_STATUS2;
} BB_TypeDef;

/* --------------------  End of section using anonymous unions  ------------------- */
#define CODE_ROM_BASE          (0x00000000UL)/*!< ROM */
#define CODE_SRAM_BASE         (0x08000000UL)
#define CODE_SRAM_BASE1        (0x20000000UL)
#define DATA_SRAM_BASE         (0x09000000UL)
#define SPI_FLASH_BASE         (0x10000000UL)

#define ROM_0_BASE             (CODE_ROM_BASE)
#define ROM_1_BASE             (ROM_0_BASE+128*1024)
#define ROM_2_BASE             (ROM_1_BASE+128*1024) 

#define APB_BASE               (0x90000000UL)
#define SCU_BASE               (APB_BASE + 0x0000UL)
#define RF_BASE                (APB_BASE + 0x10010000UL)
#define UART0_BASE             (APB_BASE + 0x2000UL)
#define UART1_BASE             (APB_BASE + 0x2800UL)
#define SPIM0_BASE             (APB_BASE + 0x3000UL)
#define SPIM1_BASE             (APB_BASE + 0x3800UL)
#define SPIS1_BASE             (APB_BASE + 0x4000UL)
#define I2C0_BASE              (APB_BASE + 0x5000UL)
#define GPIO_BASE              (APB_BASE + 0x6000UL)
#define I2SM_BASE              (APB_BASE + 0x7000UL)
#define I2SS_BASE              (APB_BASE + 0x7800UL)
#define TIMERS_BASE            (APB_BASE + 0x8000UL)
#define RTC_BASE               (APB_BASE + 0x9000UL)
#define WDT_BASE               (APB_BASE + 0xA000UL)
#define QUAD_BASE              (APB_BASE + 0xC800UL)
#define FC_BASE                (APB_BASE + 0xD000UL)
#define MDM_BASE               (APB_BASE + 0xE000UL)
#define BB_BASE                (APB_BASE + 0xE400UL)

#define FLASH_BASE             (0x10000000UL)
#define USB_BASE               (0x80000000UL)
#define DMA_BASE               (0x80040000UL)



/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/


#define SCU                    ((SCU_TypeDef    *) SCU_BASE     )
#define RF                     ((RF_TypeDef     *) RF_BASE      )
#define UART0                  ((UART_TypeDef   *) UART0_BASE   )
#define UART1                  ((UART_TypeDef   *) UART1_BASE   )
#define QUAD                   ((QUAD_TypeDef   *) QUAD_BASE    )
#define SPIM1                  ((SSI_TypeDef    *) SPIM1_BASE   )
#define SPIS1                  ((SSI_TypeDef    *) SPIS1_BASE   )
#define I2C0                   ((I2C_TypeDef    *) I2C0_BASE    )
#define GPIO                   ((GPIO_TypeDef   *) GPIO_BASE    )
#define I2SM                   ((I2S_TypeDef    *) I2SM_BASE    )
#define I2SS                   ((I2S_TypeDef    *) I2SS_BASE    )
#define TIMERS                 ((TIMERS_TypeDef *) TIMERS_BASE  )

#define RTC                    ((RTC_TypeDef    *) RTC_BASE     )
#define WDT                    ((WDT_TypeDef    *) WDT_BASE     )



#define SPIM0                  ((SSI_TypeDef    *) FLASH_BASE   )
#define FC                     ((FC_TypeDef     *) FC_BASE      ) //SPIM0_Cache
#define BB                     ((BB_TypeDef     *) BB_BASE      )

#define DMA                    ((DMA_TypeDef    *) DMA_BASE     )
#define USB                    ((USB_TypeDef    *) USB_BASE     )


#define USB_REG_BASE_ADDR           (USB_BASE)

/* CSRs Memory Map (Device Mode) */
#define USB_COREGLOBAL_CSRs         (USB_REG_BASE_ADDR + 0x0000)                /* Core Global CSRs */
#define USB_DEVICEMODE_CSRs         (USB_REG_BASE_ADDR + 0x0800)                /* Device Mode CSRs */
#define USB_POWERCLOCK_CSRs         (USB_REG_BASE_ADDR + 0x0E00)                /* Power and Clock Gating CSRs */
#define USB_DEVICEEPn_CSRs(_n)      (USB_REG_BASE_ADDR + 0x1000 * ((_n) + 1))  /* Data FIFO (DFIFO) Access Register, n Range: 0 ~ 15 */
#define USB_DFIFODEBUG              (USB_REG_BASE_ADDR + 0x20000)               /* Direct Access to Data FIFO RAM for Debugging */

/* Core Global CSR Map */
#define USB_CG_OTGCTL               (USB_COREGLOBAL_CSRs + 0x000)               /* Control and Status Register */
#define USB_CG_OTGINT               (USB_COREGLOBAL_CSRs + 0x004)               /* Interrupt Register */
#define USB_CG_AHBCFG               (USB_COREGLOBAL_CSRs + 0x008)               /* AHB Configuration Register */
#define USB_CG_USBCFG               (USB_COREGLOBAL_CSRs + 0x00C)               /* USB Configuration Register */
#define USB_CG_RSTCTL               (USB_COREGLOBAL_CSRs + 0x010)               /* Reset Register */
#define USB_CG_INTSTS               (USB_COREGLOBAL_CSRs + 0x014)               /* Interrupt Register */
#define USB_CG_INTMSK               (USB_COREGLOBAL_CSRs + 0x018)               /* Interrupt Mask Register */
#define USB_CG_RXSTSR               (USB_COREGLOBAL_CSRs + 0x01C)               /* Receive Status Debug Read/Status Read Registers */
#define USB_CG_RXSTSP               (USB_COREGLOBAL_CSRs + 0x020)               /* Receive Status Debug Read/Status Pop Registers */
#define USB_CG_RXFSIZ               (USB_COREGLOBAL_CSRs + 0x024)               /* Receive FIFO Size Register */
#define USB_CG_NPTXFSIZ             (USB_COREGLOBAL_CSRs + 0x028)               /* Non-Periodic Transmit FIFO Size Register */
#define USB_CG_NPTXSTS              (USB_COREGLOBAL_CSRs + 0x02C)               /* Non-Periodic Transmit FIFO/Queue Status Register */
#define USB_CG_I2CCTL               (USB_COREGLOBAL_CSRs + 0x030)               /* I2C Access Register */
#define USB_CG_PVNDCTL              (USB_COREGLOBAL_CSRs + 0x034)               /* PHY Vendor Control Register */
#define USB_CG_GPIO                 (USB_COREGLOBAL_CSRs + 0x038)               /* General Purpose Input/Output Register */
#define USB_CG_UID                  (USB_COREGLOBAL_CSRs + 0x03C)               /* User ID Register */
#define USB_CG_ID                   (USB_COREGLOBAL_CSRs + 0x040)               /* ID Register */
#define USB_CG_HWCFG1               (USB_COREGLOBAL_CSRs + 0x044)               /* User HW Config1 Register */
#define USB_CG_HWCFG2               (USB_COREGLOBAL_CSRs + 0x048)               /* User HW Config2 Register */
#define USB_CG_HWCFG3               (USB_COREGLOBAL_CSRs + 0x04C)               /* User HW Config3 Register */
#define USB_CG_HWCFG4               (USB_COREGLOBAL_CSRs + 0x050)               /* User HW Config4 Register */
#define USB_CG_LPMCFG               (USB_COREGLOBAL_CSRs + 0x054)               /* Core LPM Configuration Register */
#define USB_CG_PWRDN                (USB_COREGLOBAL_CSRs + 0x058)               /* Power Down Register  */
#define USB_CG_DFIFOCFG             (USB_COREGLOBAL_CSRs + 0x05C)               /* DFIFO Software Config Register */
#define USB_CG_ADPCTL               (USB_COREGLOBAL_CSRs + 0x060)               /* ADP Timer, Control and Status Register */
#define USB_CG_HPTXFSIZ             (USB_COREGLOBAL_CSRs + 0x100)               /* Host Periodic Transmit FIFO Size Register  */
#define USB_CG_DPTXFSIZn(_n)        (USB_COREGLOBAL_CSRs + 0x104 + (_n) * 0x04) /* Device Periodic Transmit FIFO-n Size Register, n Range: 0 ~ 15 */
#define USB_CG_DIEPTXFn(_n)         (USB_COREGLOBAL_CSRs + 0x104 + (_n) * 0x04) /* Device IN Endpoint Transmit FIFO Size Register, n Range: 0 ~ 15 */

/* Device Mode CSR Map */
#define USB_DM_CFG                  (USB_DEVICEMODE_CSRs + 0x000)               /* Device Configuration Register */
#define USB_DM_CTL                  (USB_DEVICEMODE_CSRs + 0x004)               /* Device Control Register */
#define USB_DM_STS                  (USB_DEVICEMODE_CSRs + 0x008)               /* Device Status Register */
#define USB_DM_IEPMSK               (USB_DEVICEMODE_CSRs + 0x010)               /* Device IN Endpoint Common Interrupt Mask Register  */
#define USB_DM_OEPMSK               (USB_DEVICEMODE_CSRs + 0x014)               /* Device OUT Endpoint Common Interrupt Mask Register  */
#define USB_DM_AINT                 (USB_DEVICEMODE_CSRs + 0x018)               /* Device All Endpoints Interrupt Register */
#define USB_DM_AINTMSK              (USB_DEVICEMODE_CSRs + 0x01C)               /* Device All Endpoints Interrupt Mask Register  */
#define USB_DM_TKNQR1               (USB_DEVICEMODE_CSRs + 0x020)               /* Device IN Token Sequence Learning Queue Read Register 1 */
#define USB_DM_TKNQR2               (USB_DEVICEMODE_CSRs + 0x024)               /* Device IN Token Sequence Learning Queue Read Register 2 */
#define USB_DM_TKNQR3               (USB_DEVICEMODE_CSRs + 0x030)               /* Device IN Token Sequence Learning Queue Read Register 3 */
#define USB_DM_TKNQR4               (USB_DEVICEMODE_CSRs + 0x034)               /* Device IN Token Sequence Learning Queue Read Register 4 */
#define USB_DM_VBUSDIS              (USB_DEVICEMODE_CSRs + 0x028)               /* Device VBUS Discharge Time Register  */
#define USB_DM_VBUSPULSE            (USB_DEVICEMODE_CSRs + 0x02C)               /* Device VBUS Pulsing Time Register */
#define USB_DM_THRCTL               (USB_DEVICEMODE_CSRs + 0x030)               /* Device Threshold Control Register */
#define USB_DM_IEPEMPMSK            (USB_DEVICEMODE_CSRs + 0x034)               /* Device IN Endpoint FIFO Empty Interrupt Mask Register */
#define USB_DM_EACHINT              (USB_DEVICEMODE_CSRs + 0x038)               /* Device Each Endpoint Interrupt Register  */
#define USB_DM_EACHINTMSK           (USB_DEVICEMODE_CSRs + 0x03C)               /* Device Each Endpoint Interrupt Register Mask */
#define USB_DM_IEPEACHMSKn(_n)      (USB_DEVICEMODE_CSRs + 0x040 + (_n) * 0x04) /* Device Each In Endpoint-n Interrupt Register, n Range: 0 ~ 15 */
#define USB_DM_OEPEACHMSKn(_n)      (USB_DEVICEMODE_CSRs + 0x080 + (_n) * 0x04) /* Device Each Out Endpoint-n Interrupt Register, n Range: 0 ~ 15 */
#define USB_DM_IEPCTLn(_n)          (USB_DEVICEMODE_CSRs + 0x100 + (_n) * 0x20) /* Device Control IN Endpoint-n Control Register, n Range: 0 ~ 15 */
#define USB_DM_IEPINTn(_n)          (USB_DEVICEMODE_CSRs + 0x108 + (_n) * 0x20) /* Device IN Endpoint-n Interrupt Register, n Range: 0 ~ 15 */
#define USB_DM_IEPTSIZn(_n)         (USB_DEVICEMODE_CSRs + 0x110 + (_n) * 0x20) /* Device IN Endpoint-n Transfer Size Register, n Range: 0 ~ 15 */
#define USB_DM_IEPDMAn(_n)          (USB_DEVICEMODE_CSRs + 0x114 + (_n) * 0x20) /* Device IN Endpoint-n DMA Address Register, n Range: 0 ~ 15 */
#define USB_DM_TXFSTSn(_n)          (USB_DEVICEMODE_CSRs + 0x118 + (_n) * 0x20) /* Device IN Endpoint Transmit FIFO Status Register, n Range: 0 ~ 15 */
#define USB_DM_IEPDMABn(_n)         (USB_DEVICEMODE_CSRs + 0x11C + (_n) * 0x20) /* Device IN Endpoint-n DMA Buffer Address Register, n Range: 0 ~ 15 */
#define USB_DM_OEPCTLn(_n)          (USB_DEVICEMODE_CSRs + 0x300 + (_n) * 0x20) /* Device Control OUT Endpoint-n Control Register, n Range: 0 ~ 15 */
#define USB_DM_OEPINTn(_n)          (USB_DEVICEMODE_CSRs + 0x308 + (_n) * 0x20) /* Device OUT Endpoint-n Interrupt Register, n Range: 0 ~ 15 */
#define USB_DM_OEPTSIZn(_n)         (USB_DEVICEMODE_CSRs + 0x310 + (_n) * 0x20) /* Device OUT Endpoint-n Transfer Size Register , n Range: 0 ~ 15 */
#define USB_DM_OEPDMAn(_n)          (USB_DEVICEMODE_CSRs + 0x314 + (_n) * 0x20) /* Device OUT Endpoint-n DMA Address Register, n Range: 0 ~ 15 */
#define USB_DM_OEPDMABn(_n)         (USB_DEVICEMODE_CSRs + 0x31C + (_n) * 0x20) /* Device OUT Endpoint-n DMA Buffer Address Register, n Range: 0 ~ 15 */

/* Power and Clock Gating CSR Map */
#define USB_PC_GCCTL                (USB_POWERCLOCK_CSRs + 0x00)                /* Power and Clock Gating Control Register */

/* Data FIFO (DFIFO) Access Register Map */
#define USB_DA_INOUTWRn(_n)         (USB_DEVICEEPn_CSRs(_n))                    /* Device IN(WO)/OUT(RO) Endpoint n, n Range: 0 ~ 15 */



#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  /* __BR003_H__ */


