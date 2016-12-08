from matplotlib.pyplot import *
import sys
import os
import re as regex

name = sys.argv[1][:-4]

with open(name + ".dat","r") as infile:
    lines = infile.readlines()

x = [float(val) for val in lines[0].split()[1:]]
i = 0
for line in lines[1:]:
    t = float(regex.findall(r"\{([^\}]+)\}",line)[0])
    u = [float(val) for val in line.split()[1:]]
    figure()
    xlabel("x")
    axis([0,1,0,1])
    ylabel("u")
    plot(x,u,label="t=%.2f" % t)
    legend(loc="upper left")
    savefig("%s%08d.png" % (name,i), dpi=60)
    i += 1

delay = int(round(2000.0/i))
os.system("convert -delay %d -loop 0 %s*.png %s.gif" % (delay,name,name))
os.system("rm *.png")
