//Automatically generate file.

wire    [1:0]  i2ss_ws_slv_tmp;
wire    [1:0]  pcmclk_in_tmp;
wire    [1:0]  i2ss_sdi0_tmp;
wire    [1:0]  i2ss_sclk_pre_mux_tmp;
wire    [1:0]  swd_io_din_tmp;
wire    [5:0]  spim0_rxd_3_tmp;
wire    [1:0]  i2sm_sdi0_tmp;
wire    [1:0]  pcmdin_tmp;
wire    [1:0]  spim1_miso_tmp;
wire    [1:0]  spis1_sclk_in_pre_mux_tmp;
wire    [5:0]  spim0_rxd_0_tmp;
wire    [1:0]  swd_clock_outtmp_tmp;
wire    [5:0]  spim0_rxd_1_tmp;
wire    [1:0]  pcmfsync_in_tmp;
wire    [1:0]  spis1_mosi_tmp;
wire    [5:0]  spim0_rxd_2_tmp;

assign    swd_io_din  = swd_io_din_tmp [0]| swd_io_din_tmp [1]; 
assign    i2ss_sdi0  = i2ss_sdi0_tmp [0]| i2ss_sdi0_tmp [1]; 
assign    i2ss_sclk_pre_mux  = i2ss_sclk_pre_mux_tmp [0]| i2ss_sclk_pre_mux_tmp [1]; 
assign    pcmdin  = pcmdin_tmp [0]| pcmdin_tmp [1]; 
assign    swd_clock_outtmp  = swd_clock_outtmp_tmp [0]| swd_clock_outtmp_tmp [1]; 
assign    spim1_miso  = spim1_miso_tmp [0]| spim1_miso_tmp [1]; 
assign    spis1_sclk_in_pre_mux  = spis1_sclk_in_pre_mux_tmp [0]| spis1_sclk_in_pre_mux_tmp [1]; 
assign    pcmfsync_in  = pcmfsync_in_tmp [0]| pcmfsync_in_tmp [1]; 
assign    spim0_rxd[0]  = spim0_rxd_0_tmp [0]| spim0_rxd_0_tmp [1]| spim0_rxd_0_tmp [2]| spim0_rxd_0_tmp [3]| spim0_rxd_0_tmp [4]| spim0_rxd_0_tmp [5]; 
assign    spim0_rxd[1]  = spim0_rxd_1_tmp [0]| spim0_rxd_1_tmp [1]| spim0_rxd_1_tmp [2]| spim0_rxd_1_tmp [3]| spim0_rxd_1_tmp [4]| spim0_rxd_1_tmp [5]; 
assign    spim0_rxd[2]  = spim0_rxd_2_tmp [0]| spim0_rxd_2_tmp [1]| spim0_rxd_2_tmp [2]| spim0_rxd_2_tmp [3]| spim0_rxd_2_tmp [4]| spim0_rxd_2_tmp [5]; 
assign    spim0_rxd[3]  = spim0_rxd_3_tmp [0]| spim0_rxd_3_tmp [1]| spim0_rxd_3_tmp [2]| spim0_rxd_3_tmp [3]| spim0_rxd_3_tmp [4]| spim0_rxd_3_tmp [5]; 
assign    pcmclk_in  = pcmclk_in_tmp [0]| pcmclk_in_tmp [1]; 
assign    i2sm_sdi0  = i2sm_sdi0_tmp [0]| i2sm_sdi0_tmp [1]; 
assign    i2ss_ws_slv  = i2ss_ws_slv_tmp [0]| i2ss_ws_slv_tmp [1]; 
assign    spis1_mosi  = spis1_mosi_tmp [0]| spis1_mosi_tmp [1]; 


`BIDIRPAD(0,6,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,uart0_sout,floating_net[0],
~gpio_porta_ddr[0],`PAD_BDIR_IE,gpio_porta_dr[0],gpio_ext_porta[0],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rf_tx_en,floating_net[1],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,uart0_sout,floating_net[2],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,uart0_sout,floating_net[3],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,uart0_sout,floating_net[4])

