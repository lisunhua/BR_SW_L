class nlp_reset extends chip_base_test;
		`uvm_component_utils(nlp_reset)

		function new(string name, uvm_component parent);
			super.new(name, parent);
		endfunction: new

		task main_phase(uvm_phase phase);
	    phase.raise_objection(phase);

		force `SCU_XRM.remap_rst      = chip_clk_if.remap_rst     ;
//	force `CLK_XRM.i2ss_sclk_src  = `CLK_XRM.osc_24m ;
	force `CORE_XRM.u_i2ss_sclk_testclk_mux.clk_out  = `CLK_XRM.osc_24m ;

			#5ms;
	for (int i=0; i<10; i++) begin  sa_env.common_reset_checker_default();  #1ms;  end
	for (int i=0; i<10; i++) begin  sa_env.common_reset_checker();          #1ms;  end

		  phase.drop_objection(phase);
		endtask: main_phase
endclass: nlp_reset

