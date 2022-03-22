#include<cstdio>

const int N = 1e6 + 5;

int n, q;
long long a[N << 2], tag[N << 2];

int lc(int p) { return p * 2; }
int rc(int p) { return p * 2 + 1; }

void f(int p, int l, int r, long long x) {
  a[p] += (long long)(r - l + 1) * x;
  tag[p] += x;
}

void push_down(int p, int l, int r) {
  if (tag[p]) {
    int mid = (l + r) >> 1;
    f(lc(p), l, mid, tag[p]);
    f(rc(p), mid + 1, r, tag[p]);
    tag[p] = 0;
  }
}

void push_up(int p) {
  a[p] = a[lc(p)] + a[rc(p)];
}

void build(int p, int l, int r) {
  if (l == r) {
    scanf("%lld", &a[p]);
    return ;
  }
  int mid = (l + r) >> 1;
  build(lc(p), l, mid);
  build(rc(p), mid + 1, r);
  push_up(p);
}

void upd(int p, int l, int r, int ul, int ur, int x) {
  if (ul <= l && r <= ur) {
    f(p, l, r, x);
    return ;
  }
  push_down(p, l, r);
  int mid = (l + r) >> 1;
  if (ul <= mid) upd(lc(p), l, mid, ul, ur, x);
  if (mid < ur) upd(rc(p), mid + 1, r, ul, ur, x);
  push_up(p);
}

long long query(int p, int l, int r, int ql, int qr) {
  if (ql <= l && r <= qr) return a[p];
  push_down(p, l, r);
  int mid = (l + r) >> 1;
  long long ans = 0;
  if (ql <= mid) ans += query(lc(p), l, mid, ql, qr);
  if (mid < qr) ans += query(rc(p), mid + 1, r, ql, qr);
  return ans;
}

int main() {
  scanf("%d%d", &n, &q);
  build(1, 1, n);

  while (q--) {
    int op, l, r, x;
    scanf("%d%d%d", &op, &l, &r);
    if (op == 1) {
      scanf("%d", &x);
      upd(1, 1, n, l, r, x);
    }
    else printf("%lld\n", query(1, 1, n, l, r));
  }
  return 0;
}
