def iterative_josephus(n, k):
    a = 1
    for i in range(1, n + 1):
        a = (a + k - 1) % i + 1
    return a

def recursive_josephus(n, k):
    return 1 if n == 1 else (recursive_josephus(n - 1, k) + k - 1) % n + 1

n, k = (int(token) for token in input().split())
print(iterative_josephus(n, k) - 1)
