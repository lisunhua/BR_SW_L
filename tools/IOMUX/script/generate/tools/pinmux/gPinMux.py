#-*-coding:utf-8-*-
############################################################################
#describe： Generate V file from the pin mux map of excel
#auth：     merger
#date：     019-07-12
#Run:       python gPinMux.py excel_file_path save_file
############################################################################

import os
import sys

sys.path.append("..")
sys.path.append("./tools")

#sys.path.append(os.getcwd()+"/tool/")
#sys.path.append(os.getcwd()+"/pinmux/")
import xlrd
import cm2gt
import pintmd

FUNS        = 6             #MAX FUNS NUM
ITMES       = 7             #itmes define

prdhand     = "`BIDIRPAD"


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
        print ("Error: Dictionary set",h,l,idx)
        exit()


############################################################################
def handleDataToV(tmp_lt,g_lst,dig_lt,row,length,hd,fs,db,f_net,h):   
    itmes = ITMES   #itmes    

    oen_ = 1
    out_ = 3
    in_  = 5 

    Start_row= 9

    for i in range(length-itmes,0,0-itmes):
        if row[i] == 'N/A':
            fs-=1
        else:
            break

    code =  hd +"("+ str(int(row[0])) + "," + str(fs) + ","+ "\n"   #Header 

    for i in range(Start_row,length,itmes):
        dicti =  handleDataCheckDict(db,row[i],h,i)
        code  += dicti["OEN"] + "," if row[i+oen_]== "" else row[i+oen_] + ","
        code  += dicti["IEN"] + ","
        code  += dicti["OUT"] + "," if row[i+out_]== "" else row[i+out_] + ","
        code  += dicti["IN" ] +"["+ str(f_net) +"]"+  ("," if i+in_ <length-2 else "") \
                 if row[i+in_]== "" else row[i+in_] + ("," if i+in_ <length-2 else "")

        code  += "\n" if i<length-itmes else ")"
        f_net += 1 if row[i+in_]== "" else 0

        if "tmp" in row[i+in_]:
            tmp_lt.append(row[i+in_].split("_tmp")[0])
        elif row[i+in_] =="":
            pass
        else:
            g_lst.append(row[i+in_].split("[")[0])

        if "dig" in row[i+out_]:
            dig_lt.append(row[i+out_].split("[")[0])

    return code,f_net


def handleDataheader(tp_l,g_l,db,f_net):
    code = ""
    gList = list(set(g_l))
    tList = list(set(tp_l))
    bu_list = []

#global  define ____________________________________________________
    # for gl in gList:
    #     code += "wire    ["+str(g_l.count(gl)-1)+":0]  "+gl+";\n"
    # code+="wire    ["+str(f_net-1)+":0]  "+db["O"]["IN"]+";\n"
    # code+="\n"
#global tmp  define ________________________________________________
    for tl in tList:
        code += "wire    ["+str(tp_l.count(tl)-1)+":0]  "+tl+"_tmp;\n"
    code+="\n"

#global or__________________________________________________________
    for tl in tList:
        bufl=tl.split("_")
        fg = 1
        for d in bufl[-1]:
            if d >="0" and d <="9":
                pass
            else:
                fg=0
        if fg:
            bu_list.append(tl.split("_"+bufl[-1])[0])
        else:
            bu_list.append(tl)
#global tmp or_____________________________________________________
    bList = list(set(bu_list))

    for bl in bList:
        if bu_list.count(bl)>1:
            for i in range(0,bu_list.count(bl)):
                code += "assign    "+bl+"["+str(i)+"]  = "

                for co in range(0,tp_l.count(bl+"_"+str(i))):
                    code += bl+"_"+str(i)+"_tmp "+"["+str(co)+"]" 
                    code += "; " if co == tp_l.count(bl+"_"+str(i))-1 else "| "

                code += "\n"
        else:
            code += "assign    "+bl+"  = "
            for co in range(0,tp_l.count(bl)):
                code += bl+"_tmp "+"["+str(co)+"]" 
                code += "; " if co == tp_l.count(bl)-1 else "| "

            code += "\n"
        # for i in range(0,tp_l.count(tl))
        
    return code



############################################################################
def handle_excel_parsing(workbook,sheet_index):
    File    = "//Automatically generate file.\n\n"

    index   = 0
    Fnet    = 0  
    run     = 0

    codes   = ""

    tmp_list = []
    g_list   = []
    dig_list = []

    sheet1 = workbook.sheet_by_index(sheet_index)        # sheet 0
 
    db = handleDataDictionary(sheet1,sheet1.nrows)       #fill  dictionary
    for i in range(0,sheet1.nrows-2):               #Find Start row
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

    for i in range(index,sheet1.nrows): 
        line,Fnet = handleDataToV(tmp_list,g_list,dig_list,sheet1.row_values(i),sheet1.ncols,prdhand,FUNS,db,Fnet,i)
        codes += line +"\n\n"

    File += handleDataheader(tmp_list,g_list,db,Fnet) + "\n\n"
    File += codes

    return File,sheet1.name


############################################################################
def read_excel(file):
    File = ""
    name = ""
    workbook = xlrd.open_workbook(file)

    # return handle_excel_parsing(workbook,0) 
    File,name = handle_excel_parsing(workbook,0)         #only parsing page 0

    File += pintmd.getTMCode(workbook.sheet_by_index(1)) #only parsing page 1

    return File,name
    


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

    SaveFile(dict_argc["FileOUTput"],codes,"w")

    print("File Path:"+ dict_argc["FileInput"])
    print("File Save to:"+dict_argc["FileOUTput"])
