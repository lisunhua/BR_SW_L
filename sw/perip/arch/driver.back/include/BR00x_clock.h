/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_clock.h
 * @brief     This file provides the clock firmware functions.
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

#ifndef __BR00x_CLOCK_H___
#define __BR00x_CLOCK_H___

#ifdef __cplusplus
 extern "C" {
#endif

#include "BR00x_config.h"
#include "BR00x_clock.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef BR1051Axx
typedef enum
{
    reset_mcu_none,
    reset_mcu_sw,
    reset_mcu_wdt,
    reset_mcu_brown_out,
    reset_mcu_pin
}CLK_LastReset_Type;


typedef enum
{
    SYS_LFCLK_TO_HFCLK,
    SYS_LFCLK_TO_OSC32K,
}CLK_SysClkLfclk_Type;

typedef enum
{
    PLL_OSC_16M  = 0,
    PLL_PLL_32M  = 1,
    PLL_PLL_64M  = 3,
    PLL_PLL_128M = 5,
    PLL_OSC_16M1 = 7,
}CLK_SysClkHfclk_Type;


typedef enum
{
    CLK_SPIMS1_TO_LFCLK,
    CLK_SPIMS1_TO_HFCLK
}CLK_SysClkSpims1_Tpye;

typedef enum
{
    CLK_I2S_TO_LFCLK,
    CLK_I2S_TO_HFCLK
    
}CLK_SysClkI2S_Tpye;

typedef enum
{
    CLK_WDT_TO_LFCLK,
    CLK_WDT_TO_HFCLK
    
}CLK_SysClkWDT_Tpye;

typedef enum
{
    CLK_TIMER_TO_LFCLK,
    CLK_TIMER_TO_HFCLK
    
}CLK_SysClkTIMER_Tpye;


typedef enum
{
    CLK_SPIM0_TO_SYS     = 1,
    CLK_SPIM0_TO_PLL_32M = 2,
    CLK_SPIM0_TO_PLL_64M = 3,
    
}CLK_SysClkSPIM0_Tpye;


typedef struct
{
    uint32_t Sys_Sel    :1;
    uint32_t sys_hclk   :3;
    uint32_t sys_spi1ms :1;
    uint32_t Sys_i2s    :1;
    uint32_t Sys_wdt    :1;
    uint32_t sys_unused :1;
    
    uint32_t Sys_timer0 :1;
    uint32_t Sys_timer1 :1;
    uint32_t Sys_timer2 :1;
    uint32_t Sys_timer3 :1;
    uint32_t Sys_timer4 :1;
    uint32_t Sys_timer5 :1;
    uint32_t Sys_timer6 :1;
    uint32_t Sys_timer7 :1;
    uint32_t Sys_spim0  :2;
    uint32_t unuserd    :15;


}SYS_CLK_Sel_Info;


typedef struct
{
    uint32_t Dev_hclk_bb  :3;//[0-2]
    uint32_t Dev_hclk_dma :3;//[3-5]
    uint32_t Dev_pclk_sclk:4;//[6-9]    //Pclk -> AHB CLK
    uint32_t Dev_spims1   :3;//[10-12]
    uint32_t Dev_Sys_i2s  :8;//[13-20]
    uint32_t Dev_Sys_wdt  :2;//[21-22]
    uint32_t unuserd      :9;//[23-31]
}SYS_CLK_Dev_Info;


typedef enum
{
    CLT_CLK_TIMER0,
    CLT_CLK_TIMER1,
    CLT_CLK_TIMER2,
    CLT_CLK_TIMER3,
    CLT_CLK_TIMER4,
    CLT_CLK_TIMER5,
    CLT_CLK_TIMER6,
    CLT_CLK_TIMER7,
    CLT_CLK_SPIM0_XIP,
    CLT_CLK_RF_MODEM_SPI_SLAVE,
    
    CLT_CLK_WTD    = 31,
    
}CLK_ModuleClt_Type;

typedef enum
{
    CLK_TIMER0,
    CLK_TIMER1,
    CLK_TIMER2,
    CLK_TIMER3,
    CLK_TIMER4,
    CLK_TIMER5,
    CLK_TIMER6,
    CLK_TIMER7,
}CLK_Timers_Type;

typedef enum
{
    TIMERN_DIV_F_APBCLK_1,      /*F_apbclk/1*/
    TIMERN_DIV_F_APBCLK_4,      /*F_apbclk/4*/
    TIMERN_DIV_F_APBCLK_16,     /*F_apbclk/16*/
    TIMERN_DIV_F_APBCLK_256,    /*F_apbclk/256*/
    TIMERN_DIV_F_APBCLK_1024,   /*F_apbclk/1024*/
}CLK_TimerDiv_Type;

typedef struct
{
    CLK_Timers_Type    timer_type;
    CLK_TimerDiv_Type  timer_div;

}CLK_TimerInfo_Type;


typedef struct
{
    SYS_CLK_Sel_Info clk_sel;
    SYS_CLK_Dev_Info slc_dev;

}SYS_CLK_InitInfo_Type;

typedef enum
{
    SYS_DOMIAN,
    PERI_DOMAIN,
    BB_DOMAIN,
    RF_DOMAIN,
    ROM_0_DOMAIN,
    ROM_1_DOMAIN,
    RAM_0_0_DAMAIN,
    RAM_0_1_DOMAIN,
    RAM_1_8K_DOAMIN,
    RAM_1_4K_DOMAIN,
    RAM_1_2K_DOAMIN,

    BB_WAKEUP = 30,
    CPU_SLEEP = 31,
    
}SYS_CLT_PWRConfig_type;




/**
  * @brief  Initializes the SYS_CLK  according to the specified
  *         parameters in the SYS_CLK_InitInfo_Type.
  * @param  SYS_CLK_InitInfo_Type: pointer to a SYS_CLK_InitInfo_Type structure that
  *         contains the configuration information for the specified SYS_CLK .
  * @retval None
  */
void CLK_SYS_Init(SYS_CLK_InitInfo_Type *CLK_InitStru);


/**
  * @brief  Initializes the timers_CLK  according to the specified
  *         parameters in the SYS_CLK_InitInfo_Type.
  * @param  CLK_TimerInfo_Type: pointer to a CLK_TimerInfo_Type structure that
  *         contains the configuration information for the specified timers_CLK .
  * @retval None
  */
void CLK_SYS_Timer_Init(CLK_TimerInfo_Type *CLK_InitStru);


/**
  * @brief  Initializes the SCU  according to the specified
  *         parameters in the SCU_InitInfo_Type.
  * @param  CLK_TimerStru: pointer to a CLK_TimersInfo_Type structure that
  *         contains the configuration information for the specified SCU Timer .
  * @retval None
  */
void SCU_ClkTimesDiv(CLK_TimerInfo_Type *CLK_TimerStru);


/**
  * @brief  Used to request a PWR type to Sleep.
  * @param SYS_CLT_PWRConfig_type Required type
  * @param status  Write 1 for sleep request
  * @retval None
  */
void SCU_ClkSetPwrConfig(SYS_CLT_PWRConfig_type  type ,bool status);

/**
  * @brief  Used to get a PWR register Status.
  * @param SYS_CLT_PWRConfig_type Required type
  * @retval 1 NORMAL /0 sleep
  */
bool SCU_ClkGetPwrStatus(SYS_CLT_PWRConfig_type  type);


/**
  * @brief  This function sets the clock enable state of each module.
  * 
  * @param clk_type
  * @param status : true (enable)/false (disable)
  * @retval None.
  */
void SCU_SetModuleEnable(CLK_ModuleClt_Type clk_type ,bool status);


/**
  * @brief  This function gets  current reset count.
  * 
  * @param None
  * @retval The soc reset count.
  */
uint32_t SCU_GetCurrentResetNum(void);


/**
  * @brief  This function gets the current latest reset type.
  * 
  * @param None
  * @retval The soc latest reset type.
  */
CLK_LastReset_Type SCU_GetLastReset(void);


#endif




#if  defined(BR002)||defined(BR003)||defined(BR005)
/**********************************/
typedef enum
{
	CLK_12M,
	CLK_24M,
	CLK_48M,
	CLK_96M,
}SCU_96MDIVCtl_Type;

typedef enum
{
  CLK_OSC26m,         //26M mux
  CLK_HCLK_MUX,       //BR002:208M BR003:96M (DIV OUT)
  CLK_32K_MUX_HCLK    //32.768k mux
}SCU_HclkSelect_Type;


typedef enum
{
  HCLK_2_PLCK,           //HCLK clock
  HCLK_DIV_2_PCLK,       //HCLK div to pclk clock
}SCU_PclkSelect_Type;



typedef enum
{
  HCLK_2_PLCK_PRE,       //HCLK clock
  HCLK_DIV02,            //HCLK DIV 02 clock
  HCLK_DIV03,            //HCLK DIV 03 clock
  HCLK_DIV04,            //HCLK DIV 04 clock
  HCLK_DIV05,            //HCLK DIV 05 clock  
  HCLK_DIV06,            //HCLK DIV 06 clock  
  HCLK_DIV07,            //HCLK DIV 07 clock  
  HCLK_DIV08,            //HCLK DIV 08 clock  
  HCLK_DIV09,            //HCLK DIV 09 clock  
  HCLK_DIV10,            //HCLK DIV 10 clock  
  HCLK_DIV11,            //HCLK DIV 11 clock  
  HCLK_DIV12,            //HCLK DIV 12 clock  
  HCLK_DIV13,            //HCLK DIV 13 clock  
  HCLK_DIV14,            //HCLK DIV 14 clock  
  HCLK_DIV15,            //HCLK DIV 15 clock  
  HCLK_DIV16,            //HCLK DIV 16 clock  
    
}SCU_Pclk_Pre_Select_Type;


typedef enum
{
	CLK_HCLK_MAIN,
	CLK_SPIM0_104M,
}SCU_SPIM0Select_Type;

typedef enum
{
	CLK_RCO_32K,
	CLK_OSC_32K,
	clk_DIV_32K,
}SCU_32KSelect_Type;

typedef enum
{
	CLK_RCO_48M,
	CLK_DIV_48M,
}SCU_USBSelect_Type;


typedef enum
{
	CLK_PCLK,
	CLK_OSC_26M,
}SCU_UART0Select_Type;


/************************************/

typedef enum
{
	CLK_TM0,
	CLK_TM1,
	CLK_TM2,
	CLK_TM3,
	CLK_TM4,
	CLK_TM5,
	CLK_TM6,
	CLK_TM7,
}SCU_Timers_Type;



void SCU_ClockSelectDivControl(SCU_96MDIVCtl_Type st);
void SCU_PClkSelect(SCU_PclkSelect_Type st);
void SCU_PClkPreSelect(SCU_Pclk_Pre_Select_Type st);
void SCU_HClkSelect(SCU_HclkSelect_Type st);
void SCU_SPIM0ClkSelect(SCU_SPIM0Select_Type st);
void SCU_32KClkSelect(SCU_32KSelect_Type st);
void SCU_USBClkSelect(SCU_USBSelect_Type st);
void SCU_UART0ClkSelect(SCU_UART0Select_Type st);
void SCU_BB_MEM_ADC_ClkSelect(bool st);
void SCU_BB_MEM_DAC_ClkSelect(bool st);
void SCU_RF_ADC_ClkSelect(uint32_t st);


void SCU_SPI1Div(uint32_t div);
void SCU_32KDiv(uint32_t div);
void SCU_WdtDiv(uint32_t div);
void SCU_I2SDiv(uint32_t div);
void SCU_RTCDiv(uint32_t div);
void SCU_TimersDiv(SCU_Timers_Type tm,uint16_t div);

#endif







#ifdef __cplusplus
}
#endif

#endif /* __BR00x_CLOCK_H___ */

