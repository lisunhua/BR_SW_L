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

CODE_NUM_LEN = 30


#funcations
############################################################################
def SaveFile(name,file,gz):
    with open(name,gz) as f:
        f.write(file)

############################################################################
def STR_ICR_LEN(st,l):
    for le in range(len(st),l):
            st+=" "
    return st

############################################################################
def handleDataDictionary(sheet,length):
    idx = 0
    for i in range(0,length-2):
        if  sheet.col_values(0)[i+0]=="DIR" and \
            sheet.col_values(0)[i+1]=="I"   and \
            sheet.col_values(0)[i+2]=="O":
            idx = i+1
            break

    if idx > length-4:
        return

    data_I  = { "OEN":str(int(sheet.row_values(idx+0)[1])),\
                "IE":str(int(sheet.row_values(idx+0)[2])),\
                "REN":str(int(sheet.row_values(idx+0)[3]))}
    data_O  = { "OEN":str(int(sheet.row_values(idx+1)[1])),\
                "IE":str(int(sheet.row_values(idx+1)[2])),\
                "REN":str(int(sheet.row_values(idx+1)[3]))}
    data_NA = { "OEN":str(int(sheet.row_values(idx+2)[1])),\
                "IE":str(int(sheet.row_values(idx+2)[2])),\
                "REN":str(int(sheet.row_values(idx+2)[3]))}
    data_TM = { "OEN":str(int(sheet.row_values(idx+3)[1])),\
                "IE":str(int(sheet.row_values(idx+3)[2])),\
                "REN":str(int(sheet.row_values(idx+3)[3]))}
    data_GZ = { "OEN":str(int(sheet.row_values(idx+4)[1])),\
                "IE":str(int(sheet.row_values(idx+4)[2])),\
                "REN":str(int(sheet.row_values(idx+4)[3]))}
    # print(data_I)
    # print(data_O)
    # print(data_NA)
    # print(data_TM)
    # print(data_GZ)

    return {"I":data_I,"O":data_O,"N/A":data_NA,"TM":data_TM,"GZ":data_GZ} 


def handleDataCheck(ppath,pinpath,func,tname,fg):
    if ppath == "":
        print("Error: "+tname+ " test mode:"+str(func)+" ppath is null")
        exit()

    if func>0 and pinpath == "" and fg =="I":
            pinpath = ""+tname+"_test_pad2core["+ppath.split("[")[-1]

    if func>0 and pinpath == "" and fg =="O":
            pinpath = ""+tname+"_test_core2pad["+ppath.split("[")[-1]

    if func ==0 and pinpath == "":
        print("warning: "+tname+ " test mode: "+ppath+" "+str(func)+" pinpath is null")

    if func >0 and pinpath == "":
        print("Error: "+tname+ " test mode: "+ppath+" "+str(func)+" pinpath is null")
        exit()

    return pinpath

def handleDataMtI(sidx,sheet,dpath_n,ppath_n,opath_n,ipath_n,func,tname):
    cell =""
    for i in range(sidx,sheet.nrows): 
        if sheet.col_values(dpath_n)[i] == "I":
            pinpath = handleDataCheck(sheet.col_values(ppath_n)[i],sheet.col_values(ipath_n)[i],func,tname,"I")

            core = pinpath
            pad  = tname+"_test_pad2core["+sheet.col_values(ppath_n)[i].split("[")[-1]

            # print(core)
            if core == "" or core == pad or core == tname+"_test_pad2core["+sheet.col_values(ppath_n)[i].split("[")[-1]:
                pass
            else:
                cell += "assign "+core +"    = "+pad+";\n"

    return cell 

def handleDataMtO(sidx,sheet,dpath_n,ppath_n,opath_n,ipath_n,func,tname):
    cell =""
    pinpath = ""
    for i in range(sidx,sheet.nrows): 
        # pinpath =handleDataCheck(sheet.col_values(ppath_n)[i],sheet.col_values(opath_n)[i],func,tname,"O")
        core = sheet.col_values(opath_n)[i]
        pad  = tname+"_test_core2pad["+sheet.col_values(ppath_n)[i].split("[")[-1]

        if core == "":
            core = "1\'b0"

        pad = STR_ICR_LEN(pad,CODE_NUM_LEN)

        cell +="assign "+ pad+"    = "+core+";\n"

    return cell 


