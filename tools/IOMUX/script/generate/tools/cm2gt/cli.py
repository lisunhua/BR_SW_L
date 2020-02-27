#-*-coding:utf-8-*-
############################################################################
#describe： command line interface 
#auth：     merger
#date：     019-07-12
#Run:       
############################################################################



import sys
import getopt


class Getopt_argv:
    """docstring for Getopt_argv"""
    def __init__(self, argv):
        # super(Getopt_argv, self).__init__()
        # self.argv = argv
        try:
            opts,args = getopt.getopt(argv,)
