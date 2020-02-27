/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_wdt.c
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

#include "cm_printf.h"
#include "verify_slave_wdt.h"
#include "verify_message.h"
#include "verify_register_handle.h"
#include "BR00x_config.h"
#include "BR00x_wdt.h"

#ifdef WDT_DEBUG_LOG
#define wdtprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define wdtprf(format, ...)
#endif


const RegisterCell WDT_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,  0x0000003E,     &WDT->CR},
    {true,  true,   2,  0x0000000F,     &WDT->TORR},
    {true,  false,  3,  0xFFFFFFFF,     (volatile uint32_t*)&WDT->CCVR},
    {false, true,   4,  0x000000FF,     &WDT->CRR}, 
    {true,  false,  5,  0x00000001,     (volatile uint32_t*)&WDT->STAT},
    {true,  false,  6,  0x00000001,     (volatile uint32_t*)&WDT->EIO},
};

/***********************************************************
                        Register
************************************************************/
bool cmd_VerifyRegisterWdtCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    
    wdtprf("WDT Register case1\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(WDT_CKEn,true);
    WDT->CR = 0x1e;
//WDT->CR  Control Register(W/R) 
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&WDT->CR,0x1e);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&WDT->CR);
 
//WDT->TORR  //Timeout Range Register 
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP3,&WDT->TORR,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP4,&WDT->TORR);

//WDT->CCVR Current Counter Value Register(R) 
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP5,(volatile uint32_t*)&WDT->CCVR);
    
//WDT->CRR    Counter Restart Register(W) 
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP6,&WDT->CRR,0x76);   
 
//WDT->STAT Interrupt Status Register(R) 
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP7,(volatile uint32_t*)&WDT->STAT);//TB Need write 0,close RTC 
    
//WDT->EIO Interrupt Clear Register (R)
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP8,(volatile uint32_t*)&WDT->EIO);//TB Need write 0,close RTC 
   
    Verify_SendCResult(BRCASE_RESULT,sut);
    
    return sut;

}


bool cmd_VerifyRegisterWdtCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    wdtprf("WDT Reg case2\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(WDT_CKEn,true);
    sut =Verify_RegisterHandle(WDT_RegList,sizeof(WDT_RegList),idx);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;

}



/***********************************************************
                        APP
************************************************************/

bool cmd_VerifyAppWdtCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    wdtprf("WDT App case1\r\n");
    verify_SendCid(cmd,&idx);
    {
        WDT_InitInfo_Type Wdt_InitStru;
        Wdt_InitStru.response_mode = WDT_RESPONSE_RESET;
        Wdt_InitStru.timeout_init_period = 0;       //Cannot Set
        
        SystemDevClockCtl(WDT_CKEn,true); 
        
        for(uint32_t pd = 0; pd<15 ;pd++)
        {
            Wdt_InitStru.timeout_period   = pd; // CLOCK Width   = timeout period +16 
            for(WDT_PclkCycles_Type pct =WDT_2PCLK_CYCLES;pct<=WDT_256PCLK_CYCLES;pct++)
            {
                Wdt_InitStru.pclk_cycles = pct;
                wdtprf("WDT [%d],[%d]\r\n",pd,pct);
                
                WDT_Init(&Wdt_InitStru);
                wdtprf("WDT cut[%X]\r\n",WDT_CounterCurrentValue());
                wdtprf("WDT cut[%X]\r\n",WDT_CounterCurrentValue());
                SCU->DEV_CONFIG |= 0x01ul <<31;
                wdtprf("WDT cut[%X]\r\n",WDT_CounterCurrentValue());
                wdtprf("WDT cut[%X]\r\n",WDT_CounterCurrentValue());
                SCU->DEV_CONFIG &= ~(0x01ul <<31);
                wdtprf("WDT cut[%X]\r\n",WDT_CounterCurrentValue());
                wdtprf("WDT cut[%X]\r\n",WDT_CounterCurrentValue());
                
                wdtprf("WDT kick\r\n");
                WDT_CountRestart();
                wdtprf("WDT cut[%X]\r\n",WDT_CounterCurrentValue());
                wdtprf("WDT cut[%X]\r\n",WDT_CounterCurrentValue());
                wdtprf("WDT cut[%X]\r\n",WDT_CounterCurrentValue());
                
            }   
        }  
        Wdt_InitStru.timeout_period = 0;
        Wdt_InitStru.pclk_cycles = WDT_8PCLK_CYCLES;
        WDT_Init(&Wdt_InitStru);        
    }
    
    wdtprf("WDT Test Completed\r\n");  
    Verify_SendCResult(BRCASE_RESULT,sut);
    
    return sut;

}


static  uint8_t  WDT_Run_Test=0;
bool cmd_VerifyAppWdtCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    wdtprf("WDT APP case2\r\n");
    verify_SendCid(cmd,&idx);
    {
        WDT_InitInfo_Type Wdt_InitStru;
        
        Wdt_InitStru.response_mode = WDT_RESPONSE_INTRTRUPT_RESET;
        Wdt_InitStru.timeout_init_period = 0;       //Cannot Set
                
        SystemDevClockCtl(WDT_CKEn,true); 
        
        for(uint32_t pd = 0; pd<3 ;pd++)   //Select parameter tests that are easy to test
        {
            Wdt_InitStru.timeout_period   = pd; // CLOCK Width   = timeout period +16 
            
            uint32_t max_pck = pd+1;
            if (max_pck>WDT_256PCLK_CYCLES)
                max_pck = WDT_256PCLK_CYCLES;
            
            for(WDT_PclkCycles_Type pct =WDT_2PCLK_CYCLES;pct<=max_pck;pct++)
            {
                Wdt_InitStru.pclk_cycles = pct;
                WDT_Run_Test++;
               
                WDT_Init(&Wdt_InitStru);
                wdtprf("wdt:pd[%d],pct[%d]\r\n",pd,pct);
                while(WDT_Run_Test);
            }   
        }            
    }
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    
    return sut;

}


bool cmd_VerifyAppWdtCase3(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    wdtprf("WDT App case3\r\n");
    verify_SendCid(cmd,&idx);
    {
        WDT_InitInfo_Type Wdt_InitStru;
        Wdt_InitStru.response_mode = WDT_RESPONSE_RESET;
        Wdt_InitStru.timeout_init_period = 0;       //Cannot Set
        
        SystemDevClockCtl(WDT_CKEn,true); 
        Wdt_InitStru.timeout_period = 0;
        Wdt_InitStru.pclk_cycles = WDT_8PCLK_CYCLES;
        WDT_Init(&Wdt_InitStru);        
    } 
    MCU_Sleep(20);
    Verify_SendCResult(BRCASE_RESULT,sut);
    
    return sut;

}

void NMI_Handler(void)
{
    if(WDT_Run_Test)
        wdt_ClearInterrupt();
    
    wdtprf("WDT Int[%d]\r\n",WDT_Run_Test);
    WDT_Run_Test=0;
}



