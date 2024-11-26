#include <stdio.h>
#include <stdlib.h>

#define MAXLEN (500000)

int IO_getline(char* dest, int max) {
	char* dest0 = dest;
	for (*dest = 0, fgets(dest, max, stdin); *dest >= ' '; dest++);; *dest = 0;
	return dest - dest0;
}

static struct {
	const int* disjset;
	int d;
	int len;
} SA_compare_ctx;

int SA_compare(const int A, const int B) {
	if (SA_compare_ctx.disjset[A] - SA_compare_ctx.disjset[B]) return SA_compare_ctx.disjset[A] - SA_compare_ctx.disjset[B];
	const int A2 = A + SA_compare_ctx.d;
	const int B2 = B + SA_compare_ctx.d;
	if (A2 < SA_compare_ctx.len && B2 < SA_compare_ctx.len) return SA_compare_ctx.disjset[A2] - SA_compare_ctx.disjset[B2];
	else return B2 - A2;
}
void MergeSort_impl_SA(int list[], int sorted[], const int left, const int right) {
	if (left >= right) return;
	const int mid = left + (right - left) / 2;
	MergeSort_impl_SA(list, sorted, left, mid);
	MergeSort_impl_SA(list, sorted, mid + 1, right);
	int idx = left, first = left, second = mid + 1;
	while (first <= mid && second <= right) {
		if (SA_compare(list[first], list[second]) <= 0) sorted[idx++] = list[first++];
		else sorted[idx++] = list[second++];
	}
	while (first <= mid)    sorted[idx++] = list[first++];
	while (second <= right) sorted[idx++] = list[second++];
	for (int i = left; i <= right; i++) list[i] = sorted[i];
}
void MergeSort_SA(int list[], const int size) {
	int* sorted = calloc(size, sizeof(int)); if (!sorted) exit(1);
	MergeSort_impl_SA(list, sorted, 0, size - 1);
	free(sorted);
}
void Construct_suffix_array(int sa_dest[], int sa_disjset[], const char text[], const int len) {
	// When the construction ends, 'sa_disjset' becomes the inverse function of 'sa'.

	for (int i = 0; i < len; i++) {
		sa_dest[i] = i;
		sa_disjset[i] = text[i];
	}

	SA_compare_ctx.disjset = sa_disjset;
	SA_compare_ctx.len = len;

	for (int d = 1;; d *= 2) {
		static int sa_disjset_temp[MAXLEN];

		SA_compare_ctx.d = d;
		MergeSort_SA(sa_dest, len);

		int set_idx = 0;
		sa_disjset_temp[sa_dest[0]] = 0;

		for (int i = 1; i < len; i++) {
			if (SA_compare(sa_dest[i - 1], sa_dest[i])) set_idx++;
			sa_disjset_temp[sa_dest[i]] = set_idx;
		}

		for (int i = 0; i < len; i++) sa_disjset[i] = sa_disjset_temp[i];

		if (set_idx == len - 1) break;
	}
}
void Construct_longest_common_prefix(int lcp_dest[], const int sa[], const int sa_inverse[], const char text[], const int len) {
	for (int k = 0, i = 0; i < len; i++) {
		if (sa_inverse[i] == len - 1) continue;
		int j = sa[sa_inverse[i] + 1]; // j: The suffix following the i-th largest suffix
		while (text[i + k] == text[j + k]) k++;
		lcp_dest[sa_inverse[i]] = k;
		if (k > 0) k--;
	}
}
void solve9248(const char text[], const int len) {
	static int sa_disjset[MAXLEN];
	static int sa[MAXLEN];
	static int lcp[MAXLEN];


	Construct_suffix_array(sa, sa_disjset, text, len);
	Construct_longest_common_prefix(lcp, sa, sa_disjset, text, len);

	for (int i = 0; i < len; i++) {
		printf("%d ", sa[i] + 1);
	}

	printf("\nx ");

	for (int i = 0; i < len - 1; i++) {
		printf("%d ", lcp[i]);
	}

	putchar('\n');

#ifndef ONLINE_JUDGE
	for (int i = 0; i < len; i++)
		printf("i: %-2d, sa: %-2d, lcp: %-2d [%s]\n", i, sa[i], lcp[i], &text[sa[i]]);
#endif
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	static char text[MAXLEN + 2];
	int len = IO_getline(text, sizeof(text));
	solve9248(text, len);
}