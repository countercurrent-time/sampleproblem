from random import random, randint, choice
from thaw.bind import get

n = get('n')
a = get('a')

d = dict()
size = 0

print(n)

for i in range(0, n):
    op = randint(1, 10)
    if size == 0 or op > 6:
        op = 1
    if op == 1:
        x = randint(-a, a)
        size += 1
        if d.__contains__(x):
            d[x] += 1
        else:
            d[x] = 1
    if op == 2:
        pair = d.popitem()
        size -= 1
        if pair[1] > 1:
            d[pair[0]] = pair[1] - 1
        x = pair[0]
    if op == 3:
        pair = d.popitem()
        x = pair[0]
        d[pair[0]] = pair[1]
    if op == 4:
        x = randint(1, size)
    if op == 5:
        x = randint(min(d) + 1, a)
    if op == 6:
        x = randint(-a, max(d) - 1)
    print(op, x)

