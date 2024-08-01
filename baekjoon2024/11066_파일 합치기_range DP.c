#define __USE_MINGW_ANSI_STDIO 0
#include <stdio.h>
#include <string.h>

#define MAXN (500)

struct recursive_ctx {
	int memo[MAXN][MAXN];
	long long* psum;
} ctx;

int MIN_i32(int A, int B) {
	return A <= B ? A : B;
}
int PSUM_get(const long long psum[], int from, int to) {
	return (int)(psum[to + 1] - psum[from]);
}
int solve11066_impl(const int arr[], int N, int L, int R) {
	if (ctx.memo[L][R] > -1) {
		return ctx.memo[L][R];
	}

	int min_value = 1 << 30;

	for (int i = L; i < R; i++) {
		int a = solve11066_impl(arr, N, L, i) + solve11066_impl(arr, N, i + 1, R);
		int b = PSUM_get(ctx.psum, L, R);
		min_value = MIN_i32(min_value, a + b);
	}

	return ctx.memo[L][R] = min_value;
}
void solve11066(const int arr[], int N) {
	static long long arr_psum[MAXN + 1];

	memset(ctx.memo, -1, sizeof(ctx.memo));

	for (int i = 0; i < N; i++) { ctx.memo[i][i] = 0; }

	arr_psum[0] = 0LL;

	for (int i = 0; i < N; i++) { arr_psum[i + 1] = arr_psum[i] + (long long)arr[i]; }

	ctx.psum = arr_psum;
	printf("%d\n", solve11066_impl(arr, N, 0, N - 1));
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	static int arr[MAXN];
	int T;
	scanf("%d", &T);
	do {
		int N;
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &arr[i]);
		}
		solve11066(arr, N);
	} while (--T > 0);
}