`BIDIRPAD(1,6,
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,uart0_sin_0,
~gpio_porta_ddr[1],`PAD_BDIR_IE,gpio_porta_dr[1],gpio_ext_porta[1],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rf_rx_en,floating_net[5],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,uart0_sin_1,
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,uart0_sin_2,
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,uart0_sin_3)

`BIDIRPAD(2,6,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,uart0_rts_n,floating_net[6],
~gpio_porta_ddr[2],`PAD_BDIR_IE,gpio_porta_dr[2],gpio_ext_porta[2],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,timers_toggle[0],floating_net[7],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bb_clk_12m,floating_net[8],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rco_32k_bb,floating_net[9],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[0],floating_net[10])

`BIDIRPAD(3,6,
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,uart0_cts_n,
~gpio_porta_ddr[3],`PAD_BDIR_IE,gpio_porta_dr[3],gpio_ext_porta[3],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,timers_toggle[1],floating_net[11],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,clk_26m_out,floating_net[12],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,resetn_rf,floating_net[13],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[1],floating_net[14])

`BIDIRPAD(4,6,
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,swd_clock_outtmp_tmp[0],
~gpio_porta_ddr[4],`PAD_BDIR_IE,gpio_porta_dr[4],gpio_ext_porta[4],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,timers_toggle[2],floating_net[15],
~i2c_ic_clk_oe,`PAD_BDIR_IE,`PAD_IPORT_TIE,i2c_scl_sin_0,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rf_tx_en,floating_net[16],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,swd_clock_outtmp_tmp[1])

`BIDIRPAD(5,6,
~swd_io_oe,`PAD_BDIR_IE,swd_io_dout,swd_io_din_tmp[0],
~gpio_porta_ddr[5],`PAD_BDIR_IE,gpio_porta_dr[5],gpio_ext_porta[5],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,timers_toggle[3],floating_net[17],
~i2c_ic_data_oe,`PAD_BDIR_IE,`PAD_IPORT_TIE,i2c_sda_sin_0,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rf_rx_en,floating_net[18],
~swd_io_oe,`PAD_BDIR_IE,swd_io_dout,swd_io_din_tmp[1])

`BIDIRPAD(6,6,
~gpio_porta_ddr[6],`PAD_BDIR_IE,gpio_porta_dr[6],gpio_ext_porta[6],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,`PAD_IPORT_TIE,floating_net[19],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,`PAD_IPORT_TIE,floating_net[20],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,lfclk_main_test,floating_net[21],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,dpll_lock,floating_net[22],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[2],floating_net[23])

`BIDIRPAD(7,6,
~gpio_porta_ddr[7],`PAD_BDIR_IE,gpio_porta_dr[7],gpio_ext_porta[7],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,clk_ext_32k_in,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,timers_toggle[0],floating_net[24],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,pclk_en,floating_net[25],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,dpll_out_16m,floating_net[26],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[3],floating_net[27])

`BIDIRPAD(8,6,
~gpio_porta_ddr[8],`PAD_BDIR_IE,gpio_porta_dr[8],gpio_ext_porta[8],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,dcdc_start_test,floating_net[28],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,timers_toggle[1],floating_net[29],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,hw_rst_n,floating_net[30],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rco32_coarse_done,floating_net[31],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[4],floating_net[32])

`BIDIRPAD(9,6,
~gpio_porta_ddr[9],`PAD_BDIR_IE,gpio_porta_dr[9],gpio_ext_porta[9],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,dcdc_ocp_det,floating_net[33],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,timers_toggle[2],floating_net[34],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,freeclk_rst_n,floating_net[35],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,dcdc_pwm_test,floating_net[36],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[5],floating_net[37])

`BIDIRPAD(10,6,
~gpio_porta_ddr[10],`PAD_BDIR_IE,gpio_porta_dr[10],gpio_ext_porta[10],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,dcdc_zcd_test,floating_net[38],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,timers_toggle[3],floating_net[39],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bb_clk_status,floating_net[40],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,resetn_rf_fun,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[6],floating_net[41])

