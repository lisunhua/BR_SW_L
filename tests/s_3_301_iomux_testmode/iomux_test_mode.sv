//Automatically generate file.

`include "inputs/soc_top/sim/tb/inc/chip_def.inc"

task iomux_all_testmode;
    reg func_in_error;
    reg func_out_error;
    reg scan_in_error;
    reg scan_out_error;
    reg mbist_in_error;
    reg mbist_out_error;
    reg bsd_in_error;
    reg bsd_out_error;

    func_in_error = 0;
    func_out_error = 0;
    scan_in_error = 0;
    scan_out_error = 0;
    mbist_in_error = 0;
    mbist_out_error = 0;
    bsd_in_error = 0;
    bsd_out_error = 0;
    

//======================func test=====================

    //Enbale Test mode
    force `DUT_XRM.TEST = 1;
    force `DUT_XRM.GPIO[22:20]        = 0; //0--func mode,4--scan mode, 5--mbist mode,6--bsd mode
    #10
    check_in_testmode (1'b1,`DUT_XRM.GPIO[29],func_in_error,"GPIO[29]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[30],func_in_error,"GPIO[30]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[31],func_in_error,"GPIO[31]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[32],func_in_error,"GPIO[32]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[33],func_in_error,"GPIO[33]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[34],func_in_error,"GPIO[34]  _INPUT");
    #10
