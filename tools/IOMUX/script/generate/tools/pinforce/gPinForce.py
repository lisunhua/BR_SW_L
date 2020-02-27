#-*-coding:utf-8-*-
############################################################################
#describe： Generate V file from the pin mux map of excel
#auth：     merger
#date：     019-07-12
#Run:       python gPinMux.py excel_file_path save_file
############################################################################

import os
import sys

# sys.path.append("../")
sys.path.append("./tools")

#sys.path.append(os.getcwd()+"/tool/")
#sys.path.append(os.getcwd()+"/pinmux/")
import xlrd
import cm2gt

OUTPUTFILE  = ""

FUNS        = 6             #MAX FUNS NUM
ITMES       = 7             #itmes define
FULLMUX_N   = 6
############################################################################
header_default="\
task iomux_function_default;\n\n\
  reg test_error = 0;\n\
  force `DUT_XRM.TEST = 0;\n\n"


############################################################################
trail_default = "\n\n\n\n\
$display(\"TEST_ERROR = %d\",test_error);\n\
  if (test_error != 0)\n\
    $display(\"tests are wrong.............................................\");\n\
  else begin\n\
    $display(\"All tests are right!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\");\n\
  end\n\
  endtask: iomux_function_default\n"


############################################################################
header = "\
task iomux_function;\n\n\
  reg test_error = 0;\n\
  force `DUT_XRM.TEST = 0;\n\n"


############################################################################
trail = "\n\n\n\n\
$display(\"TEST_ERROR = %d\",test_error);\n\
  if (test_error != 0)\n\
    $display(\"tests are wrong.............................................\");\n\
  else begin\n\
    $display(\"All tests are right!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\");\n\
  end\n\
endtask: iomux_function\n\n\
task chech_in_function (bit left_signal, bit right_signal, string name,int function_num,\
 int error_count, string in_out);\n\
  if (left_signal != right_signal) begin\n\
      error_count = error_count + 1; \n\
      $display(\"%t L = %b, R = %b,GPIO_bit = %s test FAIL,function_num = %0x,test_error = \
%0d,direction = %s!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\",$realtime,left_signal,\
right_signal,name,function_num,error_count,in_out);\n\
    end\n\
    #1000;\n\
endtask: chech_in_function\n"



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
            sheet.col_values(0)[i+1]=="O"   and \
            sheet.col_values(0)[i+2]=="O1":
            idx = i+1
            break

    if idx > length-4:
        return

    data_O  = { "OEN":sheet.row_values(idx+0)[1],"IEN":sheet.row_values(idx+0)[2],
                "OUT":sheet.row_values(idx+0)[3],"IN" :sheet.row_values(idx+0)[4].split("[")[0]}
    data_O1 = { "OEN":sheet.row_values(idx+1)[1],"IEN":sheet.row_values(idx+1)[2],
                "OUT":sheet.row_values(idx+1)[3],"IN" :sheet.row_values(idx+1)[4].split("[")[0]}
    data_I  = { "OEN":sheet.row_values(idx+2)[1],"IEN":sheet.row_values(idx+2)[2],
                "OUT":sheet.row_values(idx+2)[3],"IN" :sheet.row_values(idx+2)[4].split("[")[0]}
    data_IO = { "OEN":sheet.row_values(idx+3)[1],"IEN":sheet.row_values(idx+3)[2],
                "OUT":sheet.row_values(idx+3)[3],"IN" :sheet.row_values(idx+3)[4].split("[")[0]}
    data_NA = { "OEN":sheet.row_values(idx+4)[1],"IEN":sheet.row_values(idx+4)[2],
                "OUT":sheet.row_values(idx+4)[3],"IN" :sheet.row_values(idx+4)[4].split("[")[0]}
    data_IO1= { "OEN":sheet.row_values(idx+5)[1],"IEN":sheet.row_values(idx+5)[2],
                "OUT":sheet.row_values(idx+5)[3],"IN" :sheet.row_values(idx+5)[4].split("[")[0]}
    # print(data_O)
    # print(data_O1)
    # print(data_I)
    # print(data_IO)
    # print(data_NA)
    return {"O":data_O,"O1":data_O1,"I":data_I,"IO":data_IO,"N/A":data_NA,"IO1":data_IO1} 


############################################################################
def handleDataCheckDict(db,idx,h,l):
    if db.has_key(idx):
        return db[idx]
    else:
        print ("Error: Dictionary sit",h,l,idx)
        exit()

