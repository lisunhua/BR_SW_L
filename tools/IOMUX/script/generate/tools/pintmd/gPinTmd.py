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


#start pin 
TEST_PIN_S = 20
#pin num
TEST_PIN_N = 3


trail = "\n\
// check task \n\
task check_in_testmode (left_sigin,right_sigal,int error_count,string name); \n\
//  #10;// it would tested the value of singal 10ns ago;\n\
  if (left_sigin !== right_sigal) \n\
    begin\n\
      error_count = error_count + 1;\n\
      $display(\"%t %s left signal is %b, right signal is %b test FAIL!!!!!!!!!!\",$realtime,name,left_sigin,right_sigal);\n\
    end //else\n\
    //$display(\"%t %s left signal is %b, right signal is %b test RIGHT\",$realtime,name,left_sigin,right_sigal);\n\
  #10;\n\
endtask: check_in_testmode"

trail_scan = "\n\
// check task \n\
task check_in_testmode (left_sigin,right_sigal,int error_count,string name); \n\
//  #10;// it would tested the value of singal 10ns ago;\n\
  if (left_sigin !== right_sigal) \n\
    begin\n\
      error_count = error_count + 1;\n\
      $display(\"%t %s left signal is %b, right signal is %b test FAIL!!!!!!!!!!\",$realtime,name,left_sigin,right_sigal);\n\
    end //else\n\
    //$display(\"%t %s left signal is %b, right signal is %b test RIGHT\",$realtime,name,left_sigin,right_sigal);\n\
    force `DUT_XRM.TEST = 0;\n\
  #10;\n\
endtask: check_in_testmode"


#funcations
############################################################################
def SaveFile(name,file,gz):
    with open(name,gz) as f:
        f.write(file)

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

    data_O  = { "OEN":sheet.row_values(idx+0)[1],"IE":sheet.row_values(idx+0)[2],"REN":sheet.row_values(idx+0)[3]}
    data_I  = { "OEN":sheet.row_values(idx+1)[1],"IE":sheet.row_values(idx+1)[2],"REN":sheet.row_values(idx+1)[3]}
    data_NA = { "OEN":sheet.row_values(idx+2)[1],"IE":sheet.row_values(idx+2)[2],"REN":sheet.row_values(idx+2)[3]}
    data_gz = { "OEN":sheet.row_values(idx+3)[1],"IE":sheet.row_values(idx+3)[2],"REN":sheet.row_values(idx+3)[3]}
    # print(data_O)
    # print(data_I)
    # print(data_NA)
    # print(data_gz)
    return {"O":data_O,"I":data_I,"N/A":data_NA,"GZ":data_gz} 


def handleDataCheck(ppath,pinpath,func,tname,fg):
    if ppath == "":
        print("Error: "+tname+ " test mode:"+str(func)+" ppath is null")
        exit()

    if func>0 and pinpath == "" and fg =="I":
            pinpath = "`IOMUX_XRM."+tname+"_test_pad2core["+ppath.split("[")[-1]

    if func>0 and pinpath == "" and fg =="O":
            pinpath = "`IOMUX_XRM."+tname+"_test_core2pad["+ppath.split("[")[-1]

    if func ==0 and pinpath == "":
        print("warning: "+tname+ " test mode: "+ppath+" "+str(func)+" pinpath is null")

    if func >0 and pinpath == "":
        print("Error: "+tname+ " test mode: "+ppath+" "+str(func)+" pinpath is null")
        exit()

    # if tname == "scan":
    #     print(tname +" "+fg +" "+pinpath)

    return pinpath

def handleDataMtI(sidx,sheet,dpath_n,ppath_n,opath_n,ipath_n,func,tname):
    cell =""
    pinpath = ""
    rel_cell =""

    for i in range(sidx,sheet.nrows): 
        if sheet.col_values(dpath_n)[i] == "I":
            pinpath = handleDataCheck(sheet.col_values(ppath_n)[i],sheet.col_values(ipath_n)[i],func,tname,"I")
            cell += "\
    force "+sheet.col_values(ppath_n)[i]+"  = $urandom;\n"
            rel_cell +="\
    release "+sheet.col_values(ppath_n)[i]+" ;\n"

    cell += "" if cell =="" else "    #10\n" 
    #######################################
    for i in range(sidx,sheet.nrows): 
        if sheet.col_values(dpath_n)[i] == "I":
            pinpath = handleDataCheck(sheet.col_values(ppath_n)[i],sheet.col_values(ipath_n)[i],func,tname,"I")
            cell += "\
    check_in_testmode ("+pinpath+","\
                        +sheet.col_values(ppath_n)[i]\
                        +","+tname+"_in_error,\""\
                        +sheet.col_values(ppath_n)[i].split(".")[-1]+\
                        "  _INPUT\");\n"

    # cell += "" if cell =="" else "    #10\n" 

    # cell+= rel_cell
    return cell ,rel_cell

