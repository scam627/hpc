import math
import matplotlib.pyplot as plt
import numpy as np

xp = []
yp = []
xs = []
ys = []
f = open('out_parallel.txt','r')
data = f.read().split('\n')
for line in data:
    coor = line.split(' ')
    if len(coor) > 1:
        xp.append(coor[0])
        yp.append(coor[1])
f.close()
f = open('out_serial.txt','r')
data = f.read().split('\n')
for line in data:
    coor = line.split(' ')
    if len(coor) > 1:
        xs.append(coor[0])
        ys.append(coor[1])
f.close()
plt.plot(xp, yp, 'r', xs,ys,'g')
plt.show()