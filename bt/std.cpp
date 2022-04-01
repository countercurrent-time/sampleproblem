#include<cstdio>
const int N = 100005;
int m;

struct Splay {
  int tot, root;
  int ch[N][2], fa[N], val[N];
  int cnt[N], size[N];
  int New(int x, int f) {
    tot++;
    size[tot] = cnt[tot] = 1;
    ch[tot][0] = ch[tot][1] = 0;
    val[tot] = x;
    fa[tot] = f;
    if (f) ch[f][val[f] < x] = tot;
    return tot;
  }
  void del(int x) {
    fa[x] = ch[x][0] = ch[x][1] = 0;
    val[x] = 0;
    size[x] = cnt[x] = 0;
  }
  void clear() {
    tot = root = 0;
  }
  void push_up(int x) {
    size[x] = cnt[x] + size[ch[x][0]] + size[ch[x][1]];
  }
  bool get(int x) {
    return x == ch[fa[x]][1];
  }
  void rotate(int x) {
    int f = fa[x], gf = fa[f];
    bool flag = get(x);
    ch[f][flag] = ch[x][flag ^ 1];
    fa[ch[x][flag ^ 1]] = f;
    ch[x][flag ^ 1] = f;
    fa[f] = x;
    fa[x] = gf;
    if (gf) ch[gf][val[x] > val[gf]] = x; // or if (gf) ch[gf][f == ch[gf][1]] = x;
    push_up(f);
    push_up(x);
  }
  void splay(int x) {
    for (int f; f = fa[x], f; rotate(x))
      if (fa[f]) rotate(get(x) == get(f) ? f : x);
    root = x;
  }
  void insert(int x) {
    int p = root, last = 0;
    while (p && val[p] != x) last = p, p = ch[p][val[p] < x];
    if (p) cnt[p]++, push_up(p);
    else p = New(x, last);
    splay(p);
  }
  void remove(int x) {
    getrank(x);
    if (cnt[root] > 1) {
      cnt[root]--;
      size[root]--;
    }
    else if (ch[root][0] && ch[root][1]) {
      int p = root;
      splay(getpre());
      ch[root][1]= ch[p][1];
      fa[ch[p][1]] = root;
      push_up(root);
      del(p);
    }
    else {
      int p = root;
      root = ch[p][0] + ch[p][1];
      fa[root] = 0;
      push_up(root);
      del(p);
    }
  }
  int getrank(int x) {
    int p = root;
    while (p && val[p] != x) p = ch[p][val[p] < x];
    if (p) splay(p);
    return p ? size[ch[p][0]] + 1 : -1;
  }
  int getval(int x) {
    int p = root;
    while (p && x > 0) {
      if (size[ch[p][0]] >= x) p = ch[p][0];
      else if (size[ch[p][0]] + cnt[p] >= x) return val[p];
      else x -= size[ch[p][0]] + cnt[p], p = ch[p][1];
    }
    splay(p);
    return p ? val[p] : -1;
  }
  int getpre() {
    int p = ch[root][0];
    while (ch[p][1]) p = ch[p][1];
    return p;
  }
  int getnext() {
    int p = ch[root][1];
    while (ch[p][0]) p = ch[p][0];
    return p;
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
      case 3: printf("%d\n", set.getrank(x)); break;
      case 4: printf("%d\n", set.getval(x)); break;
      case 5: set.insert(x); printf("%d\n", set.val[set.getpre()]); set.remove(x); break;
      case 6: set.insert(x); printf("%d\n", set.val[set.getnext()]); set.remove(x); break;
    }
  }
  return 0;
}
