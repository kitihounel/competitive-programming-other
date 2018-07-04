b, br, bs, a, s = (int(token) for token in input().split())
bm = (br - b) * bs
am = y = 0
while am <= bm:
    am += s
    y  += 1
print(a + y)
