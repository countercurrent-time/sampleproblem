除了 `getrankbyval`（即代码中的 `rank()`），其他函数基于 `splay(p, k)`，`split(p, k)` 和 `merge` 的 Splay 版本。

`splay(p, k)` 会将以 `p` 为根的子树中权值第 `k` 大的节点旋转到 `p` 的位置。

`split(p, k)` 会将以 `p` 为根的子树分为两部分，第一部分的节点是权值较小的 `k` 个节点。

`rotate(int& p, int d)` 采用将节点 `p` 旋转到 `ch[p][d]` 的位置的版本。

注意这里的 `d` 与左右旋的定义相反，即右旋指的是 `d == 0` 时的旋转情况，反之亦然。因为 `d == 0` 时 `p` 的右儿子被旋转到了 `p` 的位置：

```cpp
void rotate(int& p, int d) {
  int q = ch[p][d];
  ch[p][d] = ch[q][d ^ 1], ch[q][d ^ 1] = p;
  push_up(p), push_up(q);
  p = q;
}
```

保留三种 `splay(p, rank)` 的写法。

第一个版本是《算法竞赛入门经典训练指南》的版本，[因版权原因暂时不给出源代码，仅给出非官方镜像的链接](https://raw.githubusercontent.com/gzhu-team-509/aoapc-training-guide/master/bookcodes/ch3/uva11922.cpp)。

很可惜虽然《算法竞赛入门经典》与《算法竞赛入门经典训练指南》中的代码与部分习题代码均开放，但原代码仓库并未包含明确的开源许可证或者版权声明。

注意在需要 `insert()` 的伸展树中，由于 `insert()` 会用可能不存在的权值和过大、过小的排名调用 `split(), splay()` 和 `merge()`，需要在这个版本的 `cmp()` 基础上额外判断 `ch[p][d]` 是否为空节点。

源代码中的 `split()` 额外判断了 `k <= 0` 一种情况， `merge()` 额外判断了 `l == 0` 的情况，也是因为 `insert()` 可能用伸展树中不存在的权值调用它们。

注意在 `splay()` 的第二处 `rotate()` 中使用的参数是 `ch[p][d]` 而不是 `q`，这是为了能让 `rotate()` 通过传递引用修改 `ch[p][d]`。

下面是第二个版本，形式上不仅与第一个版本很接近，同时也是三个版本中最接近迭代版的 `splay(p, k)` 的版本：

```cpp
int cmp(int p, int& k) {
  int d = k - size[ch[p][0]];
  if (d == 1 || p == 0 || ch[p][d > 0] == 0) return -1;
  return d <= 0 ? 0 : (k -= size[ch[p][0]] + 1, 1);
}
void splay(int& p, int k) {
  int d = cmp(p, k);
  if (d != -1) {
    int q = ch[p][d], d2 = cmp(q, k);
    if (d2 != -1) {
      splay(ch[q][d2], k);
      d == d2 ? rotate(p, d) : rotate(q, d ^ 1);
    }
    rotate(p, d);
  }
}
```

第三个版本，一定程度上简化了递归过程，但由于 `flag` 的引入不如第二个版本思路简单清晰：

```cpp
int cmp(int p, int& k) {
  int d = k - size[ch[p][0]];
  if (d == 1 || p == 0 || ch[p][d > 0] == 0) return -1;
  return d <= 0 ? 0 : (k -= size[ch[p][0]] + 1, 1);
}
void splay(int& p, int k, int& f, int d, int flag) {
  int d2 = cmp(p, k);
  if (d2 != -1) {
    splay(ch[p][d], k, p, d2, flag ^ 1);
    if (flag) rotate(d == d2 ? f : p, d2);
    else rotate(p, d);
  }
}
```

保留两个 `rank(i, v)` 的写法及它们的不推荐写的压行版本：

```cpp
int rank(int i, int v) {
  if (val[i] == v) return size[ch[i][0]] + 1;
  else if (val[i] > v) return rank(ch[i][0], v);
  return rank(ch[i][1], v) + size[ch[i][0]] + 1;
}
int rank(int i, int v) {
  return (val[i] == v ? 0 : rank(ch[i][val[i] < v], v)) + (val[i] <= v ? size[ch[i][0]] + 1 : 0);
}
```

```cpp
int rank(int i, int v) {
  if (!i) return 1;
  if (val[i] >= v) return rank(ch[i][0], v);
  return rank(ch[i][1], v) + size[ch[i][0]] + 1;
}

int rank(int i, int v) {
  return bool(i) + rank(ch[i][val[i] < v], v) + (val[i] < v ? size[ch[i][0]] + 1 : 0);
}
```

`split()` 没有判断 `k > size[p]` 的情况，这是因为把以 `p` 为根的子树分为 `std::make_pair(p, ch[p][1])` 的形式具有特殊性，会正确处理 `k > size[p]` 时的情况。如果采用 `std::make_pair(ch[p][0], p)` 的分法则需要特殊地考虑 `k > size[p]` 而不用考虑 `k <= 0`。

这份代码的调用子程序的方式是正确的，这也具有特殊性。因为题目要求中除查询排名为 $x$ 的数以外的情况所给的条件都是权值而非排名，这份代码中要获取权值对应的排名只能调用 `rank()` 函数，而 `rank()` 函数是从权值到排名的映射，严格单调递增，返回值具有唯一性，所以虽然代码中允许重复权值的多个节点存在，但 `splay()` 等函数被强制使用 `rank()` 的返回值做参数，这保证了：

1. `splay()` 和 `split()` 的操作具有唯一性，不会发生歧义。
2. 其它函数被强制使用 `rank()` 以将输入数据给出的权值转化为排名，因此保证了 `splay()` 和 `split()` 能总是被被正确调用。

我们会在第四种形式的伸展树中看到使用权值作为 `splay()` 和 `split()` 的参数且使用多个独立节点而非一个带有计数器的节点存储相同的权值时，由于权值的不唯一性而具有歧义，导致相同的权值在 `split()` 中被分到两边，这会直接导致调用 `split()` 且依赖于相同权值节点被分到同一边的 `rank(), getpre(), getnext()` 函数出错。这些内容将包含在 `sol4.md` 。
