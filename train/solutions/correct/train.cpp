#include "train.h"

#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

#define F first
#define S second
#define pii pair<LL, LL>
#define pb push_back
#define pq priority_queue
#define rep(i,a,b) for (long long i=a; i < (b); i++)
#define MP make_pair
#define SZ(x) (static_cast<long long>(x.size()))
#define MOD 1000000007LL

const long long maxn = 1e5 + 10;

long long n, m, w, tot = 0;
pair <pii, long long> meal[maxn];
pair <pii, long long> meal_copy[maxn];
long long c[maxn];
vector <long long> neg[maxn];
struct Train{
  long long x, y, a, b, c;
} train[maxn];

bool cmp(pair<pii, long long> i1, pair<pii, long long> i2) {
  return MP(i1.F.S, i1.F.F) < MP(i2.F.S, i2.F.F);
}

bool cmp1(Train i1, Train i2) {
  return i1.a < i2.a;
}

long long dist[maxn];
vector <long long> city[maxn], lst[maxn];
long long id[maxn], bg[maxn], ed[maxn];
pq <pii, vector<pii>, greater<pii> > q;
bool mark[maxn];
long long curmeal = 0;

//persistnet segtree
long long rt[maxn], lc[maxn * 100], rc[maxn * 100], val[maxn * 100];

long long query(long long c, long long cl, long long cr, long long l, long long r) {
  if (l <= cl and cr <= r) return val[c];
  long long mid = cl + cr >> 1;
  long long ret = 0;
  if (l <= mid) ret = query(lc[c], cl, mid, l, r);
  if (r > mid) ret += query(rc[c], mid + 1, cr, l, r);
  return ret;
}

long long getval(long long t) { //dist + # meals strictly after the current long longerval
  long long ret = dist[t];
  if (curmeal == 0) return ret;
  long long cnt = curmeal;
  long long pos = upper_bound(meal_copy, meal_copy + w, MP(MP(train[t].b, MOD), MOD)) - meal_copy;
  if (pos > 0) cnt -= query(rt[pos - 1], 0, w - 1, 0, curmeal - 1);
  ret += cnt * c[train[t].y];
  return ret;
}

long long findKth(long long c1, long long c2, long long cl, long long cr, long long K) {
  if (cl == cr) return cl;
  long long mid = cl + cr >> 1;
  long long tmp = val[lc[c2]] - val[lc[c1]];
  if (K <= tmp) return findKth(lc[c1], lc[c2], cl, mid, K);
  K -= tmp;
  return findKth(rc[c1], rc[c2], mid + 1, cr, K);
}

long long getKth(long long l, long long r, long long K) {
  long long bg = lower_bound(meal_copy, meal_copy + w, MP(MP(l, -1LL), -1LL)) - meal_copy;
  long long ed = upper_bound(meal_copy, meal_copy + w, MP(MP(r, MOD), MOD)) - meal_copy;
  if (ed == 0 or ed - bg < K) return -1;
  return findKth((bg == 0 ? 0 : rt[bg - 1]), rt[ed - 1], 0, w - 1, K);
}

long long init(long long cl, long long cr) {
  if (cl == cr) {
    val[tot] = 0;
    return tot++;
  }
  long long tmp = tot, mid = cl + cr >> 1;
  lc[tmp] = init(cl, mid);
  rc[tmp] = init(mid + 1, cr);
  val[tmp] = 0;
  return tmp;
}

void calc(long long t) {
  long long tmp = train[t].y;
  long long tt = city[tmp][lst[tmp][id[t]]];
  long long dif = dist[t] - dist[tt];
  long long K = (dif + c[tmp] - 1) / c[tmp];
  long long val = getKth(train[tt].b + 1, train[t].b, K);
  if (val != -1) neg[val].pb(t), assert(val >= curmeal);
}

void update(long long c, long long cl, long long cr, long long pos) {
  val[c]++;
  if (cl == cr) return;
  long long mid = cl + cr >> 1;
  if (pos <= mid) {
    lc[tot] = lc[lc[c]];
    rc[tot] = rc[lc[c]];
    val[tot] = val[lc[c]];
    lc[c] = tot++;
    update(lc[c], cl, mid, pos);
  } else {
    lc[tot] = lc[rc[c]];
    rc[tot] = rc[rc[c]];
    val[tot] = val[rc[c]];
    rc[c] = tot++;
    update(rc[c], mid + 1, cr, pos);
  }
}

