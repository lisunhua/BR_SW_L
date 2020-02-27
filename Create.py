#!/usr/bin/python  
# -*- coding:utf8 -*-  
  
import os
import sys  

def CreatFile(Path,new_Path):
    files = os.listdir(Path) 
    dirList = []
    for f in files:
        if(os.path.isdir(Path + '/' + f)):  
            if(f[0] == '.'):  
                pass  
            else:
                print("Dir:"+ Path + '/' + f)   
                dirList.append(f)  
                os.mkdir(new_Path + '/' + f)
        
        if os.path.isfile(Path + '/' + f) : 
            file_new = new_Path + '/' + f
            file_old = Path + '/' + f

            
            #print(file_old)
            #print(file_new)
            #Cat指令创建文件
            os.system("cat " + file_old +" > "+ file_new )

            #创建新的空文件
            #fi = open((new_Path + '/' + f ),"w")
            #fi.close() 
            #print("file:"+ Path + '/' + f) 

    for dl in dirList:  
        CreatFile(Path + '/' + dl,new_Path + '/' + dl) 


if __name__ == '__main__':
	print("argv:"+ str(len(sys.argv)))
	if len(sys.argv)<3:
		print("please Input Path!")
		exit()

	if(os.path.isdir(sys.argv[2])):  
		pass
	else:
		os.mkdir(sys.argv[2])

	print("Path:"+sys.argv[1])
	print("New Path:"+sys.argv[2])
	CreatFile(sys.argv[1],sys.argv[2])


	#fi = open("BR002/arch/boot/boot_cmd.c","w")
	#fi.close() 
	
	
	
	
	