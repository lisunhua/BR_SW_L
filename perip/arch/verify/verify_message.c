/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_message.c
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

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "cm_printf.h"
#include "BR00x_config.h"
#include "BR00x_uart.h"
#include "verify_message.h"


#ifdef MESSAGE_DEBUG_LOG
#define mgeprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define mgeprf(format, ...)
#endif


static volatile uint32_t VERIFY_MESSGAE_RUN_CID = 0;
static volatile uint32_t VERIFY_MESSGAE_CMD = 0;

static volatile bool VERIFY_RUN_CF = false;

void Verify_SendEndSimulation(void);


/* Get a run Case Falg*/
bool VerifyIsGo(void)
{
    if(VERIFY_RUN_CF)
    {
        VERIFY_RUN_CF = false;
        return true;
    }
    return false;
}

/* Set a run Case Falg*/
void VerifyRunCase(void)
{
    VERIFY_RUN_CF = true ;
}

/* Get current Case ID*/
uint32_t  verify_messageGetRunCid(void)
{
    uint32_t  cid = VERIFY_MESSGAE_RUN_CID;
    return cid; 
}



/* Send a message to UVM*/
void Verify_messageSend(uint32_t cmd, uint32_t val)
{
    SCU->SEND_DATA  = val;
    SCU->SEND_CMD   = cmd;
}

/* Send a message to UVM*/
void Verify_FmessageSend(uint32_t cmd, uint32_t val)
{
    SCU->READ_DATA = val;
    SCU->READ_CMD  = cmd ;
}




/* Receive a message to UVM*/
bool Verify_messageReceive(uint32_t *cmd, uint32_t *val)
{
    while(SCU->READ_CMD == VERIFY_MESSGAE_CMD){};
    *cmd   = SCU->READ_CMD;
    *val = SCU->READ_DATA;
    VERIFY_MESSGAE_CMD = *cmd;
    return true;
}



/* Receive a message to UVM*/
bool Verify_messageGetRData(uint32_t *cmd, uint32_t *val)
{
   
    *cmd  = SCU->READ_CMD;
    *val  = SCU->READ_DATA;
    return true;
}


/* Get current UVM message*/
bool verify_messageGetReceive(uint32_t *cmd, uint32_t *val)
{
    if(SCU->READ_CMD != VERIFY_MESSGAE_CMD)
    {
        *cmd    = SCU->READ_CMD;
        *val    = SCU->READ_DATA;
        VERIFY_MESSGAE_CMD = *cmd;
        return true;
    }
    else
    {   
        *cmd = 0;
        *val =0;
        return false;
    }
    
}


/* Contorl Run a case*/
void verify_SendRunCaseId(uint32_t Cid)
{
    Verify_messageSend(BRCASE_RID,Cid);
    VerifyRunCase();
}

/* Check that the run instruction is received */
bool Verify_messageCheckRececive(void)
{
    uint32_t cid  =0;
    uint32_t data =0;
    verify_messageGetReceive(&cid,&data);
    if(cid == BRCASE_RID)
    {
        VERIFY_MESSGAE_RUN_CID = data;
#ifndef BR_DUAL
        Verify_messageSend(BRCASE_RID,1);
#endif 
        VerifyRunCase();
        return true;
    }
   return false;
}


/****************************************************
Send Case ID ->UVM 
*****************************************************/
bool verify_SendCid(uint32_t cid,uint32_t *data)
{
    bool sut = true;
#ifndef BR_NO_UVM
    uint32_t cd=0,va=0;
      
    Verify_messageSend(BRCASE_CID,cid);
    Verify_messageReceive(&cd,&va);
    if(!(cd == BRCASE_CID && va != 0))
        sut =false;
    *data = va;
#endif  
    return sut;   
  
}

/*
Step by step to verify,CPU Send and UVM Check
*/
bool verify_step_SendCheckData(uint32_t step,func_handle func)
{
    uint32_t cd=0,va=0;
    bool sut = true;
    
    Verify_messageSend(step,0);
    func();
    Verify_messageReceive(&cd,&va);
    if(!(cd == step && va == 1))
        sut =false;
    
    return sut;
}

/*
Step by step to verify,CPU Send and UVM Check a register
*/
bool verify_step_SendCheckOneData(uint32_t step,volatile uint32_t *reg,uint32_t val)
{
    uint32_t cd=0,va=0;
    bool sut = true;
    mgeprf("Setp %d Send \r\n",(step-0x20)&0xffff);
    *reg = val;
    Verify_messageSend(step,val);
    Verify_messageReceive(&cd,&va);
    if(!(cd == step && va == 1))
        sut =false;
    
    return sut;
}

/*
Step by step to verify,CPU Send and UVM Check a register
*/
bool verify_step_SendCheckOneDataDma(uint32_t step,volatile uint32_t *reg,uint32_t val,bool rt)
{
    uint32_t cd=0,va=0;
    bool sut = true;
    mgeprf("Setp %d Send \r\n",(step-0x20)&0xffff);
    if(rt)
        *reg = (val|0xff00);
    else
        *reg = val;
    
    Verify_messageSend(step,val);
    Verify_messageReceive(&cd,&va);
    if(!(cd == step && va == 1))
        sut =false;
    
    return sut;
}

