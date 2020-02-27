/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_timers.c
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
#include "verify_slave_timers.h"
#include "verify_message.h"
#include "verify_register_handle.h"

#include "BR00x_config.h"
#include "BR00x_timers.h"

#ifdef TIMERS_DEBUG_LOG
#define timprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define timprf(format, ...)
#endif

#define     SEC(X)      (X*SystemCoreClock)
#define     MSEC(X)     (X*SystemCoreClock/1000)
#define     USEC(X)     (X*SystemCoreClock/1000000)


const RegisterCell Timers_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    
    //timer0
    {true,  true,   1,  0xFFFFFFFF,      &TIMERS->TIMER[0].LOAD_COUNT},
    {true,  false,  2,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[0].CURRENT_COUNT},
    {true,  true,   3,  0x0000000E,      &TIMERS->TIMER[0].CONTROL_REG},//enable not Cannot set
    {true,  false,  4,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[0].EOI},
    {true,  false,  5,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[0].INTSTATUS},
    
    //timer1
    {true,  true,   6,  0xFFFFFFFF,      &TIMERS->TIMER[1].LOAD_COUNT},
    {true,  false,  7,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[1].CURRENT_COUNT},
    {true,  true,   8,  0x0000000E,      &TIMERS->TIMER[1].CONTROL_REG},//enable not Cannot set
    {true,  false,  9,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[1].EOI},
    {true,  false,  10,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[1].INTSTATUS},
    
    //timer2
    {true,  true,   11,  0xFFFFFFFF,      &TIMERS->TIMER[2].LOAD_COUNT},
    {true,  false,  12,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[2].CURRENT_COUNT},
    {true,  true,   13,  0x0000000E,      &TIMERS->TIMER[2].CONTROL_REG},//enable not Cannot set
    {true,  false,  14,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[2].EOI},
    {true,  false,  15,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[2].INTSTATUS},
    
    //timer3
    {true,  true,   16,  0xFFFFFFFF,      &TIMERS->TIMER[3].LOAD_COUNT},
    {true,  false,  17,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[3].CURRENT_COUNT},
    {true,  true,   18,  0x0000000E,      &TIMERS->TIMER[3].CONTROL_REG},//enable not Cannot set
    {true,  false,  19,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[3].EOI},
    {true,  false,  20,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[3].INTSTATUS},
    
    //timer4
    {true,  true,   21,  0xFFFFFFFF,      &TIMERS->TIMER[4].LOAD_COUNT},
    {true,  false,  22,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[4].CURRENT_COUNT},
    {true,  true,   23,  0x0000000E,      &TIMERS->TIMER[4].CONTROL_REG},//enable not Cannot set
    {true,  false,  24,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[4].EOI},
    {true,  false,  25,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[4].INTSTATUS},
    
    //timer5
    {true,  true,   26,  0xFFFFFFFF,      &TIMERS->TIMER[5].LOAD_COUNT},
    {true,  false,  27,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[5].CURRENT_COUNT},
    {true,  true,   28,  0x0000000E,      &TIMERS->TIMER[5].CONTROL_REG},//enable not Cannot set
    {true,  false,  29,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[5].EOI},
    {true,  false,  30,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[5].INTSTATUS},
    
    //timer6
    {true,  true,   31,  0xFFFFFFFF,      &TIMERS->TIMER[6].LOAD_COUNT},
    {true,  false,  32,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[6].CURRENT_COUNT},
    {true,  true,   33,  0x0000000E,      &TIMERS->TIMER[6].CONTROL_REG},//enable not Cannot set
    {true,  false,  34,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[6].EOI},
    {true,  false,  35,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[6].INTSTATUS},
    
    //timer7
    {true,  true,   36,  0xFFFFFFFF,      &TIMERS->TIMER[7].LOAD_COUNT},
    {true,  false,  37,  0xFFFFFFFF,     (volatile uint32_t *)&TIMERS->TIMER[7].CURRENT_COUNT},
    {true,  true,   38,  0x0000000E,      &TIMERS->TIMER[7].CONTROL_REG},//enable not Cannot set
    {true,  false,  39,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[7].EOI},
    {true,  false,  40,  0x00000001,     (volatile uint32_t *)&TIMERS->TIMER[7].INTSTATUS},
    
    {true,  false,  41,  0x00000007,     (volatile uint32_t *)&TIMERS->INT_STATUS},
    {true,  false,  42,  0x00000007,     (volatile uint32_t *)&TIMERS->EOI},
    {true,  false,  43,  0x00000007,     (volatile uint32_t *)&TIMERS->RAW_INT_STATUS},
    
    {true,  true,   44,  0xFFFFFFFF,      &TIMERS->TIMER1_LOAD_COUNT2},
    {true,  true,   45,  0xFFFFFFFF,      &TIMERS->TIMER2_LOAD_COUNT2},
    {true,  true,   46,  0xFFFFFFFF,      &TIMERS->TIMER3_LOAD_COUNT2},
    {true,  true,   47,  0xFFFFFFFF,      &TIMERS->TIMER4_LOAD_COUNT2},
    {true,  true,   48,  0xFFFFFFFF,      &TIMERS->TIMER5_LOAD_COUNT2},
    {true,  true,   49,  0xFFFFFFFF,      &TIMERS->TIMER6_LOAD_COUNT2},
    {true,  true,   50,  0xFFFFFFFF,      &TIMERS->TIMER7_LOAD_COUNT2},
    {true,  true,   51,  0xFFFFFFFF,      &TIMERS->TIMER8_LOAD_COUNT2},
   
};


