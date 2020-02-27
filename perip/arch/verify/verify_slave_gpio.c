/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_gpio.c
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
#include "verify_slave_gpio.h"
#include "verify_message.h"
#include "verify_register_handle.h"

#include "BR00x_config.h"
#include "BR00x_gpio.h"


#ifdef GPIO_DEBUG_LOG
#define gpioprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define gpioprf(format, ...)
#endif



const RegisterCell GPIO_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,  0xFFFFFFFF,     &GPIO->DR0},
    {true,  true,   2,  0xFFFFFFFF,     &GPIO->DDR0},
    {true,  true,   3,  0xFFFFFFFF,     &GPIO->IE},
    {true,  true,   4,  0xFFFFFFFF,     &GPIO->IM},
    {true,  true,   5,  0xFFFFFFFF,     &GPIO->ITL},
    {true,  true,   6,  0xFFFFFFFF,     &GPIO->IP},
    {true,  false,  7,  0xFFFFFFFF,     (volatile uint32_t *)&GPIO->IS},
    {true,  false,  8,  0xFFFFFFFF,     (volatile uint32_t *)&GPIO->RIS},
    {true,  true,   9,  0xFFFFFFFF,     &GPIO->DB},
    {true,  false,  10, 0xFFFFFFFF,     (volatile uint32_t *)&GPIO->EXTDR0},
    {false, true,   11, 0xFFFFFFFF,     &GPIO->EOI},
};



/***********************************************************
                        Register
************************************************************/
//bool cmd_VerifyRegisterGPIOCasebase(uint32_t cmd, uint8_t *param_line,uint16_t len)
//{
//    
//    Verify_messageSend(0x101,0xaa);
//    GPIO->DR0 = 0xaa;
//    return true;
//}


bool cmd_VerifyRegisterGPIOCasebase(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    uint32_t cid = cmd;
    bool sut = true;
    uint32_t idx=0;
    gpioprf("GPIO Register case base\r\n");
    verify_SendCid(cid,&idx);
    SystemDevClockCtl(GPIO_CKEn,true);
    
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&GPIO->DR0,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&GPIO->DR0);
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}




bool cmd_VerifyRegisterGPIOCasebase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    gpioprf("GPIO Register case base1\r\n");
    verify_SendCid(cmd,&idx);
    uint32_t stp=0;
    SystemDevClockCtl(GPIO_CKEn,true);
    
    for(uint16_t i=0;i<32;i++)
    {
        if(sut){
            sut = verify_step_SendCheckOneData(
                (BRCASE_STOP1+stp|((((((uint32_t)&GPIO->DR0)- GPIO_BASE)&0xffff)+1)<<16)),
                &GPIO->DR0,0x01<<i);
            stp++;
        }
        else
            break;
    }
   
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



bool cmd_VerifyRegisterGPIOCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    gpioprf("GPIO Register case1\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(GPIO_CKEn,true);
//GPIO->DR0     
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP1,&GPIO->DR0,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP2,&GPIO->DR0);
//GPIO->DDR0     
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP3,&GPIO->DDR0,0xaa);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP4,&GPIO->DDR0);
//GPIO->IE     
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP5,&GPIO->IE,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP6,&GPIO->IE);

//GPIO->IM     
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP7,&GPIO->IM,0xaa);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP8,&GPIO->IM);

//GPIO->ITL     
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP9,&GPIO->ITL,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP10,&GPIO->ITL);

//GPIO->IP     
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP11,&GPIO->IP,0xaa);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP12,&GPIO->IP);

//GPIO->IS    //only Read 
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP13,(volatile uint32_t *)&GPIO->IS);
//GPIO->RIS   //only Read  
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP14,(volatile uint32_t *)&GPIO->RIS);

//GPIO->DB     
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP15,&GPIO->DB,0x55);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP16,&GPIO->DB);

//GPIO->EXTDR0   //only Read   
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP17,(volatile uint32_t *)&GPIO->EXTDR0);
  
//GPIO->EOI    //only write  
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP18,&GPIO->EOI,0x1);

    Verify_SendCResult(BRCASE_RESULT,sut);
    
    return sut;

}

bool cmd_VerifyRegisterGPIOCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    gpioprf("GPIO App case2\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(GPIO_CKEn,true);
    sut =Verify_RegisterHandle(GPIO_RegList,sizeof(GPIO_RegList),idx);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;

}


/***********************************************************
                        APP
************************************************************/

