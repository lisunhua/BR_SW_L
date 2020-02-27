#!/usr/bin/python  
# -*- coding:utf8 -*-  
  
import os
import sys  

def FindFile(Path,cmd):
    files = os.listdir(Path) 
    dirList = []
    for f in files:
        if(os.path.isdir(Path + '/' + f)):  
            if(f[0] == '.'):  
                pass  
            if f == 'flash' or f =='d_flash':  
                pass
            else:
                # print("Dir:"+ Path + '/' + f)   
                dirList.append(f)  
        if os.path.isfile(Path + '/'+ f):
            if f == "makefile":
                print("\n########################################################################")
                print(Path) 
                name =   Path.split("/")[-1].split("_")[2][0]
                # if name!="2":
                rut = os.system("cd "+Path+"\n make "+cmd)
                if rut !=0 :
                    print("ERROR: pin["+hex(rut)+"]")
                    exit()

                # print("os cmd:"+ str(os.system("cd "+Path+"\n make "+cmd)))

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

	
	
	