/*
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright (c) 1999-2018 Barrot Technology Limited
 *
 * All rights reserved.
 *
 *------------------------------------------------------------------------------
 */
/**
 * @file verify_slave_uart.c
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
#include "verify_slave_uart.h"
#include "verify_message.h"
#include "verify_register_handle.h"

#include "BR00x_config.h"
#include "BR00x_uart.h"
#include "BR00x_gpio.h"
#include "BR00x_clock.h"

#ifdef BR_FPGA
extern void UART0_Handle(uint8_t  ch);
#endif

#ifdef UART_DEBUG_LOG
#define urtprf(format, ...) cm_printf(format, ##__VA_ARGS__)
#else
#define urtprf(format, ...)
#endif


const RegisterCell UART0_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  false,  1,  0x000000FF,     (volatile uint32_t *)&UART0->RBR},//LCR[7] cleared
    {false, true,   2,  0x000000FF,     &UART0->THR},//LCR[7] cleared
    {true,  true,   3,  0x0000000F,     &UART0->IER},//LCR[7] cleared
    {true,  true,   4,  0x000000FF,     &UART0->DLL},//LCR[7] set
    {true,  true,   5,  0x000000FF,     &UART0->DLH},//LCR[7] set
    {false, true,   6,  0x000000FF,     &UART0->FCR},
    {true,  false,  7,  0x000000CF,     (volatile uint32_t *)&UART0->IIR},
    {true,  true,   8,  0x000000FF,     &UART0->LCR},
    {true,  true,   9,  0x0000007F,     &UART0->MCR},
    {true,  false,  10, 0x000000FF,     (volatile uint32_t *)&UART0->LSR},
    {true,  false,  11, 0x0000001F,     (volatile uint32_t *)&UART0->USR},
    {true,  false,  12, 0x0000001F,     (volatile uint32_t *)&UART0->TFL},
    {true,  false,  13, 0x0000001F,     (volatile uint32_t *)&UART0->RFL},
    {true,  true,   14, 0x0000000F,     &UART0->DLF},
};

const RegisterCell UART1_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  false,  1,  0x000000FF,     (volatile uint32_t *)&UART1->RBR},//LCR[7] cleared
    {false, true,   2,  0x000000FF,     &UART1->THR},//LCR[7] cleared
    {true,  true,   3,  0x0000000F,     &UART1->IER},//LCR[7] cleared
    {true,  true,   4,  0x000000FF,     &UART1->DLL},//LCR[7] set
    {true,  true,   5,  0x000000FF,     &UART1->DLH},//LCR[7] set
    {false, true,   6,  0x000000FF,     &UART1->FCR},
    {true,  false,  7,  0x000000CF,     (volatile uint32_t *)&UART1->IIR},
    {true,  true,   8,  0x000000FF,     &UART1->LCR},
    {true,  true,   9,  0x0000007F,     &UART1->MCR},
    {true,  false,  10, 0x000000FF,     (volatile uint32_t *)&UART1->LSR},
    {true,  false,  11, 0x0000001F,     (volatile uint32_t *)&UART1->USR},
    {true,  false,  12, 0x0000000F,     (volatile uint32_t *)&UART1->TFL},
    {true,  false,  13, 0x0000000F,     (volatile uint32_t *)&UART1->RFL},
    {true,  true,   14, 0x0000000F,     &UART1->DLF},
};


/***********************************************************
                        Register
************************************************************/
bool Uart_RegTest(UART_TypeDef *UARTx)
{
    bool sut = true;
    
    SystemDevClockCtl(UART1_CKEn,true);
    
//UARTx->RBR  Receiver Buffer 
    UARTx->LCR &= ~0x80;
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP1,(volatile uint32_t *)&UARTx->RBR);
//UARTx->THR  Transmit Buffer 
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP2,&UARTx->THR,0XAA); 

//UARTx->IER   Interrupt Enable Register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP3,&UARTx->IER ,0x03);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP4,&UARTx->IER); 
   
//UARTx->DLL  Divisor Latch (Low)  
    UARTx->LCR |= 0x80;
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP5,&UARTx->DLL,0x26);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP6,&UARTx->DLL); 
    
