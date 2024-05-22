#include"september.h"
#define MaxN 100500
int son[MaxN];
bool vis[MaxN];
std::vector<int> g[MaxN];
void calc(int N, std::vector<int>& S, bool *flag, int *tmin, int *tmax)
{
	for (int i = 0; i < N; i++)
		vis[i] = 0;
	int cnt = 0;
	for (int i = 0; i < N-1; i++) {
		int u = S[i];
		tmin[u] = std::min(tmin[u], i);
		tmax[u] = std::max(tmax[u], i);
		vis[u] = 1;
		cnt += son[u];
		for (int j = 0; j < g[u].size(); j++)
			if (vis[g[u][j]])
				cnt--;
		flag[i] &= (cnt==0);
	}
}
int tmin[MaxN], tmax[MaxN], o[MaxN];
bool flag[MaxN];
int solve(int N, int M, std::vector<int> F, std::vector<std::vector<int>> S) {
	for (int i = 0; i < N; i++) {
		g[i].clear();
	 	son[i] = 0;
    }
	for (int i = 1; i < N; i++) {
		g[F[i]].push_back(i);
		g[i].push_back(F[i]);
		son[F[i]]++;
	}
	for (int i = 0; i+1 < N-1; i++) {
		flag[i] = 1;
		o[i] = 0;
	}
	for (int i = 1; i < N; i++) {
		tmin[i] = N+1;
		tmax[i] = -1;
	}
	for (int i = 0; i < M; i++)
		calc(N, S[i], flag, tmin, tmax);
	for (int id = 1; id < N; id++) {
		o[tmin[id]]++;
		o[tmax[id]]--;
	}
	int ans = 1;
	for (int i = 0; i+1 < N-1; i++) {
		if (i>0)
			o[i] += o[i-1];
		if (!o[i] && flag[i])
			ans++;
	}
	return ans;
}
