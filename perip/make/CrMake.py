#!/usr/bin/python  
# -*- coding:utf8 -*-  
  
import os
import sys  

#----------------------------------------------------
def saveFile(name,file,gz):
    with open(name,gz) as f:
        f.write(file)
#----------------------------------------------------
def ReadFile(name,gz):
    with open(name,gz) as f:
        return f.read()

#----------------------------------------------------------------------
def FilePathPro(pa):
    file_dir = "    $(SOFTWARE_DIR)/"+pa
    file_dir = file_dir.replace("../","")
    return file_dir

#----------------------------------------------------------------------
def CreatFile(Path,cmd,ty):
    files = os.listdir(Path) 
    dirList = []
    f_pth = ""
    for f in files:
        pa = Path + '/' + f
        if f[0] == '.' or f[0] == '~':  
            pass  
        elif(os.path.isdir(pa)):  
            file_dir = FilePathPro(pa)

            if str(os.listdir(pa)).find(".h") != -1:
                file_dir = file_dir.replace("    ","   -I ")
            elif str(os.listdir(pa)).find(".ld") != -1:
                file_dir = file_dir.replace("    ","   -L ")
            else:
                file_dir = ""

            if "dir" == ty and file_dir != "":
                f_pth +=" \\\n"+file_dir

            dirList.append(f)  

        elif os.path.isfile(pa) : 
            file_name = FilePathPro(pa)
            file_type = file_name.split(".")[-1]

            if file_type == "ld":
                file_name = file_name.replace("    ","   -T ")

            if file_type == ty:
                if cmd =="split":
                    f_pth += " \\\n    " + file_name.split(".")[0].split("/")[-1] +".o"
                else:
                    f_pth += " \\\n" + file_name 

    for dl in dirList:  
        f_pth += CreatFile(Path + '/' + dl, cmd,ty) 

    return f_pth

#----------------------------------------------------------------------
def cmd_praser(argv):
    print("File:" + argv[1])
    File = argv[1]
    cmd  = ""
    if len(argv) == 3:
        cmd = sys.argv[2]   
    print("Cmd :" + cmd)
    print("#----------------------------------------------------\n")
    return File,cmd

#----------------------------------------------------------------------
if __name__ == '__main__':
    print("argv:"+ str(len(sys.argv)))
    if len(sys.argv)<3:
        print("please Input Path!")
        exit()

    File , cmd = cmd_praser(sys.argv)

    include_path = "\n\nPR_INC_INCLUDE   := "
    source_path  = "\n\nPR_SRC_FILE      := "
    HANDLE_path  = "\n\nPR_HAD_FILE      := "
    scr_path     = "\n\nPR_O_path        := "
    asm_path     = "\n\n#PR_ASM_SUP      := "
    lind_path    = "\n\n#PR_LIK_LD       := "
    

    include_path += CreatFile(File,cmd,"dir")
    source_path  += CreatFile(File,cmd,"c")
    HANDLE_path  += CreatFile(File,cmd,"h")
    scr_path     += CreatFile(File,"split","c")
    asm_path     += CreatFile(File,cmd,"s")
    lind_path    += CreatFile(File,cmd,"ld")


    print(include_path)
    print(source_path)
    print(HANDLE_path)
    print(scr_path)
    print(asm_path)
    print(lind_path)

    saveFile("makefile.path",include_path+source_path+HANDLE_path+scr_path+asm_path+lind_path,"w")



	
	
	