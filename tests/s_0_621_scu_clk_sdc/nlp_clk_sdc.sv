class nlp_clk_sdc extends chip_base_test;
		`uvm_component_utils(nlp_clk_sdc)

		function new(string name, uvm_component parent);
			super.new(name, parent);
		endfunction: new

		task main_phase(uvm_phase phase);               	 
			uvm_status_e status1;    
	                uvm_reg_data_t read_value;
  		    phase.raise_objection(phase);

//               	      force `CLK_XRM.adc_cal_switch = chip_clk_if.adc_cal_switch;
               	      force `BBREG_XRM.rft_time[12][4] = chip_clk_if.adc_cal_switch;
//               	      force `CLK_XRM.dac_cal_switch = chip_clk_if.dac_cal_switch;
               	      force `BBREG_XRM.rft_time[12][3] = chip_clk_if.dac_cal_switch;
//               	      force `CLK_XRM.adda_test_cap  = chip_clk_if.adda_test_cap ;
               	      force `BBREG_XRM.rft_time[12][9]  = chip_clk_if.adda_test_cap ;
//               	      force `CLK_XRM.adc_clk_24_26  = chip_clk_if.adc_clk_24_26 ;
               	      force `BB_XRM.adc_clk_24_26[1:0]  = chip_clk_if.adc_clk_24_26 ;
//               	      force `CLK_XRM.pclk_intr_req  = 1'b1 ;
               	      force `GPIO_XRM.U_apb_gpio_ctrl.gpio_intrclk_en  = 1'b1 ;
//	force `CLK_XRM.i2ss_sclk_src  = `CLK_XRM.osc_24m ;
	force `CORE_XRM.u_i2ss_sclk_testclk_mux.clk_out  = `CLK_XRM.osc_24m ;
	force `M3_XRM.GATEHCLK  = chip_clk_if.cpu_gate_hclk ;
	force `BB_XRM.u_rw_cm_timing_gen_lp.osc_en = chip_clk_if.bb_osc_en ;
	force chip_clk_if.mux_32k_sel = `CLK_XRM.mux_32k_sel;
                      @(posedge `SCUREG_XRM.presetn);
                      sa_env.chip_reg.DATA1.write(.status(status1),.value('hE020),.path(UVM_BACKDOOR));              // config rco32k trans_in 
                      sa_env.chip_reg.PAD_CFG.write(.status(status1),.value('h100F_0F0F_0F0F_0F0F),.path(UVM_BACKDOOR)); // config rco32k trans_in 
			#5ms;
//			for (int i=0; i<20; i++) begin   //chenge 5 to 20, for hw_32k_sel coverage.
//		    sa_env.common_clock_checker();
//				#10us;
//        $display("CLK_SDC_CYCLE The %d times loop", i);
//			end
		    sa_env.common_clock_checker();
      #100us;
		  phase.drop_objection(phase);
		endtask: main_phase
endclass: nlp_clk_sdc

