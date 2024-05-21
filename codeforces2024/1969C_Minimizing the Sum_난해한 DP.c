// codeforces.com/contest/1969/problem/C
// C. Minimizing the Sum
// dp, implementation, *1700

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
void solveC(int arr[], int N, int K) {
	static long long dp[MAXN + 1][11];

	for (int i = 0; i <= N; i++) for (int j = 0; j <= K; j++) {
		dp[i][j] = INF;
	}

	dp[0][0] = 0LL;

	for (int i = 0; i < N; i++) for (int j = 0; j <= K && (i == 0 || j < i); j++) {
		int A = (1 << 30);
		for (int d = 0; i + d < N && j + d <= K; d++) {
			A = MIN_i32(A, arr[i + d]);
			dp[i + d + 1][j + d] = MIN_i64(dp[i + d + 1][j + d], dp[i][j] + (long long)(d + 1) * A);
		}
	}

	for (int i = K; i >= 0; i--) {
		if (dp[N][i] < INF) {
			printf("%lld\n", dp[N][i]);
			break;
		}
	}
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