//======================  I ========================
    force `DUT_XRM.GPIO[29]  = $urandom;
    force `DUT_XRM.GPIO[30]  = $urandom;
    force `DUT_XRM.GPIO[31]  = $urandom;
    force `DUT_XRM.GPIO[32]  = $urandom;
    force `DUT_XRM.GPIO[33]  = $urandom;
    force `DUT_XRM.GPIO[34]  = $urandom;
    #10
    check_in_testmode (`IOMUX_XRM.u_tmmux.func_test_pad2core[29],`DUT_XRM.GPIO[29],func_in_error,"GPIO[29]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.func_test_pad2core[30],`DUT_XRM.GPIO[30],func_in_error,"GPIO[30]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.func_test_pad2core[31],`DUT_XRM.GPIO[31],func_in_error,"GPIO[31]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.func_test_pad2core[32],`DUT_XRM.GPIO[32],func_in_error,"GPIO[32]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.func_test_pad2core[33],`DUT_XRM.GPIO[33],func_in_error,"GPIO[33]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.func_test_pad2core[34],`DUT_XRM.GPIO[34],func_in_error,"GPIO[34]  _INPUT");
    #10
    release `DUT_XRM.GPIO[29] ;
    release `DUT_XRM.GPIO[30] ;
    release `DUT_XRM.GPIO[31] ;
    release `DUT_XRM.GPIO[32] ;
    release `DUT_XRM.GPIO[33] ;
    release `DUT_XRM.GPIO[34] ;
    if (func_in_error !== 0)
        $display("func mode input test FAIL");
    else
        $display("func mode input test PASS");
//======================  O ========================

    release   `DUT_XRM.GPIO[19:0];
    release   `DUT_XRM.GPIO[34:23];
    force `UART0_XRM.sout  = $urandom;
    force `CLK_XRM.pclk_en  = $urandom;
    force `ANATOP_XRM.RCO_32K_BB  = $urandom;
    force `ANA_XRM.CLK_26M_OUT  = $urandom;
    force `ANATOP_XRM.POR_BB  = $urandom;
    force `ANATOP_XRM.LVD_BB  = $urandom;
    force `ANATOP_XRM.DPLL_LOCK  = $urandom;
    force `ANATOP_XRM.DPLL_OUT_192M_TEST  = $urandom;
    force `ANATOP_XRM.DPLL_OUT_24M  = $urandom;
    force `QL_XRM.RESETN_RF  = $urandom;
    force `CLK_XRM.pclk_main_test  = $urandom;
    force `CLK_XRM.hclk_main_test  = $urandom;
    force `CLK_XRM.lfclk_main_test  = $urandom;
    force `CLK_XRM.h2p_clk_test  = $urandom;
    force `RST_XRM.hw_rst_n  = $urandom;
    force `RST_XRM.freeclk_rst_n  = $urandom;
    force `ANATOP_XRM.DPLL_OUT_16M  = $urandom;
    force `CLK_XRM.clk_12m_bb  = $urandom;
    force `CLK_XRM.clk_24m_bb  = $urandom;
    force `CLK_XRM.clk_48m_bb  = $urandom;
    #10
    check_in_testmode (`DUT_XRM.GPIO[0],`UART0_XRM.sout,func_out_error,"GPIO[0]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[1],`CLK_XRM.pclk_en,func_out_error,"GPIO[1]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[2],`ANATOP_XRM.RCO_32K_BB,func_out_error,"GPIO[2]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[3],`ANA_XRM.CLK_26M_OUT,func_out_error,"GPIO[3]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[4],`ANATOP_XRM.POR_BB,func_out_error,"GPIO[4]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[5],`ANATOP_XRM.LVD_BB,func_out_error,"GPIO[5]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[6],`ANATOP_XRM.DPLL_LOCK,func_out_error,"GPIO[6]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[7],`ANATOP_XRM.DPLL_OUT_192M_TEST,func_out_error,"GPIO[7]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[10],`ANATOP_XRM.DPLL_OUT_24M,func_out_error,"GPIO[10]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[11],`QL_XRM.RESETN_RF,func_out_error,"GPIO[11]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[14],`CLK_XRM.pclk_main_test,func_out_error,"GPIO[14]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[15],`CLK_XRM.hclk_main_test,func_out_error,"GPIO[15]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[16],`CLK_XRM.lfclk_main_test,func_out_error,"GPIO[16]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[17],`CLK_XRM.h2p_clk_test,func_out_error,"GPIO[17]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[18],`RST_XRM.hw_rst_n,func_out_error,"GPIO[18]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[19],`RST_XRM.freeclk_rst_n,func_out_error,"GPIO[19]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[25],`ANATOP_XRM.DPLL_OUT_16M,func_out_error,"GPIO[25]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[26],`CLK_XRM.clk_12m_bb,func_out_error,"GPIO[26]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[27],`CLK_XRM.clk_24m_bb,func_out_error,"GPIO[27]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[28],`CLK_XRM.clk_48m_bb,func_out_error,"GPIO[28]  _OUTPUT");
    #10
    release `UART0_XRM.sout ;
    release `CLK_XRM.pclk_en ;
    release `ANATOP_XRM.RCO_32K_BB ;
    release `ANA_XRM.CLK_26M_OUT ;
    release `ANATOP_XRM.POR_BB ;
    release `ANATOP_XRM.LVD_BB ;
    release `ANATOP_XRM.DPLL_LOCK ;
    release `ANATOP_XRM.DPLL_OUT_192M_TEST ;
    release `ANATOP_XRM.DPLL_OUT_24M ;
    release `QL_XRM.RESETN_RF ;
    release `CLK_XRM.pclk_main_test ;
    release `CLK_XRM.hclk_main_test ;
    release `CLK_XRM.lfclk_main_test ;
    release `CLK_XRM.h2p_clk_test ;
    release `RST_XRM.hw_rst_n ;
    release `RST_XRM.freeclk_rst_n ;
    release `ANATOP_XRM.DPLL_OUT_16M ;
    release `CLK_XRM.clk_12m_bb ;
    release `CLK_XRM.clk_24m_bb ;
    release `CLK_XRM.clk_48m_bb ;

    if (func_out_error !== 0)
        $display("func mode output test FAIL");
    else
        $display("func mode output test PASS");

    //Disable Test mode
    force `DUT_XRM.TEST = 0;
    #1000;
    

//======================scan test=====================

    //Enbale Test mode
    force `DUT_XRM.TEST = 1;
    force `GPIO_XRM.gpio_intrclk_en = 1'b1 ;
    #10
    force `DUT_XRM.GPIO[22:20]        = 4; //0--func mode,4--scan mode, 5--mbist mode,6--bsd mode
    #10
    check_in_testmode (1'b1,`DUT_XRM.GPIO[29],scan_in_error,"GPIO[29]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[30],scan_in_error,"GPIO[30]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[31],scan_in_error,"GPIO[31]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[32],scan_in_error,"GPIO[32]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[33],scan_in_error,"GPIO[33]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[34],scan_in_error,"GPIO[34]  _INPUT");
    #10
//======================  I ========================
    force `DUT_XRM.GPIO[0]  = $urandom;
    force `DUT_XRM.GPIO[1]  = $urandom;
    force `DUT_XRM.GPIO[2]  = $urandom;
    force `DUT_XRM.GPIO[3]  = $urandom;
    force `DUT_XRM.GPIO[4]  = $urandom;
    force `DUT_XRM.GPIO[5]  = $urandom;
    force `DUT_XRM.GPIO[6]  = $urandom;
    force `DUT_XRM.GPIO[7]  = $urandom;
    force `DUT_XRM.GPIO[8]  = $urandom;
    force `DUT_XRM.GPIO[9]  = $urandom;
    force `DUT_XRM.GPIO[10]  = $urandom;
    force `DUT_XRM.GPIO[11]  = $urandom;
    force `DUT_XRM.GPIO[12]  = $urandom;
    force `DUT_XRM.GPIO[13]  = $urandom;
    force `DUT_XRM.GPIO[23]  = $urandom;
    force `DUT_XRM.GPIO[24]  = $urandom;
    force `DUT_XRM.GPIO[29]  = $urandom;
    force `DUT_XRM.GPIO[30]  = $urandom;
    force `DUT_XRM.GPIO[31]  = $urandom;
    force `DUT_XRM.GPIO[32]  = $urandom;
    force `DUT_XRM.GPIO[33]  = $urandom;
    force `DUT_XRM.GPIO[34]  = $urandom;
    #10
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[0],`DUT_XRM.GPIO[0],scan_in_error,"GPIO[0]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[1],`DUT_XRM.GPIO[1],scan_in_error,"GPIO[1]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[2],`DUT_XRM.GPIO[2],scan_in_error,"GPIO[2]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[3],`DUT_XRM.GPIO[3],scan_in_error,"GPIO[3]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[4],`DUT_XRM.GPIO[4],scan_in_error,"GPIO[4]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[5],`DUT_XRM.GPIO[5],scan_in_error,"GPIO[5]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[6],`DUT_XRM.GPIO[6],scan_in_error,"GPIO[6]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[7],`DUT_XRM.GPIO[7],scan_in_error,"GPIO[7]  _INPUT");
    check_in_testmode (`RST_XRM.test_reset,`DUT_XRM.GPIO[8],scan_in_error,"GPIO[8]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[9],`DUT_XRM.GPIO[9],scan_in_error,"GPIO[9]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[10],`DUT_XRM.GPIO[10],scan_in_error,"GPIO[10]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[11],`DUT_XRM.GPIO[11],scan_in_error,"GPIO[11]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[12],`DUT_XRM.GPIO[12],scan_in_error,"GPIO[12]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[13],`DUT_XRM.GPIO[13],scan_in_error,"GPIO[13]  _INPUT");
    check_in_testmode (`DUT_XRM.scan_test_clock,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[24],`DUT_XRM.GPIO[24],scan_in_error,"GPIO[24]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[29],`DUT_XRM.GPIO[29],scan_in_error,"GPIO[29]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[30],`DUT_XRM.GPIO[30],scan_in_error,"GPIO[30]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[31],`DUT_XRM.GPIO[31],scan_in_error,"GPIO[31]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[32],`DUT_XRM.GPIO[32],scan_in_error,"GPIO[32]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[33],`DUT_XRM.GPIO[33],scan_in_error,"GPIO[33]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.scan_test_pad2core[34],`DUT_XRM.GPIO[34],scan_in_error,"GPIO[34]  _INPUT");
    check_in_testmode (`GPIO_XRM.pclk                          ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_GPIO_XRM.pclk  _INPUT");
    check_in_testmode (`GPIO_XRM.pclk_intr                     ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_GPIO_XRM.pclk_intr  _INPUT");
    check_in_testmode (`GPIO_XRM.dbclk                         ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_GPIO_XRM.dbclk  _INPUT");
    check_in_testmode (`RTC_XRM.PCLK                           ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_RTC_XRM.PCLK  _INPUT");
    check_in_testmode (`RTC_XRM.CLK1HZ                         ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_RTC_XRM.CLK1HZ  _INPUT");
    check_in_testmode (`SCU_XRM.u_apb_eg_slave_interface.pclk  ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SCU_XRM.u_apb_eg_slave_interface.pclk  _INPUT");
    check_in_testmode (`SCU_XRM.u_apb_eg_slave_reg.pclk        ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SCU_XRM.u_apb_eg_slave_reg.pclk  _INPUT");
    check_in_testmode (`SCU_XRM.u_bb_wakeup.pclk               ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SCU_XRM.u_bb_wakeup.pclk  _INPUT");
    check_in_testmode (`SCU_XRM.u_bb_wakeup.lfclk              ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SCU_XRM.u_bb_wakeup.lfclk  _INPUT");
    check_in_testmode (`PMU_XRM.clk                            ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_PMU_XRM.clk  _INPUT");
    check_in_testmode (`BB_XRM.hclk                            ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_BB_XRM.hclk  _INPUT");
    check_in_testmode (`BB_XRM.clk_52m                         ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_BB_XRM.clk_52m  _INPUT");
    check_in_testmode (`BB_XRM.clk_26m                         ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_BB_XRM.clk_26m  _INPUT");
    check_in_testmode (`BB_XRM.clk_13m                         ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_BB_XRM.clk_13m  _INPUT");
    check_in_testmode (`BB_XRM.clk_bb_mem_adc                  ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_BB_XRM.clk_bb_mem_adc  _INPUT");
    check_in_testmode (`BB_XRM.clk_bb_mem_dac                  ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_BB_XRM.clk_bb_mem_dac  _INPUT");
    check_in_testmode (`BB_XRM.clk_bt_adc                      ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_BB_XRM.clk_bt_adc  _INPUT");
    check_in_testmode (`BB_XRM.clk_bt_dac                      ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_BB_XRM.clk_bt_dac  _INPUT");
    check_in_testmode (`BB_XRM.low_power_clk                   ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_BB_XRM.low_power_clk  _INPUT");
    check_in_testmode (`BB_XRM.pclk                            ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_BB_XRM.pclk  _INPUT");
    check_in_testmode (`QL_XRM.CLK_26M_RF                      ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_QL_XRM.CLK_26M_RF  _INPUT");
    check_in_testmode (`QL_XRM.BB_CLK_DAC                      ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_QL_XRM.BB_CLK_DAC  _INPUT");
    check_in_testmode (`QL_XRM.BB_CLK_ADC_mux                  ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_QL_XRM.BB_CLK_ADC_mux  _INPUT");
    check_in_testmode (`SPS1_XRM.pclk                          ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SPS1_XRM.pclk  _INPUT");
    check_in_testmode (`SPS1_XRM.ssi_clk                       ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SPS1_XRM.ssi_clk  _INPUT");
    check_in_testmode (`UART0_XRM.pclk                         ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_UART0_XRM.pclk  _INPUT");
    check_in_testmode (`UART0_XRM.sclk                         ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_UART0_XRM.sclk  _INPUT");
    check_in_testmode (`USB_XRM.hclk                           ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_USB_XRM.hclk  _INPUT");
    check_in_testmode (`USB_XRM.utmi_clk                       ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_USB_XRM.utmi_clk  _INPUT");
    check_in_testmode (`USB_XRM.utmifs_clk48                   ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_USB_XRM.utmifs_clk48  _INPUT");
    check_in_testmode (`M3_XRM.SWCLKTCK                        ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_M3_XRM.SWCLKTCK  _INPUT");
    check_in_testmode (`M3_XRM.FCLK                            ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_M3_XRM.FCLK  _INPUT");
    check_in_testmode (`M3_XRM.HCLK                            ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_M3_XRM.HCLK  _INPUT");
    check_in_testmode (`M3_XRM.TRACECLKIN                      ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_M3_XRM.TRACECLKIN  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.ahb_ds128.HCLK            ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.ahb_ds128.HCLK  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.ahb_to_rom0.HCLK          ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.ahb_to_rom0.HCLK  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.ahb_to_sram0.HCLK         ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.ahb_to_sram0.HCLK  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.ahb_to_sram1.HCLK         ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.ahb_to_sram1.HCLK  _INPUT");
    check_in_testmode (`FLASHC_XRM.HCLK                        ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_FLASHC_XRM.HCLK  _INPUT");
    check_in_testmode (`FLASHC_XRM.PCLKG                       ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_FLASHC_XRM.PCLKG  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_ahb_d.hclk              ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.i_ahb_d.hclk  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_ahb_dma.hclk            ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.i_ahb_dma.hclk  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_ahb_i.hclk              ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.i_ahb_i.hclk  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_ahb_s.hclk              ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.i_ahb_s.hclk  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_apb0.hclk               ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.i_apb0.hclk  _INPUT");
    check_in_testmode (`DMAC_XRM.hclk                          ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_DMAC_XRM.hclk  _INPUT");
    check_in_testmode (`I2C_XRM.pclk                           ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_I2C_XRM.pclk  _INPUT");
    check_in_testmode (`I2SM_XRM.pclk                          ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_I2SM_XRM.pclk  _INPUT");
    check_in_testmode (`I2SM_XRM.sclk                          ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_I2SM_XRM.sclk  _INPUT");
    check_in_testmode (`I2SS_XRM.pclk                          ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_I2SS_XRM.pclk  _INPUT");
    check_in_testmode (`I2SS_XRM.sclk                          ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_I2SS_XRM.sclk  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_apb0.hclk           ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.i_icm_apb0.hclk  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_bb.hclk             ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.i_icm_bb.hclk  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_dma.hclk            ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.i_icm_dma.hclk  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_flash.hclk          ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.i_icm_flash.hclk  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_ram0.hclk           ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.i_icm_ram0.hclk  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_rom0.hclk           ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.i_icm_rom0.hclk  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_usb.hclk            ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SYS_MAIN_XRM.i_icm_usb.hclk  _INPUT");
    check_in_testmode (`SPM0_XRM.hclk                          ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SPM0_XRM.hclk  _INPUT");
    check_in_testmode (`SPM0_XRM.ssi_clk                       ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SPM0_XRM.ssi_clk  _INPUT");
    check_in_testmode (`SPM1_XRM.pclk                          ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SPM1_XRM.pclk  _INPUT");
    check_in_testmode (`SPM1_XRM.ssi_clk                       ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_SPM1_XRM.ssi_clk  _INPUT");
    check_in_testmode (`TIMER_XRM.pclk                         ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_TIMER_XRM.pclk  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_1_clk                  ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_TIMER_XRM.timer_1_clk  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_2_clk                  ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_TIMER_XRM.timer_2_clk  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_3_clk                  ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_TIMER_XRM.timer_3_clk  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_4_clk                  ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_TIMER_XRM.timer_4_clk  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_5_clk                  ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_TIMER_XRM.timer_5_clk  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_6_clk                  ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_TIMER_XRM.timer_6_clk  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_7_clk                  ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_TIMER_XRM.timer_7_clk  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_8_clk                  ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_TIMER_XRM.timer_8_clk  _INPUT");
    check_in_testmode (`UART1_XRM.pclk                         ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_UART1_XRM.pclk  _INPUT");
    check_in_testmode (`WDT_XRM.pclk                           ,`DUT_XRM.GPIO[23],scan_in_error,"GPIO[23]_WDT_XRM.pclk  _INPUT");
    check_in_testmode (`GPIO_XRM.presetn                       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_GPIO_XRM.presetn  _INPUT");
    check_in_testmode (`GPIO_XRM.dbclk_res_n                   ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_GPIO_XRM.dbclk_res_n  _INPUT");
    check_in_testmode (`RTC_XRM.PRESETn                        ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_RTC_XRM.PRESETn  _INPUT");
    check_in_testmode (`RTC_XRM.nRTCRST                        ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_RTC_XRM.nRTCRST  _INPUT");
    check_in_testmode (`RTC_XRM.nPOR                           ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_RTC_XRM.nPOR  _INPUT");
    check_in_testmode (`SCU_XRM.u_apb_eg_slave_reg.presetn     ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SCU_XRM.u_apb_eg_slave_reg.presetn  _INPUT");
    check_in_testmode (`SCU_XRM.u_bb_wakeup.presetn            ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SCU_XRM.u_bb_wakeup.presetn  _INPUT");
    check_in_testmode (`PMU_XRM.rstn                           ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_PMU_XRM.rstn  _INPUT");
    check_in_testmode (`BB_XRM.master_nrst                     ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_BB_XRM.master_nrst  _INPUT");
    check_in_testmode (`BB_XRM.crypt_nrst                      ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_BB_XRM.crypt_nrst  _INPUT");
    check_in_testmode (`BB_XRM.hreset_n                        ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_BB_XRM.hreset_n  _INPUT");
    check_in_testmode (`BB_XRM.low_power_nrst                  ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_BB_XRM.low_power_nrst  _INPUT");
    check_in_testmode (`BB_XRM.presetn                         ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_BB_XRM.presetn  _INPUT");
    check_in_testmode (`QL_XRM.RESETN_RF                       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_QL_XRM.RESETN_RF  _INPUT");
    check_in_testmode (`SPS1_XRM.presetn                       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SPS1_XRM.presetn  _INPUT");
    check_in_testmode (`SPS1_XRM.ssi_rst_n                     ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SPS1_XRM.ssi_rst_n  _INPUT");
    check_in_testmode (`UART0_XRM.presetn                      ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_UART0_XRM.presetn  _INPUT");
    check_in_testmode (`UART0_XRM.s_rst_n                      ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_UART0_XRM.s_rst_n  _INPUT");
    check_in_testmode (`USB_XRM.hreset_n                       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_USB_XRM.hreset_n  _INPUT");
    check_in_testmode (`USB_XRM.prst_n                         ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_USB_XRM.prst_n  _INPUT");
    check_in_testmode (`M3_XRM.PORESETn                        ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_M3_XRM.PORESETn  _INPUT");
    check_in_testmode (`M3_XRM.SYSRESETn                       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_M3_XRM.SYSRESETn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.ahb_ds128.HRESETn         ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.ahb_ds128.HRESETn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.ahb_to_rom0.HRESETn       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.ahb_to_rom0.HRESETn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.ahb_to_sram0.HRESETn      ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.ahb_to_sram0.HRESETn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.ahb_to_sram1.HRESETn      ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.ahb_to_sram1.HRESETn  _INPUT");
    check_in_testmode (`FLASHC_XRM.HRESETn                     ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_FLASHC_XRM.HRESETn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_ahb_d.hresetn           ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.i_ahb_d.hresetn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_ahb_dma.hresetn         ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.i_ahb_dma.hresetn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_ahb_i.hresetn           ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.i_ahb_i.hresetn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_ahb_s.hresetn           ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.i_ahb_s.hresetn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_apb0.hresetn            ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.i_apb0.hresetn  _INPUT");
    check_in_testmode (`DMAC_XRM.hresetn                       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_DMAC_XRM.hresetn  _INPUT");
    check_in_testmode (`I2C_XRM.presetn                        ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_I2C_XRM.presetn  _INPUT");
    check_in_testmode (`I2SM_XRM.presetn                       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_I2SM_XRM.presetn  _INPUT");
    check_in_testmode (`I2SM_XRM.sresetn                       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_I2SM_XRM.sresetn  _INPUT");
    check_in_testmode (`I2SS_XRM.presetn                       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_I2SS_XRM.presetn  _INPUT");
    check_in_testmode (`I2SS_XRM.sresetn                       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_I2SS_XRM.sresetn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_apb0.hresetn        ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.i_icm_apb0.hresetn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_bb.hresetn          ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.i_icm_bb.hresetn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_dma.hresetn         ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.i_icm_dma.hresetn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_flash.hresetn       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.i_icm_flash.hresetn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_ram0.hresetn        ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.i_icm_ram0.hresetn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_rom0.hresetn        ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.i_icm_rom0.hresetn  _INPUT");
    check_in_testmode (`SYS_MAIN_XRM.i_icm_usb.hresetn         ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SYS_MAIN_XRM.i_icm_usb.hresetn  _INPUT");
    check_in_testmode (`SPM0_XRM.hresetn                       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SPM0_XRM.hresetn  _INPUT");
    check_in_testmode (`SPM0_XRM.ssi_rst_n                     ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SPM0_XRM.ssi_rst_n  _INPUT");
    check_in_testmode (`SPM1_XRM.presetn                       ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SPM1_XRM.presetn  _INPUT");
    check_in_testmode (`SPM1_XRM.ssi_rst_n                     ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_SPM1_XRM.ssi_rst_n  _INPUT");
    check_in_testmode (`TIMER_XRM.presetn                      ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_TIMER_XRM.presetn  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_1_resetn               ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_TIMER_XRM.timer_1_resetn  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_2_resetn               ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_TIMER_XRM.timer_2_resetn  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_3_resetn               ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_TIMER_XRM.timer_3_resetn  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_4_resetn               ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_TIMER_XRM.timer_4_resetn  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_5_resetn               ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_TIMER_XRM.timer_5_resetn  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_6_resetn               ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_TIMER_XRM.timer_6_resetn  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_7_resetn               ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_TIMER_XRM.timer_7_resetn  _INPUT");
    check_in_testmode (`TIMER_XRM.timer_8_resetn               ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_TIMER_XRM.timer_8_resetn  _INPUT");
    check_in_testmode (`UART1_XRM.presetn                      ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_UART1_XRM.presetn  _INPUT");
    check_in_testmode (`WDT_XRM.presetn                        ,`DUT_XRM.GPIO[8] ,scan_in_error,"GPIO[8]_WDT_XRM.presetn  _INPUT");
    #10
    release `DUT_XRM.GPIO[0] ;
    release `DUT_XRM.GPIO[1] ;
    release `DUT_XRM.GPIO[2] ;
    release `DUT_XRM.GPIO[3] ;
    release `DUT_XRM.GPIO[4] ;
    release `DUT_XRM.GPIO[5] ;
    release `DUT_XRM.GPIO[6] ;
    release `DUT_XRM.GPIO[7] ;
    release `DUT_XRM.GPIO[8] ;
    release `DUT_XRM.GPIO[9] ;
    release `DUT_XRM.GPIO[10] ;
    release `DUT_XRM.GPIO[11] ;
    release `DUT_XRM.GPIO[12] ;
    release `DUT_XRM.GPIO[13] ;
    release `DUT_XRM.GPIO[23] ;
    release `DUT_XRM.GPIO[24] ;
    release `DUT_XRM.GPIO[29] ;
    release `DUT_XRM.GPIO[30] ;
    release `DUT_XRM.GPIO[31] ;
    release `DUT_XRM.GPIO[32] ;
    release `DUT_XRM.GPIO[33] ;
    release `DUT_XRM.GPIO[34] ;
    if (scan_in_error !== 0)
        $display("scan mode input test FAIL");
    else
        $display("scan mode input test PASS");
//======================  O ========================

    release   `DUT_XRM.GPIO[19:0];
    release   `DUT_XRM.GPIO[34:23];
    force `IOMUX_XRM.u_tmmux.scan_test_core2pad[14]  = $urandom;
    force `IOMUX_XRM.u_tmmux.scan_test_core2pad[15]  = $urandom;
    force `IOMUX_XRM.u_tmmux.scan_test_core2pad[16]  = $urandom;
    force `IOMUX_XRM.u_tmmux.scan_test_core2pad[17]  = $urandom;
    force `IOMUX_XRM.u_tmmux.scan_test_core2pad[18]  = $urandom;
    force `IOMUX_XRM.u_tmmux.scan_test_core2pad[19]  = $urandom;
    force `IOMUX_XRM.u_tmmux.scan_test_core2pad[25]  = $urandom;
    force `IOMUX_XRM.u_tmmux.scan_test_core2pad[26]  = $urandom;
    force `IOMUX_XRM.u_tmmux.scan_test_core2pad[27]  = $urandom;
    force `IOMUX_XRM.u_tmmux.scan_test_core2pad[28]  = $urandom;
    #10
    check_in_testmode (`DUT_XRM.GPIO[14],`IOMUX_XRM.u_tmmux.scan_test_core2pad[14],scan_out_error,"GPIO[14]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[15],`IOMUX_XRM.u_tmmux.scan_test_core2pad[15],scan_out_error,"GPIO[15]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[16],`IOMUX_XRM.u_tmmux.scan_test_core2pad[16],scan_out_error,"GPIO[16]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[17],`IOMUX_XRM.u_tmmux.scan_test_core2pad[17],scan_out_error,"GPIO[17]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[18],`IOMUX_XRM.u_tmmux.scan_test_core2pad[18],scan_out_error,"GPIO[18]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[19],`IOMUX_XRM.u_tmmux.scan_test_core2pad[19],scan_out_error,"GPIO[19]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[25],`IOMUX_XRM.u_tmmux.scan_test_core2pad[25],scan_out_error,"GPIO[25]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[26],`IOMUX_XRM.u_tmmux.scan_test_core2pad[26],scan_out_error,"GPIO[26]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[27],`IOMUX_XRM.u_tmmux.scan_test_core2pad[27],scan_out_error,"GPIO[27]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[28],`IOMUX_XRM.u_tmmux.scan_test_core2pad[28],scan_out_error,"GPIO[28]  _OUTPUT");
    #10
    release `IOMUX_XRM.u_tmmux.scan_test_core2pad[14] ;
    release `IOMUX_XRM.u_tmmux.scan_test_core2pad[15] ;
    release `IOMUX_XRM.u_tmmux.scan_test_core2pad[16] ;
    release `IOMUX_XRM.u_tmmux.scan_test_core2pad[17] ;
    release `IOMUX_XRM.u_tmmux.scan_test_core2pad[18] ;
    release `IOMUX_XRM.u_tmmux.scan_test_core2pad[19] ;
    release `IOMUX_XRM.u_tmmux.scan_test_core2pad[25] ;
    release `IOMUX_XRM.u_tmmux.scan_test_core2pad[26] ;
    release `IOMUX_XRM.u_tmmux.scan_test_core2pad[27] ;
    release `IOMUX_XRM.u_tmmux.scan_test_core2pad[28] ;

    if (scan_out_error !== 0)
        $display("scan mode output test FAIL");
    else
        $display("scan mode output test PASS");

    release  `GPIO_XRM.gpio_intrclk_en;

    //Disable Test mode
    force `DUT_XRM.TEST = 0;
    #1000;
    

//======================mbist test=====================

    //Enbale Test mode
    force `DUT_XRM.TEST = 1;
    force `DUT_XRM.GPIO[22:20]        = 5; //0--func mode,4--scan mode, 5--mbist mode,6--bsd mode
    #10
    check_in_testmode (1'b1,`DUT_XRM.GPIO[29],mbist_in_error,"GPIO[29]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[30],mbist_in_error,"GPIO[30]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[31],mbist_in_error,"GPIO[31]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[32],mbist_in_error,"GPIO[32]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[33],mbist_in_error,"GPIO[33]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[34],mbist_in_error,"GPIO[34]  _INPUT");
    #10
//======================  I ========================
    force `DUT_XRM.GPIO[0]  = $urandom;
    force `DUT_XRM.GPIO[1]  = $urandom;
    force `DUT_XRM.GPIO[2]  = $urandom;
    force `DUT_XRM.GPIO[3]  = $urandom;
    force `DUT_XRM.GPIO[4]  = $urandom;
    force `DUT_XRM.GPIO[8]  = $urandom;
    force `DUT_XRM.GPIO[12]  = $urandom;
    force `DUT_XRM.GPIO[29]  = $urandom;
    force `DUT_XRM.GPIO[30]  = $urandom;
    force `DUT_XRM.GPIO[31]  = $urandom;
    force `DUT_XRM.GPIO[32]  = $urandom;
    force `DUT_XRM.GPIO[33]  = $urandom;
    force `DUT_XRM.GPIO[34]  = $urandom;
    #10
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[0],`DUT_XRM.GPIO[0],mbist_in_error,"GPIO[0]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[1],`DUT_XRM.GPIO[1],mbist_in_error,"GPIO[1]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[2],`DUT_XRM.GPIO[2],mbist_in_error,"GPIO[2]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[3],`DUT_XRM.GPIO[3],mbist_in_error,"GPIO[3]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[4],`DUT_XRM.GPIO[4],mbist_in_error,"GPIO[4]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[8],`DUT_XRM.GPIO[8],mbist_in_error,"GPIO[8]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[12],`DUT_XRM.GPIO[12],mbist_in_error,"GPIO[12]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[29],`DUT_XRM.GPIO[29],mbist_in_error,"GPIO[29]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[30],`DUT_XRM.GPIO[30],mbist_in_error,"GPIO[30]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[31],`DUT_XRM.GPIO[31],mbist_in_error,"GPIO[31]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[32],`DUT_XRM.GPIO[32],mbist_in_error,"GPIO[32]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[33],`DUT_XRM.GPIO[33],mbist_in_error,"GPIO[33]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.mbist_test_pad2core[34],`DUT_XRM.GPIO[34],mbist_in_error,"GPIO[34]  _INPUT");
    #10
    release `DUT_XRM.GPIO[0] ;
    release `DUT_XRM.GPIO[1] ;
    release `DUT_XRM.GPIO[2] ;
    release `DUT_XRM.GPIO[3] ;
    release `DUT_XRM.GPIO[4] ;
    release `DUT_XRM.GPIO[8] ;
    release `DUT_XRM.GPIO[12] ;
    release `DUT_XRM.GPIO[29] ;
    release `DUT_XRM.GPIO[30] ;
    release `DUT_XRM.GPIO[31] ;
    release `DUT_XRM.GPIO[32] ;
    release `DUT_XRM.GPIO[33] ;
    release `DUT_XRM.GPIO[34] ;
    if (mbist_in_error !== 0)
        $display("mbist mode input test FAIL");
    else
        $display("mbist mode input test PASS");
//======================  O ========================

    release   `DUT_XRM.GPIO[19:0];
    release   `DUT_XRM.GPIO[34:23];
    force `IOMUX_XRM.u_tmmux.mbist_test_core2pad[11]  = $urandom;
    force `IOMUX_XRM.u_tmmux.mbist_test_core2pad[14]  = $urandom;
    force `IOMUX_XRM.u_tmmux.mbist_test_core2pad[15]  = $urandom;
    force `IOMUX_XRM.u_tmmux.mbist_test_core2pad[16]  = $urandom;
    force `IOMUX_XRM.u_tmmux.mbist_test_core2pad[17]  = $urandom;
    force `IOMUX_XRM.u_tmmux.mbist_test_core2pad[18]  = $urandom;
    force `IOMUX_XRM.u_tmmux.mbist_test_core2pad[19]  = $urandom;
    force `IOMUX_XRM.u_tmmux.mbist_test_core2pad[23]  = $urandom;
    force `IOMUX_XRM.u_tmmux.mbist_test_core2pad[24]  = $urandom;
    force `IOMUX_XRM.u_tmmux.mbist_test_core2pad[25]  = $urandom;
    force `IOMUX_XRM.u_tmmux.mbist_test_core2pad[26]  = $urandom;
    force `IOMUX_XRM.u_tmmux.mbist_test_core2pad[27]  = $urandom;
    #10
    check_in_testmode (`DUT_XRM.GPIO[11],`IOMUX_XRM.u_tmmux.mbist_test_core2pad[11],mbist_out_error,"GPIO[11]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[14],`IOMUX_XRM.u_tmmux.mbist_test_core2pad[14],mbist_out_error,"GPIO[14]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[15],`IOMUX_XRM.u_tmmux.mbist_test_core2pad[15],mbist_out_error,"GPIO[15]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[16],`IOMUX_XRM.u_tmmux.mbist_test_core2pad[16],mbist_out_error,"GPIO[16]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[17],`IOMUX_XRM.u_tmmux.mbist_test_core2pad[17],mbist_out_error,"GPIO[17]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[18],`IOMUX_XRM.u_tmmux.mbist_test_core2pad[18],mbist_out_error,"GPIO[18]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[19],`IOMUX_XRM.u_tmmux.mbist_test_core2pad[19],mbist_out_error,"GPIO[19]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[23],`IOMUX_XRM.u_tmmux.mbist_test_core2pad[23],mbist_out_error,"GPIO[23]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[24],`IOMUX_XRM.u_tmmux.mbist_test_core2pad[24],mbist_out_error,"GPIO[24]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[25],`IOMUX_XRM.u_tmmux.mbist_test_core2pad[25],mbist_out_error,"GPIO[25]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[26],`IOMUX_XRM.u_tmmux.mbist_test_core2pad[26],mbist_out_error,"GPIO[26]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[27],`IOMUX_XRM.u_tmmux.mbist_test_core2pad[27],mbist_out_error,"GPIO[27]  _OUTPUT");
    #10
    release `IOMUX_XRM.u_tmmux.mbist_test_core2pad[11] ;
    release `IOMUX_XRM.u_tmmux.mbist_test_core2pad[14] ;
    release `IOMUX_XRM.u_tmmux.mbist_test_core2pad[15] ;
    release `IOMUX_XRM.u_tmmux.mbist_test_core2pad[16] ;
    release `IOMUX_XRM.u_tmmux.mbist_test_core2pad[17] ;
    release `IOMUX_XRM.u_tmmux.mbist_test_core2pad[18] ;
    release `IOMUX_XRM.u_tmmux.mbist_test_core2pad[19] ;
    release `IOMUX_XRM.u_tmmux.mbist_test_core2pad[23] ;
    release `IOMUX_XRM.u_tmmux.mbist_test_core2pad[24] ;
    release `IOMUX_XRM.u_tmmux.mbist_test_core2pad[25] ;
    release `IOMUX_XRM.u_tmmux.mbist_test_core2pad[26] ;
    release `IOMUX_XRM.u_tmmux.mbist_test_core2pad[27] ;

    if (mbist_out_error !== 0)
        $display("mbist mode output test FAIL");
    else
        $display("mbist mode output test PASS");

    //Disable Test mode
    force `DUT_XRM.TEST = 0;
    #1000;
    

//======================bsd test=====================

    //Enbale Test mode
    force `DUT_XRM.TEST = 1;
    force `DUT_XRM.GPIO[22:20]        = 6; //0--func mode,4--scan mode, 5--mbist mode,6--bsd mode
    #10
    check_in_testmode (1'b1,`DUT_XRM.GPIO[29],bsd_in_error,"GPIO[29]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[30],bsd_in_error,"GPIO[30]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[31],bsd_in_error,"GPIO[31]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[32],bsd_in_error,"GPIO[32]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[33],bsd_in_error,"GPIO[33]  _INPUT");
    check_in_testmode (1'b1,`DUT_XRM.GPIO[34],bsd_in_error,"GPIO[34]  _INPUT");
    #10
//======================  I ========================
    force `DUT_XRM.GPIO[4]  = $urandom;
    force `DUT_XRM.GPIO[5]  = $urandom;
    force `DUT_XRM.GPIO[6]  = $urandom;
    force `DUT_XRM.GPIO[15]  = $urandom;
    force `DUT_XRM.GPIO[16]  = $urandom;
    force `DUT_XRM.GPIO[18]  = $urandom;
    force `DUT_XRM.GPIO[19]  = $urandom;
    force `DUT_XRM.GPIO[29]  = $urandom;
    force `DUT_XRM.GPIO[30]  = $urandom;
    force `DUT_XRM.GPIO[31]  = $urandom;
    force `DUT_XRM.GPIO[32]  = $urandom;
    force `DUT_XRM.GPIO[33]  = $urandom;
    force `DUT_XRM.GPIO[34]  = $urandom;
    #10
    check_in_testmode (`QL_XRM.SPI_CLK,`DUT_XRM.GPIO[4],bsd_in_error,"GPIO[4]  _INPUT");
    check_in_testmode (`QL_XRM.SPI_CSN,`DUT_XRM.GPIO[5],bsd_in_error,"GPIO[5]  _INPUT");
    check_in_testmode (`QL_XRM.SPI_DI,`DUT_XRM.GPIO[6],bsd_in_error,"GPIO[6]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.bsd_test_pad2core[15],`DUT_XRM.GPIO[15],bsd_in_error,"GPIO[15]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.bsd_test_pad2core[16],`DUT_XRM.GPIO[16],bsd_in_error,"GPIO[16]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.bsd_test_pad2core[18],`DUT_XRM.GPIO[18],bsd_in_error,"GPIO[18]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.bsd_test_pad2core[19],`DUT_XRM.GPIO[19],bsd_in_error,"GPIO[19]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.bsd_test_pad2core[29],`DUT_XRM.GPIO[29],bsd_in_error,"GPIO[29]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.bsd_test_pad2core[30],`DUT_XRM.GPIO[30],bsd_in_error,"GPIO[30]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.bsd_test_pad2core[31],`DUT_XRM.GPIO[31],bsd_in_error,"GPIO[31]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.bsd_test_pad2core[32],`DUT_XRM.GPIO[32],bsd_in_error,"GPIO[32]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.bsd_test_pad2core[33],`DUT_XRM.GPIO[33],bsd_in_error,"GPIO[33]  _INPUT");
    check_in_testmode (`IOMUX_XRM.u_tmmux.bsd_test_pad2core[34],`DUT_XRM.GPIO[34],bsd_in_error,"GPIO[34]  _INPUT");
    #10
    release `DUT_XRM.GPIO[4] ;
    release `DUT_XRM.GPIO[5] ;
    release `DUT_XRM.GPIO[6] ;
    release `DUT_XRM.GPIO[15] ;
    release `DUT_XRM.GPIO[16] ;
    release `DUT_XRM.GPIO[18] ;
    release `DUT_XRM.GPIO[19] ;
    release `DUT_XRM.GPIO[29] ;
    release `DUT_XRM.GPIO[30] ;
    release `DUT_XRM.GPIO[31] ;
    release `DUT_XRM.GPIO[32] ;
    release `DUT_XRM.GPIO[33] ;
    release `DUT_XRM.GPIO[34] ;
    if (bsd_in_error !== 0)
        $display("bsd mode input test FAIL");
    else
        $display("bsd mode input test PASS");
//======================  O ========================

    release   `DUT_XRM.GPIO[19:0];
    release   `DUT_XRM.GPIO[34:23];
    force `QL_XRM.SPI_DO  = $urandom;
    force `IOMUX_XRM.pad_cfg[58:56] = 1;
    force `IOMUX_XRM.u_tmmux.bsd_test_core2pad[17]  = $urandom;
    #10
    check_in_testmode (`DUT_XRM.GPIO[7],`QL_XRM.SPI_DO,bsd_out_error,"GPIO[7]  _OUTPUT");
    check_in_testmode (`DUT_XRM.GPIO[17],`IOMUX_XRM.u_tmmux.bsd_test_core2pad[17],bsd_out_error,"GPIO[17]  _OUTPUT");
    #10
    release `IOMUX_XRM.pad_cfg[58:56] ;
    release `QL_XRM.SPI_DO ;
    release `IOMUX_XRM.u_tmmux.bsd_test_core2pad[17] ;

    if (bsd_out_error !== 0)
        $display("bsd mode output test FAIL");
    else
        $display("bsd mode output test PASS");

    //Disable Test mode
    force `DUT_XRM.TEST = 0;
    #1000;
endtask: iomux_all_testmode


// check task 
task check_in_testmode (left_sigin,right_sigal,int error_count,string name); 
//  #10;// it would tested the value of singal 10ns ago;
  if (left_sigin !== right_sigal) 
    begin
      error_count = error_count + 1;
      $display("%t %s left signal is %b, right signal is %b test FAIL!!!!!!!!!!",$realtime,name,left_sigin,right_sigal);
    end //else
    //$display("%t %s left signal is %b, right signal is %b test RIGHT",$realtime,name,left_sigin,right_sigal);
  #10;
endtask: check_in_testmode

