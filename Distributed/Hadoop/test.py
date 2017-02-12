import re

res = re.sub(r"[.,;()!?\xe2]", '', "lskdjfskd, lekrlk (\xe2)- dlkdfsl (,?0)! ;dslf;")
print (res)
