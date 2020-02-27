#include "BR00x_config.h"
#include "system_BR00x.h"
#include "BR00x_uart.h"
#include "BR00x_timers.h"
#include "cm_printf.h"


void AppInitUART(void)
{
#ifdef COREMKE
    UART_InitInfo_Type UART_InitStru;
    UART_InitStru.UART_BaudRate             = 500000;
    UART_InitStru.UART_WordLength           = UART_WL_8BITS;
    UART_InitStru.UART_StopBits             = UART_SB_1BIT;
    UART_InitStru.UART_ParityMode           = UART_PM_NONE;
    UART_InitStru.UART_HardwareFlowControl  = UART_FC_NONE;
    UART_InitStru.UART_FIFOMode             = UART_FM_ENABLE;
    UART_InitStru.UART_DMAMode              = UART_DM_MODE_0;
    UART_InitStru.UART_TX_FIFOTriggerMode   = UART_TT_EMPTY;
    UART_InitStru.UART_RX_FIFOTriggerMode   = UART_RT_1_CHARACTER;
     
    UART_Init(UART0, &UART_InitStru); 
#endif
}

void AppInitTIMER_TM0(void)
{
    
#ifdef COREMKE
    TIMER_InitInof_TypeDef TIMER_InitStru;
    NVIC_ClearPendingIRQ(TIMER0_IRQn);
    NVIC_EnableIRQ(TIMER0_IRQn);
    
    TIMER_InitStru.TIMER_PwmValue = 0;
    TIMER_InitStru.TIMER_LoadValue= 0xffffffff;
    TIMER_InitStru.TIMER_InterruptMask= TIMER_INTERRUPT_UNMASKED;
    TIMER_InitStru.TIMER_mode= TIMER_USER_DEFINED;
    TIMER_InitStru.TIMER_Pwd= TIMER_PWM_DISABLE;
    TIMER_InitStru.TIMER_sch= TIMER_ENABLE;
    
    TIMER_InitStru.TIMERx= TM0;
    TIMER_Init(&TIMER_InitStru);
    

#endif    
}