def handlecell(defa,fg,path,Out_p,In_p,path_oe,oen_agt,pin,time,oen_val,val,pt_type,fullmux_en):
    cell_1 = "//"+fg+"\n\
    release  "+ Out_p+";"
    
    cell_2 ="\
    force    "+ In_p+ " = $urandom;\n"

    cell_3 ="\
    force    `IOMUX_XRM.pad_cfg[ "+str(pin)+"*8+:8] = 'h"+str(val)+";  \n"
    cell_4 ="\
    force    "+ path_oe+" = 'b"+str((1 if oen_val==0 else 0) if oen_agt == 1 else oen_val) +";    //OEN="+str(oen_val)+" \n"
    cell_5="\
    #100;\n\
    chech_in_function("+Out_p+" , "+ In_p+ " , \""+path.split(".")[-1]+"\" ,'h"+str(val)+" ,test_error ,\""+pt_type+"\");"
    
    if fullmux_en == 1:  #FULL MUX NO NEED PAD_CFG
        cell_3=""

    if OUTPUTFILE == "default":
        cell_3=""

    if OUTPUTFILE == "default" and fg == "I of IO":  #notice fg change,for the time doing 
        cell_1 +="\n\
    release  "+path_oe+";\n"

    cell =""
    if defa   == 0:
        cell = cell_1+cell_2+cell_5
    elif defa == 1:
        cell = cell_1+cell_2+cell_3+cell_5
    elif defa == 2:
        cell = cell_1+cell_2+cell_3+cell_4+cell_5

    elif defa == 3:
        cell = cell_1+cell_5
    elif defa == 4:
        cell = cell_1+cell_3+cell_5
    elif defa == 5:
        cell = cell_1+cell_3+cell_4+cell_5

    elif defa ==6:
        cell ="\
    chech_in_function("+Out_p+" , "+ In_p+ " , \""+path.split(".")[-1]+"\" ,'h"+str(val)+" ,test_error ,\""+pt_type+"\");"

    return cell

def handleCellCheckExit(path,Out_p,In_p,fg,path_oe,icr_cell,num):
    if fg:
        if path_oe == "":
            print("Error"+str(num)+": OEN Path Is Null: "+ path + "  Funcation:"+str(icr_cell))
            exit()
    else:
        if path=="" or Out_p=="" or In_p=="":
            print("Error"+str(num)+": Path Is Null: "+ path + "  Funcation:"+str(icr_cell))
            exit()

