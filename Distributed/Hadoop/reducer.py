import sys

def my_reduce(pair, count):
    return pair, sum(count)


prev_pair = None
counts = []

for line in sys.stdin:
    pair, count = line.split("\t");
    if pair != prev_pair and prev_pair is not None:
        res_pair, res_count = my_reduce(prev_pair, counts)
        print(res_pair + "\t" + res_count)
        counts = []
    prev_pair = pair
    counts.append(int(count))

if prev_pair is not None:
    res_pair, res_count = my_reduce(prev_pair, counts)
    print(res_pair + "\t" + res_count)

