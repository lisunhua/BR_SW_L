#!/usr/bin/python  
# -*- coding:utf8 -*-  
  
import os
import sys  


DataBase ="/data/soc/BR8051A01/blocks/asher/DM50_Sim_Data/"


corr_code ="soc_tb.DUT.u_dig_top.u_bb_domain.u_rw_btdm_top_wrap.u_btdm50_mdm_core.corr_code[63:0]"
bt_dp_hec_crc_word = "soc_tb.DUT.u_dig_top.u_bb_domain.u_rw_btdm_top_wrap.u_rw_btdm_top.\
u_rw_bt_core.u_rw_bt_core_cntl.u_rw_bt_packet_cntl.u_rw_bt_packet_cntl_main_fsm.\
dp_hec_crc_word[7:0]"
le_crc_init_value ="soc_tb.DUT.u_dig_top.u_bb_domain.u_rw_btdm_top_wrap.u_rw_btdm_top.u_rw_ble_core.\
u_rw_ble_core_cntl.u_rw_ble_packet_cntl.u_rw_ble_packet_cntl_main_fsm.crc_init_value[23:0]"


IQdata_depth="soc_tb.u_agc_sim_m.IQdata_depth"
PAD_LOAD_DEPTH="soc_tb.u_agc_sim_m.pad_load_depth"

BLE_TYPE = 2
BR_TYPE  = 1

def file_name(file_dir):
    for root,dirs,files,in os.walk(file_dir):
        return root,dirs,files


def file_size(fil):
    coun=0;
    for x in fil.split("\n"):
        coun+=1
    return coun

def saveFile(name,file,gz):
    with open(name,gz) as f:
        f.write(file)

def ReadFile(name,gz):
    with open(name,gz) as f:
        return f.read()


def check_file(file):
    if os.path.isfile(file):
        pass
    else:
        print(file+" Not Find !")
        exit()

def SetLen(str_s,leng):
    while len(str_s)<leng:
        str_s ="0"+str_s
    if len(str_s)>leng:
        print(str_s)
        str_s = str_s[0:leng-1]

    return str_s

if __name__ == '__main__':
    # print("argv:"+ str(len(sys.argv)))
    if len(sys.argv) < 2:
        print("please Input Path!")
        exit()

    caseType = 0;
    dir_name = os.getcwd().split("/")[-1]
    # root,dirs,files = file_name("./");
    # print(root,dirs,files)
    if dir_name.find("bb_bt_br_") !=-1:
        dir_name = dir_name.split("bb_bt_br_")[-1]
        caseType = BR_TYPE   #BR Case
    elif  dir_name.find("bb_bt_le_") !=-1:
        dir_name = dir_name.split("bb_bt_le_")[-1]
        caseType = BLE_TYPE   #BLE Case


    if caseType==0:
        print("name Error")
        exit()

    print("----------------------------------------------------------------")
    check_file("case_sim_ctrl.ucli")
    check_file(DataBase+dir_name+"/CRCInit.txt")
    check_file(DataBase+dir_name+"/syncword.txt")

    check_file(DataBase+dir_name+"/rx_sig24M_i.txt")
    check_file(DataBase+dir_name+"/rx_sig24M_q.txt")

    check_file(DataBase+dir_name+"/Payload.txt")

    print(dir_name)

    ucil     = ReadFile("case_sim_ctrl.ucli","r")
    CrcInit  = ReadFile(DataBase+dir_name+"/CRCInit.txt","r")
    Syncword = ReadFile(DataBase+dir_name+"/syncword.txt","r")


    rx_sig24M_i = ReadFile(DataBase+dir_name+"/rx_sig24M_i.txt","r")
    rx_sig24M_q = ReadFile(DataBase+dir_name+"/rx_sig24M_q.txt","r")

    payload = ReadFile(DataBase+dir_name+"/Payload.txt","r")
    
    datedepth = 0
    i_depth= file_size(rx_sig24M_i);
    q_depth= file_size(rx_sig24M_q);
    if i_depth>q_depth:
        datedepth = q_depth
    else:
        datedepth = i_depth

    payload_depth = file_size(payload);

    
    CrcInit_bin="";
    for ui in CrcInit.split("\n"):
        CrcInit_bin=str(ui)+CrcInit_bin;
    CrcInit_bin = CrcInit_bin.replace(" ","")


    Syncword_bin="";
    for ui in Syncword.split("\n"):
        Syncword_bin=str(ui)+Syncword_bin;
    Syncword_bin = Syncword_bin.replace(" ","")



    Syncword_bin = SetLen(Syncword_bin,64);
    Syncword_bin = format(int(Syncword_bin,2),"x")
    Syncword_bin = "64'h"+Syncword_bin

    if caseType==BR_TYPE:
        CrcInit_bin  = SetLen(CrcInit_bin,8);
        CrcInit_bin = format(int(CrcInit_bin,2),"x")
        CrcInit_bin  = "8'h"+CrcInit_bin
    elif caseType==BLE_TYPE:
        CrcInit_bin  = SetLen(CrcInit_bin,24);
        CrcInit_bin = format(int(CrcInit_bin,2),"x")
        CrcInit_bin  = "24'h"+CrcInit_bin

    new_ucil = ucil

    # print(CrcInit_bin)
    # print(Syncword_bin)

    crc_fg = True
    sync_fg = True
    depth = True
    payload_d =True

    for ui in ucil.split("\n"):
        if ui.find(corr_code) != -1:
            new_ucil = new_ucil.replace(ui,"force {"+corr_code+"} " +Syncword_bin)
            sync_fg = False
        elif ui.find(bt_dp_hec_crc_word) != -1:
            if  caseType==BR_TYPE:
                crc_fg = False;
                new_ucil = new_ucil.replace(ui,"force {"+bt_dp_hec_crc_word+"} " +CrcInit_bin)
            else:
                new_ucil = new_ucil.replace(ui+"","");
        elif ui.find(le_crc_init_value) != -1:
            if caseType==BLE_TYPE:
                crc_fg = False;
                new_ucil = new_ucil.replace(ui,"force {"+le_crc_init_value+"} " +CrcInit_bin)
            else:
                new_ucil = new_ucil.replace(ui,"")
        elif ui.find(IQdata_depth) !=-1:
            new_ucil = new_ucil.replace(ui,"force {"+IQdata_depth+"} " +"32'h"+format(datedepth,"x"))
            depth=False
        elif ui.find(PAD_LOAD_DEPTH) !=-1:
            new_ucil = new_ucil.replace(ui,"force {"+PAD_LOAD_DEPTH+"} " +"32'h"+format(payload_depth,"x"))
            payload_d=False


    if crc_fg:
        if caseType==BLE_TYPE:
            new_ucil = new_ucil.replace("run 10us","run 10us\nforce {"+le_crc_init_value+"} " +CrcInit_bin)
        elif   caseType==BR_TYPE:
            new_ucil = new_ucil.replace("run 10us","run 10us\nforce {"+bt_dp_hec_crc_word+"} " +CrcInit_bin)

    if sync_fg:
        new_ucil = new_ucil.replace("run 10us","run 10us\nforce {"+corr_code+"} " +Syncword_bin)


    if depth:
        new_ucil = new_ucil.replace("run 10us","run 10us\nforce {"+IQdata_depth+"} " +"32'h"+format(datedepth,"x"))

    if payload_d:
        new_ucil = new_ucil.replace("run 10us","run 10us\nforce {"+PAD_LOAD_DEPTH+"} " +"32'h"+format(payload_depth,"x"))

    print(new_ucil)
    saveFile("case_sim_ctrl.ucli",new_ucil,"w");


	
	
	