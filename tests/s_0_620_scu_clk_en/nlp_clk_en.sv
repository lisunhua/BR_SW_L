class nlp_clk_en extends chip_base_test;
		`uvm_component_utils(nlp_clk_en)

		function new(string name, uvm_component parent);
			super.new(name, parent);
		endfunction: new

		task main_phase(uvm_phase phase);
	    phase.raise_objection(phase);

//	force `CLK_XRM.timers_en      = chip_clk_if.timers_en     ;
	force `AON_XRM.timer_en[7:0]      = chip_clk_if.timers_en     ;
//	force `CLK_XRM.pclk_intr_req  = chip_clk_if.pclk_intr_req ;
	force `GPIO_XRM.U_apb_gpio_ctrl.gpio_intrclk_en  = chip_clk_if.pclk_intr_req ;
//	force `CLK_XRM.cpu_gate_hclk  = chip_clk_if.cpu_gate_hclk ;
	force `M3_XRM.GATEHCLK  = chip_clk_if.cpu_gate_hclk ;
//	force `CLK_XRM.i2ss_sclk_src  = `CLK_XRM.osc_24m ;
	force `CORE_XRM.u_i2ss_sclk_testclk_mux.clk_out  = `CLK_XRM.osc_24m ;
			#5ms;
			for (int i=0; i<10; i++) begin
		    sa_env.common_clk_gating_checker();
				#10us;
			end
      #100us;
		  phase.drop_objection(phase);
		endtask: main_phase
endclass: nlp_clk_en
