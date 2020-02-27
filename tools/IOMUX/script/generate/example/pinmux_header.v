wire		uart0_sin_0;
wire		uart0_sin_1;
wire		uart0_sin_2;
wire		uart0_sin_3;
wire		resetn_rf_fun_0;
wire		resetn_rf_fun_1;
wire		rf_spis_clk_ana_io;
wire		rf_spis_csn_ana_io;
wire		rf_spis_mosi_ana_io;
wire	[1:0]	swd_clock_outtmp_tmp;
wire	[1:0]	swd_io_din_tmp;
wire	[1:0]	clk_ext_in_tmp;
wire	[1:0]	rf_test_in_0_tmp;
wire	[1:0]	rf_test_in_1_tmp;
wire	[1:0]	rf_test_in_2_tmp;
wire	[1:0]	rf_test_in_3_tmp;
wire	[5:0]	spim0_rxd_0_tmp;
wire	[5:0]	spim0_rxd_1_tmp;
wire	[5:0]	spim0_rxd_2_tmp;
wire	[5:0]	spim0_rxd_3_tmp;

assign 	swd_clock_outtmp= swd_clock_outtmp_tmp[0] | swd_clock_outtmp_tmp[1];
assign	swd_io_din	= swd_io_din_tmp[0] | swd_io_din_tmp[1];

assign	clk_ext_in	= clk_ext_in_tmp[0] | clk_ext_in_tmp[1];

assign	rf_test_in[0]	= rf_test_in_0_tmp[0] | rf_test_in_0_tmp[1];
assign	rf_test_in[1]	= rf_test_in_1_tmp[0] | rf_test_in_1_tmp[1];
assign	rf_test_in[2]	= rf_test_in_2_tmp[0] | rf_test_in_2_tmp[1];
assign	rf_test_in[3]	= rf_test_in_3_tmp[0] | rf_test_in_3_tmp[1];

assign	spim0_rxd[0]	= spim0_rxd_0_tmp[0] | spim0_rxd_0_tmp[1] | spim0_rxd_0_tmp[2] | spim0_rxd_0_tmp[3] | spim0_rxd_0_tmp[4] | spim0_rxd_0_tmp[5];   
assign	spim0_rxd[1]	= spim0_rxd_1_tmp[0] | spim0_rxd_1_tmp[1] | spim0_rxd_1_tmp[2] | spim0_rxd_1_tmp[3] | spim0_rxd_1_tmp[4] | spim0_rxd_1_tmp[5];   
assign	spim0_rxd[2]	= spim0_rxd_2_tmp[0] | spim0_rxd_2_tmp[1] | spim0_rxd_2_tmp[2] | spim0_rxd_2_tmp[3] | spim0_rxd_2_tmp[4] | spim0_rxd_2_tmp[5];   
assign	spim0_rxd[3]	= spim0_rxd_3_tmp[0] | spim0_rxd_3_tmp[1] | spim0_rxd_3_tmp[2] | spim0_rxd_3_tmp[3] | spim0_rxd_3_tmp[4] | spim0_rxd_3_tmp[5];   