bool cmd_VerifyAppGPIOCase1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    gpioprf("GPIO App case1\r\n");
    verify_SendCid(cmd,&idx);    
    {
        GPIO_InitInfo_Type GPIO_InitStru;    
        PADConfig_Type      PAG_InitStru;

        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
       
        SystemPADConfig(PADID0,&PAG_InitStru);
        SystemPADConfig(PADID1,&PAG_InitStru);
        SystemPADConfig(PADID2,&PAG_InitStru);
        SystemPADConfig(PADID3,&PAG_InitStru);
                
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        
        
        
        GPIO_InitStru.dir           = GPOP_DIR_OUT;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;
        SystemDevClockCtl(GPIO_CKEn,true);
        
        for(GPIO_PinId_Type pin     = GPIO_PIN_0;pin <GPIO_PIN_32;pin++)
        {
            GPIO_InitStru.pin = pin;
            GPIO_Init(&GPIO_InitStru);
            GPIO_WriteBit(pin,1);
            sut = Verify_SendAppStep(BRCASE_STOP1+pin,0xFF);
        }
        
    }
  
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyAppGPIOCase2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    gpioprf("GPIO App case2\r\n");
    verify_SendCid(cmd,&idx);
    {
        GPIO_InitInfo_Type GPIO_InitStru;
        PADConfig_Type      PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
       
        SystemPADConfig(PADID0,&PAG_InitStru);
        SystemPADConfig(PADID1,&PAG_InitStru);
        SystemPADConfig(PADID2,&PAG_InitStru);
        SystemPADConfig(PADID3,&PAG_InitStru);
                
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        
        GPIO_InitStru.dir           = GPOP_DIR_OUT;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;
        SystemDevClockCtl(GPIO_CKEn,true);
        for(GPIO_PinId_Type pin = GPIO_PIN_0;pin <GPIO_PIN_32;pin++)
        {
            GPIO_InitStru.pin = pin;
            GPIO_Init(&GPIO_InitStru);
            GPIO_WriteBit(pin,0);
            sut = Verify_SendAppStep(BRCASE_STOP1+pin,0xff);
        }
        
    }
    
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

bool cmd_VerifyAppGPIOCase3(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    gpioprf("GPIO App case3\r\n");
    verify_SendCid(cmd,&idx);
    uint32_t step_count =0;
    {
        GPIO_InitInfo_Type GPIO_InitStru;
        PADConfig_Type      PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
       
        SystemPADConfig(PADID0,&PAG_InitStru);
        SystemPADConfig(PADID1,&PAG_InitStru);
        SystemPADConfig(PADID2,&PAG_InitStru);
        SystemPADConfig(PADID3,&PAG_InitStru);
                
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        
        GPIO_InitStru.dir           = GPOP_DIR_OUT;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;
        SystemDevClockCtl(GPIO_CKEn,true);
        for(GPIO_PinId_Type pin = GPIO_PIN_0;pin <GPIO_PIN_32;pin++)
        {
            GPIO_InitStru.pin = pin;
            GPIO_Init(&GPIO_InitStru);
            
            GPIO_WriteBit(pin,1);
            sut = Verify_SendAppStep(BRCASE_STOP1+step_count,0xff);
            step_count++;
            
            GPIO_WriteBit(pin,0);
            sut = Verify_SendAppStep(BRCASE_STOP1+step_count,0xff);
            step_count++;
        }       
    }

    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}