def handleCellIO(fg,path,path_oe,path_out,path_in,pin,icr_cell,inc,fullmux_en):
    cell    = ""
    In_p    = ""
    Out_p   = ""
    IOtype  = ""

    defa    = 0 #0: no force ; 1:force clt,no oen; 2:force clt and oen
    oen_agt = 0
    oen_val = 0

    if path_oe == "":
        pass
    else:
        if path_oe[0] == "~":
            path_oe = path_oe.split("~")[-1]
            oen_agt = 1

    if icr_cell==0:
        pass
    else:
        defa=1

    if OUTPUTFILE == "default":
        if defa ==1:
            inc+=1
            icr_cell+=1
            return cell,icr_cell,inc

    else:
        if defa == 0:
            defa=1

    if   fg=="I":
        In_p    = path
        Out_p   = path_in
        IOtype  = "IN"
        oen_val = 1

    elif fg=="O":
        In_p    = path_out 
        Out_p   = path
        IOtype  = "OUT"
        oen_val = 0

    elif fg=="IO":
        In_p   = path
        Out_p  = path_in
        IOtype = "IN"
        fg = "I of IO"
        oen_val = 1

        handleCellCheckExit(path,Out_p,In_p,0,path_oe,icr_cell,1)
        if defa==0:
            cell += handlecell(defa,fg,path,Out_p,In_p,path_oe,oen_agt,pin,inc*1000,oen_val,icr_cell*10,IOtype,fullmux_en) +"\n\n"
           
        else:
            defa  = 2
            handleCellCheckExit(path,Out_p,In_p,1,path_oe,icr_cell,2)
            cell += handlecell(defa,fg,path,Out_p,In_p,path_oe,oen_agt,pin,inc*1000,oen_val,icr_cell*10,IOtype,fullmux_en) +"\n\n"
        
        defa=2
        handleCellCheckExit(path,Out_p,In_p,1,path_oe,icr_cell,3)
        inc+=1
        fg = "O of IO"
        In_p   = path_out 
        Out_p  = path
        IOtype = "OUT"
        oen_val = 0

    elif fg=="IO1":
        In_p   = path
        Out_p  = path_in
        IOtype = "IN"
        fg = "I of IO1"
        oen_val = 1

        handleCellCheckExit(path,Out_p,In_p,0,path_oe,icr_cell,1)
        if defa==0:
            defa = 3
            cell += handlecell(defa,fg,path,Out_p,In_p,path_oe,oen_agt,pin,inc*1000,oen_val,icr_cell*10,IOtype,fullmux_en) +"\n\n"
           
        else:
            defa  = 2
            defa  = 5
            handleCellCheckExit(path,Out_p,In_p,1,path_oe,icr_cell,2)
            cell += handlecell(defa,fg,path,Out_p,In_p,path_oe,oen_agt,pin,inc*1000,oen_val,icr_cell*10,IOtype,fullmux_en) +"\n\n"
        
        defa  = 2
        defa  = 5
        inc+=1
        fg = "O of IO1"
        In_p   = path_out 
        Out_p  = path
        IOtype = "OUT"
        oen_val = 0

    elif fg=="O1":
        In_p    = path_out 
        Out_p   = path
        IOtype  = "OUT"
        oen_val = 0
        defa  = 2

    elif fg == "N/A":
        icr_cell+=1
        return cell,icr_cell,inc

    elif fg =="Z":
        In_p    = "1'bZ"
        Out_p   = path
        IOtype  = "OUT"
        oen_val = 0
        defa    = 6

    elif fg =="Y":
        In_p    = "1'b1" 
        Out_p   = path
        IOtype  = "OUT"
        oen_val = 0
        defa    = 6


    handleCellCheckExit(path,Out_p,In_p,0,path_oe,icr_cell,4)

    cell += handlecell(defa,fg,path,Out_p,In_p,path_oe,oen_agt,pin,inc*1000,oen_val,icr_cell*10,IOtype,fullmux_en) +"\n\n"
    
    inc+=1
    icr_cell+=1

    # print(path)
    # print(path_oe)
    # print(path_out)
    # print(path_in)
    return cell,icr_cell,inc


def handleDataFmHeader(idx,val):
    full_mux_header = "\
//##################GPIO["+str(idx)+":"+str(idx+FULLMUX_N-1)+"\
] function"+str(val)+" -------------------------------------\n"
    for i in range(FULLMUX_N):
        full_mux_header+="\
    force    `IOMUX_XRM.pad_cfg[ "+str(idx+i)+"*8+:8] = 'h"+str(val*10)+";\n"
    return full_mux_header



# inc_cell is  Function num
# h-index is   PIN num

############################################################################
def handleDataToFM(rows,length,hight,fulmux_idx,start_idx):   
    itmes    = ITMES   #itmes  

    Start_row = 2  if OUTPUTFILE == "default" else 9
    funcs = 0;
    pin   = fulmux_idx-start_idx
    cells =  ""
    code  =  ""

    for i in range(Start_row,length,itmes):   #FUNSTION LOOP
        code  +=  handleDataFmHeader(fulmux_idx-start_idx,funcs)
        pin+=1

        pin_idx = fulmux_idx-start_idx
        for idx in range(fulmux_idx,hight):
            cells,inc_cell,inc = handleCellIO(  rows(idx)[i],
                                                rows(idx)[1],
                                                rows(idx)[i+2],
                                                rows(idx)[i+4],
                                                rows(idx)[i+6],
                                                pin_idx, #PIN NUM
                                                funcs, #func_num
                                                0,1)
            pin_idx+=1

            if cells=="":
                pass
            else:
                code += cells

        funcs+=1;

    full_mux_trl="//release\n"
    for i in range(FULLMUX_N):
        full_mux_trl+="\
    force    `IOMUX_XRM.pad_cfg[ "+str(fulmux_idx-start_idx+i)+"*8+:8] = 'h0;  \n"
    
    full_mux_trl+="\
    #100;\n"
   
    return code+full_mux_trl

