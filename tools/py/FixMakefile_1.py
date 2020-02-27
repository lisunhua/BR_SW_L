#!/usr/bin/python  
# -*- coding:utf8 -*-  
  
import os
import sys  

mk_main = "../tools/makefile"

def saveFile(name,file,gz):
    with open(name,gz) as f:
        f.write(file)

def ReadFile(name,gz):
    with open(name,gz) as f:
        return f.read()

def checkIsExistC(p):
    files = os.listdir(p) 
    for f in files:
        if f.find(".c") != -1:
            return True
    return False

def HandleMakefile(f_path):
    dir_name = f_path.split("/")[-1]
    f_type=dir_name[0:5]

    # print(f_path)

    if dir_name=="flash":
        os.system("cd "+f_path+"\n rm makefile\n ln -s ../../../tools/make/makefile.flash  makefile\n")
    elif dir_name=="d_flash":
        os.system("cd "+f_path+"\n rm makefile\n ln -s ../../../tools/make/makefile.flash  makefile\n")
    elif dir_name=="rom":
        os.system("cd "+f_path+"\n rm makefile\n ln -s ../../tools/make/makefile.rom  makefile\n")
    else:
        if checkIsExistC(f_path)==False:
            os.system("cd "+f_path+"\n rm makefile\n ln -s ../../tools/make/makefile.null  makefile\n")
        elif f_type[-1]=="2":
            os.system("cd "+f_path+"\n rm makefile\n ln -s ../../tools/make/makefile.bt  makefile\n")
        else:
            os.system("cd "+f_path+"\n rm makefile\n ln -s ../../tools/make/makefile.pr  makefile\n")

def FindFile(Path,cmd):
    # print(Path)
    files = os.listdir(Path) 
    dirList = []
    for f in files:
        if(os.path.isdir(Path + '/' + f)):  
            if(f[0] == '.'):  
                pass  
            else:
                # print("Dir:"+ Path + '/' + f)   
                dirList.append(f)  
        elif os.path.isfile(Path + '/'+ f):
            # print(Path+"/"+f)
            if f == "makefile":
                # print(Path +'/'+ f)   
                HandleMakefile(Path)
            if f == "main.c":
                # print(Path +'/'+ f) 
                pass


    for dl in dirList:  
        # print(dl)
        FindFile(Path+'/'+dl,cmd) 


if __name__ == '__main__':
    print("argv:"+ str(len(sys.argv)))
    if len(sys.argv) < 2:
        print("please Input Path!")
        exit()

    print("Path:" + sys.argv[1])
    cmd = ""
    if len(sys.argv) == 3:
        cmd = sys.argv[2]
    print("Cmd :" + cmd)
    FindFile(sys.argv[1],cmd)

	
	
	