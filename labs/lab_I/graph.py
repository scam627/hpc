import math
import matplotlib.pyplot as plt
import numpy as np

f = open('out.txt','r')
x = []
y = []
data = f.read().split('\n')
for line in data:
    coor = line.split(' ')
    if len(coor) > 1:
        x.append(coor[1])
        y.append(coor[0])
f.close()
plt.plot(x, y)
plt.show()