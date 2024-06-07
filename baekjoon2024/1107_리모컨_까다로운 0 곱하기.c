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
	const int digits_len = splice_int(digits, N);
	int idx_not_same = -1;
	int avail_max = -10000;
	int avail_min = 10000;
	int ans = abs_i32(N - 100);

	for (int i = 0; i < MAXM; i++) {
		if (!available[i]) continue;
		avail_max = max_i32(avail_max, i);
		avail_min = min_i32(avail_min, i);
	}

	for (int i = 0; i < digits_len; i++) {
		if (!available[digits[i]]) {
			idx_not_same = i;
			break;
		}
	}

	if (idx_not_same == -1) {
		ans = min_i32(digits_len, ans);
		printf("%d\n", ans);
		return;
	}
	if (avail_max < 0) {
		printf("%d\n", ans);
		return;
	}

	for (int x = idx_not_same; x >= idx_not_same - 1 && x >= 0; x--) {
		int candidate[2] = { -1, -1 };

		for (int i = 1; i <= 9; i++) {
			int a = digits[x] - i;
			int b = digits[x] + i;

			if (candidate[0] == -1 && (a > 0 || (a == 0 && x != 0)) && available[a]) {
				candidate[0] = a;
			}
			if (candidate[1] == -1 && b <= 9 && available[b]) {
				candidate[1] = b;
			}
		}

		for (int i = 0; i < 2; i++) { // Search: Among same digit number
			if (candidate[i] == -1) continue;
			const int d = i == 0 ? avail_max : avail_min;
			int nearest_channel = 0, base = 1;

			for (int j = digits_len - 1; j > x; j--) {
				nearest_channel += d * base;
				base *= 10;
			}

			nearest_channel += candidate[i] * base;
			base *= 10;

			for (int i = x - 1; i >= 0; i--) {
				nearest_channel += digits[i] * base;
				base *= 10;
			}

			ans = min_i32(ans, abs_i32(nearest_channel - N) + digits_len);
		}
	}

	if (digits_len >= 2) { // Search: one digit less number
		int nearest_channel = 0, base = 1;

		for (int i = 0; i < digits_len - 1; i++) {
			nearest_channel += avail_max * base;
			base *= 10;
		}

		ans = min_i32(ans, abs_i32(nearest_channel - N) + digits_len - 1);
	}

	do { // Search: one digit more number
		int nearest_channel = 0, base = 1;
		int avail_min_except_zero = -1;

		for (int i = 1; i < MAXM; i++) {
			if (available[i]) {
				avail_min_except_zero = i;
				break;
			}
		}

		if (avail_min_except_zero == -1) { // 0 only
			break;
		}

		for (int i = 0; i < digits_len; i++) {
			nearest_channel += avail_min * base;
			base *= 10;
		}

		nearest_channel += avail_min_except_zero * base;
		base *= 10;

		ans = min_i32(ans, abs_i32(nearest_channel - N) + digits_len + 1);
	} while (0);

    if (avail_min == 0) {
        ans = min_i32(ans, N + 1);
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