//UARTx->DLH Divisor High
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP7,&UARTx->DLH,0x18);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP8,&UARTx->DLH);
        
//UARTx->FCR      FIFO Control Register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP9,&UARTx->FCR,0xE);
    
//UARTx->IIR  Interrupt Identification Register   //READ
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP10,(volatile uint32_t *)&UARTx->IIR);
    
//UARTx->LCR  Line Control Register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP11,&UARTx->LCR,0x2b);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP12,&UARTx->LCR);
        
//UARTx->MCR  Modem Control Register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP13,&UARTx->MCR,0x1f);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP14,&UARTx->MCR);    
    
    
//UARTx->LSR  Line Status Register
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP15,(volatile uint32_t *)&UARTx->LSR);    
        
//UARTx->USR  UART Status register
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP16,(volatile uint32_t *)&UARTx->USR);    
    
//UARTx->TFL  UART Status register
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP17,(volatile uint32_t *)&UARTx->TFL);    

//UARTx->RFL  UART Status register
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP18,(volatile uint32_t *)&UARTx->RFL);    

       
//UARTx->DLF  Divisor Latch Fraction Register
    if(sut)
        sut = verify_step_SendCheckOneData(BRCASE_STOP19,&UARTx->DLF,0X6);
    if(sut)
        sut = verify_step_ReceiveCheckOneData(BRCASE_STOP20,&UARTx->DLF); 
    
    return  sut;
}



void Uart0ReInit(void)
{
#ifdef  DEBUG_LOG
    UART_InitInfo_Type UART_InitStru;
    SystemDevClockCtl(UART0_CKEn,true);
    UART_InitStru.UART_BaudRate     = 500000;
    UART_InitStru.UART_WordLength   = UART_WL_8BITS;
    UART_InitStru.UART_StopBits     = UART_SB_1BIT;
    UART_InitStru.UART_ParityMode   = UART_PM_NONE;
    UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
    UART_InitStru.UART_FIFOMode     = UART_FM_ENABLE;
    UART_InitStru.UART_DMAMode      = UART_DM_MODE_0;
    UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
    UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;
    UART_Init(UART0, &UART_InitStru); 
    UART_InterruptSet(UART0,0x01ul<<UART_ERBFI);
    NVIC_EnableIRQ(UART0_IRQn);
    
#endif
}

bool cmd_VerifyRegisterUart0Case1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    memset(UART0,0,sizeof(UART_TypeDef)); //Ready Test Uart0
    
    urtprf("uart0 Register case1\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(UART0_CKEn,true);
    sut = Uart_RegTest(UART0);
    Verify_SendCResult(BRCASE_RESULT,sut);
    
    return sut;
}


bool cmd_VerifyRegisterUart1Case1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    urtprf("uart1 Register case1\r\n");
    verify_SendCid(cmd,&idx);  
    SystemDevClockCtl(UART1_CKEn,true);
    sut = Uart_RegTest(UART1);
    Verify_SendCResult(BRCASE_RESULT,sut);
    
    memset(UART0,0,sizeof(UART_TypeDef)); // Init Uart0 
    Uart0ReInit();
    
    return sut;
}


//no Need
bool cmd_VerifyRegisterUart0Case2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    urtprf("UART0 Reg case2\r\n");
    NVIC_DisableIRQ(UART0_IRQn);
    memset(UART0,0,sizeof(UART_TypeDef)); //Ready Test Uart0
    
    SystemDevClockCtl(UART0_CKEn,true);
    verify_SendCid(cmd,&idx);
    sut =Verify_RegisterUARTHandle(UART0_RegList,sizeof(UART0_RegList),&UART0->LCR,false,idx);
    Verify_SendCResult(BRCASE_RESULT,sut);
    
    memset(UART0,0,sizeof(UART_TypeDef)); // Init Uart0 
    Uart0ReInit();
    urtprf("UART0 completed\r\n");
    return sut;

}

bool cmd_VerifyRegisterUart1Case2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    urtprf("UART1 Reg case2\r\n");
    verify_SendCid(cmd,&idx);
    SystemDevClockCtl(UART1_CKEn,true);
    sut =Verify_RegisterUARTHandle(UART1_RegList,sizeof(UART1_RegList),&UART1->LCR,true,idx);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;

}

