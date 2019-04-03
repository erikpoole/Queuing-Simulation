import os

filename = "output.txt"
os.system("rm " + filename)

# Using your simulator, do a parameter space study.
# Vary customer arrival rates from 0 to 10 per minute,
# in increments of 1 minute, and max customer service times from 0 to 5 minutes,
# in increments of 0.5 minutes. Based on the resulting 90%ile service times,
# create a surface plot. Hand in two plots, one for the bank and the other for the supermarket.

for x in range(10, 20):
    for y in range(9, 19):
    # ./ simulator
    # 0.32
    # 5.1
    # 34534
        command = "./simulator " + str(float(x)/4) + " " + str(float(y)/8) + " 34534 >> " + filename
        print(str(float(x)/4) + " " + str(float(y)/8))
        os.system(command)
