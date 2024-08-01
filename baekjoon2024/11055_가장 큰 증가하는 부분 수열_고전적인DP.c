#include <stdio.h>

#define MAXN (1000)

int i32_max(int A, int B) {
	return A >= B ? A : B;
}
void solve11055(int arr[], int N) {
	static int dp[MAXN + 1] = { 0 };

	for (int i = 0; i < N; i++) {
		dp[i] = arr[i];
		for (int j = 0; j < i; j++) {
			if (arr[j] >= arr[i]) continue;
			dp[i] = i32_max(dp[i], dp[j] + arr[i]);
		}
	}

	int mx = -1;

	for (int i = 0; i < N; i++) {
		mx = i32_max(mx, dp[i]);
	}

	printf("%d\n", mx);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	static int arr[MAXN];
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	solve11055(arr, N);
}