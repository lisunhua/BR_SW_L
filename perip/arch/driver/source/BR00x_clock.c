/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file    BR00x_clock.c
 * @brief    This file provides the clock firmware functions.
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


#ifdef BR1051Axx

#define SYS_STATUS_SW_POS (8ul) 
#define SYS_STATUS_WDT_POS (9ul) 
#define SYS_STATUS_BROWN_OUT_POS (10ul) 
#define SYS_STATUS_PIN_POS (11ul) 

#define BB_DIV_POS          0
#define DMA_DIV_POS         4
#define APB_DIV_POS         12

#define PWR_TBD_POS         0
#define PWR_SLEEP_HOLD_POS  8
#define PWR_ISO_POS         9
#define PWR_RETAIN_POS      10

#define TIME1_DIV  0   /*width 4*/
#define TIME2_DIV  8
#define TIME3_DIV  16
#define TIME4_DIV  24


/**
  * @brief  Initializes the SCU  according to the specified
  *         parameters in the SCU_InitInfo_Type.
  * @param  SUC_InitStru: pointer to a SCU_InitInfo_Type structure that
  *         contains the configuration information for the specified SCU .
  * @retval None
  */
void CLK_SYS_Init(SYS_CLK_InitInfo_Type *CLK_InitStru)
{        
    SCU->CLK_SEL    =  *((uint32_t *)CLK_InitStru);
    SCU->CLK_CONFIG =  *((uint32_t *)CLK_InitStru+1);
}

void CLK_SYS_Timer_Init(CLK_TimerInfo_Type *CLK_InitStru)
{
//    SCU->TIMERS_DIV &= ~(0xFul<<CLK_InitStru->timer_type);
//    SCU->TIMERS_DIV |=  (CLK_InitStru->timer_div <<CLK_InitStru->timer_type);
}

void SCU_ClkSetPwrConfig(SYS_CLT_PWRConfig_type  type ,bool status)
{
    if(status)
        SCU->PWR_CONFIG |= (0x01ul<<type);
    else
        SCU->PWR_CONFIG &= ~(0x01ul<<type);
}   


bool SCU_ClkGetPwrStatus(SYS_CLT_PWRConfig_type  type)
{
    return  ((SCU->PWR_CONFIG>>type)&0x01);
}

/**
  * @brief  This function sets the clock enable state of each module.
  * 
  * @param clk_type:The module type that needs to be set
  * @param status : true (enable)/false (disable)
  * @retval None.
  */
void SCU_SetModuleEnable(CLK_ModuleClt_Type clk_type ,bool status)
{
    if(!status)
        SCU->DEV_CONFIG  |= (0x01ul<<clk_type);
    else
        SCU->DEV_CONFIG  &=  ~(0x01ul<<clk_type);
}

/**
  * @brief  This function gets  current reset count.
  * 
  * @param None
  * @retval The soc reset count.
  */
uint32_t SCU_GetCurrentResetNum(void)
{
    return (SCU->SYS_STATUS & 0xff);
}


/**
  * @brief  This function gets the current latest reset type.
  * 
  * @param None
  * @retval The soc latest reset type.
  */
CLK_LastReset_Type SCU_GetLastReset(void)
{
    if ((SCU->SYS_STATUS >> SYS_STATUS_SW_POS) & (0x01ul))
        return reset_mcu_sw;
    if ((SCU->SYS_STATUS >> SYS_STATUS_WDT_POS) & (0x01ul))
        return reset_mcu_wdt;
    if ((SCU->SYS_STATUS >> SYS_STATUS_BROWN_OUT_POS) & (0x01ul))
        return reset_mcu_brown_out;
    if ((SCU->SYS_STATUS >> SYS_STATUS_PIN_POS) & (0x01ul))
        return reset_mcu_pin;
    
    return reset_mcu_none;    
}


#endif


#if  defined(BR002)||defined(BR003)||defined(BR005)

//96M DIV Select
void SCU_ClockSelectDivControl(SCU_96MDIVCtl_Type st)
{   
    uint32_t clk = SCU->CLK_CTL;
    clk &= ~0x03;
    clk |= st&0x03;
    SCU->CLK_CTL = clk;
}

//PCLK Select
void SCU_PClkSelect(SCU_PclkSelect_Type st)
{
    uint32_t clk = SCU->CLK_CTL;
	clk &= ~(0x01<<2);
	clk |=  (st&0x01)<<2;
    SCU->CLK_CTL = clk;
}

