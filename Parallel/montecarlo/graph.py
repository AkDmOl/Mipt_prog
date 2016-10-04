import numpy as np
import matplotlib.pyplot as plt

x = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0]
times = []
y = []
f = open('final', 'r')
for line in f:
    split = line.split(':')
    times.append(float(split[1]))
for i in range(0, len(times)):
    y.append(float(times[0])/float(times[i]))
fig = plt.figure()
ax = fig.gca()
plt.xlabel("Number of threads")
plt.ylabel("Acceleration")
plt.plot(x, y)
plt.grid()
plt.savefig('plot.png')
