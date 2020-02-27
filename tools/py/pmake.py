#!/usr/bin/python  
# -*- coding:utf8 -*-  
  
import os
import sys  

def FindFile(Path,cmd):
    files = os.listdir(Path) 
    dirList = []
    for f in files:
        if f[0] == '.' or f[0] == '~':  
            pass

        elif(os.path.isdir(Path + '/' + f)):  
                dirList.append(f)  

        elif os.path.isfile(Path + '/'+ f):
            if f == "makefile":
                # print("\n########################################################################")
                # print(Path) 
                # print("rm "+Path+"/"+f)
                os.system("rm "+Path+"/"+ f )

                name =   Path.split("/")[-1]#.split("_")[2][0]
                # print(name)

                if   name.find("d_1_200") != -1 or  \
                     name.find("d_1_201") != -1 or  \
                     name.find("s_1_201") != -1 or  \
                     name.find("s_1_202") != -1:

                    os.system("cd "+Path+" \n ln -s ../../tools/make/makefile.null  makefile ")
                # elif name.find("d_1_201") != -1:
                #     os.system("cd "+Path+" \n ln -s ../../tools/make/makefile.null  makefile ")
                elif name.find("d_1_2") != -1:
                    os.system("cd "+Path+" \n ln -s ../../tools/make/makefile.bt  makefile ")
                elif name.find("d_1") != -1:
                    os.system("cd "+Path+" \n ln -s ../../tools/make/makefile.pr  makefile ")
                elif name.find("s_1") != -1:
                    os.system("cd "+Path+" \n ln -s ../../tools/make/makefile.pr  makefile ")
                elif name.find("s_2") != -1:
                    os.system("cd "+Path+" \n ln -s ../../tools/make/makefile.pr  makefile ")
                else:
                    print("Name if Error !!!")

            # if f == "makefile":
            #     print("rm "+Path+"/"+f)
            #     os.system("rm "+Path+"/"+ f )

   
                    # os.system("cd "+Path+"\n make "+cmd)

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

	
	
	