/***********************************************************
                        Register
************************************************************/
bool cmd_VerifyRegisterTimersCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    timprf("Timers Register case1\r\n");
    verify_SendCid(cmd,&idx);

    SystemDevClockCtl(TIMER_CKEn,true);
    for(uint8_t index=0; index<8;index++)
    {     
//&TIMERS->TIMER[index].LOAD_COUNT Value to be loaded into TimerN 
        if(sut)
            sut = verify_step_SendCheckOneData(BRCASE_STOP1+(index*7),&TIMERS->TIMER[index].LOAD_COUNT,0X11223344UL);
        if(sut)
            sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2+(index*7),&TIMERS->TIMER[index].LOAD_COUNT);   

//&TIMERS->TIMER[index].CURRENT_COUNT Current Value of Timer1 (R
        if(sut)
            sut = verify_step_ReceiveCheckOneData(BRCASE_STOP3+(index*7),(volatile uint32_t *)&TIMERS->TIMER[index].CURRENT_COUNT);   
        
//&TIMERS->TIMER[index].CONTROL_REG  Control Register for Timer1 (R/W) 
        if(sut)
            sut = verify_step_SendCheckOneData(BRCASE_STOP4+(index*7),&TIMERS->TIMER[index].CONTROL_REG,0x1e);
        if(sut)
            sut = verify_step_ReceiveCheckOneData(BRCASE_STOP5+(index*7),&TIMERS->TIMER[index].CONTROL_REG);      
        
//&TIMERS->TIMER[index].EOI Clears the interrupt from Timer1
        if(sut)
            sut = verify_step_ReceiveCheckOneData(BRCASE_STOP6+(index*7),(volatile uint32_t *)&TIMERS->TIMER[index].EOI);
        
//&TIMERS->TIMER[index].INTSTATUS Contains the interrupt status for Timer1
        if(sut)
            sut = verify_step_ReceiveCheckOneData(BRCASE_STOP7+(index*7),(volatile uint32_t *)&TIMERS->TIMER[index].INTSTATUS);     
    }
  
//&TIMERS->INT_STATUS Contains the interrupt status of all timers in the component
        if(sut)
            sut = verify_step_ReceiveCheckOneData(0x58,(volatile uint32_t *)&TIMERS->INT_STATUS);  
//&TIMERS->EOI Returns all zeroes (0) and clears all active interrupts
        if(sut)
            sut = verify_step_ReceiveCheckOneData(0x59,(volatile uint32_t *)&TIMERS->EOI);  
//&TIMERS->RAW_INT_STATUS Contains the unmasked interrupt status of all timers in the component
        if(sut)
            sut = verify_step_ReceiveCheckOneData(0x5a,(volatile uint32_t *)&TIMERS->RAW_INT_STATUS);  

    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyRegisterTimersCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    timprf("timers Register case2\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(TIMER_CKEn,true);
    sut =Verify_RegisterHandle(Timers_RegList,sizeof(Timers_RegList),idx);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}




