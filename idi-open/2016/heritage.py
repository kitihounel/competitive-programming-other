def parts(w: str):
    for i in range(1, len(w) + 1):
        yield w[0:i], w[i:]
    raise StopIteration()

def meanings(w: str) -> int:
    global e
    if len(w) == 0:
        return 1
    if w in e:
        return e[w]
    m = 0
    for p, s in filter(lambda t: t[0] in e, parts(w)):
        m += e[p] * meanings(s)
    e[w] = m
    return m

def preprocess(w: str) -> int:
    global d, e
    if len(w) == 0:
        return 1
    if w in e:
        return e[w]
    m = 0
    for p, s in filter(lambda t: t[0] in d, parts(w)):
        m += d[p] * preprocess(s)
    e[w] = m
    return m

fn = lambda a: (int(a[0]), a[1])
n, name = fn(input().split(None, 1))
d, mod  = {}, 1000000007
fn = lambda a: (a[0], int(a[1]))
for i in range(n):
    w, c = fn(input().split(None, 1))
    d[w] = c
e = {}
for w in sorted(d, key=lambda w: (len(w), w)):
    preprocess(w)
print(meanings(name) % mod)
