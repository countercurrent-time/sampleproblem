#include<cstdio>
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
  void rotate(int& p, int d) {
    int q = ch[p][d];
    link(p, d, ch[q][d ^ 1]);
    link(q, d ^ 1, p);
    p = q;
  }
  int cmp(int p, int& k) {
    int d = k - size[ch[p][0]];
    if (d == 1 || ch[p][d > 0] == 0) return -1;
    return d <= 0 ? 0 : (k -= size[ch[p][0]] + 1, 1);
  }
  void splay(int& p, int k) {
    int d = cmp(p, k);
    if (d != -1) {
      int q = ch[p][d], d2 = cmp(q, k);
      if (d2 != -1) {
        splay(ch[q][d2], k);
        rotate(d == d2 ? p : ch[p][d], d2);
      }
      rotate(p, d);
    }
  }

  pair<int, int> split(int& p, int k) {
    if (k <= 0) return std::make_pair(0, p);
    splay(p, k);
    pair<int, int> ret = std::make_pair(p, ch[p][1]);
    link(p, 1, 0);
    return ret;
  }
  int merge(int l, int r) {
    if (l == 0) return r;
    splay(l, size[l]);
    link(l, 1, r);
    return l;
  }

  void insert(int v) {
    pair<int, int> p = split(root, rank(v) - 1);
    root = merge(p.first, merge(New(v), p.second));
  }
  void remove(int v) {
    pair<int, int> p = split(root, rank(v) - 1);
    root = merge(p.first, split(p.second, 1).second);
  }
  int rank(int v) {
    int ret = rank(root, v);
    splay(root, ret);
    return ret;
  }
	int rank(int& p, int v) {
		if (!p) return 1;
		if (val[p] >= v) return rank(ch[p][0], v);
		return rank(ch[p][1], v) + size[ch[p][0]] + 1;
	}
  int find(int& p, int k) {
    splay(p, k);
    return val[p];
  }
  void getpre(int v) {
    pair<int, int> p = split(root, rank(v) - 1);
    printf("%d\n", find(p.first, size[p.first]));
    root = merge(p.first, p.second);
  }
  void getnext(int v) {
    pair<int, int> p = split(root, rank(v + 1) - 1);
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