//No Need
bool cmd_VerifyAppGPIOCase4(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    gpioprf("GPIO App case4\r\n");
    verify_SendCid(cmd,&idx);
    
    {
        GPIO_InitInfo_Type GPIO_InitStru;
        PADConfig_Type      PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        //SystemPADConfig(PADID0,&PAG_InitStru);
        SystemPADConfig(PADID1,&PAG_InitStru);
        SystemPADConfig(PADID2,&PAG_InitStru);
        SystemPADConfig(PADID3,&PAG_InitStru);
                
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        
        
        GPIO_InitStru.dir           = GPOP_DIR_IN;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;
        SystemDevClockCtl(GPIO_CKEn,true);
        for(GPIO_PinId_Type pin = GPIO_PIN_0;pin <GPIO_PIN_32;pin++)
        {
            FlagStatus st;
            GPIO_InitStru.pin = pin;
            GPIO_Init(&GPIO_InitStru);
            sut = Verify_SendAppStep(BRCASE_STOP1+pin,0xff);
            st = GPIO_ReadBit(pin);
            gpioprf("GPIO Get Pin[%X],st[%d]\r\n",pin,st);
        }       
    }
    
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

//No Need
bool cmd_VerifyAppGPIOCase5(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    gpioprf("GPIO App case5\r\n");
    verify_SendCid(cmd,&idx);
    uint32_t step_count=0;

    {
        GPIO_InitInfo_Type GPIO_InitStru;
        
        PADConfig_Type      PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
       
        //SystemPADConfig(PADID0,&PAG_InitStru);
        SystemPADConfig(PADID1,&PAG_InitStru);
        SystemPADConfig(PADID2,&PAG_InitStru);
        SystemPADConfig(PADID3,&PAG_InitStru);
                
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        
        GPIO_InitStru.dir           = GPOP_DIR_IN;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = ENABLE;
        GPIO_InitStru.int_unmask    = ENABLE;
        SystemDevClockCtl(GPIO_CKEn,true);
        for(GPIO_IntType_Type IntT = GPIO_INTTYPE_LEVEL;IntT<= GPIO_INTTYPE_EDGE;IntT++)
        {
            GPIO_InitStru.int_type      = IntT;
            for(GPIO_IntPolarity_Type IntP = GPIO_INTPOL_ACTIVELOW; IntP<= GPIO_INTPOL_ACTIVEHIGH;IntP++)
            {
                GPIO_InitStru.int_pol       = IntP;
                for(FunctionalState deb = DISABLE;deb<= 1;deb++)
                {
                    GPIO_InitStru.debounce_en   = deb;
                
                    for(GPIO_PinId_Type pin = GPIO_PIN_0;pin <GPIO_PIN_32;pin++)
                    {
                        FlagStatus st;
                        GPIO_InitStru.pin = pin;
                        GPIO_Init(&GPIO_InitStru);
                        sut = Verify_SendAppStep(BRCASE_STOP1 + step_count,0xff);
                        step_count++;
                        st = GPIO_ReadBit(pin);
                        gpioprf("GPIO Get Pin[%X],st[%d]\r\n",pin,st);
                    }  
                }
            }
        }
    }
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

#ifdef BR002
uint16_t All_Pad =13;
GPIO_PinId_Type Start_PAD   = GPIO_PIN_1;
GPIO_PinId_Type Mod_PAD     = GPIO_PIN_14;
GPIO_PinId_Type End_PAD     = GPIO_PIN_26;
#endif
#ifdef BR003
uint16_t All_Pad =14;
GPIO_PinId_Type Start_PAD   = GPIO_PIN_1;
GPIO_PinId_Type Mod_PAD     = GPIO_PIN_15;
GPIO_PinId_Type End_PAD     = GPIO_PIN_28;
#endif
bool cmd_VerifyAppGPIOCase6(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    gpioprf("GPIO App case6\r\n");
    verify_SendCid(cmd,&idx);
    Verrify_SendPinConnect(GPIO_TEST_EN);
    {
        GPIO_InitInfo_Type GPIO_Input;
        GPIO_InitInfo_Type GPIO_Output;
        
        PADConfig_Type          PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
       
        //SystemPADConfig(PADID0,&PAG_InitStru);
        SystemPADConfig(PADID1,&PAG_InitStru);
        SystemPADConfig(PADID2,&PAG_InitStru);
        SystemPADConfig(PADID3,&PAG_InitStru);
                
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        
        
        GPIO_Input.dir           = GPOP_DIR_IN;
        GPIO_Input.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_Input.int_en        = DISABLE;
        GPIO_Input.int_unmask    = DISABLE;
        GPIO_Input.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_Input.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_Input.debounce_en   = DISABLE;
        
        GPIO_Output.dir           = GPOP_DIR_OUT;
        GPIO_Output.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_Output.int_en        = DISABLE;
        GPIO_Output.int_unmask    = DISABLE;
        GPIO_Output.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_Output.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_Output.debounce_en   = DISABLE;
        SystemDevClockCtl(GPIO_CKEn,true);
       
       //need Connect Pin4-15 to pin 16-27 
        for(GPIO_PinId_Type pin = Start_PAD;pin <Mod_PAD ;pin++)
        {
            FlagStatus st;
            GPIO_Input.pin = pin;
            GPIO_Output.pin = (GPIO_PinId_Type)(pin + All_Pad);
             
            GPIO_Init(&GPIO_Input);
            GPIO_Init(&GPIO_Output);
            
            GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),1);
            st = GPIO_ReadBit(pin);
            gpioprf("GPIO Set Pin[%d],[%d];Get Pin[%d],[%d]\n",
                pin+All_Pad,1,pin,st);
            
            GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),0);
            st = GPIO_ReadBit(pin);
            gpioprf("GPIO Set Pin[%d],[%d];Get Pin[%d],[%d]\n",
                pin+All_Pad,0,pin,st);
        } 
        
        GPIO_DeInit();

        for(GPIO_PinId_Type pin = Mod_PAD;pin <= End_PAD;pin++)
        {
            GPIO_Input.pin = pin;
            GPIO_Output.pin = (GPIO_PinId_Type)(pin-All_Pad);
             
            GPIO_Init(&GPIO_Input);
            GPIO_Init(&GPIO_Output);
            
            GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),1);
            gpioprf("GPIO Set Pin[%d],[%d];Get Pin[%d],[%d]\n",
                pin-All_Pad,1,pin,GPIO_ReadBit(pin));
            
            GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),0);
            gpioprf("GPIO Set Pin[%d],[%d];Get Pin[%d],[%d]\n",
                pin-All_Pad,0,pin,GPIO_ReadBit(pin));
        }      
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

