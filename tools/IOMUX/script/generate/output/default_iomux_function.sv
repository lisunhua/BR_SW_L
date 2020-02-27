//Automatically generate file.

`include "inputs/soc_top/sim/tb/inc/chip_def.inc"

task iomux_function_default;

  reg test_error = 0;
  force `DUT_XRM.TEST = 0;

//##################GPIO[0]-------------------------------------
//O
    release  `DUT_XRM.GPIO[0];    force    `UART0_XRM.sout = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[0] , `UART0_XRM.sout , "GPIO[0]" ,'h0 ,test_error ,"OUT");



//##################GPIO[1]-------------------------------------
//I
    release  `UART0_XRM.sin;    force    `DUT_XRM.GPIO[1] = $urandom;
    #100;
    chech_in_function(`UART0_XRM.sin , `DUT_XRM.GPIO[1] , "GPIO[1]" ,'h0 ,test_error ,"IN");



//##################GPIO[2]-------------------------------------
//O
    release  `DUT_XRM.GPIO[2];    force    `UART0_XRM.rts_n = $urandom;
    #100;
    chech_in_function(`DUT_XRM.GPIO[2] , `UART0_XRM.rts_n , "GPIO[2]" ,'h0 ,test_error ,"OUT");



//##################GPIO[3]-------------------------------------
//I
    release  `UART0_XRM.cts_n;    force    `DUT_XRM.GPIO[3] = $urandom;
    #100;
    chech_in_function(`UART0_XRM.cts_n , `DUT_XRM.GPIO[3] , "GPIO[3]" ,'h0 ,test_error ,"IN");



//##################GPIO[4]-------------------------------------
//I
    release  `M3_XRM.SWCLKTCK;    force    `DUT_XRM.GPIO[4] = $urandom;
    #100;
    chech_in_function(`M3_XRM.SWCLKTCK , `DUT_XRM.GPIO[4] , "GPIO[4]" ,'h0 ,test_error ,"IN");



//##################GPIO[5]-------------------------------------
//I of IO
    release  `M3_XRM.SWDITMS;
    release  `M3_XRM.SWDOEN;
    force    `DUT_XRM.GPIO[5] = $urandom;
    #100;
    chech_in_function(`M3_XRM.SWDITMS , `DUT_XRM.GPIO[5] , "GPIO[5]" ,'h0 ,test_error ,"IN");

//O of IO
    release  `DUT_XRM.GPIO[5];    force    `M3_XRM.SWDO = $urandom;
    force    `M3_XRM.SWDOEN = 'b1;    //OEN=0 
    #100;
    chech_in_function(`DUT_XRM.GPIO[5] , `M3_XRM.SWDO , "GPIO[5]" ,'h0 ,test_error ,"OUT");



//##################GPIO[6]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[6] , 1'bZ , "GPIO[6]" ,'h0 ,test_error ,"OUT");



//##################GPIO[7]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[7] , 1'bZ , "GPIO[7]" ,'h0 ,test_error ,"OUT");



//##################GPIO[8]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[8] , 1'bZ , "GPIO[8]" ,'h0 ,test_error ,"OUT");



//##################GPIO[9]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[9] , 1'bZ , "GPIO[9]" ,'h0 ,test_error ,"OUT");



//##################GPIO[10]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[10] , 1'bZ , "GPIO[10]" ,'h0 ,test_error ,"OUT");



//##################GPIO[11]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[11] , 1'bZ , "GPIO[11]" ,'h0 ,test_error ,"OUT");



//##################GPIO[12]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[12] , 1'bZ , "GPIO[12]" ,'h0 ,test_error ,"OUT");



//##################GPIO[13]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[13] , 1'bZ , "GPIO[13]" ,'h0 ,test_error ,"OUT");



//##################GPIO[14]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[14] , 1'bZ , "GPIO[14]" ,'h0 ,test_error ,"OUT");



//##################GPIO[15]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[15] , 1'bZ , "GPIO[15]" ,'h0 ,test_error ,"OUT");



//##################GPIO[16]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[16] , 1'bZ , "GPIO[16]" ,'h0 ,test_error ,"OUT");



//##################GPIO[17]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[17] , 1'bZ , "GPIO[17]" ,'h0 ,test_error ,"OUT");



//##################GPIO[18]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[18] , 1'bZ , "GPIO[18]" ,'h0 ,test_error ,"OUT");



//##################GPIO[19]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[19] , 1'bZ , "GPIO[19]" ,'h0 ,test_error ,"OUT");



//##################GPIO[20]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[20] , 1'bZ , "GPIO[20]" ,'h0 ,test_error ,"OUT");



//##################GPIO[21]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[21] , 1'bZ , "GPIO[21]" ,'h0 ,test_error ,"OUT");



//##################GPIO[22]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[22] , 1'bZ , "GPIO[22]" ,'h0 ,test_error ,"OUT");



//##################GPIO[23]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[23] , 1'bZ , "GPIO[23]" ,'h0 ,test_error ,"OUT");



//##################GPIO[24]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[24] , 1'bZ , "GPIO[24]" ,'h0 ,test_error ,"OUT");



//##################GPIO[25]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[25] , 1'bZ , "GPIO[25]" ,'h0 ,test_error ,"OUT");



//##################GPIO[26]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[26] , 1'bZ , "GPIO[26]" ,'h0 ,test_error ,"OUT");



//##################GPIO[27]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[27] , 1'bZ , "GPIO[27]" ,'h0 ,test_error ,"OUT");



//##################GPIO[28]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[28] , 1'bZ , "GPIO[28]" ,'h0 ,test_error ,"OUT");



//##################GPIO[29]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[29] , 1'b1 , "GPIO[29]" ,'h0 ,test_error ,"OUT");



//##################GPIO[30]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[30] , 1'b1 , "GPIO[30]" ,'h0 ,test_error ,"OUT");



//##################GPIO[31]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[31] , 1'b1 , "GPIO[31]" ,'h0 ,test_error ,"OUT");



//##################GPIO[32]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[32] , 1'b1 , "GPIO[32]" ,'h0 ,test_error ,"OUT");



//##################GPIO[33]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[33] , 1'b1 , "GPIO[33]" ,'h0 ,test_error ,"OUT");



//##################GPIO[34]-------------------------------------
    chech_in_function(`DUT_XRM.GPIO[34] , 1'b1 , "GPIO[34]" ,'h0 ,test_error ,"OUT");









$display("TEST_ERROR = %d",test_error);
  if (test_error != 0)
    $display("tests are wrong.............................................");
  else begin
    $display("All tests are right!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  end
  endtask: iomux_function_default