//PCLK Pre Select
void SCU_PClkPreSelect(SCU_Pclk_Pre_Select_Type st)
{
#ifdef BR002 
    uint32_t clk = SCU->CLK_CTL;
    clk &= ~(0x07<<9);
    clk |=  (st&0x07)<<9;
    SCU->CLK_CTL = clk;

#endif
#ifdef BR003
    uint32_t clk = SCU->CLK_CTL;
    clk &= ~(0x0f<<10);
    clk |=  (st&0x0f)<<10;
    SCU->CLK_CTL = clk;
#endif

#ifdef BR005
    uint32_t clk = SCU->CLK_CTL;
    clk &= ~(0x0f<<10);
    clk |=  (st&0x0f)<<10;
    SCU->CLK_CTL = clk;
#endif
    
}


//HCLK Pre Select
void SCU_HClkSelect(SCU_HclkSelect_Type st)
{
    uint32_t clk = SCU->CLK_CTL;
    clk &= ~(0x03<<3);
    clk |=  (st&0x03)<<3;
    SCU->CLK_CTL = clk;
	
}


//SPIM0 Select
void SCU_SPIM0ClkSelect(SCU_SPIM0Select_Type st)
{
    
#ifdef BR002 
    uint32_t clk = SCU->CLK_CTL;
    clk &= ~(0x03<<5);
    clk |=  (st&0x03)<<5;
    SCU->CLK_CTL = clk;

#endif
#ifdef BR003
    uint32_t clk = SCU->CLK_CTL;
    clk &= ~(0x01<<5);
    clk |=  (st&0x01)<<5;
    SCU->CLK_CTL = clk;
#endif
#ifdef BR005
    uint32_t clk = SCU->CLK_CTL;
    clk &= ~(0x01<<5);
    clk |=  (st&0x01)<<5;
    SCU->CLK_CTL = clk;
#endif

	
}

//32K Select
void SCU_32KClkSelect(SCU_32KSelect_Type st)
{
    uint32_t clk = SCU->CLK_CTL;
    clk &=   ~(0x03<<6);
    clk |=   (st&0x03)<<6;
    SCU->CLK_CTL = clk;
	
}


void SCU_USBClkSelect(SCU_USBSelect_Type st)
{
    uint32_t clk = SCU->CLK_CTL;
    clk &=  ~(0x01<<8);
    clk |=  (st&0x01)<<8;
    SCU->CLK_CTL = clk;
	
}

void SCU_UART0ClkSelect(SCU_UART0Select_Type st)
{
#if defined(BR003)||defined(BR005)
    uint32_t clk = SCU->CLK_CTL;
    clk &=  ~(0x01<<9);
    clk |=  (st&0x01)<<9;
    SCU->CLK_CTL = clk;
#endif
}

void SCU_BB_MEM_ADC_ClkSelect(bool st)
{
#if defined(BR003)||defined(BR005)
    uint32_t clk = SCU->CLK_CTL;
    clk &=  ~(0x01<<14);
    clk |=  (st&0x01)<<14;
    SCU->CLK_CTL = clk;
#endif
}

void SCU_BB_MEM_DAC_ClkSelect(bool st)
{
#if defined(BR003)||defined(BR005)
    uint32_t clk = SCU->CLK_CTL;
    clk &=  ~(0x01<<15);
    clk |=  (st&0x01)<<15;
    SCU->CLK_CTL = clk;
#endif
}

void SCU_RF_ADC_ClkSelect(uint32_t st)
{
#if defined(BR003)||defined(BR005)
    uint32_t clk = SCU->CLK_CTL;
    clk &=  ~(0x03<<16);
    clk |=  (st&0x03)<<16;
    SCU->CLK_CTL = clk;
#endif
}



void SCU_SPI1Div(uint32_t div)
{
    uint32_t clk_div = SCU->CLK_DIV;
    clk_div &=~0xFFFF;
    clk_div |=div&0xFFFF;
    SCU->CLK_DIV = clk_div;
}

void SCU_32KDiv(uint32_t div)
{
    uint32_t clk_div = SCU->CLK_DIV;
    clk_div &=~0xFFFF0000;
    clk_div |=((div&0xFFFF)<<16);
    SCU->CLK_DIV = clk_div;
}


void SCU_WdtDiv(uint32_t div)
{
    uint32_t clk_div = SCU->CLK_DIV1;
    clk_div &=~0xFFFF;
    clk_div |=div&0xFFFF;
    SCU->CLK_DIV1 = clk_div;
}


void SCU_I2SDiv(uint32_t div)
{
    uint32_t clk_div = SCU->CLK_CTL;
    clk_div &=~0xFFFF0000;
    clk_div |=((div&0xFFFF)<<16);
    SCU->CLK_DIV1 = clk_div;
}

void SCU_RTCDiv(uint32_t div)
{
	   SCU->CLK_DIV2 = div;
}


void SCU_TimersDiv(SCU_Timers_Type tm,uint16_t div)
{
	   SCU->TIMERS_DIV[tm] = div;
}

#endif


