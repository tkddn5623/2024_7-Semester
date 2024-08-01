#pragma GCC optimize "O3"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV (100000)
#define MAXE (1000000)

typedef struct _GNode_augmented {
	int from;
	int to;
	int weight;
} GNode;
int UF_find(int disjset[], int key) {
	if (disjset[key] < 0) return key;
	else return disjset[key] = UF_find(disjset, disjset[key]);
}
void UF_union(int disjset[], int A, int B) {
	A = UF_find(disjset, A);
	B = UF_find(disjset, B);
	if (A == B) return;
	disjset[B] = A;
}
int MergeSort_compare_GNode(const GNode _A, const GNode _B) {
	return _A.weight - _B.weight;
}
void MergeSort_impl_GNode(GNode list[], GNode sorted[], const int left, const int right) {
	if (left >= right) return;
	const int mid = left + (right - left) / 2;
	MergeSort_impl_GNode(list, sorted, left, mid);
	MergeSort_impl_GNode(list, sorted, mid + 1, right);
	int idx = left, first = left, second = mid + 1;
	while (first <= mid && second <= right) {
		if (MergeSort_compare_GNode(list[first], list[second]) <= 0) sorted[idx++] = list[first++];
		else sorted[idx++] = list[second++];
	}
	while (first <= mid)    sorted[idx++] = list[first++];
	while (second <= right) sorted[idx++] = list[second++];
	for (int i = left; i <= right; i++) list[i] = sorted[i];
}
void MergeSort_GNode(GNode list[], const int size) {
	GNode* sorted = calloc(size, sizeof(GNode)); if (!sorted) exit(1);
	MergeSort_impl_GNode(list, sorted, 0, size - 1);
	free(sorted);
}
void solve1647_Kruskal(GNode edges[], const int V, const int E) {
	static int disjset[MAXV + 1];
	int mst_length = 0;
	int weight_max = -1;

	MergeSort_GNode(edges, E);

	for (int i = 1; i <= V; i++) { disjset[i] = -1; }

	for (int i = 0; i < E; i++) {
		GNode e = edges[i];
		if (UF_find(disjset, e.from) == UF_find(disjset, e.to)) continue;
		UF_union(disjset, e.from, e.to);
		mst_length += e.weight;
		if (weight_max < e.weight) weight_max = e.weight;
	}

	printf("%d\n", mst_length - weight_max);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	int V, E;
	static GNode edges[MAXE];

	scanf("%d%d", &V, &E);

	for (int i = 0; i < E; i++) {
		scanf("%d%d%d", &edges[i].from, &edges[i].to, &edges[i].weight);
	}

	solve1647_Kruskal(edges, V, E);
}