`timescale 1ns/1ps
`include "chip_def.inc"
module user_def;

  initial begin
	    force `SCUREG_XRM.pad_cfg = {20{8'b0111}} ;
            @(posedge `SCUREG_XRM.presetn) ;
            release `SCUREG_XRM.pad_cfg;
  end

endmodule  
