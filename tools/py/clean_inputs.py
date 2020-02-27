#!/usr/bin/python  
# -*- coding:utf8 -*-  
  
import os
import sys  

def FindFile(Path,cmd):
    files = os.listdir(Path) 

    for f in files:
        if(os.path.isdir(Path + '/' + f)):  
            print(f)
            if(f[0] == '.') or (f[0] == '~') or f[0] == "d":  
                pass  
            else:
                cases = os.listdir(Path+'/'+f)
                for c in cases:
                    if(os.path.isdir(Path+"/"+f+'/'+c)):  
                        if(c[0] == '.') and (c[0] == '~'):  
                            pass  
                        elif c == "inputs":
                            print("rm -rf "+Path+"/"+f+'/'+c) 
                            rut = os.system("rm -rf "+Path+"/"+f+'/'+c)
                            if rut !=0 :
                                print("ERROR: pin["+hex(rut)+"]")
                                exit()
                        else:
                            pass 


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

	
	
	