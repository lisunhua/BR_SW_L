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

extern struct uart_hci_stru *uart_get_stru(void);
#define HCI_FAKE_CMD_DISPATCH(op, par) hci_cmd_received(op, sizeof(par), par)

struct uart_hci_stru {
    rwip_eif_callback rx_callback;
    void *rx_dummy;
    uint8_t *rx_buf;
    uint32_t rx_size;
    uint32_t rx_off;

    rwip_eif_callback tx_callback;
    void *tx_dummy;
    uint8_t *tx_buf;
    uint32_t tx_size;
    uint32_t tx_off;
};

struct boot_driver_stru {
    void (*func)(void const *);
    void const *param;
};


//-------------------------------------------------------------------------------
struct boot_driver_stru s_boot_driver_list[];

void v_uart0_drv_init(void const *param)
{
    PADConfig_Type pad_config;
    memset(&pad_config,0,sizeof(PADConfig_Type));

    SystemUART0SCLKSelCtl(UART0_SC_OSC26M);
    SystemDevClockCtl(CLK_EN_UART0, ENABLE);
    SystemDevRstCtl(RST_UART0);
    delay_us(10); //Delay to make sure reset is released

    pad_config.mode = PAD_MD_0;
    SystemPADConfig(PADID0, &pad_config);
    SystemPADConfig(PADID1, &pad_config);
    
    UART_Init(UART0, (UART_InitInfo_Type const *)param);
    NVIC_SetPriority(UART0_IRQn, 1);
    NVIC_EnableIRQ(UART0_IRQn);
    NVIC_ClearPendingIRQ(UART0_IRQn);
}

static void v_sys_drv_init(void const *param)
{
#if !(__FPGA_VER__)
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
    System32KClockUpdateType(LCT_OSC_24MDIV,750);//750/* 32000 */);
    SystemCoreClockUpdateType(CCT_PLL_24M);
#endif
}


void v_uart_write(uint8_t *bufptr, uint32_t size, rwip_eif_callback callback, void* dummy)
{
    struct uart_hci_stru *s_uart_hci =  uart_get_stru();
    s_uart_hci->tx_buf = bufptr;
    s_uart_hci->tx_size = size;
    s_uart_hci->tx_off = 0;
    s_uart_hci->tx_dummy = dummy;
    s_uart_hci->tx_callback = callback;
}


extern void (*g_uart_start)(bool reset);
extern void (*g_SystemClockEnterLowPower)(bool enable);
extern void (*g_uart_write)(uint8_t *bufptr, uint32_t size, rwip_eif_callback callback, void* dummy);

void VerifyInit(void){
    s_boot_driver_list[0].func   = v_sys_drv_init;
    s_boot_driver_list[4].func   = v_uart0_drv_init;
    g_uart_write                 = v_uart_write;
}