static uint8_t GPIOInterrup_Flag[32]={\
    0,0,0,0,0,0,0,0,0,0,\
    0,0,0,0,0,0,0,0,0,0,\
    0,0,0,0,0,0,0,0,0,0,\
    0,0} ;

bool cmd_VerifyAppGPIOCase7(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    gpioprf("GPIO App case7\r\n");
    verify_SendCid(cmd,&idx);
    Verrify_SendPinConnect(GPIO_TEST_EN);
    {
        GPIO_InitInfo_Type GPIO_Input;
        GPIO_InitInfo_Type GPIO_Output;
        
        PADConfig_Type      PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
       
        //SystemPADConfig(PADID0,&PAG_InitStru);
        SystemPADConfig(PADID1,&PAG_InitStru);
        SystemPADConfig(PADID2,&PAG_InitStru);
        SystemPADConfig(PADID3,&PAG_InitStru);
                
        SystemPADConfig(PADID4,&PAG_InitStru);
        SystemPADConfig(PADID5,&PAG_InitStru);
        
        GPIO_Output.dir             = GPOP_DIR_OUT;
        GPIO_Output.mode            = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_Output.int_en          = DISABLE;
        GPIO_Output.int_unmask      = DISABLE;
        GPIO_Output.int_type        = GPIO_INTTYPE_LEVEL;
        GPIO_Output.int_pol         = GPIO_INTPOL_ACTIVELOW;
        GPIO_Output.debounce_en     = DISABLE;
        
        GPIO_Input.dir              = GPOP_DIR_IN;
        GPIO_Input.mode             = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_Input.int_en           = ENABLE;
        GPIO_Input.int_unmask       = ENABLE;
        SystemDevClockCtl(GPIO_CKEn,true);
        for(GPIO_IntType_Type IntT = GPIO_INTTYPE_LEVEL;IntT<= GPIO_INTTYPE_EDGE;IntT++)
        {
            GPIO_Input.int_type      = IntT;
            for(GPIO_IntPolarity_Type IntP = GPIO_INTPOL_ACTIVELOW; IntP<= GPIO_INTPOL_ACTIVEHIGH;IntP++)
            {
                GPIO_Input.int_pol       = IntP;
                for(FunctionalState deb = DISABLE;deb<= 1;deb++)
                {
                    GPIO_Input.debounce_en   = deb;
                    
                    GPIO_DeInit();
                    
                    for(GPIO_PinId_Type pin = Start_PAD;pin <Mod_PAD;pin++)
                    {
                        GPIO_Input.pin = pin;
                        GPIO_Output.pin = (GPIO_PinId_Type)(pin + All_Pad);
                        
                        NVIC_ClearPendingIRQ((IRQn_Type)(GPIO0_IRQn+pin));
                        NVIC_EnableIRQ((IRQn_Type)(GPIO0_IRQn+pin));
                        
                        GPIOInterrup_Flag[pin] = 0;
                        
                        GPIO_Init(&GPIO_Input);
                        GPIO_Init(&GPIO_Output);
                        
                        if(IntT == GPIO_INTTYPE_LEVEL)
                            if(IntP == GPIO_INTPOL_ACTIVELOW)
                                GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),0);
                            else
                                GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),1);     
                         else
                         {
                            if(IntP == GPIO_INTPOL_ACTIVELOW)
                            {
                                GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),1);
                                GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),0);
                            }
                            else
                            {
                                GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),0);
                                GPIO_WriteBit((GPIO_PinId_Type)(pin+All_Pad),1);
                            }
                         }

                        gpioprf("GPIO Get Pin[%d] p[%d],D[%d]\r\n",pin,IntP,IntT);
                        while(GPIOInterrup_Flag[pin]==0);
                        
                    }  
                    
                    GPIO_DeInit();
                    
                    for(GPIO_PinId_Type pin = Mod_PAD;pin <=End_PAD;pin++)
                    {
                        GPIO_Input.pin = pin;
                        GPIO_Output.pin = (GPIO_PinId_Type)(pin - All_Pad);
                        
                        NVIC_ClearPendingIRQ((IRQn_Type)(GPIO0_IRQn+pin));
                        NVIC_EnableIRQ((IRQn_Type)(GPIO0_IRQn+pin));
                        
                        GPIOInterrup_Flag[pin] = 0;
                        
                        GPIO_Init(&GPIO_Input);
                        GPIO_Init(&GPIO_Output);
                        
                        if(IntT == GPIO_INTTYPE_LEVEL)
                            if(IntP == GPIO_INTPOL_ACTIVELOW)
                                GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),0);
                            else
                                GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),1);     
                         else
                         {
                            if(IntP == GPIO_INTPOL_ACTIVELOW)
                            {
                                GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),1);
                                GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),0);
                            }
                            else
                            {
                                GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),0);
                                GPIO_WriteBit((GPIO_PinId_Type)(pin-All_Pad),1);
                            }
                         }                   
                        gpioprf("GPIO Get Pin[%d] p[%d],D[%d]\r\n",pin,IntP,IntT);
                        while(GPIOInterrup_Flag[pin]==0);                       
                    }  
                }
            }
        }
    }
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