/***********************************************************
                        APP
************************************************************/

GPIO_PinId_Type TestUartCstPin = GPIO_PIN_26;

bool cmd_VerifyAppUART0Case1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    verify_SendCid(cmd,&idx);
    urtprf("UART0 App case1\r\n");
    //UART_DeInit(UART0);
    Verrify_SendPinConnect(GPIO_UART0_EN);
    {
        GPIO_InitInfo_Type GPIO_InitStru;

        GPIO_InitStru.dir           = GPOP_DIR_OUT;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;
        GPIO_InitStru.pin   = TestUartCstPin;
        SystemDevClockCtl(GPIO_CKEn,true);
        GPIO_Init(&GPIO_InitStru);
        
        //Enable Uart Flow
        UART_AutoFlow(UART0,true);   
        GPIO_WriteBit(TestUartCstPin,1);       
        urtprf("Test Uart0 Flow Err\n");       
    }

    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;


}

void  UART0_Write_handle(void)
{
    for(uint16_t i=0 ;i<800;i++);
    GPIO_WriteBit(TestUartCstPin,0); 
}

bool cmd_VerifyAppUART0Case2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    verify_SendCid(cmd,&idx);
    urtprf("UART0 App case2\r\n");
    //UART_DeInit(UART0);
    Verrify_SendPinConnect(GPIO_UART0_EN);
    {
        GPIO_InitInfo_Type GPIO_InitStru;

        GPIO_InitStru.dir           = GPOP_DIR_OUT;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;
        GPIO_InitStru.pin           = TestUartCstPin;
        SystemDevClockCtl(GPIO_CKEn,true);
        GPIO_Init(&GPIO_InitStru);
        
        //Enable Uart Flow
        UART_AutoFlow(UART0,true);   
        GPIO_WriteBit(TestUartCstPin,0);       
        urtprf("U0 Flow\n");
        for(uint16_t i=0 ;i<800;i++);
        GPIO_WriteBit(TestUartCstPin,1); 
        UART_SetUWriteHandle(UART0_Write_handle);
        urtprf("U0 Flow ok\n");
         
    }
    for(uint16_t i=0 ;i<3000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;

}




