#-*-coding:utf-8-*-
############################################################################
#describe： Generate V file from the pin mux map of excel
#auth：     merger
#date：     019-07-12
#Run:       python gPinMux.py excel_file_path save_file
############################################################################

import os
import sys
sys.path.append("./tools")
import xlrd
import cm2gt


#funcations
############################################################################
def SaveFile(name,file,gz):
    with open(name,gz) as f:
        f.write(file)


def readFile(name,gz):
    with open(name,gz) as f:
        return f.read()


def  GetFileSize(file):
    with open (fileName,"rb") as f:
        ff = f.read()
    return len(ff)

############################################################################
def handle_excel_parsing(workbook,sheet_index):
    File    = "\n\n"#//Automatically generate file.\n\n"
    sheet = workbook.sheet_by_index(sheet_index)        # sheet 0
    # print(sheet.nrows,sheet.ncols)


    for i in range(1,sheet.nrows):
        # print(sheet.col_values(0)[i],sheet.col_values(1)[i],sheet.col_values(2)[i])
        for  c in range(0,int(sheet.col_values(2)[i])):

            File += "\n\
/*****************************************************\n\
   **"+sheet.col_values(0)[i] +"_"+str(c+1)+"\n\
*****************************************************/\n\
class chip_"+sheet.col_values(0)[i].lower() +"_"+str(c+1)+" extends handle_base;\n\
        `uvm_component_utils(chip_"+sheet.col_values(0)[i].lower() +"_"+str(c+1)+")\n\
\n\
        function new(string name, uvm_component parent);\n\
            super.new(name, parent);\n\
        endfunction: new\n\
\n\
      task main_phase(uvm_phase phase);\n\
         chip_"+sheet.col_values(0)[i].lower() +"_"+str(c+1)+"::run_id = 'h"+hex(int("0x"+sheet.col_values(1)[i].split("_")[-1],16)+c).split("x")[-1]+";\n\
         chip_"+sheet.col_values(0)[i].lower() +"_"+str(c+1)+"::data_phase(phase);\n\
      endtask:main_phase\n\
\n\
endclass: chip_"+sheet.col_values(0)[i].lower() +"_"+str(c+1)+"\n"


    return File,sheet.name


############################################################################
def read_excel(file):
    File = ""
    name = ""
    workbook = xlrd.open_workbook(file)
    return handle_excel_parsing(workbook,0) 



############################################################################
if __name__ == '__main__':
    dict_argc  = {"FileInput": "","FileOUTput":""}
    dict_argc = cm2gt.cmdParseArgv(dict_argc)

    ##################
    if dict_argc["FileInput"] == "":
        print("error :FileInput is null")
        exit()

    ##################
    if dict_argc["FileOUTput"] == "":
        print("warning :FileOUTput is null")


   #_____________________________________________________________________     
    codes,name      = read_excel(dict_argc["FileInput"])    
    
    if dict_argc["FileOUTput"] =="":
        dict_argc["FileOUTput"]    =  name+".v"

    header = readFile("./tools/uvmappt/code.txt","r")
    SaveFile(dict_argc["FileOUTput"],header+codes,"w")

    print("File Path:"+ dict_argc["FileInput"])
    print("File Save to:"+dict_argc["FileOUTput"])
