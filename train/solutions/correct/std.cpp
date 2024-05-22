#include "train.h"

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int mxN = 1e5 + 10;

int n, m, w;
const int mxN = 1e5 + 5, mxT = 1e9;
const ll inf = 1e18;
struct Train {
	int fr, to, a, b, c, id;
} e0[mxN], e1[mxN], e2[mxN];
struct Meal {
	int l, r;
} a[mxN];
ll f[mxN];
int n, m, w, pre[mxN], nxt[mxN], fir[mxN], lst[mxN], cost[mxN];
int c[mxN * 35][2], s[mxN * 35], rt[mxN];
bool operator<(const Meal &x, const Meal &y) { return x.l < y.l; }
int getC(int l, int r) {
	int cnt = 0;
	for (int i = 0; i < w; i++) {
		if (a[i].l >= l && a[i].r <= r) cnt++;
	}
	return cnt;
}
struct Event {
	int id, x, y, t;
};
bool operator<(const Event &x, const Event &y) { return x.t > y.t; }
priority_queue<Event> qe;
int getS(int p, int q, int l, int r, int x, int y) {
	if (x <= l && r <= y) return s[p] - s[q];
	int mid = (l + r) >> 1, res = 0;
	if (x <= mid) res += getS(c[p][0], c[q][0], l, mid, x, y);
	if (mid < y) res += getS(c[p][1], c[q][1], mid + 1, r, x, y);
	return res;
}
int getKth(int p, int q, int l, int r, int k) {
	if (s[p] - s[q] < k) return -1;
	if (l == r) return l;
	int mid = (l + r) >> 1;
	if (s[c[p][0]] - s[c[q][0]] >= k) return getKth(c[p][0], c[q][0], l, mid, k);
	return getKth(c[p][1], c[q][1], mid + 1, r, k - (s[c[p][0]] - s[c[q][0]]));
}
int Find(int l, int r, int k) {
	int tl = lower_bound(a, a + W, (Meal){l, 0});
	int tr = upper_bound(a, a + W, (Meal){r, 0}) - a - 1;
	if (k == -1) return getS(rt[tr], (tl ? rt[tl - 1] : 0), 0, mxT, l, r);
	return getKth(rt[tr], (tl ? rt[tl - 1] : 0), 0, mxT, k);
}
void Addeve(int pos, int x, int y) { // l 在 e[x].b+1~e[y].b 这一段里面
	ll num = (f[y] - f[x] + cost[pos] - 1) / cost[pos];
	int u = Find(e[x].b + 1, e[y].b, num);
	if (u == -1) return;
	qe.push({pos, x, y, u});
}
ll solve(int N, int M, int W, vector<int> T, vector<int> X, vector<int> Y, vector<int> A,
         vector<int> B, vector<int> C, vector<int> L, vector<int> R) {
	n = N, m = M, w = W;
	for (int i = 0; i < n; i++) cost[i] = T[i];
	for (int i = 0; i < w; i++) {
		a[i] = {L[i], R[i]};
	}
	sort(a, a + w);
	for (int i = 0, x = 0; i < w; i++) {
		x = rt[i] = Ins(x, 0, mxT, a[i].r);
	}
	for (int i = 0; i < m; i++) {
		e0[i] = e1[i] = e2[i] = {X[i], Y[i], A[i], B[i], C[i], i + 1};
	}
	sort(e1, e1 + m, [](const Train &x, const Train &y) { return x.a < y.a; });
	sort(e2, e2 + m, [](const Train &x, const Train &y) { return x.b < y.b; });
	ll ans = inf;
	for (int i = 0, j = 0; i < m; i++) {
		int x = e1[i].fr;
		f[e1[i].id] = inf;
		if (!x) {
			f[e1[i].id] = e1[i].c + 1ll * Find(0, e1[i].a - 1) * T[0];
		}
		while (j < m && e2[j].b <= e[i].a) {
			// 加入e2[j]
			int z = e2[j].id, at = e2[j].to;
			while (lst[at]) {
				int p = lst[at];
				if (f[p] < f[z]) break;
				lst[at] = pre[p], nxt[pre[p]] = 0;
			}
			pre[z] = lst[at];
			if (lst[at]) nxt[lst[at]] = z, Addeve(at, lst[at], z);
			lst[at] = z;
			j++;
		}
		while (qe.size() && qe.top.t < e1[i].a) {
			auto [id, xx, yy, t] = qe.top();
			qe.pop();
			if (nxt[xx] != yy) continue;
			pre[yy] = pre[xx];
			if (!pre[yy]) fir[id] = yy;
			else {
				nxt[pre[yy]] = yy;
				Addeve(id, pre[yy], yy);
			}
		}
		if (fir[x]) {
			int y = fir[x];
			f[e1[i].id] =
			    min(f[e1[i].id], e1[i].c + 1ll * Find(e0[y].b + 1, e1[i].a - 1) * T[x] + f[y]);
		}
		if (e1[i].to == n - 1) {
			ans = min(ans, f[e1[i].id] + 1ll * Find(e1[i].b + 1, mxT) * T[n - 1]);
		}
	}
	if (ans < inf) return ans;
	return -1;
}