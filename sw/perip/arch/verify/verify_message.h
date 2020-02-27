/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_message.h
 * @brief
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * @date    14. Augest 2019
 * @version V1.0.0
 * @author  MEIGER
*/

#ifndef  __VERIFY_MESSAGE_H__
#define  __VERIFY_MESSAGE_H__

#include <stdint.h>
#include <stdbool.h>
#include "BR00x_config.h"

typedef bool (*func_handle)(void);

typedef enum{

    BRCASE_IDLE,
    BRCASE_RID,         //Run  ID
    BRCASE_CID,         //Case ID
    BRCASE_RESULT,      //Case Result
    BRCASE_RDY,         //Soc Ready
    BRCASE_ROV_STR,     //RO Register Verify start
    BRCASE_ROV_CTP,     //RO Register Verify compelet
    
    BRCASE_DUAL_MST_RDY         =0x10,  //Soc Ready
    BRCASE_DUAL_SLV_RDY         =0x11,  //Soc Ready
    BRCASE_DUAL_ROLE_REQ_RDY    =0x12,  //Soc Ready
    BRCASE_DUAL_ROLE_RLS_RDY    =0x13,  //Soc Ready release
    
    BRCASE_STOP1    =0x20,
    BRCASE_STOP2,   
    BRCASE_STOP3,
    BRCASE_STOP4,
    BRCASE_STOP5,
    BRCASE_STOP6,
    BRCASE_STOP7,
    BRCASE_STOP8,
    BRCASE_STOP9,
    BRCASE_STOP10,
    BRCASE_STOP11,
    BRCASE_STOP12,
    BRCASE_STOP13,
    BRCASE_STOP14,
    BRCASE_STOP15,
    BRCASE_STOP16,
    BRCASE_STOP17,
    BRCASE_STOP18,
    BRCASE_STOP19,
    BRCASE_STOP20,
    BRCASE_STOP21,
    BRCASE_STOP22,
    BRCASE_STOP23,
    BRCASE_STOP24,
    BRCASE_STOP25,
    BRCASE_STOP26,
}verify_caseCmd_type;


typedef enum{
    CASE_BASE         =   0X0000,
    
    CASE_SCU_REG      =   0X0100,
    CASE_SCU_SIG      =   0X0150,
//    CASE_SCU_DUL      =   0X01A0,
    
    CASE_UART0_REG    =   0X0200,
    CASE_UART0_SIG    =   0X0250,
    CASE_UART0_DUL    =   0X02A0,
    
    CASE_UART1_REG    =   0X0300,
    CASE_UART1_SIG    =   0X0350,
    CASE_UART1_DUL    =   0X03A0,
    
    CASE_GPIO_REG     =   0X0400,
    CASE_GPIO_SIG     =   0X0450,
    CASE_GPIO_DUL     =   0X04A0,
    
    CASE_I2SM_REG     =   0X0500,
    CASE_I2SM_SIG     =   0X0550,
    CASE_I2SM_DUL     =   0X05A0,
    
    CASE_I2SS_REG     =   0X0600,
    CASE_I2SS_SIG     =   0X0650,
    CASE_I2SS_DUL     =   0X06A0,
    
    CASE_I2C_REG      =   0X0700,
    CASE_I2C_SIG      =   0X0750,
    CASE_I2C_DUL      =   0X07A0,
    
    CASE_SPIM0_REG    =   0X0800,
    CASE_SPIM0_SIG    =   0X0850,
    CASE_SPIM0_DUL    =   0X08A0,
    
    CASE_SPIM1_REG    =   0x0900,
    CASE_SPIM1_SIG    =   0X0950,
    CASE_SPIM1_DUL    =   0X09A0,
    
    CASE_SPIS1_REG    =   0X0A00,
    CASE_SPIS1_SIG    =   0X0A50,
    CASE_SPIS1_DUL    =   0X0AA0,
    
    CASE_DMA_REG      =   0X0B00,
    CASE_DMA_SIG      =   0X0B50,
    CASE_DMA_DUL      =   0X0BA0,
    
    CASE_RTC_REG      =   0X0C00,
    CASE_RTC_SIG      =   0X0C50,
    CASE_RTC_DUL      =   0X0CA0,
    
    CASE_TIMER_REG    =   0X0D00,
    CASE_TIMER_SIG    =   0X0D50,
    CASE_TIMER_DUL    =   0X0DA0,
    
    CASE_WDT_REG      =   0X0E00,
    CASE_WDT_SIG      =   0X0E50, 
    CASE_WDT_DUL      =   0X0EA0,
    
    CASE_USB_REG      =   0X0F00,
    CASE_USB_SIG      =   0X0F50,
    CASE_USB_DUL      =   0X0FA0,

}verify_caseCid_type;