def hanleDataFuncP2C(sidx,sheet,dpath_n,ppath_n,opath_n,ipath_n,func,tname):
    dpath_n = dpath_n+func*5
    opath_n = opath_n+func*5
    ipath_n = ipath_n+func*5

    codes = ""
    codes += handleDataMtI(sidx,sheet,dpath_n,ppath_n,opath_n,ipath_n,func,tname)
    return codes

def hanleDataFuncC2P(sidx,sheet,dpath_n,ppath_n,opath_n,ipath_n,func,tname):
    dpath_n = dpath_n+func*5
    opath_n = opath_n+func*5
    ipath_n = ipath_n+func*5

    codes = ""
    codes += handleDataMtO(sidx,sheet,dpath_n,ppath_n,opath_n,ipath_n,func,tname)

    return codes

# 00000000000000000100111000000000000
def hanleDatadctparm(sidx,sheet,dpath_n,func,db,tname):
    trail = ""
    cot   = 0
    for i in range(len(tname),20):
        trail+=" "
    trail += "35\'b"

    REN = "`define TEST_" + tname.upper()+"_PAD_REN"+ trail
    IE  = "`define TEST_" + tname.upper()+"_PAD_IE "+ trail
    OE  = "`define TEST_" + tname.upper()+"_PAD_OE "+ trail

    REN_b = ""
    IE_b  = ""
    OE_b  = ""

    fc = dpath_n+func*5
    for i in range(sidx,sheet.nrows): 
        # print(sheet.col_values(fc)[i])
        if sheet.col_values(fc)[i] == "":
            pritn("Error : Fanc :"+str(fc) +"GPIO["+str(i)+"] is null")
        else:
            cot+=1
            td = "_" if cot%8 ==0 else ""

            REN_b += db[sheet.col_values(fc)[i]]["REN"] +td
            IE_b  += db[sheet.col_values(fc)[i]]["IE"]  +td
            OE_b  += db[sheet.col_values(fc)[i]]["OEN"] +td

    REN +=REN_b[::-1]
    IE  +=IE_b [::-1]
    OE  +=OE_b [::-1] 
    # print(REN)
    # print(IE)
    # print(OE)
    return REN +"\n"+IE +"\n"+OE +"\n"



def handle_test_code_parsing(sheet):
    File    = "\n\n//Test the code in test mode \n"
    index   = 0
    run     = 0

    for i in range(0,sheet.nrows-2):               #Find Start row
        if  sheet.col_values(0)[i+0]== "PIN NUM"   and \
            sheet.col_values(0)[i+1]== ""          and \
            sheet.col_values(0)[i+2]== 0           and \
            sheet.col_values(0)[i+3]== 1:
            index = i+2
            run = 1
            break

    if run == 0:
        print("File Error")
        exit()    

    File +="\n// from pad to core\n"
    # File += hanleDataFuncP2C(index,sheet,2,1,4-1,6-1,0,"func")
    File += hanleDataFuncP2C(index,sheet,2,1,4-1,6-1,1,"scan")
    # File += hanleDataFuncP2C(index,sheet,2,1,4-1,6-1,2,"mbist")
    # File += hanleDataFuncP2C(index,sheet,2,1,4-1,6-1,3,"bsd")

    File +="\n// from core to pad\n"
    File += hanleDataFuncC2P(index,sheet,2,1,4-1,6-1,0,"func")
    # File += hanleDataFuncC2P(index,sheet,2,1,4-1,6-1,1,"scan")
    # File += hanleDataFuncC2P(index,sheet,2,1,4-1,6-1,2,"mbist")
    # File += hanleDataFuncC2P(index,sheet,2,1,4-1,6-1,3,"bsd")

    db = handleDataDictionary(sheet,sheet.nrows)
    File +="\n//define \n"
    File += hanleDatadctparm(index,sheet,2,0,db,"func")
    File += hanleDatadctparm(index,sheet,2,1,db,"scan")
    File += hanleDatadctparm(index,sheet,2,2,db,"mbist")
    File += hanleDatadctparm(index,sheet,2,3,db,"bsd")

    return  File

