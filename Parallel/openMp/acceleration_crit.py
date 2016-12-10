import matplotlib.pyplot as plt
 
num = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
acceleration = []
time = []
f = open("crit_res.txt", "r")
for line in f:
    split = line.split(':')
    time.append(float(split[0]))
for i in range(12):
     acceleration.append(time[0]/time[i])
fig = plt.figure()
plt.xlabel("num proc")
plt.ylabel("acceleration")
plt.plot(num, acceleration)
plt.grid()
plt.savefig("acceleration_crit.png")
