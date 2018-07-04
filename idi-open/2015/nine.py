t = int(input())
while t > 0:
    d = int(input())
    n = 1 if d == 1 else 8 * pow(9, d - 1, 1000000007) % 1000000007
    print(n)
    t = t - 1
