`timescale 1ns/1ps

module user_def;

//  `include "iomux_function_default.sv"
//  `include "iomux_function.sv"
//  `include "pad0_test.sv"

  initial begin
	repeat (40) iomux_function_default;
	repeat (40) pad0_test;
	repeat (40) iomux_function; $finish;
  end

endmodule
///`ifdef RESET_RELEASE3MS
///  initial  begin    //gw for NORESETN
///    force `RST_XRM.ext_rst_n = 1;
///    force `RST_XRM.por_bb = 1;
///  end
///`endif  