`BIDIRPAD(11,6,
~gpio_porta_ddr[11],`PAD_BDIR_IE,gpio_porta_dr[11],gpio_ext_porta[11],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,spis1_sclk_in_pre_mux_tmp[0],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,timers_toggle[0],floating_net[42],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,resetn_rf,floating_net[43],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,rf_spis_clk_ana_io,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[7],floating_net[44])

`BIDIRPAD(12,6,
~gpio_porta_ddr[12],`PAD_BDIR_IE,gpio_porta_dr[12],gpio_ext_porta[12],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,spis1_ss_in_n_0,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,timers_toggle[1],floating_net[45],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,hclk_main_test,floating_net[46],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,rf_spis_csn_ana_io,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[8],floating_net[47])

`BIDIRPAD(13,6,
~gpio_porta_ddr[13],`PAD_BDIR_IE,gpio_porta_dr[13],gpio_ext_porta[13],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spis1_miso,floating_net[48],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,timers_toggle[2],floating_net[49],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,usb_clk_test,floating_net[50],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,rf_spis_mosi_ana_io,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[9],floating_net[51])

`BIDIRPAD(14,6,
~gpio_porta_ddr[14],`PAD_BDIR_IE,gpio_porta_dr[14],gpio_ext_porta[14],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,spis1_mosi_tmp[0],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,timers_toggle[3],floating_net[52],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,pclk_main_test,floating_net[53],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rf_spis_miso_ana,floating_net[54],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[10],floating_net[55])

`BIDIRPAD(15,6,
~gpio_porta_ddr[15],`PAD_BDIR_IE,gpio_porta_dr[15],gpio_ext_porta[15],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,uart1_sout,floating_net[56],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim1_sclk_out,floating_net[57],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,spis1_sclk_in_pre_mux_tmp[1],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bb_rx_pkd_sat,floating_net[58],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[11],floating_net[59])

`BIDIRPAD(16,6,
~gpio_porta_ddr[16],`PAD_BDIR_IE,gpio_porta_dr[16],gpio_ext_porta[16],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,uart1_sin_0,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim1_ss_0_n,floating_net[60],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,spis1_ss_in_n_1,
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,clk_ext_in,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[12],floating_net[61])

`BIDIRPAD(17,6,
~gpio_porta_ddr[17],`PAD_BDIR_IE,gpio_porta_dr[17],gpio_ext_porta[17],
~i2c_ic_clk_oe,`PAD_BDIR_IE,`PAD_IPORT_TIE,i2c_scl_sin_1,
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,spim1_miso_tmp[1],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spis1_miso,floating_net[62],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,utmifs_tx_dp,floating_net[63],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[13],floating_net[64])

`BIDIRPAD(18,6,
~gpio_porta_ddr[18],`PAD_BDIR_IE,gpio_porta_dr[18],gpio_ext_porta[18],
~i2c_ic_data_oe,`PAD_BDIR_IE,`PAD_IPORT_TIE,i2c_sda_sin_1,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim1_mosi,floating_net[65],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,spis1_mosi_tmp[1],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,utmifs_tx_dm,floating_net[66],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[14],floating_net[67])

`BIDIRPAD(19,6,
~gpio_porta_ddr[19],`PAD_BDIR_IE,gpio_porta_dr[19],gpio_ext_porta[19],
~pcmclk_en,`PAD_BDIR_IE,pcmclk_out,pcmclk_in_tmp[0],
~i2s_mst_nslv[0],`PAD_BDIR_IE,i2sm_sclk_out,i2ss_sclk_pre_mux_tmp[0],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,uart1_sout,floating_net[68],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,utmifs_tx_enable_n,floating_net[69],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[15],floating_net[70])

