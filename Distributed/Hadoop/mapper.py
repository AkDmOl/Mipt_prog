import re
import sys

def my_map(line):
    clear = re.sub(r"[\"\%\[\]\$*&.,;:()!?\xe2]", '',line)
    words = clear.split()
    for i in range(1,len(words)):
        yield words[i-1] + ' ' + words[i], 1

for line in sys.stdin:
    for pair, count in my_map(line):
        print (pair + "\t" + str(count))


