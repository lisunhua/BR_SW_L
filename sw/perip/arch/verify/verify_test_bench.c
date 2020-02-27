/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_test_bench.c
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

#include <stdio.h>

#include "BR00x_uart.h"
#include "BR00x_config.h"
#include "cm_printf.h"
#include "verify_slave.h"
#include "verify_message.h"

#define TBENCH_DEBUG_LOG
#ifdef TBENCH_DEBUG_LOG
#define tbprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define tbprf(format, ...)
#endif

static volatile uint32_t RUNCID = CASE_SCU_SIG+33;

static volatile uint32_t RCD_CASE = 0;
static volatile uint32_t READ_CASE = 0;

void tb_SetRunCid(uint32_t id)
{
	RUNCID = id;
}

/* Get current UVM message*/
bool tb_messageGetReceive(uint32_t *cmd, uint32_t *val)
{
    if(SCU->SEND_CMD != RCD_CASE)
    {
        *cmd   = SCU->SEND_CMD;
        *val = SCU->SEND_DATA;
        RCD_CASE = *cmd;
        return true;
    }
    return false;
}

/* Send a message to UVM*/
void tb_Verify_messageInit(void)
{
    SCU->READ_DATA  = 0;
    SCU->READ_CMD   = 0;
}


void tb_messageSend(uint32_t cmd, uint32_t val)
{
    SCU->READ_DATA  = val;
    SCU->READ_CMD   = cmd;
    tbprf("Send[%X],[%X]\r\n",cmd,val);
}


void  tb_RWStep(volatile uint32_t *reg,
                uint32_t cid ,uint32_t val,
                bool status,
                uint32_t cmd1,uint32_t val1,
                uint32_t cmd2,uint32_t val2)
{
    if(READ_CASE==0)
    {
        if(!status)
        {
            if(*reg == val)
                tb_messageSend(cmd1,1);
            else
                tb_messageSend(cmd1,0);
        }
        else
            tb_messageSend(cmd1,val1);
        
        RCD_CASE = 0; 
        READ_CASE++;
    }else
    {
         *reg= val2;
        tb_messageSend(cmd2,val2);
        READ_CASE=0;
    }
}


void  tb_RWStep2(volatile uint32_t *reg,
                uint32_t cid ,uint32_t val,
                bool status,
                uint32_t cmd1,uint32_t val1,
                uint32_t cmd2,uint32_t val2,
                uint32_t cmd3,uint32_t val3)
{
    if(READ_CASE==0)
    {
        if(!status)
        {
            if(*reg == val)
                tb_messageSend(cmd1,1);
            else
                tb_messageSend(cmd1,0);
        }
        else
            tb_messageSend(cmd1,val1);
        
        RCD_CASE = 0; 
        READ_CASE++;
    }
    else if(READ_CASE==1)
    {
         *reg= val3;
        tb_messageSend(cmd3,val3);
        
        
        
        RCD_CASE = 0; 
        READ_CASE++;
    }
    else
    {
       if(!status)
        {
            if(*reg == val)
                tb_messageSend(cmd2,1);
            else
                tb_messageSend(cmd2,0);
        }
        else
            tb_messageSend(cmd2,val2);
        
        READ_CASE=0;
    }
}

void tb_RStep(volatile uint32_t *reg, uint32_t cmd1,uint32_t data)
{
    *reg= data;
    tb_messageSend(cmd1,data);

}

void tb_WStep(volatile uint32_t *reg,uint32_t cid ,uint32_t val, uint32_t cmd1)
{
    if(*reg == val)
        tb_messageSend(cmd1,1);
    else
        tb_messageSend(cmd1,0);
}





//cmd_VerifyBaseRamCid0x0006
void tb_case_base2(uint32_t cid,uint32_t val)
{
    if(cid == 0x04 && val ==1)
        tb_messageSend(0x01,0x6);
    else if(cid == 0x03 && val ==0x1)
        tb_messageSend(0x03,0x1);
}


//cmd_VerifyRegisterGPIOCasebase
void tb_case1(uint32_t cid,uint32_t val)
{
    if(cid == 0x04 && val ==1)
        tb_messageSend(0x01,0x701);
    else if(cid == 0x02 && val ==0x701)
        tb_messageSend(0x02,0x1);
    else if(cid == 0x20 && val ==0x55)
        tb_RWStep(&GPIO->DR0,cid,val,false,0x20,0,0x21,0xaa);
    else if(cid == 0x03 && val ==0x1)
        tb_messageSend(0x03,0x1);
}


