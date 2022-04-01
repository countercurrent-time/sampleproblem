#include<cstdio>
const int N = 1000005;

int m;
int root;
int ch[N][2];

struct Splay {
  int tot;
  int fa[N], val[N];
  int cnt[N], size[N];
  int New(int v, int f) {
    tot++;
    size[tot] = cnt[tot] = 1;
    // ch[tot][0] = ch[tot][1] = 0;
    val[tot] = v;
    link(tot, f);
    return tot;
  }
  void del(int p) {
    if (!ch[p][0] || !ch[p][1]) link(ch[p][0] | ch[p][1], fa[p], get(p));
    // val[p] = 0;
    // size[p] = cnt[p] = 0;
  }
  void push_up(int p) {
    size[p] = cnt[p] + size[ch[p][0]] + size[ch[p][1]];
  }
  bool get(int p) {
    return val[fa[p]] < val[p];
  }
  void link(int p, int f, int d = 0) {
    if (p) fa[p] = f;
    if (f) ch[f][p ? get(p) : d] = p, push_up(f); // set d manually when p is zero
    else root = p;
  }

  void rotate(int p) {
    int f = fa[p], gf = fa[f];
    link(ch[p][get(p) ^ 1], f, get(p));
    link(f, p);
    link(p, gf);
  }
  void splay(int p) {
    for (int f; f = fa[p], f; rotate(p))
      if (fa[f]) rotate(get(p) == get(f) ? f : p);
  }
  void insert(int v, int p = root) {
    if (val[p] == v) cnt[p]++, size[p]++, splay(p);
    else if (ch[p][val[p] < v] == 0) splay(New(v, p));
    else insert(v, ch[p][val[p] < v]);
  }
  void remove(int v) {
    insert(v);
    int p = root;
    if ((size[p] -= 2, cnt[p] -= 2) == 0) {
      splay(getpre());
      del(p);
    }
  }
  int rank() {
    return size[ch[root][0]] + 1;
  }
  int find(int rank, int p = root) {
    if (size[ch[p][0]] >= rank) return find(rank, ch[p][0]);
    if (size[ch[p][0]] + cnt[p] < rank) return find(rank - size[ch[p][0]] - cnt[p], ch[p][1]);
    return splay(p), val[p];
  }
  int getpre(int p = ch[root][0]) {
    return ch[p][1] ? getpre(ch[p][1]) : p;
  }
  int getnext(int p = ch[root][1]) {
    return ch[p][0] ? getnext(ch[p][0]) : p;
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
      case 3: set.insert(x); printf("%d\n", set.rank()); set.remove(x); break;
      case 4: printf("%d\n", set.find(x)); break;
      case 5: set.insert(x); printf("%d\n", set.val[set.getpre()]); set.remove(x); break;
      case 6: set.insert(x); printf("%d\n", set.val[set.getnext()]); set.remove(x); break;
    }
  }
  return 0;
}
