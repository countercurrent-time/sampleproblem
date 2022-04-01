from thaw.checker import Judger
for i in range(0, 10):
    print('#' + str(i) + ': ' + Judger(gen='gen.py', std='std.cpp', time=1, memory=128).traditional())
