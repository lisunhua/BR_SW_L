/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_register_handle.c
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
#include "verify_message.h"
#include "verify_register_handle.h"
#include "BR00x_config.h"


#ifdef VRGH_DEBUG_LOG
#define vrghprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define vrghprf(format, ...)
#endif





bool Verify_RegisterHandle(const RegisterCell *regList,uint16_t sz,uint16_t idx)
{
    bool sut = true;
    uint16_t stp=0;
    uint32_t wcmd  =0;
    uint32_t wdata =0;
    //verify Write Registers 
    uint32_t index ;
    uint32_t pidx=0;
    vrghprf("vfy reg[%p],sz[%X]\r\n",regList,sz);
    
    if(idx !=0xfffe)// Test Only Ready
    {
            
        for(index = 0;\
            index < (sz/sizeof(RegisterCell)); index++) {
                if(regList[index].regid >= idx){
                    pidx = index;
                    break;
                }
            };
        for(index = pidx;\
            index < (sz/sizeof(RegisterCell)); index++) 
        {
             if(sut){
                 if(regList[index].wt)
                     for(uint16_t k=0;k<32;k++){
                         if(regList[index].attr>>k &0x01){
                            sut = verify_step_SendCheckOneData(
                            ((BRCASE_STOP1+stp|(regList[index].regid<<16))),
                            regList[index].reg,0x01<<k);
                            stp++;
                         
                        if(!sut)
                             return sut;
                        }
                  }
             }   
        }
    }
        
    //verify Write Registers 
    if(sut){   
        Verify_messageSend(BRCASE_ROV_STR,true);
        while(1){
            if(verify_messageGetReceive(&wcmd,&wdata)){
                if(BRCASE_ROV_CTP==(wcmd&0xffff) || !sut){
                    Verify_messageSend(wcmd,1);
                    return sut;;
                }
                else {
                    for(index = 0;\
                        index < (sz/sizeof(RegisterCell)); index++) {
                        if((wcmd>>16)==regList[index].regid){
                            sut = verify_step_CheckReceiveOneData(
                            wcmd,wdata,regList[index].reg);
                            break;
                        }
                    }  
                }
            }
        }    
    }
    return sut;
}


bool Verify_RegisterDAMHandle(const RegisterCell *regList,uint16_t sz,uint16_t idx)
{
    bool sut = true;
    uint16_t stp=0;
    uint32_t wcmd  =0;
    uint32_t wdata =0;
    vrghprf("vfy reg[%p],sz[%X]\r\n",regList,sz);
//verify Write Registers 
    uint32_t index=0 ;
    uint32_t pidx=0;
    
    if(idx !=0xfffe)// Test Only Ready
    {        
        for(index = 0;\
            index < (sz/sizeof(RegisterCell)); index++) {
                if(regList[index].regid >= idx){
                    pidx = index;
                    break;
                }
            };
        for(index = pidx;\
            index < (sz/sizeof(RegisterCell)); index++) 
        {
             if(sut){
                 if(regList[index].wt)
                     for(uint16_t k=0;k<32;k++){
                         if(regList[index].attr>>k &0x01){
                             
                             
                             if((regList[index].regid>=99 && regList[index].regid<=103)|
                                (regList[index].regid>=110 && regList[index].regid<=115))
                             {
                                sut = verify_step_SendCheckOneDataDma(
                                    ((BRCASE_STOP1+stp|(regList[index].regid<<16))),
                                    regList[index].reg,0x01<<k,true);
                             }
                             else{
                             
                             
                                sut = verify_step_SendCheckOneDataDma(
                                    ((BRCASE_STOP1+stp|(regList[index].regid<<16))),
                                    regList[index].reg,0x01<<k,false);
                             }
                            stp++;
                         
                        if(!sut)
                             return sut;
                        }
                  }
             }   
        }
    }
    
    //verify Write Registers 
    if(sut){   
        Verify_messageSend(BRCASE_ROV_STR,true);
        while(1){
            if(verify_messageGetReceive(&wcmd,&wdata)){
                if(BRCASE_ROV_CTP==(wcmd&0xffff) || !sut){
                    Verify_messageSend(wcmd,1);
                    return sut;;
                }
                else {
                    for(index = 0;\
                        index < (sz/sizeof(RegisterCell)); index++) {
                        if((wcmd>>16)==regList[index].regid){
                            sut = verify_step_CheckReceiveOneData(
                            wcmd,wdata,regList[index].reg);
                            break;
                        }
                    }  
                }
            }
        }    
    }
    return sut;
}



bool Verify_RegisterUARTHandle(const RegisterCell *regList,uint16_t sz ,volatile uint32_t *reg,bool log,uint16_t idx)
{
    bool sut = true;
    uint16_t stp=0;
    uint32_t wcmd  =0;
    uint32_t wdata =0;
    uint32_t index ;
    uint32_t pidx=0;
    if(log)
        vrghprf("vfy reg[%p],sz[%X]\r\n",regList,sz);
    
    if(idx !=0xfffe)// Test Only Ready
    {
        for(index = 0;\
            index < (sz/sizeof(RegisterCell)); index++) {
                if(regList[index].regid >= idx){
                    pidx = index;
                    break;
                }
            };
        
        for(index = pidx;\
            index < (sz/sizeof(RegisterCell)); index++) 
        {
             if(sut){
                 if(regList[index].wt)
                     for(uint16_t k=0;k<32;k++){
                         if(regList[index].attr>>k &0x01){
                             
                             if(regList[index].regid < 4)
                                 *reg &= ~(0x01<<7);
                             else if(regList[index].regid >3 && regList[index].regid<6)
                                 *reg |= 0x01<<7;
                                 
                            sut = verify_step_SendCheckOneDataLog(
                            ((BRCASE_STOP1+stp|(regList[index].regid<<16))),
                            regList[index].reg,0x01<<k,log);
                            stp++;
                         
                        if(!sut)
                             return sut;
                        }
                  }
             }   
        }
    }
    
    //verify Write Registers 
    if(sut){   
        Verify_messageSend(BRCASE_ROV_STR,true);
        while(1){
            if(verify_messageGetReceive(&wcmd,&wdata)){
                if(BRCASE_ROV_CTP==(wcmd&0xffff) || !sut){
                    Verify_messageSend(wcmd,1);
                    return sut;
                }
                else {
                    for(index = 0;\
                        index < (sz/sizeof(RegisterCell)); index++) {
                        if((wcmd>>16)==regList[index].regid){
                            
                            if(regList[index].regid < 4)
                                *reg &= ~(0x01<<7);
                            else if(regList[index].regid >3 && regList[index].regid<6)
                                *reg |= 0x01<<7;
                         
                            sut = verify_step_CheckReceiveOneDataLog(
                            wcmd,wdata,regList[index].reg,log);
                            break;
                        }
                    }  
                }
            }
        }    
    }
    return sut;
}




