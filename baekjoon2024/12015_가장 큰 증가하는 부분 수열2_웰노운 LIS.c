#include <stdio.h>

#define MAXN (1000000)

int Binary_equal_or_greater(const int arr[], int left, int right, int key) {
	int pos = -1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] >= key) {
			pos = mid;
			right = mid - 1;
		}
		else left = mid + 1;
	}
	return pos;
}
void solve12015(int arr[], int N) {
	static int memo[MAXN + 1] = { 0 };
	int memo_len = 0;

	memo[memo_len++] = arr[0];

	for (int i = 1; i < N; i++) {
		if (memo[memo_len - 1] >= arr[i]) {
			memo[Binary_equal_or_greater(memo, 0, memo_len - 1, arr[i])] = arr[i];
		}
		else {
			memo[memo_len++] = arr[i];
		}
	}
	
	printf("%d\n", memo_len);
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
	solve12015(arr, N);
}