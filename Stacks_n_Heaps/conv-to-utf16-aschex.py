import sys
import binascii

ofile = open(sys.argv[2], "w")
cnt = 0
with open(sys.argv[1], "r") as file:
    for line in file.readlines():
        for i in range(len(line)):
            ofile.write("%04x" % ord(line[i]))
            if(cnt % 8 == 7):
                ofile.write("\n")
            else:
                ofile.write(" ")
            cnt += 1
            
ofile.close()