############################################################################
def handleDataToV(row,length,f_net,h,index,inc):   
    itmes    = ITMES   #itmes  
    inc_cell = 0   

    Start_row = 2  if OUTPUTFILE == "default" else 9  

    code  =  "//##################"+row[1].split(".")[-1]+"-------------------------------------\n"
    cells =  ""

    for i in range(Start_row,length,itmes):
        cells,inc_cell,inc = handleCellIO(row[i],row[1],row[i+2],row[i+4],row[i+6],h-index,inc_cell,inc,0)

        if cells=="":
            pass
        else:
            code += cells


    if OUTPUTFILE == "default":
        pass
    else:
        code+="//release\n\
    release `IOMUX_XRM.pad_cfg[ "+str(h-index)+"*8+:8];\n\
    #100;\n"

    return code,f_net,inc




############################################################################
def handle_excel_parsing(workbook,sheet_index):
    File    =  "//Automatically generate file.\n\n"
    File    += "`include \"inputs/soc_top/sim/tb/inc/chip_def.inc\"\n\n"

    funmux_idx = 0;
    index   = 0
    Fnet    = 0  
    run     = 0
    inc     = 0

    codes   = ""

    sheet1 = workbook.sheet_by_index(sheet_index)          # sheet 0

    if OUTPUTFILE == "default":
        File    += header_default
    else:
        File    += header
        for i in range(0,sheet1.nrows-2):                  #Find Start row
            if  sheet1.col_values(0)[i]== "input":
                if sheet1.row_values(i)[2] =="":
                    print("ERROR:RF force")
                else:
                    File+="\
  force "+sheet1.row_values(i)[2]+" =$urandom;\n\n"
                break

    db = handleDataDictionary(sheet1,sheet1.nrows)          #fill  dictionary
    for i in range(0,sheet1.nrows-2):                       #Find Start row
        if  sheet1.col_values(0)[i+0]== "PIN NUM"   and \
            sheet1.col_values(0)[i+1]== ""          and \
            sheet1.col_values(0)[i+2]== 0           and \
            sheet1.col_values(0)[i+3]== 1:
            index = i+2
            run = 1
            break

    if run == 0:
        print("File Error")
        exit()    

    if OUTPUTFILE == "default":
        for i in range(index,sheet1.nrows): 
        #for i in range(index,index+1): 
            line,Fnet,inc = handleDataToV(sheet1.row_values(i),sheet1.ncols,Fnet,i,index,inc)
            codes += line +"\n\n"
    else :
        for i in range(index,sheet1.nrows-FULLMUX_N): # io mux
        #for i in range(index,index+1): 
            line,Fnet,inc = handleDataToV(sheet1.row_values(i),sheet1.ncols,Fnet,i,index,inc)
            codes += line +"\n\n"
            funmux_idx = i+1

        # for i in range(funmux_idx,sheet1.nrows):  # fun mux
        codes += handleDataToFM(sheet1.row_values,sheet1.ncols,sheet1.nrows,funmux_idx,index)
      
    File += codes

    if OUTPUTFILE == "default":
        File    += "\n\n"+trail_default
    else:
        File    += "\n\n"+trail



    return File,sheet1.name


############################################################################
def read_excel(file):
    workbook = xlrd.open_workbook(file)
    return handle_excel_parsing(workbook,0) #only parsing page 1
    
############################################################################
if __name__ == '__main__':
    dict_argc  = {"FileInput": "","FileOUTput":"","default_en":"","funmux_num":""}
    dict_argc = cm2gt.cmdParseArgv(dict_argc)

    ##################
    if dict_argc["FileInput"] == "":
        print("error :FileInput is null")
        exit()

    ##################
    if dict_argc["FileOUTput"] == "":
        print("warning :FileOUTput is null")

    ##################
    if dict_argc["default_en"] == "":
        pass
    else:
        if "true" in  dict_argc["default_en"]:
            # global OUTPUTFILE 
            OUTPUTFILE =  "default"
            print("default_en true")
        else:
            print("default_en false")

    ##################
    if dict_argc["funmux_num"] == "":
        pass
    else:
        funmux_num = dict_argc["funmux_num"]
        if funmux_num.isdigit():
            # global FULLMUX_N 
            FULLMUX_N =  int(funmux_num)
        else:
            print("Error: funmux_num  param Invaild")
    ##################

    #_____________________________________________________________________
    codes,name      = read_excel(dict_argc["FileInput"])    
    
    if dict_argc["FileOUTput"]=="":
        dict_argc["FileOUTput"]    =  name+".v"

    SaveFile(dict_argc["FileOUTput"],codes,"w")

    print("File Path:"+ dict_argc["FileInput"])
    print("File Save to:"+dict_argc["FileOUTput"])
