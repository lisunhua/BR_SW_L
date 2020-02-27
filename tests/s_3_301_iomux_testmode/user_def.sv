`timescale 1ns/1ps

module user_def;
//  `include "chip_def.inc"
//  `include "iomux_test_mode.sv"

  initial begin
       @(posedge `RST_XRM.por_bb);
       repeat (40) iomux_all_testmode ;  $finish;
  end
//  initial begin                                         // tetsmode 20-22 to 10-12,   GPIO[10]=Z.
//	    force `SCUREG_XRM.pad_cfg = {20{8'b0111}} ;
//            @(posedge `SCUREG_XRM.presetn) ;
//            release `SCUREG_XRM.pad_cfg;
//  end
endmodule