//cmd_VerifyRegisterRTCCase1
void tb_case2(uint32_t cid,uint32_t val)
{
    if(cid == 0x04 && val ==1)
        tb_messageSend(0x01,0x1701);
    else if(cid == 0x02 && val ==0x1701)
    {
        tb_RWStep((volatile uint32_t *)&RTC->DR,cid,val,true,0x02,0x01,0x20,0);
    } 
    else if(cid == 0x21 && val ==0x55aa55aa)
        tb_RWStep(&RTC->CMR,cid,val,false,0x021,0x01,0x22,0xaa55aa55);
    
    else if(cid == 0x23 && val ==0x55aa55aa)
        tb_RWStep(&RTC->CLR,cid,val,false,0x023,0x01,0x24,0xaa55aa55);
    
    else if(cid == 0x25 && val ==1)
        tb_RWStep(&RTC->CCR,cid,val,false,0x025,0x01,0x26,0);
    
    else if(cid == 0x27 && val ==1)
        tb_RWStep(&RTC->IMSC,cid,val,false,0x027,0x01,0x28,0);
   
    else if(cid == 0x28 && val ==1)
    {
        //tb_RWStep2(&RTC->IMSC,cid,val,false,0x027,0x01,0x28,0);
        //RTC->RIS  = 0;
        tb_messageSend(0x29,0);
    }
    else if(cid == 0x2a && val ==0x55aa55aa)
        tb_WStep(&RTC->CMR,cid,val,0x2a);
    
//    else if(cid == 0x2b && val ==1)
//        tb_WStep(&RTC->MIS,cid,val,0x2b);
    
    else if(cid == 0x2c && val ==1)
        tb_WStep(&RTC->ICR,cid,val,0x2c);
    
    else if(cid == 0x03 && val ==0x1)
        tb_messageSend(0x03,0x1);
}


//cmd_VerifyRegisterWdtCase1
void tb_case3(uint32_t cid,uint32_t val)
{
    if(cid == 0x04 && val ==1)
        tb_messageSend(0x01,0x1B01);
    else if(cid == 0x02 && val ==0x1b01)
        tb_messageSend(0x02,0x1);

    else if(cid == 0x20 && val ==0x1e)
        tb_RWStep(&WDT->CR,cid,val,false,0x020,0x01,0x21,0);
    
    else if(cid == 0x22 && val ==0x55)
        tb_RWStep(&WDT->TORR,cid,val,false,0x022,0x01,0x23,0x53);
    
    else if(cid == 0x23 && val ==1)
        tb_RStep((volatile uint32_t*)&WDT->CCVR,0x24,0);
    
    else if(cid == 0x25 && val ==0x76)
        //tb_WStep(&WDT->CRR,cid,val,0x25);
        tb_RWStep(&WDT->CRR,cid,val,false,0x025,0x01,0x26,0);
   
    else if(cid == 0x26 && val ==1)
        tb_RStep((volatile uint32_t*)&WDT->EIO,0x27,0);
    
   
    
    else if(cid == 0x03 && val ==0x1)
        tb_messageSend(0x03,0x1);
}


//cmd_VerifyRegisterWdtCase1
//void tb_case3(uint32_t cid,uint32_t val)
//{
//    if(cid == 0x04 && val ==1)
//        tb_messageSend(0x01,0x1701);
//    else if(cid == 0x02 && val ==0x1701)
//    {
//        tb_RWStep((volatile uint32_t *)&RTC->DR,cid,val,true,0x02,0x01,0x20,0);
//    } 
//    else if(cid == 0x21 && val ==0x55aa55aa)
//        tb_RWStep(&RTC->CMR,cid,val,false,0x021,0x01,0x22,0xaa55aa55);
//    
//    else if(cid == 0x23 && val ==0x55aa55aa)
//        tb_RWStep(&RTC->CLR,cid,val,false,0x023,0x01,0x24,0xaa55aa55);
//    
//    else if(cid == 0x25 && val ==1)
//        tb_RWStep(&RTC->CCR,cid,val,false,0x025,0x01,0x26,0);
//    
//    else if(cid == 0x27 && val ==1)
//        tb_RWStep(&RTC->IMSC,cid,val,false,0x027,0x01,0x28,0);
//   
//    else if(cid == 0x28 && val ==1)
//    {
//        //tb_RWStep2(&RTC->IMSC,cid,val,false,0x027,0x01,0x28,0);
//        //RTC->RIS  = 0;
//        tb_messageSend(0x29,0);
//    }
//    else if(cid == 0x2a && val ==0x55aa55aa)
//        tb_WStep(&RTC->CMR,cid,val,0x2a);
//    
//    else if(cid == 0x2b && val ==1)
//        tb_WStep(&RTC->MIS,cid,val,0x2b);
//    
//    else if(cid == 0x2c && val ==1)
//        tb_WStep(&RTC->ICR,cid,val,0x2c);
//    
//    else if(cid == 0x03 && val ==0x1)
//        tb_messageSend(0x03,0x1);
//}

#ifdef BR_FPGA
void SysTick_Handler(void)
{
    
    uint32_t cid  =0;
    uint32_t data =0;

    //verify
    if(tb_messageGetReceive(&cid,&data))
    {
        tbprf("SYST:id[%X],[%X]\r\n",cid,data);
        //tb_case_base2(cid,data);
        //tb_case1(cid,data);
        //tb_case2(cid,data);
        //tb_case3(cid,data);
        
        /*******Manually*************/
        if(cid == 0x04 && data ==1)
            tb_messageSend(0x01,RUNCID);
        else if(cid == 0x02 && data == RUNCID)
            tb_messageSend(0x02,0x1);
        else if(cid == 0x05)
            tb_messageSend(cid,0x1);
        else //if( data ==0xFF)
            tb_messageSend(cid,0x1);
//        else if(cid == 0x03 && data ==0x1)
//            tb_messageSend(0x03,0x1);
       /*****************************/
    }
    
    
}    
#endif
void  initTestBanch(void)
{
    SysTick_Config((SystemCoreClock/1000)*3);
}







