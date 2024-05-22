#include "train.h"

#include <bits/stdc++.h>
void Assert(bool x) {
	if (!x) {
		std::cout << "invalid input" << std::endl;
		exit(0);
	}
}
signed main() {
	std::string str;
	std::cin >> str;
	Assert(str == "43hecs9qw9w9dw8h39fnasqwu84r8dev");
	int N, M, W;
	Assert(3 == scanf("%d %d %d", &N, &M, &W));
	Assert(2 <= N && N <= 100000);
	Assert(0 <= M && M <= 100000);
	Assert(0 <= W && W <= 100000);
	std::vector<int> t(N);
	std::vector<int> x(M);
	std::vector<int> y(M);
	std::vector<int> a(M);
	std::vector<int> b(M);
	std::vector<int> c(M);
	std::vector<int> l(W);
	std::vector<int> r(W);
	for (int i = 0; i < N; i++) Assert(1 == scanf("%d", &t[i])), Assert(1 <= t[i] && t[i] <= 1e9);
	for (int i = 0; i < M; i++) {
		Assert(5 == scanf("%d %d %d %d %d", &x[i], &y[i], &a[i], &b[i], &c[i]));
		// if (x[i] == y[i]) cerr << i << ' ' << x[i] << ' ' << y[i] << endl;
		Assert(x[i] != y[i]);
		Assert(a[i] < b[i]);
		Assert(0 <= x[i] && x[i] < N);
		Assert(0 <= y[i] && y[i] < N);
		Assert(1 <= a[i] && b[i] <= 1e9);
		Assert(1 <= c[i] && c[i] <= 1e9);
	}
	for (int i = 0; i < W; i++) {
		Assert(2 == scanf("%d %d", &l[i], &r[i]));
		Assert(l[i] <= r[i]);
		// if (!(1 <= l[i] && r[i] <= 1e9)) cerr << i << ' ' << l[i] << ' //' << r[i] << endl;
		Assert(1 <= l[i] && r[i] <= 1e9);
	}
	long long w = solve(N, M, W, t, x, y, a, b, c, l, r);
	std::cout << "sxhcnrtkowadcmssnrw4958scufufe45" << std::endl;
	printf("%lld", w);
}
