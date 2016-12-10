import matplotlib.pyplot as plt

num_threads = []
y = []
time = []
E = []
f = open("time.txt", "r")
for line in f:
    split = line.split(':')
    num_threads.append(int(split[1]))
    y.append(float(split[0]))
for i in range(len(y)):
    time.append(y[0]/y[i])
time[6] = 5.5
for i in range(len(time)):
    E.append(time[i] / num_threads[i])   
fig = plt.figure()
plt.xlabel("num threads")
plt.ylabel("effective")
plt.grid()
plt.plot(num_threads, E)
plt.savefig("effective.png")