bool cmd_VerifyAppUART0Case3(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    verify_SendCid(cmd,&idx);
    urtprf("UART0 App case3\r\n");
    //UART_DeInit(UART0);
    Verrify_SendPinConnect(GPIO_UART0_EN);
    {
        GPIO_InitInfo_Type GPIO_InitStru;

        GPIO_InitStru.dir           = GPOP_DIR_OUT;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;
        GPIO_InitStru.pin   = TestUartCstPin;
        SystemDevClockCtl(GPIO_CKEn,true);
        GPIO_Init(&GPIO_InitStru);
        
        GPIO_WriteBit(TestUartCstPin,0);          
        //Enable Uart Flow
        UART_AutoFlow(UART0,true);       
        urtprf("Uart0 Flow\n");
        UART_SetRts(UART0,false);
        for(uint16_t i=0 ;i<800;i++);
        UART_SetRts(UART0,true);
        for(uint16_t i=0 ;i<800;i++);
        GPIO_WriteBit(TestUartCstPin,1);          
        UART_SetUWriteHandle(UART0_Write_handle);
        urtprf("Test Uart0 Flow \n");        
    }
    for(uint16_t i=0 ;i<3000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;

}

bool cmd_VerifyAppUART0Case4(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    verify_SendCid(cmd,&idx);
    urtprf("UART0 App case4\r\n");
    {
        SCU_UART0ClkSelect(CLK_OSC_26M);
        MCU_Sleep(2);
        urtprf("UART0 SWITCH 1\r\n");
        urtprf("UART0 SWITCH 2\r\n");
        urtprf("UART0 SWITCH 3\r\n");
    }
   
    for(uint16_t i=0 ;i<3000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;

}


bool cmd_VerifyAppUART0Case5(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    verify_SendCid(cmd,&idx);
    urtprf("UART0 App case5\r\n");
    {
        PADConfig_Type PAG_InitStru;
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));  
        
        for(uint16_t mode =0;mode<=5;mode++)
        {
            
            PAG_InitStru.pad_ctl    = mode;
            SystemPADConfig(PADID0,&PAG_InitStru);
            SystemPADConfig(PADID1,&PAG_InitStru);
            urtprf("UART0 PAD CTL %d Mode\r\n",mode);
            while(UART_GetStatus(UART0)&0x01);
            MCU_Sleep(1);
            
            PAG_InitStru.pad_ctl    = PAD_MODE1;
            SystemPADConfig(PADID1,&PAG_InitStru);
            
            while(UART_GetStatus(UART0)&0x01);
            MCU_Sleep(1);
            urtprf("UART0 only TX\r\n");
            while(UART_GetStatus(UART0)&0x01);
            MCU_Sleep(1);
            
            PAG_InitStru.pad_ctl    = mode;
            SystemPADConfig(PADID0,&PAG_InitStru);
            SystemPADConfig(PADID1,&PAG_InitStru);
            PAG_InitStru.pad_ctl    = PAD_MODE1;
            SystemPADConfig(PADID0,&PAG_InitStru);
            
            while(UART_GetStatus(UART0)&0x01);
            MCU_Sleep(1);
            urtprf("UART0 only RX\r\n");
            while(UART_GetStatus(UART0)&0x01);
            MCU_Sleep(1);
            
            PAG_InitStru.pad_ctl    = mode;
            SystemPADConfig(PADID0,&PAG_InitStru);
            SystemPADConfig(PADID1,&PAG_InitStru);       
            urtprf("UART0 completed\r\n");
            while(UART_GetStatus(UART0)&0x01);
            MCU_Sleep(1);
        }
    }
   
    for(uint16_t i=0 ;i<3000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;

}




bool cmd_VerifyAppUART1Case1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    urtprf("UART1 App case1\r\n");
    verify_SendCid(cmd,&idx);
    {
        UART_InitInfo_Type UART_InitStru;
        PADConfig_Type PAG_InitStru;
        
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID15,&PAG_InitStru);
        SystemPADConfig(PADID16,&PAG_InitStru);

        SystemDevClockCtl(UART1_CKEn,true);
        
        UART_InitStru.UART_BaudRate = 921600;
        UART_InitStru.UART_WordLength = UART_WL_8BITS;
        UART_InitStru.UART_StopBits = UART_SB_1BIT;
        UART_InitStru.UART_ParityMode = UART_PM_NONE;
        UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
        UART_InitStru.UART_FIFOMode = UART_FM_ENABLE;
        UART_InitStru.UART_DMAMode = UART_DM_MODE_0;
        UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
        UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;        

        Verrify_SendPinConnect(UART1_OUTPUT);
        SystemDevClockCtl(UART1_CKEn,true);
        UART_Init(UART1, &UART_InitStru);
        UART_InterruptSet(UART1,0x01ul<<UART_ERBFI);
        NVIC_ClearPendingIRQ(UART1_IRQn);
        NVIC_EnableIRQ(UART1_IRQn);       
        cm_printf_Uart1("UART1 Verify Output\r\n");
        sut = Verify_SendAppStep(BRCASE_STOP1,0xFF);
    }
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;


}


