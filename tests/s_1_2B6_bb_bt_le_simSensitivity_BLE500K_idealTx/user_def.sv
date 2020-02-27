`timescale 1ns/1ps

module user_def;
    defparam  u_agc_sim_m.IQ_DATA_PATH_I = 
    "/data/soc/BR8051A01/blocks/asher/DM50_Sim_Data/simSensitivity_BLE500K_idealTx/rx_sig24M_i.txt";
    defparam  u_agc_sim_m.IQ_DATA_PATH_Q = 
    "/data/soc/BR8051A01/blocks/asher/DM50_Sim_Data/simSensitivity_BLE500K_idealTx/rx_sig24M_q.txt";
    defparam  u_agc_sim_m.PAY_lOAD_PATH = 
    "/data/soc/BR8051A01/blocks/asher/DM50_Sim_Data/simSensitivity_BLE500K_idealTx/Payload.txt";
    defparam  u_agc_sim_m.IQ_DATA_TYPE    = 1;
    defparam  u_agc_sim_m.PAD_LOAD_CPOINT = 1;
    defparam  u_agc_sim_m.BR_TYPE         = 2;
    
endmodule