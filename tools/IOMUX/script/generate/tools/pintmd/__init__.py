#-*-coding:utf-8-*-
############################################################################
#describe： Generate V file from the pin mux map of excel
#auth：     merger
#date：     019-07-12
#Run:      
############################################################################


import os
import sys
import gPinTmc

def getTMCode(sheet):
    return gPinTmc.handle_test_code_parsing(sheet)