//static uint8_t buf[128] = {0};
//static uint8_t index_uart1=0;
//static uint8_t Uart1_Int_Flag=0;
bool cmd_VerifyAppUART1Case2(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    urtprf("U1 App Case2\n");
    verify_SendCid(cmd,&idx);
    for(uint32_t i=0;i<300;i++);
    Verrify_SendPinConnect(UART0_UART1_EN);
    Verrify_SendPinConnect(UART1_OUTPUT);
    {
        UART_InitInfo_Type UART_InitStru;
        PADConfig_Type PAG_InitStru;
        memset(&PAG_InitStru, 0,sizeof(PADConfig_Type));
        memset(&UART_InitStru,0,sizeof(UART_InitInfo_Type));
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID15,&PAG_InitStru);
        SystemPADConfig(PADID16,&PAG_InitStru);

        UART_InitStru.UART_BaudRate             = 115200;
        UART_InitStru.UART_WordLength           = UART_WL_8BITS;
        UART_InitStru.UART_StopBits             = UART_SB_1BIT;
        UART_InitStru.UART_ParityMode           = UART_PM_NONE;
        UART_InitStru.UART_HardwareFlowControl  = UART_FC_NONE;
        UART_InitStru.UART_FIFOMode             = UART_FM_ENABLE;
        UART_InitStru.UART_DMAMode              = UART_DM_MODE_0;
        UART_InitStru.UART_TX_FIFOTriggerMode   = UART_TT_EMPTY;
        UART_InitStru.UART_RX_FIFOTriggerMode   = UART_RT_1_CHARACTER;  
    
        SystemDevClockCtl(UART1_CKEn,true);
        UART_Init(UART1, &UART_InitStru);
        UART_InterruptSet(UART1,0x01ul<<UART_ERBFI);
        NVIC_ClearPendingIRQ(UART1_IRQn);
        NVIC_EnableIRQ(UART1_IRQn); 
       
        cm_printf_Uart1("Uart1->Uart0\r\n");
        while(UART_GetStatus(UART0)& 0x01);        
        UART_Init(UART0, &UART_InitStru); 
        urtprf("56789\n");
        
    }
    for(uint32_t i=0;i<5000;i++);
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;


}

bool cmd_VerifyAppUART1Case3(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    urtprf("UART1 App case3\r\n");
    verify_SendCid(cmd,&idx);
    for(uint32_t i=0;i<300;i++);
    Verrify_SendPinConnect(UART0_UART1_EN);
    Verrify_SendPinConnect(UART1_OUTPUT);
    {
        
        UART_InitInfo_Type UART_InitStru;
        PADConfig_Type PAG_InitStru;
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID15,&PAG_InitStru);
        SystemPADConfig(PADID16,&PAG_InitStru);
        
        UART_InitStru.UART_ParityMode = UART_PM_NONE;
        UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
        
        UART_InitStru.UART_DMAMode = UART_DM_MODE_0;
        
        SystemDevClockCtl(UART1_CKEn,true);
        
        for(UART_StopBits_Type sbt =UART_SB_1BIT;sbt<=UART_SB_1_5_2BITS;sbt++)
        {
            UART_InitStru.UART_StopBits = sbt;
            for(uint32_t brt=115200;brt<500000;brt+=100000)
            {
                UART_InitStru.UART_BaudRate=brt;
                for(UART_RXFIFOTriggerMode_Type rfm=UART_RT_1_CHARACTER;rfm<=UART_RT_2_LESS;rfm++)
                {
                    UART_InitStru.UART_RX_FIFOTriggerMode = rfm;
                    for(UART_TXFIFOTriggerMode_Type tfm=UART_TT_EMPTY;tfm<=UART_TT_HALF;tfm++)
                    {
                        UART_InitStru.UART_TX_FIFOTriggerMode = tfm;
                        for(UART_FIFOMode_Type fm=UART_FM_ENABLE;fm<=UART_FM_ENABLE;fm++)
                        {
                            UART_InitStru.UART_FIFOMode = fm;
                            for(UART_WordLength_Type wl = UART_WL_8BITS;wl<UART_WL_9BITS;wl++)
                            {
                                UART_InitStru.UART_WordLength = wl;
                                while(UART_GetStatus(UART1)&0x01);
                                UART_Init(UART1, &UART_InitStru);
                                UART_InterruptSet(UART1,0x01ul<<UART_ERBFI);
                                UART_InterruptSet(UART1,0x01ul<<UART_ElSI);
                                
                                NVIC_ClearPendingIRQ(UART1_IRQn);
                                NVIC_EnableIRQ(UART1_IRQn); 
                                cm_printf_Uart1("Uart1->Uart0\r\n");
                                
                                while(UART_GetStatus(UART0)& 0x01);        
                                UART_Init(UART0, &UART_InitStru); 
                                urtprf("5689\n");
                            }
                        }
                    }
                }
            }  
        }
    }
        
    for(uint16_t i=0;i<5000;i++);
    
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}

GPIO_PinId_Type TestUart1CstPin = GPIO_PIN_25;

void  UART1_Write_handle(void)
{
    for(uint16_t i=0 ;i<800;i++);
    GPIO_WriteBit(TestUart1CstPin,0); 
}