void VerifyMain(uint32_t count)
{
    VerifyDualGetRoleHandler();

    if (count == 10) 
    {
        {
            uint8_t param[] = {0x01};
            HCI_FAKE_CMD_DISPATCH(HCI_WR_SEC_CON_HOST_SUPP_CMD_OPCODE, param);
        }
        {
            uint8_t param[] = {0x30, 0x00};
            HCI_FAKE_CMD_DISPATCH(HCI_WR_PAGE_TO_CMD_OPCODE, param);
        }
        {
            uint8_t param[] = { 0xA0, 0x00 };
            HCI_FAKE_CMD_DISPATCH(HCI_WR_CON_ACCEPT_TO_CMD_OPCODE, param);
        }
        if(GetSocRole())
        {   
            uint8_t param[] = {
                0x01, 0x23, 0x45, 0x83, 0x15, 0x00, // BD
                0x18, 0xCC,                         // Packet_Type
                0x00,                               // Page_Scan_Repetition_Mode
                0x00,                               // Reserved
                0x00, 0x00,                         // Clock_Offset
                0x01,                               // Allow_Role_Switch
            };
            HCI_FAKE_CMD_DISPATCH(HCI_CREATE_CON_CMD_OPCODE, param);
            co_printf("Create Conn\r\n");    
        }else
        { 
           {
                uint8_t param[] = {0x12, 0x00, 0x12, 0x00};
                HCI_FAKE_CMD_DISPATCH(HCI_WR_PAGE_SCAN_ACT_CMD_OPCODE, param);
                co_printf("Page Act SET\r\n");
            }
            {
                uint8_t param[] = {0x02};
                HCI_FAKE_CMD_DISPATCH(HCI_WR_SCAN_EN_CMD_OPCODE, param);
                co_printf("Page Scan EN\r\n");
            }      
        }
    }
    //HCI CMD HANDLE
    {
        struct uart_hci_stru *s_uart_hci =  uart_get_stru();

        if (s_uart_hci->tx_buf && s_uart_hci->tx_size) {
            uint8_t flag =1;
            while (s_uart_hci->tx_off < s_uart_hci->tx_size) {
                if(flag){
                	if(GetSocRole())
                    	co_printf("HCI->CLT:[");
                    else
                    	co_printf("HCI->SVR:[");
                }
                flag=0;
                co_printf("%02X ", *(s_uart_hci->tx_buf + s_uart_hci->tx_off));
                s_uart_hci->tx_off++;
            }
            if(!flag)
                co_printf("]\r\n");
            
            if (s_uart_hci->tx_callback) {
                s_uart_hci->tx_callback(s_uart_hci->tx_dummy, RWIP_EIF_STATUS_OK);
            }

            if (*s_uart_hci->tx_buf == HCI_EVT_MSG_TYPE) {
                switch (*(s_uart_hci->tx_buf + 0x01)) {
                    case HCI_CON_REQ_EVT_CODE: {             //connection request Event
                        uint8_t param[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
                        memcpy(param, (s_uart_hci->tx_buf + 3), 6);
                        HCI_FAKE_CMD_DISPATCH(HCI_ACCEPT_CON_REQ_CMD_OPCODE, param);
                        co_printf("Acc Con Req\r\n");
                        break;
                    }
                    case HCI_CON_CMP_EVT_CODE: {    //Connection Completed
                        co_printf("Conn Cmpl\r\n");
                        if (*(s_uart_hci->tx_buf + 0x03) != CO_ERROR_NO_ERROR)
                        {
                            log_error("Conn Fail! Status:%02X\r\n", *(s_uart_hci->tx_buf + 0x02));
                        }
                        
                        if(GetSocRole())
                        {
                            uint8_t param[] = {0x00, 0x00, 0x01};
                            memcpy(param, (s_uart_hci->tx_buf + 4), 2);
                            HCI_FAKE_CMD_DISPATCH(HCI_SET_CON_ENC_CMD_OPCODE, param);
                            co_printf("Set Conn Enc\r\n");
                        }
                        break;
                    }
                    case HCI_LK_REQ_EVT_CODE: {  //request Link Key
                        uint8_t param[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                                            0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
                        memcpy(param, (s_uart_hci->tx_buf + 3), 6);
                        HCI_FAKE_CMD_DISPATCH(HCI_LK_REQ_REPLY_CMD_OPCODE, param);
                        co_printf("Acc Con Req\r\n");
                        break;
                    }
                    case HCI_ENC_CHG_EVT_CODE: {   //Encryption
                        uint8_t *buf;
                        uint16_t hdl_flags = 0;
                        uint16_t len = 100;

                        if (*(s_uart_hci->tx_buf + 0x03) != CO_ERROR_NO_ERROR)
                        {
                            log_error("Encrypt Fail! Status:%02X\r\n", *(s_uart_hci->tx_buf + 0x02));
                            break;
                        }

                        SETF(hdl_flags, HCI_ACL_HDR_HDL, *((uint16_t *)(s_uart_hci->tx_buf + 4)));
                        SETF(hdl_flags, HCI_ACL_HDR_BC_FLAG, BCF_P2P);
                        SETF(hdl_flags, HCI_ACL_HDR_PB_FLAG, PBF_1ST_NF_HL_FRAG);
                        buf = hci_acl_tx_data_alloc(hdl_flags, len);
                        co_printf("Send Data: ");
                        for (int i = 0; i < len; i++)
                        {
                            buf[i] = (uint8_t)(i & 0xFF);
                        }
                        co_printf("\r\n");
                        hci_acl_tx_data_received(hdl_flags, len, buf);
                        break;
                    }
                    default:
                        break;
                }
            } else if (*s_uart_hci->tx_buf == HCI_ACL_MSG_TYPE) {
                char str[] = {0x04, 0x00};
                co_printf(str);
            }

            s_uart_hci->tx_buf = NULL;
            s_uart_hci->tx_size = 0;
            s_uart_hci->tx_off = 0;
            s_uart_hci->tx_callback = NULL;
        }
    }

}