long long solve(int N, int M, int W, vector<int> t, vector<int> X, vector<int> Y, vector<int> A, vector<int> B, vector<int> C, vector<int> L, vector<int> R) {
  n = N, m = M, w = W;
  rep(i, 0, n) c[i] = t[i];
  rep(i, 0, m)
    train[i].x = X[i], train[i].y = Y[i], train[i].a = A[i], train[i].b = B[i], train[i].c = C[i];
  rep(i, 0, w) meal[i].F = {L[i], R[i]};
  sort(meal, meal + w, cmp); //sorted by increasing B for processing
  rep(i, 0, w) {
    meal[i].S = i;
    meal_copy[i] = meal[i];
  }
  sort(meal_copy, meal_copy + w); //sorted by increasing A for segtree
  if (w > 0) init(0, w - 1);
  rep(i, 0, w) {
    rt[i] = tot;
    lc[tot] = (i > 0 ? lc[rt[i - 1]] : lc[0]);
    rc[tot] = (i > 0 ? rc[rt[i - 1]] : rc[0]);
    val[tot] = (i > 0 ? val[rt[i - 1]] : 0);
    update(tot++, 0, w - 1, meal_copy[i].S);
  }
  memset(dist, -1, sizeof(dist));
  sort(train, train + m, cmp1);
  memset(ed, -1, sizeof(ed));
  city[0].pb(m);
  lst[0].pb(-1);
  dist[m] = 0;
  train[m].y = 0, train[m].b = -1;
  bg[0] = ed[0] = 0;
  rep(i, 0, m) {
    long long X = train[i].x;    
    while (curmeal < w and meal[curmeal].F.S < train[i].a) { //look at meals
      long long cur = curmeal++;
      for (auto it : neg[cur]) {
        if (mark[it]) continue;
	    long long tmp = train[it].y;
	    if (id[it] == bg[tmp]) continue;
	    assert(lst[tmp][id[it]] != -1);
	    while (getval(city[tmp][lst[tmp][id[it]]]) >= getval(it)) {
	      mark[city[tmp][lst[tmp][id[it]]]] = 1;
	      if (lst[tmp][id[it]] == bg[tmp]) {
	        bg[tmp] = id[it];
	        break;
	      } else lst[tmp][id[it]] = lst[tmp][lst[tmp][id[it]]];
	    }
	    if (bg[tmp] != id[it]) calc(it);
      }
    }
    while (!q.empty() and q.top().F <= train[i].a) {
      long long cur = q.top().S;
      q.pop();
      long long tmp = train[cur].y;
      while (bg[tmp] <= ed[tmp] and getval(city[tmp][ed[tmp]]) >= getval(cur)) {
	    if (bg[tmp] == ed[tmp]) {
	      bg[tmp] = SZ(city[tmp]);
	      break;
	    }
	    mark[city[tmp][ed[tmp]]] = 1;
	    ed[tmp] = lst[tmp][ed[tmp]];
      }
      if (bg[tmp] > ed[tmp]) {
        id[cur] = bg[tmp] = ed[tmp] = SZ(city[tmp]);
	    city[tmp].pb(cur);
	    lst[tmp].pb(-1);
      } else {
	    id[cur] = SZ(city[tmp]);
	    city[tmp].pb(cur);
	    lst[tmp].pb(ed[tmp]);
	    ed[tmp] = id[cur];
	    calc(cur);
      }
    }
    
    if (bg[X] > ed[X]) continue;
    dist[i] = getval(city[X][bg[X]]) + train[i].c;
    q.push({train[i].b, i});
  }
  curmeal = w;
  long long ans = 1e18;
  rep(i, 0, m) if (train[i].y == n - 1 and dist[i] != -1)
    ans = min(ans, getval(i));
  if (ans < 1e18) return ans;
  else return -1;
}
