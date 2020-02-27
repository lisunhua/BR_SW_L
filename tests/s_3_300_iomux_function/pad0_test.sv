
task pad0_test;
   
  reg test_error =0 ;
  force soc_tb.DUT.u_io_mux.test_en = 0;
  #1us;

    force soc_tb.DUT.u_io_mux.pad_cfg[(0*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(1*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(2*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(3*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(4*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(5*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(6*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(7*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(8*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(9*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(10*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(11*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(12*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(13*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(14*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(15*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(16*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(17*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(18*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(19*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(20*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(21*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(22*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(23*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(24*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(25*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(26*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(27*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(28*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(29*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(30*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(31*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(32*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(33*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[(34*8+1) +: 3] = $urandom; // random IE,OEN,REN
    force soc_tb.DUT.u_io_mux.pad_cfg[0*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[1*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[2*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[3*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[4*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[5*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[6*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[7*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[8*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[9*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[10*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[11*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[12*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[13*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[14*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[15*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[16*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[17*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[18*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[19*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[20*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[21*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[22*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[23*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[24*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[25*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[26*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[27*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[28*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[29*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[30*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[31*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[32*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[33*8] = 'b1;
    force soc_tb.DUT.u_io_mux.pad_cfg[34*8] = 'b1;

#1000;
      for (int pad_cyle=0; pad_cyle<35; pad_cyle++) begin
       if(soc_tb.DUT.u_pad_ring.pad_ie[pad_cyle] != soc_tb.DUT.u_io_mux.pad_cfg[pad_cyle*8 + 1]) begin 
          $display("%t PAD_IE[%0d] padring = %b , iomux = %b error++!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!",$realtime,pad_cyle,soc_tb.DUT.u_pad_ring.pad_ie[pad_cyle],soc_tb.DUT.u_io_mux.pad_cfg[pad_cyle*8 + 1]);test_error=test_error+1;
       end         
//	else
//          $display("%t PAD_IE[%0d] padring = %b , iomux = %b right",$realtime,pad_cyle,soc_tb.DUT.u_pad_ring.pad_ie[pad_cyle],soc_tb.DUT.u_io_mux.pad_cfg[pad_cyle*8 + 1]);
       if(soc_tb.DUT.u_pad_ring.pad_oen[pad_cyle] != soc_tb.DUT.u_io_mux.pad_cfg[pad_cyle*8 + 2]) begin
          $display("%t PAD_OEN[%0d] padring = %b , iomux = %b error++!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!",$realtime,pad_cyle,soc_tb.DUT.u_pad_ring.pad_oen[pad_cyle],soc_tb.DUT.u_io_mux.pad_cfg[pad_cyle*8 + 2]);test_error=test_error+1;
       end       
//	else
//          $display("%t PAD_OEN[%0d] padring = %b , iomux = %b right",$realtime,pad_cyle,soc_tb.DUT.u_pad_ring.pad_oen[pad_cyle],soc_tb.DUT.u_io_mux.pad_cfg[pad_cyle*8 + 2]);
`ifndef GATE 
      if(soc_tb.DUT.u_pad_ring.pad_ren[pad_cyle] != soc_tb.DUT.u_io_mux.pad_cfg[pad_cyle*8 + 3]) begin
          $display("%t PAD_REN[%0d] padring = %b , iomux = %b error++!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!",$realtime,pad_cyle,soc_tb.DUT.u_pad_ring.pad_ren[pad_cyle],soc_tb.DUT.u_io_mux.pad_cfg[pad_cyle*8 + 3]);test_error=test_error+1;
       end       
      end
`else
	end
      for (int pad_cyle_ren=0; pad_cyle_ren<29; pad_cyle_ren++) begin
	      if(soc_tb.DUT.u_pad_ring.pad_ren[pad_cyle_ren] != soc_tb.DUT.u_io_mux.pad_cfg[pad_cyle_ren*8 + 3]) begin
          $display("%t PAD_REN[%0d] padring = %b , iomux = %b error++!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!",$realtime,pad_cyle_ren,soc_tb.DUT.u_pad_ring.pad_ren[pad_cyle_ren],soc_tb.DUT.u_io_mux.pad_cfg[pad_cyle_ren*8 + 3]);test_error=test_error+1;
       end  
	end
`endif
//	else
//          $display("%t PAD_REN[%0d] padring = %b , iomux = %b right",$realtime,pad_cyle,soc_tb.DUT.u_pad_ring.pad_ren[pad_cyle],soc_tb.DUT.u_io_mux.pad_cfg[pad_cyle*8 + 3]);

    if (test_error != 0) 
          $display("TEST FAIL,  test_error = %0d", test_error);
    else	
          $display("TEST SUCCEED !test_error = %0d", test_error); 

endtask: pad0_test
