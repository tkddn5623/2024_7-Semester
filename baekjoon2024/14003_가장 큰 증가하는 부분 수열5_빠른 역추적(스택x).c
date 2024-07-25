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
	static int memo[MAXN + 1] = { 0 };  //memo1: pseudo seq
	static int memo2[MAXN + 1] = { 0 }; //memo2: memo Kth stack element. (If I implement a real stack, the program will be slower.)
	int memo_len = 0;

	memo[memo_len++] = arr[0];
	memo2[0] = 1;

	for (int i = 1; i < N; i++) {
		int idx = -1;

		if (memo[memo_len - 1] >= arr[i])
			idx = Binary_equal_or_greater(memo, 0, memo_len - 1, arr[i]);
		else
			idx = memo_len++;

		memo[idx] = arr[i];
		memo2[i] = idx + 1;
	}

	printf("%d\n", memo_len);

	for (int j = memo_len, i = N - 1; i >= 0; i--) {
		if (memo2[i] == j) {
			memo[j - 1] = arr[i];
			j--;
		}
	}

	for (int i = 0; i < memo_len; i++) {
		printf("%d ", memo[i]);
	}

	putchar('\n');
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