/***********************************************************
                        APP
************************************************************/
bool cmd_VerifyAppTimersCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    timprf("Timers App case1\r\n");
    verify_SendCid(cmd,&idx);
    {
        TIMER_InitInof_TypeDef TIMER_InitStru;
        TIMER_InitStru.TIMER_PwmValue       = 0;
        TIMER_InitStru.TIMER_LoadValue      = MSEC(3);
        TIMER_InitStru.TIMER_InterruptMask  = TIMER_INTERRUPT_MASKED;
        TIMER_InitStru.TIMER_mode           = TIMER_USER_DEFINED;
        TIMER_InitStru.TIMER_Pwd            = TIMER_PWM_DISABLE;
        TIMER_InitStru.TIMER_sch            = TIMER_ENABLE;
        timprf("Mode User\r\n");
        
        SystemDevClockCtl(TIMER_CKEn,true); 
        
        for(TIMER_Num_Type tm = TM0; tm <= TM7; tm++)
        {
            TIMER_InitStru.TIMERx= tm;
            for(uint32_t i=1;i<5;i++)
            {
                TIMER_InitStru.TIMER_LoadValue= MSEC(i);
                TIMER_Init(&TIMER_InitStru); 
                
                timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                
                SCU->DEV_CONFIG |= 0x01ul <<tm;
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                SCU->DEV_CONFIG &= ~(0x01ul <<tm);
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                
                TIMER_Init(&TIMER_InitStru); 
                timprf("Reset\r\n");
                timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
            }
        }
        timprf("Mode Free\r\n");
        TIMER_InitStru.TIMER_mode= TIMER_FREE_RUNNING;
        for(TIMER_Num_Type tm = TM0; tm <= TM7; tm++)
        {
            TIMER_InitStru.TIMERx= tm;
            for(uint32_t i=1;i<5;i+=1)
            {
                TIMER_InitStru.TIMER_LoadValue= MSEC(i);
                TIMER_Init(&TIMER_InitStru); 
                
                timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                SCU->DEV_CONFIG |= 0x01ul <<tm;
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                SCU->DEV_CONFIG &= ~(0x01ul <<tm);
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                
                TIMER_Init(&TIMER_InitStru); 
                timprf("Reset\r\n");
                timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
            }
        }
    }


    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



static uint8_t  timer_Int=0;


