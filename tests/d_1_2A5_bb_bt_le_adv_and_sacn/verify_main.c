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

void VerifyInit(void){

}


void VerifyMain(uint32_t count)
{
    VerifyDualGetRoleHandler();
    if(GetSocRole())
    {
        if (count == 25) {
            struct hci_le_set_adv_param_cmd adv_param;

            ///Minimum interval for advertising
            adv_param.adv_intv_min = 0x20 + 8;
            ///Maximum interval for advertising
            adv_param.adv_intv_max = 0x20 + 8;
            ///Advertising type
            adv_param.adv_type = ADV_CONN_UNDIR;
            ///Own address type:  public=0 / random=1 / rpa_or_pub=2 / rpa_or_rnd=3
            adv_param.own_addr_type = 0;
            ///Peer address type: public=0 / random=1
            adv_param.peer_addr_type = 0;
            ///Peer Bluetooth device address
            memset(adv_param.peer_addr.addr, 0, BD_ADDR_LEN);
            ///Advertising channel map
            adv_param.adv_chnl_map = 0x07;
            ///Advertising filter policy
            adv_param.adv_filt_policy = 0x00;

            co_printf("BLE Set 1M ADV Param\r\n");
            hci_le_set_adv_param_cmd_handler(&adv_param, HCI_LE_SET_ADV_PARAM_CMD_OPCODE);
        }
        else if (count == 35) {
            struct hci_le_set_adv_data_cmd adv_data;

            adv_data.adv_data_len = 3;
            adv_data.data.data[0] = 0x02;
            adv_data.data.data[1] = 0x01;
            adv_data.data.data[2] = 0x02;

            co_printf("BLE Set 1M ADV Data\r\n");
            hci_le_set_adv_data_cmd_handler(&adv_data, HCI_LE_SET_ADV_DATA_CMD_OPCODE);
        }
        else if (count == 500) {
            struct hci_le_set_adv_en_cmd adv_en;

            adv_en.adv_en = 1;

            co_printf("BLE Set 1M ADV Enable\r\n");
            hci_le_set_adv_en_cmd_handler(&adv_en, HCI_LE_SET_ADV_EN_CMD_OPCODE);
        }
    }
    else
    {
        if (count == 25) {
            struct hci_le_set_scan_param_cmd scan_param;

            scan_param.scan_type = 1;
            scan_param.scan_intv = 6;
            scan_param.scan_window = 4;
            scan_param.own_addr_type = 0;
            scan_param.scan_filt_policy = 0;

            co_printf("BLE Set 1M Scan Param\r\n");
            hci_le_set_scan_param_cmd_handler(&scan_param, HCI_LE_SET_SCAN_PARAM_CMD_OPCODE);
        }
        else if (count == 35) {
            struct hci_le_set_scan_en_cmd scan_en;

            scan_en.scan_en = 1;
            scan_en.filter_duplic_en = 0;

            co_printf("BLE Set 1M Scan Enable\r\n");
            hci_le_set_scan_en_cmd_handler(&scan_en, HCI_LE_SET_SCAN_EN_CMD_OPCODE);
        }
    }

}