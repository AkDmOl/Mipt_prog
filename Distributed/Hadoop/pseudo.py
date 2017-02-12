import re

def map(doc):
    for line in doc:
        clear = re.sub(r"[\"\%\[\]\$*&.,;:()!?\xe2]", '',line)
        words = clear.split()
        for i in range(1,len(words)):
            yield words[i-1] + ' ' + words[i], 1

my_file = open("test.txt", "r")
my_pairs = map(my_file)
for i in my_pairs:
    print(i)