bool verify_step_SendCheckOneDataLog(uint32_t step,volatile uint32_t *reg,uint32_t val,bool log)
{
    uint32_t cd=0,va=0;
    bool sut = true;
    
    if(log)
        mgeprf("Setp %d Send \r\n",(step-0x20)&0xffff);
    *reg = val;
    Verify_messageSend(step,val);
    Verify_messageReceive(&cd,&va);
    if(!(cd == step && va == 1))
        sut =false;
    
    return sut;
}


/*
Step by step to verify, UVM Send and CPU Check
*/
bool verify_step_ReceiveCheckData(uint32_t step,func_handle func)
{
    uint32_t cd=0,va=0;
    bool sut = true;
    Verify_messageReceive(&cd,&va);
    if(!(cd == step && va == 0))
        sut =false;
    else
    {
        if(!func())
            sut =false;
    }
    Verify_messageSend(step,sut);
    
    return sut;
}

/*
Step by step to verify, UVM Send and CPU Check a register
*/
bool verify_step_ReceiveCheckOneData(uint32_t step,volatile uint32_t *reg)
{
    uint32_t cd=0,va=0;
    bool sut = true;
    mgeprf("Setp %d Receive\r\n",(step-0x20)&0xffff);
    Verify_messageReceive(&cd,&va);
    if(!(cd == step && va == *reg))
        sut =false;
    Verify_messageSend(step,sut);
    
    return sut;
}
bool verify_step_ReceiveCheckOneDataLog(uint32_t step,volatile uint32_t *reg,bool log)
{
    uint32_t cd=0,va=0;
    bool sut = true;
    if(log)
        mgeprf("Setp %d Receive\r\n",(step-0x20)&0xffff);
    
    Verify_messageReceive(&cd,&va);
    if(!(cd == step && va == *reg))
        sut =false;
    Verify_messageSend(step,sut);
    
    return sut;
}

/*
Step by step to verify, UVM Send and CPU Check a register
*/
bool verify_step_CheckReceiveOneData(uint32_t step,uint32_t val,volatile uint32_t *reg)
{
    bool sut = true;
    mgeprf("Setp %d Receive\r\n",(step-0x20)&0xffff);
    if(!(val == *reg))
        sut =false;
    Verify_messageSend(step,sut);
    return sut;
}
bool verify_step_CheckReceiveOneDataLog(uint32_t step,uint32_t val,volatile uint32_t *reg,bool log)
{
    bool sut = true;
    if(log)
        mgeprf("Setp %d Receive [%X]\r\n",(step-0x20)&0xffff,*reg);
    
    if(!(val == *reg))
        sut =false;
    Verify_messageSend(step,sut);
    return sut;
}

#ifndef ONLY_NO_UVM
/*Send Case Verify Result*/
bool Verify_SendCResult(uint32_t cmd, uint32_t val)
{
    uint32_t cd=0,va=0;
    bool sut = true;
    
    Verify_messageSend(cmd,val);
    Verify_messageReceive(&cd,&va);
    if(!(cd == cmd && va == 1))
        sut =false;

    if(cd == BRCASE_RESULT && va==1)
        Verify_SendEndSimulation();
    
    return sut;
}
#else
bool Verify_SendCResult(uint32_t cmd, uint32_t val)
{
    bool sut = true;   
    Verify_messageSend(cmd,val);
    return sut;
}

#endif

bool Verify_SendCResultBack(uint32_t cmd, uint32_t val)
{
    uint32_t cd=0,va=0;
    bool sut = true;
    
    Verify_messageSend(cmd,val);
	
		while(SCU->READ_CMD == VERIFY_MESSGAE_CMD)
		{
			mgeprf("SCU RCMD[%X] \n",SCU->READ_CMD);
		};
		cd   = SCU->READ_CMD;
		va = SCU->READ_DATA;
		mgeprf("SCU cd:[%X],va[%X]\n",cd,va);
		VERIFY_MESSGAE_CMD = cd;	
    if(!(cd == cmd && va == 1))
        sut =false;

    if(cd == BRCASE_RESULT && va==1)
        Verify_SendEndSimulation();
    
    return sut;
}


void Verify_SendEndSimulation(void)
{
    //UART_WriteByte(UART0,0x04);
    //while(1);
}



void Verrify_SendPinConnect(MessagaConnectEn_Type Mce)
{
    SCU->SEND_DATA = Mce;
}

void Verrify_SendPinCon(uint32_t xxx)
{
    SCU->SEND_DATA = xxx;
}


//##########################################################
static unsigned long g_u32TimerMsCnt = 0;

unsigned long MCU_GetTickCount(void)
{
    return g_u32TimerMsCnt;
}
#ifndef BR_FPGA
void SysTick_Handler(void)
{
  g_u32TimerMsCnt++;
}
#endif
void MCU_Sleep(unsigned int ms)
{
#ifndef BR_FPGA
    unsigned long dest_time = ms + MCU_GetTickCount();
    while (MCU_GetTickCount() <= dest_time);
#endif
}
void sysTimeUpdataClk(uint32_t clk)
{
    #ifndef BR_FPGA
    SysTick_Config(clk/1000);
    #endif
}