bool cmd_VerifyAppUART1Case4(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    verify_SendCid(cmd,&idx);
    urtprf("UART1 App flow control case4\r\n");
    UART_DeInit(UART0);
    Verrify_SendPinConnect(GPIO_UART0_EN);
    {
        GPIO_InitInfo_Type GPIO_InitStru;
        UART_InitInfo_Type UART_InitStru;
        PADConfig_Type PAG_InitStru;
        
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID15,&PAG_InitStru);
        SystemPADConfig(PADID16,&PAG_InitStru);
        
        SystemPADConfig(PADID27,&PAG_InitStru);
        SystemPADConfig(PADID28,&PAG_InitStru);
       
        UART_InitStru.UART_BaudRate = 500000;
        UART_InitStru.UART_WordLength = UART_WL_8BITS;
        UART_InitStru.UART_StopBits = UART_SB_1BIT;
        UART_InitStru.UART_ParityMode = UART_PM_NONE;
        UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
        UART_InitStru.UART_FIFOMode = UART_FM_ENABLE;
        UART_InitStru.UART_DMAMode = UART_DM_MODE_0;
        UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
        UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;  
           
        SystemDevClockCtl(UART1_CKEn,true);
        
        UART_Init(UART1, &UART_InitStru);

        GPIO_InitStru.dir           = GPOP_DIR_OUT;
        GPIO_InitStru.mode          = GPIO_MODE_SOFTWARE;//Cannot Set//
        GPIO_InitStru.int_en        = DISABLE;
        GPIO_InitStru.int_unmask    = DISABLE;
        GPIO_InitStru.int_type      = GPIO_INTTYPE_LEVEL;
        GPIO_InitStru.int_pol       = GPIO_INTPOL_ACTIVELOW;
        GPIO_InitStru.debounce_en   = DISABLE;
        GPIO_InitStru.pin   = TestUart1CstPin;
        SystemDevClockCtl(GPIO_CKEn,true);
        GPIO_Init(&GPIO_InitStru);
        
        GPIO_WriteBit(TestUart1CstPin,0);          
    
        //Enable Uart Flow
        UART_AutoFlow(UART1,true);       
        cm_printf_Uart1("Uart1 Flow\n");
        UART_SetRts(UART1,false);
        for(uint16_t i=0 ;i<800;i++);
        UART_SetRts(UART1,true);
        for(uint16_t i=0 ;i<800;i++);
        GPIO_WriteBit(TestUart1CstPin,1);          
        UART_SetUWriteHandle(UART1_Write_handle);
        cm_printf_Uart1("Test Uart1 Flow \n");        
        urtprf("Test Uart1 Flow \n");        
    }
    for(uint16_t i=0 ;i<3000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;

}
bool cmd_VerifyAppUART1Case5(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    verify_SendCid(cmd,&idx);
    urtprf("UART1 App case5\r\n");
    while(UART_GetStatus(UART0)&0x01);
    Verrify_SendPinConnect(UART1_OUTPUT);
    {
        UART_InitInfo_Type UART_InitStru;
        PADConfig_Type PAG_InitStru;
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
       
        UART_InitStru.UART_BaudRate = 500000;
        UART_InitStru.UART_WordLength = UART_WL_8BITS;
        UART_InitStru.UART_StopBits = UART_SB_1BIT;
        UART_InitStru.UART_ParityMode = UART_PM_NONE;
        UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
        UART_InitStru.UART_FIFOMode = UART_FM_ENABLE;
        UART_InitStru.UART_DMAMode = UART_DM_MODE_0;
        UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
        UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;  
           
        SystemDevClockCtl(UART1_CKEn,true);
        UART_Init(UART1, &UART_InitStru);
        
        
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        SystemPADConfig(PADID15,&PAG_InitStru);
        SystemPADConfig(PADID16,&PAG_InitStru);
        PAG_InitStru.pad_ctl    = PAD_MODE0;
        SystemPADConfig(PADID16,&PAG_InitStru);
        
        while(UART_GetStatus(UART1)&0x01);
        MCU_Sleep(1);
        cm_printf_Uart1("UART1 only TX\r\n");
        while(UART_GetStatus(UART1)&0x01);
        MCU_Sleep(1);
        
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        SystemPADConfig(PADID15,&PAG_InitStru);
        SystemPADConfig(PADID16,&PAG_InitStru);
        PAG_InitStru.pad_ctl    = PAD_MODE0;
        SystemPADConfig(PADID15,&PAG_InitStru);
        
        while(UART_GetStatus(UART1)&0x01);
        MCU_Sleep(1);
        cm_printf_Uart1("UART1 only RX\r\n");
        while(UART_GetStatus(UART1)&0x01);
        MCU_Sleep(1);
        
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        SystemPADConfig(PADID15,&PAG_InitStru);
        SystemPADConfig(PADID16,&PAG_InitStru);       
        cm_printf_Uart1("UART1 completed\r\n");
    }
   
    for(uint16_t i=0 ;i<3000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;

}





bool UART0_Rx_flag=0;
bool cmd_VerifyDualAppUART0Case1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    verify_SendCid(cmd,&idx);
    urtprf("UART0 Dual App case1\n");
    while(UART_GetStatus(UART0)& 0x01); 
    Verrify_SendPinConnect(UART1_OUTPUT);
    {
        UART_InitInfo_Type UART_InitStru;
        PADConfig_Type PAG_InitStru;
        SystemDevClockCtl(UART1_CKEn,true);
        memset(&PAG_InitStru,0,sizeof(PADConfig_Type));
        PAG_InitStru.pad_ctl            = PAD_MODE1;       
        SystemPADConfig(PADID15,&PAG_InitStru);
        SystemPADConfig(PADID16,&PAG_InitStru);
        
        UART_InitStru.UART_BaudRate             = 500000;
        UART_InitStru.UART_WordLength           = UART_WL_8BITS;
        UART_InitStru.UART_StopBits             = UART_SB_1BIT;
        UART_InitStru.UART_ParityMode           = UART_PM_NONE;
        UART_InitStru.UART_HardwareFlowControl  = UART_FC_NONE;
        UART_InitStru.UART_FIFOMode             = UART_FM_ENABLE;
        UART_InitStru.UART_DMAMode              = UART_DM_MODE_0;
        UART_InitStru.UART_TX_FIFOTriggerMode   = UART_TT_EMPTY;
        UART_InitStru.UART_RX_FIFOTriggerMode   = UART_RT_1_CHARACTER;        
        UART_Init(UART1, &UART_InitStru);
    }
    {
#if defined(BR_MASTER) || defined(BR_SLAVE)       
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif
        {
            uint32_t cd=0,va=0;
            Verify_messageReceive(&cd,&va);
            if(!(cd == BRCASE_STOP1 && va == 1))
                sut =false;
            cm_printf_Uart1("UART0 master[%d] Send\n",sut);
            Verrify_SendPinCon(0xe004);
            if(sut)   
            {
                urtprf("Master Uart0->Uart0\n");
            }
        }  
#endif
      
#ifdef BR_SLAVE   
#ifdef BR_DUAL
        if(!GetSocRole())
#endif    
        {        
            UART0_Rx_flag=1;
            cm_printf_Uart1("UART0 Slave\n");
            while(UART_GetStatus(UART0)&0x01);
            UART_InterruptSet(UART0,0x01ul<<UART_ERBFI);
            NVIC_ClearPendingIRQ(UART0_IRQn);
            NVIC_EnableIRQ(UART0_IRQn);
            cm_printf_Uart1("UART0 NVC Re\n");
            Verrify_SendPinCon(0xe004);
            Verify_messageSend(BRCASE_STOP1,true); 
        }
         
#endif
#endif
}
    for(uint16_t i=0 ;i<3000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;

}



bool cmd_VerifyDualAppUART1Case1(uint32_t cmd, uint8_t *param_line,uint16_t len)
{
    bool sut = true;
    uint32_t idx=0;
    verify_SendCid(cmd,&idx);
    urtprf("UART1 Dual App case1\r\n");
    {
#if defined(BR_MASTER) || defined(BR_SLAVE)       
        UART_InitInfo_Type UART_InitStru;
        PADConfig_Type PAG_InitStru;
        
        PAG_InitStru.set        = 0;
        PAG_InitStru.ie         = PAD_IE_ENABLE;
        PAG_InitStru.oen        = PAD_OEN_ENABLE;
        PAG_InitStru.ren        = PAD_REN_ENABLE;
        PAG_InitStru.pad_ctl    = PAD_MODE1;
        
        SystemPADConfig(PADID15,&PAG_InitStru);
        SystemPADConfig(PADID16,&PAG_InitStru);
       
        UART_InitStru.UART_BaudRate = 500000;
        UART_InitStru.UART_WordLength = UART_WL_8BITS;
        UART_InitStru.UART_StopBits = UART_SB_1BIT;
        UART_InitStru.UART_ParityMode = UART_PM_NONE;
        UART_InitStru.UART_HardwareFlowControl = UART_FC_NONE;
        UART_InitStru.UART_FIFOMode = UART_FM_ENABLE;
        UART_InitStru.UART_DMAMode = UART_DM_MODE_0;
        UART_InitStru.UART_TX_FIFOTriggerMode = UART_TT_EMPTY;
        UART_InitStru.UART_RX_FIFOTriggerMode = UART_RT_1_CHARACTER;  
           
        SystemDevClockCtl(UART1_CKEn,true);
        
        UART_Init(UART1, &UART_InitStru);
        UART_InterruptSet(UART1,0x01ul<<UART_ERBFI);
        NVIC_ClearPendingIRQ(UART1_IRQn);
        NVIC_EnableIRQ(UART1_IRQn); 
#ifdef BR_MASTER
#ifdef BR_DUAL
        if(GetSocRole())
#endif  
        {
            Verify_messageSend(BRCASE_STOP2,true);  
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP1 && va == 1))
                    sut =false;
                urtprf("UART1 master[%d]\r\n",sut);
                if(sut)   
                    cm_printf_Uart1("Uart1->Uart0\r\n");
            }
        } 
