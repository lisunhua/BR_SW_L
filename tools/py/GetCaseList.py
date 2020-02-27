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

def CheckFlst(dir):
    for fname  in os.listdir(dir):
        if fname.find(".flst") != -1:
            return True
    return False

def FindFile(Path,cmd):
    files = os.listdir(Path)
    files.sort(reverse=False)
    run_list = []
    for f in files:
        if(os.path.isdir(Path + '/' + f)):  
            if(f[0] == '.'):  
                pass  
            else:
                if cmd == "cmp":
                    run_list.append("./tools/run -c "+f[0:3])
                else:
                    if f.find(".back") != -1:
                        pass
                    else:
                        print("./tools/run -t "+f) 

    run_list = set(run_list)
    if len(run_list) != 0:
        for rl in run_list:
            print rl
                
               
if __name__ == '__main__':
    if len(sys.argv) < 2:
        exit()
    cmd = ""
    if len(sys.argv) == 3:
        cmd = sys.argv[2]
    FindFile(sys.argv[1],cmd)

	
	
	
