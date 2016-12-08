from numpy import *

a=1
for nx in [11,101]:
    x = linspace(0,1,nx)

    res = zeros(nx)
    t=0.05
    for k in range(1,nx):
        res += 2*(-1)**k/(k*pi)*exp(-(k*pi)**2*t)*sin(pi*k*x)
    res += x

    with open("analytic%d.dat" % a,"w") as fil:
        fil.write("#hei\n")
        for i in range(len(x)):
            fil.write("%g %g\n" % (x[i],res[i]))
    a += 1
