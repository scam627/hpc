import math
import matplotlib.pyplot as plt
import numpy as np

xp = np.array([])
yp = np.array([])
xs = np.array([])
ys = np.array([])
f = open('out_parallel.txt','r')
data = f.read().split('\n')
for line in data:
    coor = line.split(' ')
    if len(coor) > 1:
        xp = np.append(xp,coor[0])
        yp = np.append(yp,coor[1])
f.close()
f = open('out_serial.txt','r')
data = f.read().split('\n')
for line in data:
    coor = line.split(' ')
    if len(coor) > 1:
        xs = np.append(xs,coor[0])
        ys = np.append(ys,coor[1])
f.close()
print xp, yp
plt.plot(xp, yp, 'r', xs,ys,'g')
plt.show()