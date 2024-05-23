/*
* 2024-05-22 Wed: Upsolving
*
* codeforces.com/contest/1969/problem/C
* C. Minimizing the Sum
* dp, implementation, *1700
*
* dp[10][5] = dp[9][5] + 1 * max(a[10] ~ a[10])
*           = dp[8][4] + 2 * max(a[9]  ~ a[10])
*           = dp[7][3] + 3 * max(a[8]  ~ a[10])
*           ...
*           = dp[4][0] + 6 * max(a[5]  ~ a[10])
*/

#define __USE_MINGW_ANSI_STDIO 0
#include <stdio.h>

#define MAXN (300000)
#define MAXK (10)
#define INF  (1000000000000000000LL)


int MIN_i32(int _A, int _B) {
	return _A <= _B ? _A : _B;
}
long long MIN_i64(long long _A, long long _B) {
	return _A <= _B ? _A : _B;
}
long long solveC_topdown(const int arr[], long long dp[][MAXK + 1], int N, int K) {
	if (N <= 0 || K < 0) return INF;
	if (dp[N][K] < INF) return dp[N][K];

	long long min_value = INF;
	int min_of_arr = 1 << 30;

	for (int i = 0; (N - 1 - i) >= 1 && (K - i) >= 0; i++) {
		long long A, B;
		A = solveC_topdown(arr, dp, N - 1 - i, K - i);
		min_of_arr = MIN_i32(min_of_arr, arr[N - 1 - i]);
		B = (long long)(i + 1) * min_of_arr;
		min_value = MIN_i64(min_value, A + B);
	}

	return dp[N][K] = min_value;
}
void solveC(const int arr[], int N, int K) {
	static long long dp[MAXN + 1][MAXK + 1];

	for (int i = 0; i <= N; i++) for (int j = 0; j <= K; j++) {
		dp[i][j] = INF;
	}

	int min_of_arr = 1 << 30;

	for (int i = 0; i <= K && i + 1 <= N; i++) {
		min_of_arr = MIN_i32(min_of_arr, arr[i]);
		dp[i + 1][i] = (long long)(i + 1) * min_of_arr;
	}

	const int k = (N - 1 <= K) ? N - 1 : K;
	solveC_topdown(arr, dp, N, k);
	printf("%lld\n", dp[N][k]);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	static int arr[MAXN];
	int T;
	scanf("%d", &T);
	do {
		int N, K;
		scanf("%d%d", &N, &K);
		for (int i = 0; i < N; i++) {
			scanf("%d", &arr[i]);
		}
		solveC(arr, N, K);
	} while (--T > 0);
}