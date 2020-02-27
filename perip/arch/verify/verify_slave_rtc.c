/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_rtc.c
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
#include "verify_slave_rtc.h"
#include "verify_message.h"
#include "verify_register_handle.h"

#include "BR00x_config.h"
#include "BR00x_rtc.h"
#include "BR00x_clock.h"

#ifdef RTC_DEBUG_LOG
#define rtcprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define rtcprf(format, ...)
#endif


const RegisterCell RTC_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  false,  1,  0xFFFFFFFF,     (volatile uint32_t *)&RTC->DR},
    {true,  true,   2,  0xFFFFFFFF,     &RTC->CMR},
    {true,  true,   3,  0xFFFFFFFF,     &RTC->CLR},
    //{true,  true,   4,  0x00000001,     &RTC->CCR}, //Enable Bit ,Cannot Enable
    {true,  true,   5,  0x00000001,     &RTC->IMSC},
    {true,  false,  6,  0x00000001,     (volatile uint32_t *)&RTC->RIS},
    {true,  false,  7,  0x00000001,     (volatile uint32_t *)&RTC->MIS},
    {false, true,   8,  0x00000001,     &RTC->ICR},

};




/***********************************************************
                        Register
************************************************************/
bool cmd_VerifyRegisterRTCCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    rtcprf("RTC Register case1\r\n");
    verify_SendCid(cmd,&idx);
    
    SystemDevClockCtl(RTC_CKEn,true);
    
//RTC->DR  //only read//current RTC value  
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP1,(volatile uint32_t *)&RTC->DR);

//RTC->CMR//Counter Match Register  
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP2,&RTC->CMR,0x55aa55aa);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP3,&RTC->CMR);   
    
//RTC->CLR  //Counter Load Register  
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP4,&RTC->CLR,0x55aa55aa);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP5,&RTC->CLR);

 
////RTC->CCR    =;// Control Register(write 1 Enable)  
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP6,&RTC->CCR,1);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP7,&RTC->CCR);    
 
//RTC->IMSC//Interrupt Mask Set or Clear register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP8,&RTC->IMSC,1);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP9,&RTC->IMSC);//TB Need write 0,close RTC 
    
//RTC->RIS  //only read//Raw Interrupt Status
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP10,(volatile uint32_t *)&RTC->RIS);

//RTC->CMR//Counter Match Register  
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP11,&RTC->CMR,0x55aa55aa);
    
//RTC->MIS//Masked Interrupt Status
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP12,(volatile uint32_t *)&RTC->MIS);
    
//RTC->ICR//Interrupt Clear Registerr
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP13,&RTC->ICR,1);
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    
    return sut;

}




bool cmd_VerifyRegisterRTCCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    rtcprf("RTC Reg case2\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(RTC_CKEn,true);
    sut =Verify_RegisterHandle(RTC_RegList,sizeof(RTC_RegList),idx);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;

}

/***********************************************************
                        APP
************************************************************/

bool verify_rtcApp(bool st)
{
    uint32_t cut[3]={0,0,0};
    bool sut = true;

    for(uint8_t i=0;i<3;i++)
    {
        cut[i]=RTC_CurrentValue();
        rtcprf("RTC [%d],cut[%X]\r\n",i,cut[i]);
    }
    rtcprf("RTCl\r\n");
    if(st){
        if(!(cut[0] == cut[1] && cut[1] == cut[2]))
            sut = false;}
    else{
        if(cut[0] == cut[1] && cut[1] == cut[2])
            sut = false;}

    return sut;
}

extern unsigned long int SystemCoreClock;
#define SEC(x)      (x*SystemCoreClock)
#define MEC(x)      (x*(SystemCoreClock/1000))
#define LMEC(x)     (x*(32000UL/1000))

