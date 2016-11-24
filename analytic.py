from numpy import *

x = linspace(0,1,101)

res = zeros(101)
t=0.05
for k in range(1,101):
    res += 2*(-1)**k/(k*pi)*exp(-(k*pi)**2*t)*sin(pi*k*x)
res += x

with open("analytic.dat","w") as fil:
    for i in range(len(x)):
        fil.write("%g %g\n" % (x[i],res[i]))
