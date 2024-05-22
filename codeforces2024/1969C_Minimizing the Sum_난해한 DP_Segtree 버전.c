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
#define INF  (1000000000000000000LL)

int MIN_i32(int _A, int _B) {
	return _A <= _B ? _A : _B;
}
long long MIN_i64(long long _A, long long _B) {
	return _A <= _B ? _A : _B;
}
int MIN_of(const int arr[], int left, int right) { // Or a segment tree
	int m = 1 << 30;
	for (int i = left; i <= right; i++) {
		if (m > arr[i]) m = arr[i];
	}
	return m;
}
void SG_construct(int _Dest[], const int items[], const int item_len) {
	int leafs = 1;
	while (leafs < item_len) { leafs <<= 1; }
	for (int i = 0; i < item_len; i++) {
		_Dest[i + leafs] = items[i];
	}
	for (int i = leafs - 1; i >= 1; i--) {
		_Dest[i] = MIN_i32(_Dest[i * 2], _Dest[i * 2 + 1]);
	}
	_Dest[0] = leafs;
}
int SG_query(const int segtree[], int from, int to) {
	int ret = 1 << 30;
	from += segtree[0]; to += segtree[0];
	while (from <= to) {
		if (from % 2 == 1) ret = MIN_i32(ret, segtree[from++]);
		if (to % 2 == 0) ret = MIN_i32(ret, segtree[to--]);
		from /= 2; to /= 2;
	}
	return ret;
}
long long solveC_topdown(int arr[], long long dp[][11], int N, int K, const int segtree[]) {
	if (N <= 0 || K < 0) return INF;
	if (dp[N][K] < INF) return dp[N][K];

	long long min_value = INF;

	for (int i = 0; (N - 1 - i) >= 1 && (K - i) >= 0; i++) {
		long long A, B;
		A = solveC_topdown(arr, dp, N - 1 - i, K - i, segtree);
		B = (long long)(i + 1) * SG_query(segtree, N - 1 - i, N - 1);
		min_value = MIN_i64(min_value, A + B);
	}

	return dp[N][K] = min_value;
}
void solveC(int arr[], int N, int K) {
	static long long dp[MAXN + 1][11];
	static int segtree[1 << 20];

	for (int i = 0; i <= N; i++) for (int j = 0; j <= K; j++) {
		dp[i][j] = INF;
	}

	for (int i = 0; i <= K && i + 1 <= N; i++) {
		dp[i + 1][i] = (long long)(i + 1) * MIN_of(arr, 0, i);
	}

	SG_construct(segtree, arr, N);

	const int k = (N - 1 <= K) ? N - 1 : K;
	solveC_topdown(arr, dp, N, k, segtree);
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