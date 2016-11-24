import matplotlib.pyplot as plt
def graphic():
    calc_U = []
    calc_x = []
    U = [80, 70, 60, 50, 40, 30, 20, 15, 10, 10, 15, 20, 30]
    x = [0.005, 0.025, 0.045, 0.065, 0.085, 0.115, 0.15, 0.1775, 0.225, 0.345, 0.405, 0.435, 0.495]
    f = open('res.txt', 'r')
    for line in f:
        split = line.split(':')
        calc_x.append(float(split[0]))
        calc_U.append(float(split[1]))
    fig = plt.figure()
    plt.scatter(calc_x, calc_U, color = 'blue')
    plt.scatter(x,U, color = 'red')
    plt.grid()
    plt.savefig('plot.png')


