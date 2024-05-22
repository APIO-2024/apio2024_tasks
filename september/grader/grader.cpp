#include "september.h"

#include <iostream>
#include <string>
#include <vector>

namespace mtbpdhr2zxjo1o4i9oreohsbuzzl4s6u
{
	int taskcase ()
	{
		int N, M; std::cin >> N >> M;
		std::vector<int> F(N); F[0] = -1;
		for (int i = 1; i < N; i++) std::cin >> F[i];
		std::vector<std::vector<int>> S(M, std::vector<int>(N - 1));
		for (int i = 0; i < M; i++) for (int j = 0; j < N - 1; j++) std::cin >> S[i][j];
		return solve(N, M, F, S);
	}

	int mian ()
	{
		std::ios::sync_with_stdio(false); std::cin.tie(nullptr); std::cout.tie(nullptr);
		std::string s; std::cin >> s;
		if (s != "txy4h26c1rm1uv8tr3eonahd67u8h56x")
		{
			std::cout << "7ckgnn4wyi495puj3ibqf81dqvapyv6b" << std::endl;
			std::cout << "Invalid Input" << std::endl;
			exit(0);
		}
		int T; std::cin >> T; std::vector<int> A(T);
		for (int i = 0; i < T; i++) A[i] = taskcase();
		std::cout << "7ckgnn4wyi495puj3ibqf81dqvapyv6b" << std::endl;
		for (int i = 0; i < T; i++) std::cout << A[i] << "\n";
		return 0;
	}
}

int main () {return mtbpdhr2zxjo1o4i9oreohsbuzzl4s6u::mian();}