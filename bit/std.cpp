#include<cstdio>

const int N = 1e6 + 5;
int n, q;
long long c[N];

int lowbit(int x) {
  return x & (-x);
}

void add(int i, int x) {
  while (i <= n) {
    c[i] += x;
    i += lowbit(i);
  }
}

long long sum(int i) {
  long long ans = 0;
  while (i) {
    ans += c[i];
    i -= lowbit(i);
  }
  return ans;
}

int main() {
  scanf("%d%d", &n, &q);

  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    add(i, x);
  }

  while (q--) {
    int op;
    scanf("%d", &op);
    if (op == 1) {
      int i, x;
      scanf("%d%d", &i, &x);
      add(i, x);
    }
    else {
      int l, r;
      scanf("%d%d", &l, &r);
      printf("%lld\n", sum(r) - sum(l - 1));
    }
  }
  return 0;
}