bool cmd_VerifyAppRTCCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    rtcprf("RTC App case1\r\n");
    verify_SendCid(cmd,&idx);
    {
        RTC_InitInfo_Type RTC_InitStru;
        RTC_InitStru.RTC_Interrpt = RTC_INTERRUPT_DISABLE ;
        RTC_InitStru.RTC_InterruptValue   = SEC(1);
        RTC_InitStru.RTC_StartValue  = 0;
        
        SystemDevClockCtl(RTC_CKEn,true);
        RTC_Init(&RTC_InitStru);
        
        rtcprf("H Clock RTC 26M\r\n");
#if  defined(BR002)||defined(BR003)
        SCU_PClkSelect(HCLK_DIV_2_PCLK);
        SCU_PClkPreSelect(HCLK_2_PLCK_PRE);
#endif         
        
        sut = verify_rtcApp(false);
        
        if(sut)
        {
            RTC_Run(false);
            verify_rtcApp(true);
        }
        if(sut)
        {
            RTC_Run(true);
            verify_rtcApp(false);
        }
        if(sut)
        {
            RTC_Run(false);
            verify_rtcApp(true);
        }
        if(sut)
        {
            RTC_Run(true);
            verify_rtcApp(false);
        }
                   
        RTC_DeInit();
   
#if  defined(BR002)||defined(BR003)
        SCU_PClkSelect(HCLK_DIV_2_PCLK);
        SCU_PClkPreSelect(HCLK_DIV16);
#endif   
        rtcprf("L Clock RTC 32K\r\n");
        RTC_InitStru.RTC_InterruptValue   = LMEC(5);
        RTC_Init(&RTC_InitStru);
        sut = verify_rtcApp(false);
        if(sut)
        {
            RTC_Run(false);
            verify_rtcApp(true);
        }
        if(sut)
        {
            RTC_Run(true);
            verify_rtcApp(false);
        }
        if(sut)
        {
            RTC_Run(false);
            verify_rtcApp(true);
        }
        if(sut)
        {
            RTC_Run(true);
            verify_rtcApp(false);
        }
                   
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



static  uint8_t RCT_APP_CASE = 0;
static uint8_t RTC_Case2IntCount =0;

bool cmd_VerifyAppRTCCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    rtcprf("RTC App case2\r\n");
    verify_SendCid(cmd,&idx);
    {
        RTC_InitInfo_Type RTC_InitStru;
        uint32_t budat= RTC_Case2IntCount;
           
        rtcprf("H Clock RTC\r\n");
        RTC_InitStru.RTC_Interrpt = RTC_INTERRUPT_ENABLE ;
        RTC_InitStru.RTC_InterruptValue   = MEC(3);
        RTC_InitStru.RTC_StartValue  = 0;
        
        SystemDevClockCtl(RTC_CKEn,true);
        
        RTC_Init(&RTC_InitStru);
        RCT_APP_CASE = 2;
        RTC_Case2IntCount = 0;
        NVIC_EnableIRQ(RTC_IRQn);
        
        while(RTC_Case2IntCount<3)//There may be a problem
        {
            if(budat!=RTC_Case2IntCount)
            {
                rtcprf("RTC cut[%X]\r\n",RTC_CurrentValue());
                budat = RTC_Case2IntCount;
            }
        };  
       
//        RTC_DeInit();     
//#if  defined(BR002)||defined(BR003)
//        SCU_HClkSelect(CLK_32K_MUX_HCLK);
//#endif 
//        rtcprf("H Clock RTC\r\n");
//        RTC_InitStru.RTC_Interrpt = RTC_INTERRUPT_ENABLE ;
//        RTC_InitStru.RTC_InterruptValue   = MEC(3);
//        RTC_InitStru.RTC_StartValue  = 0;
//        RTC_Init(&RTC_InitStru);
//        RCT_APP_CASE = 2;
//        RTC_Case2IntCount = 0;
//        NVIC_EnableIRQ(RTC_IRQn);
//        
//        while(RTC_Case2IntCount<3)//There may be a problem
//        {
//            if(budat!=RTC_Case2IntCount)
//            {
//                rtcprf("RTC cut[%X]\r\n",RTC_CurrentValue());
//                budat = RTC_Case2IntCount;
//            }
//        };  
//     
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

static uint8_t  RTC_Case3IntCount =0;
static uint32_t RTC_Case3MatVal =0;
bool cmd_VerifyAppRTCCase3(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    rtcprf("RTC App case3\r\n");
    
    verify_SendCid(cmd,&idx);
    {
        RTC_InitInfo_Type RTC_InitStru;
        uint32_t budat= RTC_Case3IntCount;
        
//#if  defined(BR002)||defined(BR003)
//        SCU_HClkSelect(CLK_OSC26m);
//#endif           
        rtcprf("H Clock RTC\r\n");
        
        RTC_Case3MatVal =MEC(3);
        RTC_InitStru.RTC_Interrpt = RTC_INTERRUPT_ENABLE ;
        RTC_InitStru.RTC_InterruptValue   =RTC_Case3MatVal;
        RTC_InitStru.RTC_StartValue  = 0;
        
        SystemDevClockCtl(RTC_CKEn,true);
        RTC_Init(&RTC_InitStru);
        RCT_APP_CASE = 3;
        NVIC_EnableIRQ(RTC_IRQn);
        
        while(RTC_Case3IntCount<3)//There may be a problem
        {
            if(budat!=RTC_Case3IntCount)
            {
                rtcprf("RTC cut[%X]\r\n",RTC_CurrentValue());
                budat= RTC_Case3IntCount;
            }
        }; 
        
//        RTC_DeInit();
//        
//#if  defined(BR002)||defined(BR003)
//        SCU_HClkSelect(CLK_32K_MUX_HCLK);
//#endif  
//        rtcprf("L Clock RTC\r\n");       
//        
//        RTC_Case3MatVal =MEC(3);
//        RTC_Case3IntCount= 0;
//        RTC_InitStru.RTC_Interrpt = RTC_INTERRUPT_ENABLE ;
//        RTC_InitStru.RTC_InterruptValue   =RTC_Case3MatVal;
//        RTC_InitStru.RTC_StartValue  = 0;
//        RTC_Init(&RTC_InitStru);
//        RCT_APP_CASE = 3;
//        NVIC_EnableIRQ(RTC_IRQn);
//        
//        while(RTC_Case3IntCount<3)//There may be a problem
//        {
//            if(budat!=RTC_Case3IntCount)
//            {
//                rtcprf("RTC cut[%X]\r\n",RTC_CurrentValue());
//                budat= RTC_Case3IntCount;
//            }
//        }; 
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

void RTC_IRQHandler(void)       
{     
    RTC_ClearInterrupt();
    
    if(RCT_APP_CASE==2)
    {
        RTC_Case2IntCount++;
        RTC_SET_LOAD_COUNTER_VALUE(0);
    }
    else if(RCT_APP_CASE==3)
    {
        RTC_Case3IntCount++;
        RTC_Case3MatVal += MEC(3);
        RTC_SET_INTERRUPT_MATCH_VALUE(RTC_Case3MatVal);
    }
    
    cm_printf("RTC [%d]Int,[%d].[%d]\r\n",RCT_APP_CASE,RTC_Case2IntCount,RTC_Case3IntCount);
}  



