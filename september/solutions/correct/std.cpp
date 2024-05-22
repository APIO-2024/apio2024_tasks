#include <bits/stdc++.h>
#include "september.h"

int solve (int N, int M, std::vector<int> F, std::vector<std::vector<int>> S)
{
	int K = 0, L = 0, R = 0;
	std::vector<int> c(N), d(N), f(N);
	for (int i = 1; i < N; i++) d[F[i]]++;
	auto add = [&] (int p)
	{
		for (int i = 0; i < M; i++)
		{
			if (c[S[i][p]] == 0) R++;
			if (++c[S[i][p]] == M)
			{
				R--; f[S[i][p]] = 1; L++;
				for (int u = S[i][p]; !d[u] and f[u]; d[u = F[u]]--) L--;
			}
		}
	};
	for (int l = 0, r; l < N - 1; K++, l = r + 1) for (add(r = l); L + R; add(++r)) ;
	return K;
}