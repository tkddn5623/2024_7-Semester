#include <stdio.h>

#define MAXM (10)

int abs_i32(int A) {
	return A >= 0 ? A : -A;
}
int min_i32(int A, int B) {
	return A <= B ? A : B;
}
int max_i32(int A, int B) {
	return A >= B ? A : B;
}
int splice_int(int* Dest, int n) {
	int m = 100000, i = 6;
	while (m > 1 && !(n / m)) { m /= 10; i--; }
	do { *Dest++ = n / m; n %= m; } while (m /= 10);
	return i;
}
void solve1107(int available[], int N) {
	int digits[8] = { 0 };
	int digits_len;
	int ans = abs_i32(N - 100);

	for (int i = 0; i <= (500000 + 500000 - 100 - 6); i++) {
		digits_len = splice_int(digits, i);

		for (int j = 0; j < digits_len; j++) {
			if (!available[digits[j]]) goto LOOP_CONTINUE;
		}

		ans = min_i32(ans, abs_i32(N - i) + digits_len);
		//printf("i %d, ans %d\n", i, ans);

	LOOP_CONTINUE:;
	}

	printf("%d\n", ans);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	int available[MAXM + 1] = { 0 };
	int N, M;

	scanf("%d%d", &N, &M);

	for (int i = 0; i < MAXM; i++)
		available[i] = 1;

	for (int i = 0; i < M; i++) {
		int a;
		scanf("%d", &a);
		available[a] = 0;
	}

	solve1107(available, N);
}