#!/usr/bin/python
#-*-coding:utf-8-*- 


import os
import sys

def GetFileSzie(file):
	with open (fileName,"rb") as f:
		sz= f.read()
	return len(sz)

fileName = ""
if len(sys.argv) == 2:
	fileName =sys.argv[1]
else:
	print "file Error"
	exit();

hex_s ="\n const char ram_data[]= {\n	"	
with open(fileName,"rb") as f:
	bin = f.read()
	for i in range(0,len(bin)):
		hex_s += "0x"+bin[i].encode("hex") +","
		if (i+1)%16==0 :
			hex_s+="\n	"
			
		print(bin[i].encode("hex"))
	hex_s+= "\n};\n"
	f.close()
	
	
fileName = fileName.replace(".bin",".h")

with open(fileName,"w") as f:
	f.write(hex_s)
	f.close()
	

