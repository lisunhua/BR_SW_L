#include "boot_bluetooth.h"

#include "rwip_config.h" // RW SW configuration

#include "arch.h"      // architectural platform definitions
#include <stdlib.h>    // standard lib functions
#include <stddef.h>    // standard definitions
#include <stdint.h>    // standard integer definition
#include <stdbool.h>   // boolean definition
#include "rwip.h"      // RW SW initialization
#include "dbg.h"
#include "em_map.h"
#include "nvds.h"
#include "BR8051Axx.h"
#include "uart.h"
#include "dma.h"
#include "verdef.h"
#include "boot_driver.h"
#include "lld.h"

#include "co_hci.h"
#include "hci.h"

#include "rf.h"
#include "ld_test.h"

#include "reg_btcore.h"         // BT core registers
#include "vsimv.h"

struct boot_driver_stru {
    void (*func)(void const *);
    void const *param;
};

struct boot_driver_stru s_boot_driver_list[];

const static UART_InitInfo_Type v_uart0_default_cfg = {
    .UART_BaudRate              = 1800,
    .UART_WordLength            = UART_WL_8BITS,
    .UART_StopBits              = UART_SB_1BIT,
    .UART_ParityMode            = UART_PM_NONE,
    .UART_HardwareFlowControl   = UART_FC_NONE,
    .UART_DMAMode               = UART_DM_MODE_0,
    .UART_FIFOMode              = UART_FM_ENABLE,
    .UART_TX_FIFOTriggerMode    = UART_TT_HALF,
    .UART_RX_FIFOTriggerMode    = UART_RT_1_CHARACTER,
};


extern void uart_irq_handler(void);

void v_uart_start(bool reset)
{
    //Will be re-call!!!!!!!!!
    uint32_t uart_param;
    nvds_tag_len_t uart_length;

    UART_InitInfo_Type uart0_cfg = {
        .UART_BaudRate              = 1800,
        .UART_WordLength            = UART_WL_8BITS,
        .UART_StopBits              = UART_SB_1BIT,
        .UART_ParityMode            = UART_PM_NONE,
        .UART_HardwareFlowControl   = UART_FC_NONE,
        .UART_DMAMode               = UART_DM_MODE_0,
        .UART_FIFOMode              = UART_FM_ENABLE,
        .UART_TX_FIFOTriggerMode    = UART_TT_HALF,
        .UART_RX_FIFOTriggerMode    = UART_RT_1_CHARACTER,
    };
    
    boot_driver_init(1 << BOOT_DRV_BIT_POS_UART0, &uart0_cfg);
    UART0_IRQHandler_Req(uart_irq_handler);

#ifdef ROM_VERSION
    if (!reset) {
        const uint8_t h4_evt[] = {0x04, 0x0F, 0x04, 0x00, 0x01, 0x00, 0x00};
        UART_WriteData(UART0, h4_evt, sizeof(h4_evt));
    }
#endif
    
}

static void v_sys_drv_init(void const *param)
{
    NVIC_SetPriorityGrouping(6);
    SystemDevClockCtl(CLK_EN_RF, ENABLE);  //Enable BB pclk to access BB RFT/Modem REG
    SystemDevClockCtl(CLK_EN_BBP, ENABLE); //Enable BB pclk to access BB RFT/Modem REG
    SystemDevClockCtl(CLK_EN_BBH, ENABLE); //Enable BB hclk to access BB RFT/Modem REG
    SystemDevClockCtl(CLK_EN_BBL, ENABLE); //Enable BB lclk to enable low power support
    delay_us(20); //Delay to make sure clock is stable
    {
         PADConfig_Type pad_config;
         memset(&pad_config,0,sizeof(PADConfig_Type));
         pad_config.mode = PAD_MD_1;
         SystemPADConfig(PADID7, &pad_config);  //external low power clock input; //for tb
         SCU->DATA[1] = 0xE020;                 // TODO  SH //TB Need
    }
    System32KAutoCLKEnCtl(true);
    System32KClockUpdateType(LCT_OSC_32K, 0);
    SystemCoreClockUpdateType(CCT_PLL_24M);
}


void v_SystemClockLowPowerCtlFunc(bool enable)
{
    if (enable) {
        while (!(SCU->DEV_STATUS & (1 << 8))); 
    } 
    if (enable) 
        SystemDevClockCtl(CLK_EN_BBH, DISABLE); 
    // else
    //     SystemDevClockCtl(CLK_EN_BBH, ENABLE);   
}


extern void (*g_uart_start)(bool reset);
extern void (*g_SystemClockEnterLowPower)(bool enable);

void VerifyInit(void){
    s_boot_driver_list[0].func   =  v_sys_drv_init;
    s_boot_driver_list[4].param  =  &v_uart0_default_cfg;

    g_uart_start               = v_uart_start;
   // g_SystemClockEnterLowPower = v_SystemClockLowPowerCtlFunc;
}

void VerifyMain(uint32_t count){
    //VerifyDualGetRoleHandler();
}