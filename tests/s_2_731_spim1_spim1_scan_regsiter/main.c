
#include <stdio.h>
#include "BR00x_uart.h"
#include "BR00x_clock.h"
#include "BR00x_config.h"
#include "verify_message.h"
#include "verify_register_handle.h"
#include "log_uart_config.h"


const RegisterCell SPIM1_RegList[]=
{
//  {read,  write,  Register ID ,register_attr, Register},
    {true,  true,   1,   0x0000F3FC,     &SPIM1->CTRLR0},
    {true,  true,   2,   0x000000FF,     &SPIM1->CTRLR1},
//    {true,  true,   3,   0x00000001,     &SPIM1->SSIENR},//Enable Bit Cannot set
    {true,  true,   4,   0x00000007,     &SPIM1->MWCR},//SSIC_IS_MASTER == 1 
    {true,  true,   5,   0x00000001,     &SPIM1->SER},//SSIC_NUM_SLAVES == 1
    {true,  true,   6,   0x0000FFFE,     &SPIM1->BAUDR},
    {true,  true,   7,   0x00000007,     &SPIM1->TXFTLR},// TX_ABW=2
    {true,  true,   8,   0x00000007,     &SPIM1->RXFTLR},// TX_ABW=2
    {true,  false,  9,   0x00000007,     (volatile uint32_t*)&SPIM1->TXFLR}, // TX_ABW=2
    {true,  false,  10,  0x00000007,     (volatile uint32_t*)&SPIM1->RXFLR}, // TX_ABW=2
    {true,  false,  11,  0x00000007,     (volatile uint32_t*)&SPIM1->SR},
    {true,  true,   12,  0x0000003F,     &SPIM1->IMR},
    {true,  false,  13,  0x0000003F,     (volatile uint32_t*)&SPIM1->ISR},
    {true,  false,  14,  0x0000003F,     (volatile uint32_t*)&SPIM1->RISR},
    //Read Clear Interrupt
    {true,  false,  15,  0x00000001,     (volatile uint32_t*)&SPIM1->TXOICR},
    {true,  false,  16,  0x00000001,     (volatile uint32_t*)&SPIM1->RXOICR},
    {true,  false,  17,  0x00000001,     (volatile uint32_t*)&SPIM1->RXUICR},
    {true,  false,  18,  0x00000001,     (volatile uint32_t*)&SPIM1->MSTICR},
    {true,  false,  19,  0x00000001,     (volatile uint32_t*)&SPIM1->ICR},
    
//    {true,  true,   20,  0x00000003,     (volatile uint32_t*)&SPIM1->DMACR},
//    {true,  true,   21,  0x00000007,     &SPIM1->DMATDLR}, // TX_ABW=2
//    {true,  true,   22,  0x00000007,     &SPIM1->DMARDLR}, // TX_ABW=2
    
    {true,  true,   23,  0xFFFFFFFF,     &SPIM1->DR[0]}, // TX_ABW=2
   
};


int main (void)
{
    sysTimeUpdataClk(SystemCoreClock);
    Verrify_SendPinConnect(UART0_OUTPUT);
    LOGUartInit();
    c_printf("s_2_731_spim1_spim1_scan_regsiter case \r\n");
    {
        bool sut = true;
        uint32_t idx=0;
        SystemDevClockCtl(SPIM1_CKEn,true);
        SPIM1->SSIENR = DISABLE;
        sut =Verify_RegisterHandle(SPIM1_RegList,sizeof(SPIM1_RegList),idx);
	
	Verify_SendCResult(BRCASE_RESULT,sut);
    }
    SimulationEnd();
    while(1){     
    };
}
















