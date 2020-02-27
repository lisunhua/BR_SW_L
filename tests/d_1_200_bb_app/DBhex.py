#!/usr/bin/python
#-*-coding:utf-8-*-    

import os
import sys

def FlieSave(File,bin,gz):
    with open(File, gz) as f:
        f.write(bin)

def  GetFileSize(file):
	with open (fileName,"rb") as f:
		ff = f.read()
	return len(ff)

fileName = ""
if len(sys.argv) == 2:
	fileName = sys.argv[1]
else:
	print "File Error"
	exit();

filesize = GetFileSize(fileName)
print "file Size:",filesize
if filesize >3*1024*128:
	print "The File is too large "
	exit()

def GetBinFile(fName,fSize):
	bin1 = ""
	bin2 = ""
	bin3 = ""
	b1=""
	with open(fileName,"rb") as f:
		for i in range(0,1024*128/4*3):
			if i<fSize/4:
				b1 = f.read(4)
				b1 = b1[::-1]
				bin3 += "{0:0>32b}".format(long(b1.encode("hex"),16))
				bin3 += "\n"
			elif i*4 > fSize:
				bin3 += "{0:0>32b}".format(0)
				bin3 += "\n"
			else :
				b1 = f.read()
				b1 = b1[::-1]
				if b1 != "":
					bin3 += "{0:0>32b}".format(long(b1.encode("hex"),16))
					bin3 += "\n"
				else:
					bin3 += "{0:0>32b}".format(0)
					bin3 += "\n"

			if i == 1024*128/4-1:
				bin1 = bin3;
				bin3 =""
				print "_rom0"
			if i == 1024*128/4*2 -1:
				bin2 = bin3
				bin3=""
				print "_rom1"

	print "_rom2"
	return bin1,bin2,bin3




bin1,bin2,bin3 = GetBinFile(fileName,filesize)
#print bin1
fileName = fileName.replace(".bin","")
FlieSave(fileName+"_rom0.hex",bin1,"w")
FlieSave(fileName+"_rom1.hex",bin2,"w")
FlieSave(fileName+"_rom2.hex",bin3,"w")


