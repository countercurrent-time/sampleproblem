#include<cstdio>
#include<cstdlib>
#include<algorithm>
using std::pair;
const int N = 100005;
int m;

struct Splay {
  int tot, root;
  int ch[N][2], val[N];
  int size[N];
  int New(int v) {
    tot++;
    size[tot] = 1;
    val[tot] = v;
    return tot;
  }
  void push_up(int p) {
    size[p] = 1 + size[ch[p][0]] + size[ch[p][1]];
  }
  void link(int p, int d, int c) {
    if (p) {
      ch[p][d] = c;
      push_up(p);
    }   
  }
  void rotate(int& p, int d, int v) {
    int q = ch[p][d];
    if (val[q] <= v || (ch[q][d] != 0 && val[ch[q][d]] <= v)) {
      link(p, d, ch[q][d ^ 1]);
      link(q, d ^ 1, p);
      p = q;
    }
  }
  int cmpv(int p, int v) {
    if (p == 0 || ch[p][val[p] <= v] == 0) return -1;
    return val[p] <= v;
  }
  void splay(int& p, int v) {
    int d = cmpv(p, v);
    if (d != -1) {
      int q = ch[p][d], d2 = cmpv(q, v);
      if (d2 != -1) {
        splay(ch[q][d2], v);
        rotate(d == d2 ? p : ch[p][d], d2, v);
      }
      rotate(p, d, v);
    } 
  }
  int merge(int l, int r) {
    if (l == 0) return r;
    splay(l, find(l, size[l]));
    link(l, 1, r);
    return l;
  }
  pair<int, int> split(int& p, int v) {
    splay(p, v);
    if (val[p] > v) return std::make_pair(0, p);
    pair<int, int> ret = std::make_pair(p, ch[p][1]);
    link(p, 1, 0);
    return ret;
  }
  void insert(int v) {
    pair<int, int> p = split(root, v);
    root = merge(p.first, merge(New(v), p.second));
  }
  void remove(int v) {
    pair<int, int> p = split(root, v - 1);
    pair<int, int> q = split(p.second, v);
    root = merge(merge(p.first, merge(ch[q.first][0], ch[q.first][1])), q.second);
  }
  int rank(int v) {
    pair<int, int> p = split(root, v - 1);
    int ret = size[p.first] + 1;
    root = merge(p.first, p.second);
    find(root, rand() % size[root] + 1);
    return ret;
  }
  int find(int& p, int rank) {
    int ret = __find(p, rank);
    splay(p, ret);
    return ret;
  }
  int __find(int p, int rank) {
		if (size[ch[p][0]] == rank - 1) return val[p];
		if (size[ch[p][0]] >= rank) return __find(ch[p][0], rank);
		return __find(ch[p][1], rank - size[ch[p][0]] - 1);
	}
  void getpre(int v) {
    pair<int, int> p = split(root, v - 1);
    printf("%d\n", find(p.first, size[p.first]));
    root = merge(p.first, p.second);
  }
  void getnext(int v) {
    pair<int, int> p = split(root, v);
    printf("%d\n", find(p.second, 1));
    root = merge(p.first, p.second);
  }
};

Splay set;

int main() {
  scanf("%d", &m);
  while (m--) {
    int op, x;
    scanf("%d%d", &op, &x);
    switch(op) {
      case 1: set.insert(x); break;
      case 2: set.remove(x); break;
      case 3: printf("%d\n", set.rank(x)); break;
      case 4: printf("%d\n", set.find(set.root, x)); break;
      case 5: set.getpre(x); break;
      case 6: set.getnext(x); break;
    }
  }
  return 0;
}
