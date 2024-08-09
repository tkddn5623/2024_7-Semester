// DFS Depth optimization question... (2024-08-01, in hongdae ipgue)
// O3 option: 18736KB, 60ms
// O2 option: 35516KB, 64ms
#pragma GCC optimize "O3"
#include <stdio.h>

#define MAXN (1000)
#define MAXM (1000)

void IO_getline(char* dest, int max) {
	for (*dest = 0, fgets(dest, max, stdin); *dest >= ' '; dest++);; *dest = 0;
}
int IO_read_int() {
	int a, b, c;
	while ((c = getchar()) && c < '-');
	for (b = c < '0' ? 0 : c & 0xf; (a = getchar()) >= '0'; b = b * 10 + (a & 0xf));
	return c == '-' ? -b : b;
}
int UF_find(int disjset[], int key) {
	if (disjset[key] < 0) return key;
	else return disjset[key] = UF_find(disjset, disjset[key]);
}
void UF_union(int disjset[], int A, int B) {
	A = UF_find(disjset, A);
	B = UF_find(disjset, B);
	if (A == B) return;
	disjset[A] += disjset[B];
	disjset[B] = A;
}
int UF_size(int disjset[], int key) {
	return -disjset[UF_find(disjset, key)];
}


static const int dx[] = { 1, -1, 0, 0 };
static const int dy[] = { 0, 0, 1, -1 };
static int disjset[MAXN * MAXM];
static int visited[MAXN][MAXM];
static char input[MAXN][MAXM + 2];
static int R, C;

int Array_find(const int arr[], int N, int key) {
	for (int i = 0; i < N; i++) {
		if (arr[i] == key) return i;
	}
	return -1;
}
void solve16946_DFS(int r1, int c1, int r0, int c0) {
	if (r1 < 0 || r1 >= R || c1 < 0 || c1 >= C ||
		input[r1][c1] == '1' || visited[r1][c1]) return;

	visited[r1][c1] = 1;

	if (r0 != -1 && c0 != -1) {
		UF_union(disjset, r1 * C + c1, r0 * C + c0);
	}

	for (int i = 0; i < 4; i++) {
		int r2 = r1 + dx[i];
		int c2 = c1 + dy[i];
		if (r2 < 0 || r2 >= R || c2 < 0 || c2 >= C ||
			input[r2][c2] == '1' || visited[r2][c2]) continue;
		solve16946_DFS(r2, c2, r1, c1);
	}
}
void solve16946() {
	static char answer[MAXN * (MAXM + 1)];
	int answer_idx = 0;

	for (int j = R * C, i = 0; i < j; i++) {
		disjset[i] = -1;
	}

	for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
		visited[i][j] = 0;
	}

	for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
		solve16946_DFS(i, j, -1, -1);
	}

	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (input[i][j] == '0') {
				answer[answer_idx++] = '0';
			}
			else {
				int visited_[4] = { -1,-1,-1,-1 };
				int sum = 1;

				for (int k = 0; k < 4; k++) {
					int r = i + dx[k];
					int c = j + dy[k];
					if (r < 0 || r >= R || c < 0 || c >= C || input[r][c] == '1') continue;
					int disj_num = UF_find(disjset, r * C + c);
					if (Array_find(visited_, 3, disj_num) > -1) continue;
					visited_[k] = disj_num;
					sum += UF_size(disjset, disj_num);
				}

				answer[answer_idx++] = (sum % 10) | '0';
				/*
				// Integer output
				int divisor = 1000000000;
				while (divisor > 1 && !(sum / divisor)) { divisor /= 10; }
				do { answer[answer_idx++] = '0' | sum / divisor; sum %= divisor; } while (divisor /= 10);
				*/
			}
		}
		answer[answer_idx++] = '\n';
	}

	answer[answer_idx++] = '\0';
	puts(answer);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	R = IO_read_int();
	C = IO_read_int();

	for (int i = 0; i < R; i++) {
		IO_getline(input[i], sizeof(input[i]));
	}

	solve16946();

}