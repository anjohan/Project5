from matplotlib.pylab import *

nt = 1000001
nx = 101

x = linspace(0,1,nx)
u = zeros((nt,nx))

u[:,-1] = 1 #Boundary conditions

for j in range(nt-1):
    u[j+1,1:-1] = 0.5*(u[j,:-2] + u[j,2:])

plot(x,u[1000],label="1 000 time steps")
plot(x,u[-1],label="1 000 000 time steps")
legend(loc="best")
show()