def handleDataMtO(sidx,sheet,dpath_n,ppath_n,opath_n,ipath_n,func,tname):
    cell =""
    pinpath = ""
    rel_cell =""
    for i in range(sidx,sheet.nrows): 
        if sheet.col_values(dpath_n)[i] == "O":
            pinpath = handleDataCheck(sheet.col_values(ppath_n)[i],sheet.col_values(opath_n)[i],func,tname,"O")
            cell += "\
    force "+pinpath+"  = $urandom;\n"
            rel_cell +="\
    release "+pinpath+" ;\n"

    cell += "" if cell =="" else "    #10\n" 
    #######################################
    for i in range(sidx,sheet.nrows): 
        if sheet.col_values(dpath_n)[i] == "O":
            pinpath =handleDataCheck(sheet.col_values(ppath_n)[i],sheet.col_values(opath_n)[i],func,tname,"O")
            cell += "\
    check_in_testmode ("+sheet.col_values(ppath_n)[i]+","\
                        +pinpath\
                        +","+tname+"_out_error,\""\
                        +sheet.col_values(ppath_n)[i].split(".")[-1]+\
                        "  _OUTPUT\");\n"

    # cell += "" if cell =="" else "    #10\n" 
    # cell+= 
    return cell ,rel_cell


def hanleDataFuncMt(sidx,sheet,dpath_n,ppath_n,opath_n,ipath_n,func,tname,sheet_st):
    dpath_n = dpath_n+func*5
    opath_n = opath_n+func*5
    ipath_n = ipath_n+func*5
    STCode =""

    codes = "\
    \n\n//======================"+tname+" test=====================\n"
    codes +="\n\
    //Enbale Test mode\n\
    force `DUT_XRM.TEST = 1;\n"
    if func == 1:
        STCode = gPinTmSt.handle_ScanTCodesparsing(sheet_st)
        codes+="\
    force `GPIO_XRM.gpio_intrclk_en = 1'b1 ;\n"
        codes+="\
    #10\n"
    codes += "\
    force `DUT_XRM.GPIO["+str(TEST_PIN_S+TEST_PIN_N-1)+":"+str(TEST_PIN_S)+"]        = "+str(func + (0 if func ==0 else 3))+"; //0--func mode,\
4--scan mode, 5--mbist mode,6--bsd mode\n"
    
    codes+="\
    #10\n\
    check_in_testmode (1'b1,`DUT_XRM.GPIO[29],"+tname+"_in_error"+",\"GPIO[29]  _INPUT\");\n\
    check_in_testmode (1'b1,`DUT_XRM.GPIO[30],"+tname+"_in_error"+",\"GPIO[30]  _INPUT\");\n\
    check_in_testmode (1'b1,`DUT_XRM.GPIO[31],"+tname+"_in_error"+",\"GPIO[31]  _INPUT\");\n\
    check_in_testmode (1'b1,`DUT_XRM.GPIO[32],"+tname+"_in_error"+",\"GPIO[32]  _INPUT\");\n\
    check_in_testmode (1'b1,`DUT_XRM.GPIO[33],"+tname+"_in_error"+",\"GPIO[33]  _INPUT\");\n\
    check_in_testmode (1'b1,`DUT_XRM.GPIO[34],"+tname+"_in_error"+",\"GPIO[34]  _INPUT\");\n\
    #10\n";
    
    cellI,rele_cellI = handleDataMtI(sidx,sheet,dpath_n,ppath_n,opath_n,ipath_n,func,tname)
    cellO,rele_cellO = handleDataMtO(sidx,sheet,dpath_n,ppath_n,opath_n,ipath_n,func,tname)  
    # if func == 1:
    #     STCode = gPinTmSt.handle_ScanTCodesparsing(sheet_st)
    #     codes+="\
    # #10\n"
    #     codes+="\
    # force `GPIO_XRM.gpio_intrclk_en = 1'b1 ;\n"
        
    codes += "" if cellI =="" else ("//======================  I ===============\
=========\n"+cellI + STCode +("" if codes =="" else "    #10\n" )+ rele_cellI \
    +"\
    if ("+tname+"_in_error !== 0)\n\
        $display(\""+tname+" mode input test FAIL\");\n\
    else\n\
        $display(\""+tname+" mode input test PASS\");\n")

    codes += "" if cellO =="" else ("//======================  O ================\
========\n"+ "\n\
    release   `DUT_XRM.GPIO["+str(TEST_PIN_S-1)+":0];\n\
    release   `DUT_XRM.GPIO["+str(sheet.nrows-sidx-1)+":"+str(TEST_PIN_S+TEST_PIN_N)+"];\n"\
    +cellO +("" if codes =="" else "    #10\n" )+ rele_cellO \
    + "\n\
    if ("+tname+"_out_error !== 0)\n\
        $display(\""+tname+" mode output test FAIL\");\n\
    else\n\
        $display(\""+tname+" mode output test PASS\");\n")

    if func == 1:
        codes += "" if codes =="" else  "\n\
    release  `GPIO_XRM.gpio_intrclk_en;\n"

    codes +="\n\
    //Disable Test mode\n\
    force `DUT_XRM.TEST = 0;\n\
    #1000;\n"


    return codes


