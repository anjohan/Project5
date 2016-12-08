import os
import re as regex
from numpy import *

dx = 0.1
ratios = linspace(0.1,1,19)
dt = ratios*dx**2
t_max = 0.5
filename = "stability1d.dat"

methods = ["forward_Euler","backward_Euler","Crank_Nicolson"]

maxerror = [[],[],[]]

def exact(x,t):
    res = zeros(len(x))
    for k in range(1,101):
        res += 2*(-1)**k/(k*pi)*exp(-(k*pi)**2*t)*sin(pi*k*x)
    res += x
    return res

def data(line):
    t = float(regex.findall(r"\{([^\}]+)\}",lines[k])[0])
    u = array([float(val) for val in lines[k].split()[1:]])
    return t, u

for i in range(3):
    method = methods[i]
    for j in range(len(dt)):
        dn = 1
        os.system("./onedim_ui.x %s %s %g %g %g %d" % (filename,method,dt[j],t_max,dx,dn))
        with open(filename,"r") as infile:
            lines = infile.readlines()
        x = array(map(float,lines[0].split()[1:]))
        errors = []
        for k in range(1,len(lines)):
            t,u = data(lines[k])
            errors.append(max(abs(u-exact(x,t))))
        maxerror[i].append(max(errors))

with open(filename,"w") as outfile:
    for i in range(len(ratios)):
        outfile.write("%g" % ratios[i])
        for j in range(3):
            outfile.write(" %g" % maxerror[j][i])
        outfile.write("\n")
