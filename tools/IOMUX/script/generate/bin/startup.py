#-*-coding:utf-8-*-
############################################################################
#describe： The is list to generate file  
#auth：     merger
#date：     019-07-12
#Run:       
############################################################################
import os
import sys

sys.path.append("./tools")
import cm2gt

############################################################################
CMD_TOOL    = "python"

PATH_OUTPUT = "./output/"
PATH_INPUT  = "./file/"
PATH_TOOLS  = "./tools/"

FILE_INTPUT = "BR8051A01_iomux_full_test.xls"


############################################################################

pinmux_dict = {
                  "pinmux":
                  {
                      "cmd":"gPinMux.py",
                      "FileInput":FILE_INTPUT,
                      "FileOUTput":"pinmux.v",
                  },    
                  "pinforce":
                  {
                      "cmd":"gPinForce.py",
                      "FileInput":FILE_INTPUT,
                      "FileOUTput":"iomux_function.sv",
                      "default_en":"false",
                      "funmux_num":"6",
                  },
                  "pinforce_d":
                  {
                      "cmd":"gPinForce.py",
                      "FileInput":FILE_INTPUT,
                      "FileOUTput":"default_iomux_function.sv",
                      "default_en":"true",
                  },
                  # "pintmd_func":
                  # {
                  #     "cmd":"gPinTmd.py",
                  #     "FileInput":FILE_INTPUT,
                  #     "FileOUTput":"iomux_func_testmode.sv",
                  #     "FileType":"func"
                  # },
                  # "pintmd_scan":
                  # {
                  #     "cmd":"gPinTmd.py",
                  #     "FileInput":FILE_INTPUT,
                  #     "FileOUTput":"iomux_scan_testmode.sv",
                  #     "FileType":"scan"
                  # },
                  # "pintmd_mbist":
                  # {
                  #     "cmd":"gPinTmd.py",
                  #     "FileInput":FILE_INTPUT,
                  #     "FileOUTput":"iomux_mbist_testmode.sv",
                  #     "FileType":"mbist"
                  # },
                  # "pintmd_bsd":
                  # {
                  #     "cmd":"gPinTmd.py",
                  #     "FileInput":FILE_INTPUT,
                  #     "FileOUTput":"iomux_bsd_testmode.sv",
                  #     "FileType":"bsd"
                  # },
                  "pintmd_all":
                  {
                      "cmd":"gPinTmd.py",
                      "FileInput":FILE_INTPUT,
                      "FileOUTput":"iomux_test_mode.sv",
                      "FileType":"all"
                  },
                  # "uvmappt":
                  # {
                  #    "cmd":"gUvmAppt.py",
                  #    "FileInput":"BR003_appt.xls",
                  #    "FileOUTput":"chip_appt.sv",
                  # },
              }


##############################################################################################
if __name__ == '__main__':
    cm2gt.cmdParse_dict(pinmux_dict,CMD_TOOL,PATH_OUTPUT,PATH_INPUT,PATH_TOOLS)
##################################  end  #####################################################