`BIDIRPAD(20,6,
~gpio_porta_ddr[20],`PAD_BDIR_IE,gpio_porta_dr[20],gpio_ext_porta[20],
~pcmfsync_en,`PAD_BDIR_IE,pcmfsync_out,pcmfsync_in_tmp[0],
~i2s_mst_nslv[0],`PAD_BDIR_IE,i2sm_ws_out,i2ss_ws_slv_tmp[0],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,uart1_sin_1,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,utmifs_suspend_n,floating_net[71],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bb_wakeup_req,floating_net[72])

`BIDIRPAD(21,6,
~gpio_porta_ddr[21],`PAD_BDIR_IE,gpio_porta_dr[21],gpio_ext_porta[21],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,pcmdin_tmp[0],
~i2s_mst_nslv[0],`PAD_BDIR_IE,i2sm_sdo0,i2ss_sdi0_tmp[0],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rf_tx_en,floating_net[73],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,utmifs_fs_edge_sel,floating_net[74],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bb_osc_en,floating_net[75])

`BIDIRPAD(22,6,
~gpio_porta_ddr[22],`PAD_BDIR_IE,gpio_porta_dr[22],gpio_ext_porta[22],
~pcmdout_en,`PAD_BDIR_IE,pcmdout,floating_net[76],
i2s_mst_nslv[0],`PAD_BDIR_IE,i2ss_sdo0,i2sm_sdi0_tmp[0],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rf_rx_en,floating_net[77],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,usb_up_p_en,floating_net[78],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bb_clk_status,floating_net[79])

`BIDIRPAD(23,6,
~gpio_porta_ddr[23],`PAD_BDIR_IE,gpio_porta_dr[23],gpio_ext_porta[23],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim1_sclk_out,floating_net[80],
~pcmclk_en,`PAD_BDIR_IE,pcmclk_out,pcmclk_in_tmp[1],
~i2s_mst_nslv[1],`PAD_BDIR_IE,i2sm_sclk_out,i2ss_sclk_pre_mux_tmp[1],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,usb_up_m_en,floating_net[81],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[16],floating_net[82])

`BIDIRPAD(24,6,
~gpio_porta_ddr[24],`PAD_BDIR_IE,gpio_porta_dr[24],gpio_ext_porta[24],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim1_ss_0_n,floating_net[83],
~pcmfsync_en,`PAD_BDIR_IE,pcmfsync_out,pcmfsync_in_tmp[1],
~i2s_mst_nslv[1],`PAD_BDIR_IE,i2sm_ws_out,i2ss_ws_slv_tmp[1],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,utmifs_rx_dp,floating_net[84],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[17],floating_net[85])

`BIDIRPAD(25,6,
~gpio_porta_ddr[25],`PAD_BDIR_IE,gpio_porta_dr[25],gpio_ext_porta[25],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,spim1_miso_tmp[0],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,pcmdin_tmp[1],
~i2s_mst_nslv[1],`PAD_BDIR_IE,i2sm_sdo0,i2ss_sdi0_tmp[1],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,utmifs_rx_dm,floating_net[86],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[18],floating_net[87])

`BIDIRPAD(26,6,
~gpio_porta_ddr[26],`PAD_BDIR_IE,gpio_porta_dr[26],gpio_ext_porta[26],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim1_mosi,floating_net[88],
~pcmdout_en,`PAD_BDIR_IE,pcmdout,floating_net[89],
i2s_mst_nslv[1],`PAD_BDIR_IE,i2ss_sdo0,i2sm_sdi0_tmp[1],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,utmifs_rx_rcv,floating_net[90],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[19],floating_net[91])

`BIDIRPAD(27,6,
~gpio_porta_ddr[27],`PAD_BDIR_IE,gpio_porta_dr[27],gpio_ext_porta[27],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,uart1_rts_n,floating_net[92],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rf_tx_en,floating_net[93],
~i2c_ic_clk_oe,`PAD_BDIR_IE,`PAD_IPORT_TIE,i2c_scl_sin_2,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rf_test_out,floating_net[94],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[20],floating_net[95])

`BIDIRPAD(28,6,
~gpio_porta_ddr[28],`PAD_BDIR_IE,gpio_porta_dr[28],gpio_ext_porta[28],
`PAD_INPUT_OE,`PAD_INPUT_IE,`PAD_IPORT_TIE,uart1_cts_n,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rf_rx_en,floating_net[96],
~i2c_ic_data_oe,`PAD_BDIR_IE,`PAD_IPORT_TIE,i2c_sda_sin_2,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,rco32_fine_done,floating_net[97],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,bt_dbg_bus[21],floating_net[98])

`BIDIRPAD(29,6,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim0_ss_0_n,floating_net[99],
spim0_ssi_oe_n[0],`PAD_BDIR_IE,spim0_txd[0],spim0_rxd_0_tmp[1],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim0_sclk_out,floating_net[100],
spim0_ssi_oe_n[3],`PAD_BDIR_IE,spim0_txd[3],spim0_rxd_3_tmp[3],
spim0_ssi_oe_n[2],`PAD_BDIR_IE,spim0_txd[2],spim0_rxd_2_tmp[4],
spim0_ssi_oe_n[1],`PAD_BDIR_IE,spim0_txd[1],spim0_rxd_1_tmp[5])

`BIDIRPAD(30,6,
spim0_ssi_oe_n[1],`PAD_BDIR_IE,spim0_txd[1],spim0_rxd_1_tmp[0],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim0_ss_0_n,floating_net[101],
spim0_ssi_oe_n[0],`PAD_BDIR_IE,spim0_txd[0],spim0_rxd_0_tmp[2],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim0_sclk_out,floating_net[102],
spim0_ssi_oe_n[3],`PAD_BDIR_IE,spim0_txd[3],spim0_rxd_3_tmp[4],
spim0_ssi_oe_n[2],`PAD_BDIR_IE,spim0_txd[2],spim0_rxd_2_tmp[5])

`BIDIRPAD(31,6,
spim0_ssi_oe_n[2],`PAD_BDIR_IE,spim0_txd[2],spim0_rxd_2_tmp[0],
spim0_ssi_oe_n[1],`PAD_BDIR_IE,spim0_txd[1],spim0_rxd_1_tmp[1],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim0_ss_0_n,floating_net[103],
spim0_ssi_oe_n[0],`PAD_BDIR_IE,spim0_txd[0],spim0_rxd_0_tmp[3],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim0_sclk_out,floating_net[104],
spim0_ssi_oe_n[3],`PAD_BDIR_IE,spim0_txd[3],spim0_rxd_3_tmp[5])

`BIDIRPAD(32,6,
spim0_ssi_oe_n[3],`PAD_BDIR_IE,spim0_txd[3],spim0_rxd_3_tmp[0],
spim0_ssi_oe_n[2],`PAD_BDIR_IE,spim0_txd[2],spim0_rxd_2_tmp[1],
spim0_ssi_oe_n[1],`PAD_BDIR_IE,spim0_txd[1],spim0_rxd_1_tmp[2],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim0_ss_0_n,floating_net[105],
spim0_ssi_oe_n[0],`PAD_BDIR_IE,spim0_txd[0],spim0_rxd_0_tmp[4],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim0_sclk_out,floating_net[106])

`BIDIRPAD(33,6,
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim0_sclk_out,floating_net[107],
spim0_ssi_oe_n[3],`PAD_BDIR_IE,spim0_txd[3],spim0_rxd_3_tmp[1],
spim0_ssi_oe_n[2],`PAD_BDIR_IE,spim0_txd[2],spim0_rxd_2_tmp[2],
spim0_ssi_oe_n[1],`PAD_BDIR_IE,spim0_txd[1],spim0_rxd_1_tmp[3],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim0_ss_0_n,floating_net[108],
spim0_ssi_oe_n[0],`PAD_BDIR_IE,spim0_txd[0],spim0_rxd_0_tmp[5])

`BIDIRPAD(34,6,
spim0_ssi_oe_n[0],`PAD_BDIR_IE,spim0_txd[0],spim0_rxd_0_tmp[0],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim0_sclk_out,floating_net[109],
spim0_ssi_oe_n[3],`PAD_BDIR_IE,spim0_txd[3],spim0_rxd_3_tmp[2],
spim0_ssi_oe_n[2],`PAD_BDIR_IE,spim0_txd[2],spim0_rxd_2_tmp[3],
spim0_ssi_oe_n[1],`PAD_BDIR_IE,spim0_txd[1],spim0_rxd_1_tmp[4],
`PAD_OUTPUT_OE,`PAD_OUTPUT_IE,spim0_ss_0_n,floating_net[110])



//Test the code in test mode 

// from pad to core
assign scan_test_reset    = scan_test_pad2core[8];
assign scan_test_clock    = scan_test_pad2core[23];

// from core to pad
assign func_test_core2pad[0]             = uart0_sout;
assign func_test_core2pad[1]             = pclk_en;
assign func_test_core2pad[2]             = rco_32k_bb;
assign func_test_core2pad[3]             = clk_26m_out;
assign func_test_core2pad[4]             = por_bb;
assign func_test_core2pad[5]             = lvd_bb;
assign func_test_core2pad[6]             = dpll_lock;
assign func_test_core2pad[7]             = dpll_out_192m_test;
assign func_test_core2pad[8]             = 1'b0;
assign func_test_core2pad[9]             = 1'b0;
assign func_test_core2pad[10]            = dpll_out_24m;
assign func_test_core2pad[11]            = resetn_rf;
assign func_test_core2pad[12]            = 1'b0;
assign func_test_core2pad[13]            = 1'b0;
assign func_test_core2pad[14]            = pclk_main_test;
assign func_test_core2pad[15]            = hclk_main_test;
assign func_test_core2pad[16]            = lfclk_main_test;
assign func_test_core2pad[17]            = h2p_clk_test;
assign func_test_core2pad[18]            = hw_rst_n;
assign func_test_core2pad[19]            = freeclk_rst_n;
assign func_test_core2pad[20]            = 1'b0;
assign func_test_core2pad[21]            = 1'b0;
assign func_test_core2pad[22]            = 1'b0;
assign func_test_core2pad[23]            = 1'b0;
assign func_test_core2pad[24]            = 1'b0;
assign func_test_core2pad[25]            = dpll_out_16m;
assign func_test_core2pad[26]            = bb_clk_12m;
assign func_test_core2pad[27]            = bb_clk_24m;
assign func_test_core2pad[28]            = bb_clk_48m;
assign func_test_core2pad[29]            = 1'b0;
assign func_test_core2pad[30]            = 1'b0;
assign func_test_core2pad[31]            = 1'b0;
assign func_test_core2pad[32]            = 1'b0;
assign func_test_core2pad[33]            = 1'b0;
assign func_test_core2pad[34]            = 1'b0;

//define 
`define TEST_FUNC_PAD_REN                35'b000_00000001_10000000_00110011_00000000
`define TEST_FUNC_PAD_IE                 35'b111_11100001_11110000_00110011_00000000
`define TEST_FUNC_PAD_OE                 35'b111_11100001_11110000_00110011_00000000
`define TEST_SCAN_PAD_REN                35'b000_00000000_00000000_00000000_00000000
`define TEST_SCAN_PAD_IE                 35'b111_11100001_11110000_00111111_11111111
`define TEST_SCAN_PAD_OE                 35'b111_11100001_11110000_00111111_11111111
`define TEST_MBIST_PAD_REN               35'b000_00010000_00000000_00100110_11100000
`define TEST_MBIST_PAD_IE                35'b111_11110000_01110000_00110111_11111111
`define TEST_MBIST_PAD_OE                35'b111_11110000_01110000_00110111_11111111
`define TEST_BSD_PAD_REN                 35'b000_00011111_10000000_01111111_00001111
`define TEST_BSD_PAD_IE                  35'b111_11111111_11111101_11111111_01111111
`define TEST_BSD_PAD_OE                  35'b111_11111111_11111101_11111111_01111111
