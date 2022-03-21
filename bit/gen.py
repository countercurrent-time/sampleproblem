from random import randint
from thaw.bind import get

n = get('n')
q = get('q')
a = get('a')

print(n, q)

for i in range(0, n):
    print(randint(-a, a), end=' ')
print('\n')

for i in range(0, q):
    op = randint(1, 2)
    if op == 1:
        print(op, randint(1, n), randint(-a, a))
    else:
        l = randint(1, n)
        r = randint(1, n)
        if l > r:
            l, r = r, l
        print(op, l, r)

