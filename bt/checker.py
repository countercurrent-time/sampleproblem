from thaw.checker import Judger
from thaw.bind import put

put('n', 100)
put('a', 100)
for i in range(0, 3):
    print('#' + str(i) + ': ' + Judger(gen='gen.py', std='std.cpp', time=1, memory=128).traditional())

put('n', 10000)
put('a', 10000)
for i in range(3, 6):
    print('#' + str(i) + ': ' + Judger(gen='gen.py', std='std.cpp', time=1, memory=128).traditional())

put('n', 100000)
put('a', 100000)
for i in range(6, 10):
    print('#' + str(i) + ': ' + Judger(gen='gen.py', std='std.cpp', time=1, memory=128).traditional())