void GPIO0_IRQHandler(void)
{
    gpioprf("GPIO0:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_0);
    GPIOInterrup_Flag[0] = 1;
    NVIC_DisableIRQ(GPIO0_IRQn);
}
void GPIO1_IRQHandler(void)
{
    gpioprf("GPIO1:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_1);
    GPIOInterrup_Flag[1] = 1;
    NVIC_DisableIRQ(GPIO1_IRQn);
}
void GPIO2_IRQHandler(void)
{
    gpioprf("GPIO2:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_2);
    GPIOInterrup_Flag[2] = 1;
    NVIC_DisableIRQ(GPIO2_IRQn);
}
void GPIO3_IRQHandler(void)
{
    gpioprf("GPIO3:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_3);
    GPIOInterrup_Flag[3] = 1;
    NVIC_DisableIRQ(GPIO3_IRQn);
}
void GPIO4_IRQHandler(void)
{
    gpioprf("GPIO4:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_4);
    GPIOInterrup_Flag[4] = 1;
    NVIC_DisableIRQ(GPIO4_IRQn);
}
void GPIO5_IRQHandler(void)
{
    gpioprf("GPIO5:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_5);
    GPIOInterrup_Flag[5] = 1;
    NVIC_DisableIRQ(GPIO5_IRQn);
}
void GPIO6_IRQHandler(void)
{
    gpioprf("GPIO6:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_6);
    GPIOInterrup_Flag[6] = 1;
    NVIC_DisableIRQ(GPIO6_IRQn);
}
void GPIO7_IRQHandler(void)
{
    gpioprf("GPIO7:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_7);
    GPIOInterrup_Flag[7] = 1;
    NVIC_DisableIRQ(GPIO7_IRQn);
}
void GPIO8_IRQHandler(void)
{
    gpioprf("GPIO8:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_8);
    GPIOInterrup_Flag[8] = 1;
    NVIC_DisableIRQ(GPIO8_IRQn);
}
void GPIO9_IRQHandler(void)
{
    gpioprf("GPIO9:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_9);
    GPIOInterrup_Flag[9] = 1;
    NVIC_DisableIRQ(GPIO9_IRQn);
}
void GPIO10_IRQHandler(void)
{
    gpioprf("GPIO10:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_10);
    GPIOInterrup_Flag[10] = 1;
    NVIC_DisableIRQ(GPIO10_IRQn);
}
void GPIO11_IRQHandler(void)
{
    gpioprf("GPIO11:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_11);
    GPIOInterrup_Flag[11] = 1;
    NVIC_DisableIRQ(GPIO11_IRQn);
}
void GPIO12_IRQHandler(void)
{
    gpioprf("GPIO12:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_12);
    GPIOInterrup_Flag[12] = 1;
    NVIC_DisableIRQ(GPIO12_IRQn);
}
void GPIO13_IRQHandler(void)
{
    gpioprf("GPIO13:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_13);
    GPIOInterrup_Flag[13] = 1;
    NVIC_DisableIRQ(GPIO13_IRQn);
}
void GPIO14_IRQHandler(void)
{
    gpioprf("GPIO14:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_14);
    GPIOInterrup_Flag[14] = 1;
    NVIC_DisableIRQ(GPIO14_IRQn);
}
void GPIO15_IRQHandler(void)
{
    gpioprf("GPIO15:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_15);
    GPIOInterrup_Flag[15] = 1;
    NVIC_DisableIRQ(GPIO15_IRQn);
}
void GPIO16_IRQHandler(void)
{
    gpioprf("GPIO16:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_16);
    GPIOInterrup_Flag[16] = 1;
    NVIC_DisableIRQ(GPIO16_IRQn);
}
void GPIO17_IRQHandler(void)
{
    gpioprf("GPIO17:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_17);
    GPIOInterrup_Flag[17] = 1;
    NVIC_DisableIRQ(GPIO17_IRQn);
}
void GPIO18_IRQHandler(void)
{
    gpioprf("GPIO18:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_18);
    GPIOInterrup_Flag[18] = 1;
    NVIC_DisableIRQ(GPIO18_IRQn);
}
void GPIO19_IRQHandler(void)
{
    gpioprf("GPIO19:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_0);
    GPIOInterrup_Flag[19] = 1;
    NVIC_DisableIRQ(GPIO19_IRQn);
}
void GPIO20_IRQHandler(void)
{
    gpioprf("GPIO20:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_20);
    GPIOInterrup_Flag[20] = 1;
    NVIC_DisableIRQ(GPIO20_IRQn);
}
void GPIO21_IRQHandler(void)
{
    gpioprf("GPIO21:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_21);
    GPIOInterrup_Flag[21] = 1;
    NVIC_DisableIRQ(GPIO21_IRQn);
}
void GPIO22_IRQHandler(void)
{
    gpioprf("GPIO22:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_22);
    GPIOInterrup_Flag[22] = 1;
    NVIC_DisableIRQ(GPIO22_IRQn);
}
void GPIO23_IRQHandler(void)
{
    gpioprf("GPIO23:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_23);
    GPIOInterrup_Flag[23] = 1;
    NVIC_DisableIRQ(GPIO23_IRQn);
}
void GPIO24_IRQHandler(void)
{
    gpioprf("GPIO24:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_24);
    GPIOInterrup_Flag[24] = 1;
    NVIC_DisableIRQ(GPIO24_IRQn);
}
void GPIO25_IRQHandler(void)
{
    gpioprf("GPIO25:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_25);
    GPIOInterrup_Flag[25] = 1;
    NVIC_DisableIRQ(GPIO25_IRQn);
}
void GPIO26_IRQHandler(void)
{
    gpioprf("GPIO26:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_26);
    GPIOInterrup_Flag[26] = 1;
    NVIC_DisableIRQ(GPIO26_IRQn);
}
void GPIO27_IRQHandler(void)
{
    gpioprf("GPIO27:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_27);
    GPIOInterrup_Flag[27] = 1;
    NVIC_DisableIRQ(GPIO27_IRQn);
}
void GPIO28_IRQHandler(void)
{
    gpioprf("GPIO28:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_28);
    GPIOInterrup_Flag[28] = 1;
    NVIC_DisableIRQ(GPIO28_IRQn);
}
void GPIO29_IRQHandler(void)
{
    gpioprf("GPIO29:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_29);
    GPIOInterrup_Flag[29] = 1;
    NVIC_DisableIRQ(GPIO29_IRQn);
}

void GPIO30_IRQHandler(void)
{
    gpioprf("GPIO30:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_30);
    GPIOInterrup_Flag[30] = 1;
    NVIC_DisableIRQ(GPIO30_IRQn);
}
void GPIO31_IRQHandler(void)
{
    gpioprf("GPIO31:IRQ\r\n");
    GPIO_ClrIntBit(GPIO_PIN_31);
    GPIOInterrup_Flag[1] = 1;
    NVIC_DisableIRQ(GPIO31_IRQn);
}



