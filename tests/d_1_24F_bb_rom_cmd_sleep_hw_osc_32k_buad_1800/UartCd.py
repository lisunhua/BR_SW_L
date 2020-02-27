#!/usr/bin/python
#-*-coding:utf-8-*-    

import os
import sys

def FlieSave(File,bin,gz):
    with open(File, gz) as f:
        f.write(bin)

def FileRead(file):
	with open (fileName,"rb") as f:
		ff = f.read()
	return ff

def GetFileSize(file):
	with open (fileName,"rb") as f:
		ff = f.read()
	return len(ff)

def hex_2str(hx):
	while len(hx)<2:
		hx ="0"+hx
	return hx

def hex_4str(hx):
	while len(hx)<4:
		hx ="0"+hx
	return hx

def File_UARTCmdPar(line):
	cmd  = line.split("[")[0][1:].lower()
	data = line.split("[")[1].split("]")[0]

	out_f=""
	# print(cmd)
	if cmd == "baud":
		out_f+="//baud \n"
		baud = 921600/int(data)
		baud = hex_2str(hex(baud).split("0x")[1]).upper()
		out_f+="E0"+"\n" +baud+"\n"

	elif cmd == "time":
		out_f+="//time \n"
		time = hex(int(data)).split("0x")[1].upper()
		time = hex_4str(time)
		out_f+="E1\n" +time[2:4]+"\n" +time[0:2]+"\n"

	elif cmd == "str":
		out_f +="//str \n"
		out_f +="D0\n" 
		st_len = hex(len(data)).split("0x")[1].upper()
		st_len = hex_4str(st_len)
		out_f+=st_len[2:4]+"\n" +st_len[0:2]+"\n"

		for bi in data:
			bi = hex(ord(bi)).split("0x")[1].upper()
			bi = hex_2str(bi)
			out_f+= bi+"\n"

	elif cmd == "hex":
		out_f+="//hex \n"
		out_f +="D0\n"
		cdata =data.replace(" ","") 
		# print(cdata)
		hlen = hex(len(cdata.split(","))).split("0x")[1]
		hlen = hex_4str(hlen)
		out_f+=hlen[2:4]+"\n" +hlen[0:2]+"\n"

		for hd in cdata.split(","):
			hd = hex_2str(hd)
			out_f+= hd.upper()+"\n"

	elif cmd == "disrft":
		out_f+="//disRFt \n"
		out_f+="E2\n" +hex_2str(hex(int(data)).split("0x")[1]).upper()+"\n"

	elif cmd == "distft":
		out_f+="//disTFt \n"
		out_f+="E3\n" +hex_2str(hex(int(data)).split("0x")[1]).upper()+"\n"

	elif cmd == "disrn":
		out_f+="//disRn \n"
		out_f+="E4\n"+hex_2str(hex(int(data)).split("0x")[1]).upper()+"\n"

	elif cmd == "distn":
		out_f+="//disTn \n"
		out_f+="E5\n"+hex_2str(hex(int(data)).split("0x")[1]).upper()+"\n"

	elif cmd == "urxtmo":
		out_f+="//uRXTmo \n"
		out_f+="E6\n"+hex_2str(hex(int(data)).split("0x")[1]).upper()+"\n"

	elif cmd == "bclk":
		out_f+="//bclk \n"
		bclk = hex_4str(hex(1000000000/4/int(data)).split("0x")[1]).upper()
		out_f+="E7\n"+bclk[2:4]+"\n" +bclk[0:2]+"\n"

	elif cmd == "stop":
		out_f+="//stop \n"
		out_f+="F1\n"+hex_2str(hex(int(data)).split("0x")[1]).upper()+"\n"

	elif cmd == "ufasttx":
		out_f+="//uFastTx \n"
		out_f+="D1\n"+hex_2str(hex(int(data)).split("0x")[1]).upper()+"\n"

	return out_f



if __name__ =="__main__":
	fileName = ""
	if len(sys.argv) >= 2:
		fileName = sys.argv[1]
		print("InFile->"+fileName)
	else:
		print "File Error"
		exit();
	Udata= "//start \n01\n"

	file = FileRead(fileName)
	for line in file.split("\n"):
		if line[0:1] ==" ":
			pass
		elif line[0:1] =="#":
			pass
		elif line[0:2] =="//":
			pass
		elif line[0:1] =="$":
			# print(line)
			Udata += File_UARTCmdPar(line)
		
	Udata+= "FF\n"+"00\n"+"00\n"+"00\n"  # end

	out_file= "uart.cm"

	if len(sys.argv) == 3:
		out_file =sys.argv[2]

	out_file= "uart.cm"
	if len(sys.argv) >=3 :
		out_file =  sys.argv[2];

	# print("!!!!!!!!!!!!!!!!")
	FlieSave(out_file,Udata,"w")
	print("OutFile->"+out_file)
	# print(Udata)


