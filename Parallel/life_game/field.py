import numpy as np
import matplotlib.pyplot as plt

def draw_life():
    f = open("first_gen.txt", "r")
    l,w = f.readline().split(' ');
    field = np.zeros((int(l), int(w)));
    life  = open("res.txt", "r")
    for line in life:
        y,x = line.split(',')
        field[y,x] = 1.0
    plt.imshow(field, cmap = plt.cm.Greys, interpolation = 'nearest')
    plt.show()
    plt.savefig("life.png");
