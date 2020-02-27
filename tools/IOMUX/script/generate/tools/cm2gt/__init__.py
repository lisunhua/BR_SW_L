#-*-coding:utf-8-*-
############################################################################
#describe: management cmd parseing
#auth：     merger
#date：     019-07-12
#Run:       
############################################################################

import os
import sys
import getopt


############################################################################
def cmdParseArgv(dict_argc):
    # dict_argc  = {"FileInput": "","FileOUTput":"","default_en":"","funmux_num":""}
    FileInput  = ""
    FileOUTput = ""

    if len(sys.argv) < 2:
        print("please Input File Path!")
        exit() 
#############################################################################
    for k in dict_argc.keys():
        for ag in sys.argv:
            if k in ag:
                if ag.split("=")[0]=="" or ag.split("=")[1] =="":
                    print("Error: cmd param err!")
                else:
                    key = ag.split("=")[0]
                    val = ag.split("=")[1]

                    if  key in dict_argc:
                        dict_argc[key] = val
                    else:
                        print("Error: "+key+" Invaild :"+val)


    return  dict_argc



##############################################################################################
def cmdParse_dict(pinmux_dict,CMD_TOOL,PATH_OUTPUT,PATH_INPUT,PATH_TOOLS):
    cmd_cout = 0
    cmd  = " "
    cmd1 = ""
    cmd2 = ""
    for cmd_dict in pinmux_dict:
        for key in pinmux_dict[cmd_dict]:
            if pinmux_dict[cmd_dict][key] == "":
                print("error: cmd:"+cmd_cout+"key:"+key)
                exit()

            if key == "cmd":
                pinmux_dict[cmd_dict][key] = PATH_TOOLS+pinmux_dict[cmd_dict][key].\
                split(".")[0].lower()[1:]+"/"+pinmux_dict[cmd_dict][key]
            elif key == "FileInput":
                pinmux_dict[cmd_dict][key] = PATH_INPUT+pinmux_dict[cmd_dict][key]
            elif key == "FileOUTput":
                pinmux_dict[cmd_dict][key] = PATH_OUTPUT+pinmux_dict[cmd_dict][key]

            if key == "cmd":
                cmd1 = pinmux_dict[cmd_dict][key]+" "
            else:
                cmd2+= key+"="+pinmux_dict[cmd_dict][key]+" "

        cmd+= cmd1 +cmd2
        # print(CMD_TOOL + cmd)
        # print(cmd1)
        # print(cmd2)
        print("\n###################################")
        print("generate file: "+cmd1.split("/")[-2])
        os.system(CMD_TOOL + cmd)
        cmd_cout+=1
        cmd = " "
        cmd1= ""
        cmd2= ""
##############################################################################################
##############################################################################################
##############################################################################################
