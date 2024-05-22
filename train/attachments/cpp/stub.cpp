#include "train.h"

#include <cassert>
#include <cstdio>

#include <vector>

signed main() {
  int N, M, W;
  assert(3 == scanf("%d %d %d", &N, &M, &W));
  std::vector<int> t(N);
  std::vector<int> x(M);
  std::vector<int> y(M);
  std::vector<int> a(M);
  std::vector<int> b(M);
  std::vector<int> c(M);
  std::vector<int> l(W);
  std::vector<int> r(W);
  for (int i = 0; i < N; i++)
    assert(1 == scanf("%d", &t[i]));
  for (int i = 0; i < M; i++)
    assert(5 == scanf("%d %d %d %d %d", &x[i], &y[i], &a[i], &b[i], &c[i]));
  for (int i = 0; i < W; i++)
    assert(2 == scanf("%d %d", &l[i], &r[i]));
  printf("%lld", solve(N, M, W, t, x, y, a, b, c, l, r));
}
