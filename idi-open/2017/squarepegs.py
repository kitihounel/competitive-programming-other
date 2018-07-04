from math import sqrt
from itertools import chain
from bisect import bisect_right

n, m, k = (float(token) for token in input().split())
plots   = [float(r) for r in input().split()]
circles = [float(r) for r in input().split()]
squares = [float(l) / sqrt(2) for l in input().split()]
houses  = list(sorted(chain(circles, squares)))
plots.sort()

ans = 0
while len(houses) > 0 and len(plots) > 0:
    i = bisect_right(plots, houses[0])
    if i < len(plots):
        ans += 1
        del plots[i]
    else:
        break
    del houses[0]
print(ans)