typedef enum
{
    UART1_OUTPUT    = 0xA001,
    UART0_OUTPUT    = 0xA002,
    
    GPIO_TEST_EN    = 0xE010,
    GPIO_TEST_DIS   = 0xE011,
    
    GPIO_UART0_EN   = 0xE012,
    GPIO_UART1_EN   = 0xE013,
    
    UART1_UART0_EN  = 0xE014,
    UART1_UART0_DIS = 0xE015,
    
    UART0_UART1_EN  = 0xE016,
    UART0_UART1_DIS = 0xE017,

    SPIM1_FL_EN     = 0xE018,
    SPIM1_FL_DIS    = 0xE019,

    SPIM1_FH_EN     = 0xE01A,
    SPIM1_FH_DIS    = 0xE01B,
    
    CLK32K_EN  	    = 0xE020,
    CLK32K_DIS 	    = 0xE021,

    SPIM1_FLASH     = 0xE031,
    
    TMODE_EN        = 0XEF01,
    TMODE_DIS       = 0XEF00,
    
    TMODE_0         = 0XEE00,
    TMODE_1         = 0XEE01,
    TMODE_2         = 0XEE02,
    TMODE_3         = 0XEE03,
    TMODE_4         = 0XEE04,
    TMODE_5         = 0XEE05,

}MessagaConnectEn_Type;


typedef enum
{
    DUAL_I2C_PIN_DIS            = 0xD001,
    DUAL_I2C_PIN_EN             = 0xD002,

    DUAL_I2S_2TO5_PIN_DIS       = 0xD003,
    DUAL_I2S_2TO5_PIN_EN        = 0xD004,

    DUAL_I2S_17TO20_PIN_DIS     = 0xD005,
    DUAL_I2S_17TO20_PIN_EN      = 0xD006,

    DUAL_SPI1_07TO10_PIN_DIS    = 0xD007,
    DUAL_SPI1_07TO10_PIN_EN     = 0xD008,

    DUAL_SPI1_11TO14_PIN_DIS    = 0xD009,
    DUAL_SPI1_11TO14_PIN_EN     = 0xD00A,

    DUAL_SPI0TO1_PIN_DIS        = 0xD00B,
    DUAL_SPI0TO1_PIN_EN         = 0xD00C,

    DUAL_UART0TO0_PIN_DIS       = 0xD00D,
    DUAL_UART0TO0_PIN_EN        = 0xD00E,

    DUAL_UART1TO1_PIN_DIS       = 0xD00F,
    DUAL_UART1TO1_PIN_EN        = 0xD010,

    DUAL_UART0TO1_PIN_DIS       = 0xD011,
    DUAL_UART0TO1_PIN_EN        = 0xD012,

    DUAL_UART1TO0_PIN_DIS       = 0xD013,
    DUAL_UART1TO0_PIN_EN        = 0xD014,

}MessagaDualCE_Type;



    
bool  VerifyIsGo(void);
uint32_t  verify_messageGetRunCid(void);
void Verify_messageInit(void);
void Verify_messageSend(uint32_t cmd, uint32_t val);
bool Verify_messageReceive(uint32_t *cmd, uint32_t *val);
bool verify_messageGetReceive(uint32_t *cmd, uint32_t *val);
bool Verify_messageCheckRececive(void);
bool Verify_messageGetRData(uint32_t *cmd, uint32_t *val);

void verify_SendRunCaseId(uint32_t Cid);
  

bool verify_SendCid(uint32_t cid,uint32_t *data);
bool Verify_SendCResult(uint32_t cmd, uint32_t val);
bool Verify_SendCResultBack(uint32_t cmd, uint32_t val);

bool verify_step_SendCheckData(uint32_t step,func_handle func);
bool verify_step_SendCheckOneData(uint32_t step,volatile uint32_t *reg,uint32_t val);
bool verify_step_SendCheckOneDataDma(uint32_t step,volatile uint32_t *reg,uint32_t val,bool rt);
bool verify_step_SendCheckOneDataLog(uint32_t step,volatile uint32_t *reg,uint32_t val,bool log);

bool verify_step_ReceiveCheckData(uint32_t step,func_handle func);
bool verify_step_ReceiveCheckOneData(uint32_t step,volatile uint32_t *reg);
bool verify_step_ReceiveCheckOneDataLog(uint32_t step,volatile uint32_t *reg,bool log);
bool verify_step_CheckReceiveOneData(uint32_t step,uint32_t val,volatile uint32_t *reg);
bool verify_step_CheckReceiveOneDataLog(uint32_t step,uint32_t val,volatile uint32_t *reg,bool log);

#define Verify_SendAppStep(x,y) Verify_SendCResult(x,y)
#define Verify_SendRovStart(x,y) Verify_SendCResult(x,y)

//contorl tb Connect Pin
void Verrify_SendPinConnect(MessagaConnectEn_Type Mce);
void Verrify_SendPinCon(uint32_t Mce);



#ifdef BR_DUAL
void VerifyDualGetRoleHandler(void);

typedef enum
{
     SOC_SLAVE   = false,
     SOC_MASTER  = true
}SocRole;


void SetSocRole(SocRole role);
bool GetSocRole(void);


#endif

void MCU_Sleep(unsigned int ms);
void sysTimeUpdataClk(uint32_t clk);

#endif



