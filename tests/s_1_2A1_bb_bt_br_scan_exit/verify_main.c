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


void VerifyInit(void){

}


void VerifyMain(uint32_t count)
{
    if (count == 25) {
        struct hci_le_set_ext_adv_param_cmd adv_param;

        /// Advertising handle
        adv_param.adv_hdl = 0x00;
        /// Advertising event properties
        adv_param.adv_evt_properties = ADV_CON | ADV_LEGACY;
        /// Primary advertising minimum interval
        adv_param.prim_adv_intv_min[0] = 0x25;
        adv_param.prim_adv_intv_min[1] = 0x00;
        adv_param.prim_adv_intv_min[2] = 0x00;
        /// Primary advertising maximum interval
        adv_param.prim_adv_intv_max[0] = 0x25;
        adv_param.prim_adv_intv_max[1] = 0x00;
        adv_param.prim_adv_intv_max[2] = 0x00;
        /// Primary advertising channel map
        adv_param.prim_adv_chnl_map = 0x01;
        /// Own address type:  public=0 / random=1 / rpa_or_pub=2 / rpa_or_rnd=3
        adv_param.own_addr_type = 0;
        /// Peer address type: public=0 / random=1
        adv_param.peer_addr_type = 0;
        /// Peer Bluetooth device address
        //adv_param.peer_addr;
        /// Advertising filter policy
        adv_param.adv_filt_policy = 0x00;
        /// Advertising Tx power
        adv_param.adv_tx_pwr = 0x00;
        /// Primary advertising PHY
        adv_param.prim_adv_phy = 0x03;
        /// Secondary advertising max skip
        adv_param.sec_adv_max_skip = 0x00;
        /// Secondary advertising PHY
        adv_param.sec_adv_phy = 0x02;
        /// Advertising SID
        adv_param.adv_sid = 0x00;
        /// Scan request notification enable
        adv_param.scan_req_notif_en = 0x00;

        co_printf("BLE Set Ext ADV Param\r\n");
        hci_le_set_ext_adv_param_cmd_handler(&adv_param, HCI_LE_SET_EXT_ADV_PARAM_CMD_OPCODE);
    }
    else if (count == 30) {
        struct hci_le_set_ext_adv_data_cmd adv_data;

        /// Advertising handle
        adv_data.adv_hdl = 0x00;
        /**
         *  Operation
         *  0x00 Intermediate fragment of fragmented extended advertising data
         *  0x01 First fragment of fragmented extended advertising data
         *  0x02 Last fragment of fragmented extended advertising data
         *  0x03 Complete extended advertising data
         *  0x04 [ID7300_r06] Unchanged data (just update the Advertising DID)
         *  All other values Reserved for future use
         */
        adv_data.operation = 0x00;
        /**
         *  Fragment preference
         *  0x00 The Controller may fragment all Host advertising data
         *  0x01 The Controller should not fragment nor minimize fragmentation of Host advertising data
         *  All other values Reserved for future use
         */
        adv_data.frag_pref = 0x00;
        /// Advertising Data Length (0-252 bytes)
        adv_data.data_len = 0x03;
        /// Advertising data
        adv_data.data[0] = 0x02;
        adv_data.data[1] = 0x01;
        adv_data.data[2] = 0x02;

        co_printf("BLE Set Ext ADV Data\r\n");
        hci_le_set_ext_adv_data_cmd_handler(&adv_data, HCI_LE_SET_EXT_ADV_DATA_CMD_OPCODE);
    }
#if 0
    else if (count == 35) {
        struct hci_le_set_ext_scan_rsp_data_cmd scan_rsp_data;

        /// Advertising handle
        scan_rsp_data.adv_hdl = 0x00;
        /**
         *  Operation
         *  0x00 Intermediate fragment of fragmented extended advertising data
         *  0x01 First fragment of fragmented extended advertising data
         *  0x02 Last fragment of fragmented extended advertising data
         *  0x03 Complete extended advertising data
         *  0x04 [ID7300_r06] Unchanged data (just update the Advertising DID)
         *  All other values Reserved for future use
         */
        scan_rsp_data.operation = ADV_DATA_OP_COMPLETE;
        /**
         *  Fragment preference
         *  0x00 The Controller may fragment all Host advertising data
         *  0x01 The Controller should not fragment nor minimize fragmentation of Host advertising data
         *  All other values Reserved for future use
         */
        scan_rsp_data.frag_pref = 0x00;
        /// Advertising Data Length (0-252 bytes)
        scan_rsp_data.data_len = 0x03;
        /// Advertising data
        scan_rsp_data.data[0] = 0x02;
        scan_rsp_data.data[1] = 0x01;
        scan_rsp_data.data[2] = 0x02;

        co_printf("BLE Set Ext ADV Scan Resp Data\r\n");
        hci_le_set_ext_scan_rsp_data_cmd_handler(&scan_rsp_data, HCI_LE_SET_EXT_SCAN_RSP_DATA_CMD_OPCODE);
    }
#endif
    else if (count == 40) {
        struct hci_le_set_ext_adv_en_cmd adv_en;

        /// Enable
        adv_en.enable = 1;
        /// Number of sets (1 - 0x3F)
        adv_en.nb_sets = 1;
        /// Advertising handle
        adv_en.adv_hdl[0] = 0x00;
        /// Duration (N * 10 ms), 0x0000 No advertising duration. Advertising to continue until the Host disables it.
        adv_en.duration[0] = 0x01;
        /// Maximum number of extended advertising events
        adv_en.max_ext_adv_evt[0] = 0x10;

        co_printf("BLE Set Ext ADV Enable\r\n");
        hci_le_set_ext_adv_en_cmd_handler(&adv_en, HCI_LE_SET_EXT_ADV_EN_CMD_OPCODE);
    }
}