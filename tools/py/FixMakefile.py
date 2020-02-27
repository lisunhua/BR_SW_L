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


def MedMakefile(pt):
    # os.system("mv " + pt + " " +pt+".back")
    # print(pt)
    name = pt.split("/")[-2]
    ty   = name.split("_")[0]
    num  = name.split("_")[-1]
    mk = ReadFile(mk_main,"r")
    if ty == "base":
        if num == "2" :
            mk =  mk.replace("all: sgl","all: sgl_m")
        elif num == "3":
            mk =mk.replace("all: sgl","all: sgl_m")
    elif ty == "dual":
        mk = mk.replace("all: sgl","all: dul")
    elif ty == "single":
        pass
    saveFile(pt,mk,"wr")
    # print(name)
    # print(ty)
    # print(mk)



def MedMakefile(pt):
    # os.system("mv " + pt + " " +pt+".back")
    # print(pt)
    name = pt.split("/")[-2]
    ty   = name.split("_")[0]
    num  = name.split("_")[2]


    mk = ReadFile(mk_main,"r")
    if ty == "s":
        if num   == "101" :
            mk =  mk.replace("all: sgl","all: sgl_m")
        elif num == "103":
            mk =  mk.replace("all: sgl","all: sgl_m")


    elif ty == "d":
        mk = mk.replace("all: sgl","all: dul")
    elif ty == "single":
        pass
    saveFile(pt,mk,"wr")

    print(name)
    print(ty)
    print(num)



def FindFile(Path,cmd):
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
            if f == "makefile":
                # print("\n########################################################################")
                print(Path +'/'+ f)   
                MedMakefile(Path +'/'+ f)
                # os.system("cd "+Path+"\n make "+cmd)
            if f == "main.c":
                print(Path +'/'+ f) 


    for dl in dirList:  
        FindFile(Path + '/' + dl,cmd) 


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

	
	
	