import sys
import random;
import string

numWords = int(sys.argv[1])
mychoices = "abcdefghijklmnopqrstuvwxyz0123456789"
with open(sys.argv[2], "w") as file:
    for i in range(numWords):
        w = ""
        wordLen = random.randrange(1,28)
        for j in range(wordLen):
            w += random.choice(mychoices)
        file.write(w+"\n")
            
