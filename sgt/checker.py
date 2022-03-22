from thaw.checker import Judger
from thaw.bind import put

put('n', 100)
put('q', 100)
put('a', 100)
for i in range(0, 3):
    print('#' + str(i) + ': ' + Judger(gen='gen.py', std='std.cpp', time=3, memory=128).traditional())

put('n', 10000)
put('q', 10000)
put('a', 10000)
for i in range(3, 7):
    print('#' + str(i) + ': ' + Judger(gen='gen.py', std='std.cpp', time=3, memory=128).traditional())

put('n', 1000000)
put('q', 1000000)
put('a', 1000000)
for i in range(7, 10):
    print('#' + str(i) + ': ' + Judger(gen='gen.py', std='std.cpp', time=3, memory=128).traditional())