bool cmd_VerifyAppTimersCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    timprf("Timers App case2\r\n");
    verify_SendCid(cmd,&idx);
    {
        TIMER_InitInof_TypeDef TIMER_InitStru;
        TIMER_InitStru.TIMER_PwmValue = 0;
        TIMER_InitStru.TIMER_LoadValue= MSEC(10);
        TIMER_InitStru.TIMER_InterruptMask= TIMER_INTERRUPT_UNMASKED;
        TIMER_InitStru.TIMER_mode= TIMER_USER_DEFINED;
        TIMER_InitStru.TIMER_Pwd= TIMER_PWM_DISABLE;
        TIMER_InitStru.TIMER_sch= TIMER_ENABLE;
        timprf("Mode User\r\n");
        
        SystemDevClockCtl(TIMER_CKEn,true); 
        
        for(TIMER_Num_Type tm = TM0; tm <= TM7; tm++)
        {
            TIMER_InitStru.TIMERx= tm;
            for(uint32_t i=3;i<6;i++)
            {
                TIMER_InitStru.TIMER_LoadValue= MSEC(i);
                timer_Int=0;
                NVIC_ClearPendingIRQ((IRQn_Type)(TIMER1_IRQn+tm));
                NVIC_EnableIRQ((IRQn_Type)(TIMER0_IRQn+tm));
                TIMER_Init(&TIMER_InitStru);
                timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
                while(timer_Int<3);//There may be a problem
                TIMER_Stop(tm,false);
                NVIC_DisableIRQ((IRQn_Type)(TIMER0_IRQn+tm));
               
            }
        }
        
        
        timprf("Mode Free\r\n");
        TIMER_InitStru.TIMER_mode= TIMER_FREE_RUNNING;
        for(TIMER_Num_Type tm = TM0; tm <= TM7; tm++)
        {
            TIMER_InitStru.TIMERx= tm;
            uint32_t tme= MSEC(3);
            TIMER_InitStru.TIMER_LoadValue= tme;
            timer_Int=0;
            NVIC_ClearPendingIRQ((IRQn_Type)(TIMER1_IRQn+tm));
            NVIC_EnableIRQ((IRQn_Type)(TIMER0_IRQn+tm));
            TIMER_Init(&TIMER_InitStru);
            timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            
            while(!timer_Int);//There may be a problem
            timprf("stop\r\n");
            TIMER_Stop(tm,false);
            timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            TIMER_Stop(tm,true);
            timprf("Run\r\n");
            timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
            
            
            
            TIMER_Stop(tm,false);
            NVIC_DisableIRQ((IRQn_Type)(TIMER0_IRQn+tm));
        }
    }


    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyAppTimersCase3(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    timprf("Timers App case pwd 3\r\n");
    verify_SendCid(cmd,&idx);
    {
        TIMER_InitInof_TypeDef  TIMER_InitStru;
        
        PADConfig_Type          PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;

        SystemPADConfig(PADID23,&PAG_InitStru);
        SystemPADConfig(PADID24,&PAG_InitStru);
        SystemPADConfig(PADID25,&PAG_InitStru);
        SystemPADConfig(PADID26,&PAG_InitStru);
        
        
        TIMER_InitStru.TIMER_InterruptMask  = TIMER_INTERRUPT_MASKED;
        TIMER_InitStru.TIMER_mode           = TIMER_USER_DEFINED;
        TIMER_InitStru.TIMER_Pwd            = TIMER_PWM_ENABLE;
        TIMER_InitStru.TIMER_sch            = TIMER_ENABLE;
        
        SystemDevClockCtl(TIMER_CKEn,true); 
        
        timprf("Mode User\r\n");
        for(TIMER_Num_Type tm = TM0; tm < TM4; tm++)
        {
            TIMER_InitStru.TIMERx= tm;
            for(uint32_t i=0;i<=100;i+=5)
            {
                TIMER_InitStru.TIMER_LoadValue      = i;
                TIMER_InitStru.TIMER_PwmValue       = 100-i;
                
                TIMER_Init(&TIMER_InitStru); 
                
                timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                
            }
        }
        timprf("Mode Free\r\n");
        TIMER_InitStru.TIMER_mode= TIMER_FREE_RUNNING;
        for(TIMER_Num_Type tm = TM0; tm <= TM4; tm++)
        {
            TIMER_InitStru.TIMERx= tm;
            
            for(uint32_t i=0;i<=100;i+=5)
            {
                TIMER_InitStru.TIMER_LoadValue      = i;
                TIMER_InitStru.TIMER_PwmValue       = 100-i;
                TIMER_Init(&TIMER_InitStru); 
           
                timprf("TIME[%d],ctd[%X]\r\n",tm,TIMER_GetTimeCurrentValue(tm));
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
                timprf("TIME[%d],ctd[%X]\t\n",tm,TIMER_GetTimeCurrentValue(tm));
            }
        }
     }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



void TIMER0_IRQHandler(void)    
{     
    cm_printf("TIMER0_IRQ \r\n"); 
    TIMER_ClearInterrupt(TM0);   
    TIMER_ClearAllInterrupt();
    timer_Int++;

}  
void TIMER1_IRQHandler(void)    
{     
    TIMER_ClearInterrupt(TM1);
    cm_printf("TIMER1_IRQ\r\n");
    timer_Int++;    
}  
void TIMER2_IRQHandler(void)    
{     
    TIMER_ClearInterrupt(TM2);
    cm_printf("TIMER2_IRQ\r\n"); 
    timer_Int++;
}  
void TIMER3_IRQHandler(void)    
{     
    TIMER_ClearInterrupt(TM3);
    cm_printf("TIMER3_IRQ\r\n"); 
    timer_Int++;
}  
void TIMER4_IRQHandler(void)    
{   
    TIMER_ClearInterrupt(TM4);
    cm_printf("TIMER4_IRQ\r\n"); 
    timer_Int++;
}  
void TIMER5_IRQHandler(void)    
{     
    TIMER_ClearInterrupt(TM5);
    cm_printf("TIMER5_IRQ\r\n"); 
    timer_Int++;
}  
void TIMER6_IRQHandler(void)    
{     
    TIMER_ClearInterrupt(TM6);
    cm_printf("TIMER6_IRQ\r\n"); 
    timer_Int++;
}  
void TIMER7_IRQHandler(void)    
{     
    cm_printf("TIMER7_IRQ\r\n"); 

    TIMER_ClearInterrupt(TM7);
    TIMER_ClearAllInterrupt(); 
    timer_Int++;    
}




