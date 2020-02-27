#-*-coding:utf-8-*-
############################################################################
#describe： Generate V file from the pin mux map of excel
#auth：     merger
#date：     019-07-12
#Run:      
############################################################################
import os
import sys

sys.path.append("..")
sys.path.append("./tools")

import xlrd
import cm2gt
import gPinTmSt


def handleDataCell(In,Out,nme):
    while len(In)<40:
        In+=" "

    while len(Out)<17:
        Out+=" "   
    return "\
    check_in_testmode ("+In+","+Out+",scan_in_error,\""+nme+"  _INPUT\");\n"
    


def handleDataline(i,sheet,ppth_n,ipth_n,nm_n):

    pin_path = sheet.col_values(ppth_n)[1]
    ip_path  = sheet.col_values(ipth_n)[i]
    name     = sheet.col_values(nm_n  )[i]
    i_back = 1
    while(ip_path==""):       
        ip_path  = sheet.col_values(ipth_n)[i-i_back]
        i_back+=1
        # print("path:"+str(i_back) +ip_path)
    if name == "":
        return ""
    else:
        return handleDataCell(ip_path+"."+name,  pin_path,  pin_path.split(".")[-1]+"_"+ip_path.replace("`","")+"."+name)


def handle_ScanTCodesparsing(sheet):
    File    = ""
    #78 8 
    # print(sheet.nrows,sheet.ncols)
    for i in range(1,sheet.nrows): 
        File+=handleDataline(i,sheet,2,3,4)

    for i in range(1,sheet.nrows): 
        File+=handleDataline(i,sheet,5,6,7)
        # print(sheet.col_values(3)[i+0])
    # File += "" if File =="" else "    #10\n" 
    return  File