#endif
      
#ifdef BR_SLAVE  
#ifdef BR_DUAL
        if(!GetSocRole())
#endif 
        {        
            Verify_messageSend(BRCASE_STOP1,true); 
            {
                uint32_t cd=0,va=0;
                Verify_messageReceive(&cd,&va);
                if(!(cd == BRCASE_STOP2 && va == 1))
                    sut =false;
                urtprf("UART1 Slave[%d]\r\n",sut);
                if(sut)   
                    cm_printf_Uart1("Uart1->Uart0\r\n");
            }     
        }            
#endif
#endif
    }
    
    for(uint16_t i=0;i<10000;i++);
    Verify_SendCResult(BRCASE_RESULT,sut);
    return sut;
}



void UART0_IRQHandler(void)
{ 
#ifdef BR_SLAVE
#ifdef BR_DUAL
    if(!GetSocRole())
#endif 
    {
        if(UART0_Rx_flag)
        {
            if (UART_LSRCheckBits(UART0, UART_LSR_BIT_DR)) 
            {
                uint8_t data = UART_ReadByte(UART0);
                UART_WriteData(UART1,&data,1);
            }
        }
    }
#endif   
    if(UART_GetInterruptID(UART0) == BUSY_DETECT)  
    {
        UART_GetStatus(UART0);
    } 
#ifdef BR_FPGA

    if (UART_LSRCheckBits(UART0, UART_LSR_BIT_DR)) 
    {
        uint8_t data = UART_ReadByte(UART0);
        UART0_Handle(data);
        
    }
#endif

}


void UART1_IRQHandler(void)
{ 
    if (UART_LSRCheckBits(UART1, UART_LSR_BIT_DR)) 
    {   
#if !(defined(BR_MASTER) || defined(BR_SLAVE))   
        //cm_printf_Uart1("[%X]\n",UART_ReadByte(UART1));       
        uint8_t data = UART_ReadByte(UART1);
        UART_WriteData(UART1,&data,1);       
#else
        uint8_t data = UART_ReadByte(UART1);
        UART_WriteData(UART0,&data,1);   
#endif
    } 
    if(UART_GetInterruptID(UART1) == BUSY_DETECT)  
    {
        UART_GetStatus(UART1);
    }        
}