############################################################################
def handle_excel_parsing(workbook,sheet_index,file_type):
    File   = "//Automatically generate file.\n\n"
    File  += "`include \"inputs/soc_top/sim/tb/inc/chip_def.inc\"\n\n"
    File  +="task iomux_"+file_type+"_testmode;\n"
    


    File +="\
    reg func_in_error;\n\
    reg func_out_error;\n\
    reg scan_in_error;\n\
    reg scan_out_error;\n\
    reg mbist_in_error;\n\
    reg mbist_out_error;\n\
    reg bsd_in_error;\n\
    reg bsd_out_error;\n\
\n\
    func_in_error = 0;\n\
    func_out_error = 0;\n\
    scan_in_error = 0;\n\
    scan_out_error = 0;\n\
    mbist_in_error = 0;\n\
    mbist_out_error = 0;\n\
    bsd_in_error = 0;\n\
    bsd_out_error = 0;\n\
"
    # File +="\n//Enbale Test mode\n\
    # force `DUT_XRM.TEST = 1;\n"


    index   = 0
    run     = 0

    sheet_tm = workbook.sheet_by_index(sheet_index)        # sheet 1  TEST MODE
    db = handleDataDictionary(sheet_tm,sheet_tm.nrows)       #fill  dictionary
    for i in range(0,sheet_tm.nrows-2):               #Find Start row
        if  sheet_tm.col_values(0)[i+0]== "PIN NUM"   and \
            sheet_tm.col_values(0)[i+1]== ""          and \
            sheet_tm.col_values(0)[i+2]== 0           and \
            sheet_tm.col_values(0)[i+3]== 1:
            index = i+2
            run = 1
            break

    if run == 0:
        print("File Error")
        exit()    

    if file_type=="func":
        File += hanleDataFuncMt(index,sheet_tm,2,1,4,6,0,"func" ,workbook.sheet_by_index(sheet_index+1))
    if file_type=="scan":
        File += hanleDataFuncMt(index,sheet_tm,2,1,4,6,1,"scan" ,workbook.sheet_by_index(sheet_index+1))
    if file_type=="mbist":
        File += hanleDataFuncMt(index,sheet_tm,2,1,4,6,2,"mbist",workbook.sheet_by_index(sheet_index+1))
    if file_type=="bsd":
        File += hanleDataFuncMt(index,sheet_tm,2,1,4,6,3,"bsd"  ,workbook.sheet_by_index(sheet_index+1))

    if file_type=="all":
        File += hanleDataFuncMt(index,sheet_tm,2,1,4,6,0,"func" ,workbook.sheet_by_index(sheet_index+1))
        File += hanleDataFuncMt(index,sheet_tm,2,1,4,6,1,"scan" ,workbook.sheet_by_index(sheet_index+1))
        File += hanleDataFuncMt(index,sheet_tm,2,1,4,6,2,"mbist",workbook.sheet_by_index(sheet_index+1))
        File += hanleDataFuncMt(index,sheet_tm,2,1,4,6,3,"bsd"  ,workbook.sheet_by_index(sheet_index+1))



    # File += "\n\n\
    # force `DUT_XRM.TEST = 0;\n"
    File += "endtask: iomux_"+file_type+"_testmode"
    # if file_type=="scan":
    #     File +="\n\n"+trail_scan +"\n\n"
    # else:
    #     File +="\n\n"+trail +"\n\n"
    File +="\n\n"+trail +"\n\n"
    return File,sheet_tm.name



def handle_test_code_parsing(workbook,sheet_index):
    File    = "//Test the code in test mode \n"
    index   = 0
    run     = 0

    sheet_tm = workbook.sheet_by_index(sheet_index)        # sheet 1  TEST MODE
    db = handleDataDictionary(sheet_tm,sheet_tm.nrows)       #fill  dictionary
    for i in range(0,sheet_tm.nrows-2):               #Find Start row
        if  sheet_tm.col_values(0)[i+0]== "PIN NUM"   and \
            sheet_tm.col_values(0)[i+1]== ""          and \
            sheet_tm.col_values(0)[i+2]== 0           and \
            sheet_tm.col_values(0)[i+3]== 1:
            index = i+2
            run = 1
            break

    if run == 0:
        print("File Error")
        exit()    


    return  File





############################################################################
def read_excel(file,file_type):
    workbook = xlrd.open_workbook(file)
    return handle_excel_parsing(workbook,1,file_type) #only parsing page 1
    


############################################################################
if __name__ == '__main__':
    dict_argc  = {"FileInput": "","FileOUTput":"","FileType":""}
    dict_argc = cm2gt.cmdParseArgv(dict_argc)

    ##################
    if dict_argc["FileInput"] == "":
        print("error :FileInput is null")
        exit()

    ##################
    if dict_argc["FileOUTput"] == "":
        print("warning :FileOUTput is null")


   #_____________________________________________________________________     
    codes,name      = read_excel(dict_argc["FileInput"],dict_argc["FileType"])    
    
    if dict_argc["FileOUTput"] =="":
        dict_argc["FileOUTput"]    =  name+".v"

    SaveFile(dict_argc["FileOUTput"],codes,"w")

    print("File Path:"+ dict_argc["FileInput"])
    print("File Save to:"+dict_argc["FileOUTput"])
