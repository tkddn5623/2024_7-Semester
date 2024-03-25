#include <stdio.h>
#include <stdlib.h>

#define MAXV (100000)
#define INF  (1111111111)

typedef struct _GNode {
	union { struct { int id, weight; }; struct _GNode* tail; };
	struct _GNode* next;
} GNode;

typedef struct {
	GNode* edges;
	int vtxsize;
	int edgesize;
	int edgecount;
} Graph;

int solve28472_build_minimax_tree_dfs_min(Graph* graph, int minimax[], int current, int parent);
int solve28472_build_minimax_tree_dfs_max(Graph* graph, int minimax[], int current, int parent);

Graph* GR_new(int vtxsize, int edgesize) {
	Graph* graph;
	graph = malloc(sizeof(Graph)); if (!graph) exit(1);
	graph->edges = calloc(edgesize + vtxsize, sizeof(GNode)); if (!graph->edges) exit(1);
	graph->vtxsize = vtxsize;
	graph->edgesize = edgesize + vtxsize;
	graph->edgecount = vtxsize;
	for (int i = 0; i < vtxsize; i++) {
		graph->edges[i].next = &graph->edges[i];
		graph->edges[i].tail = &graph->edges[i];
	}
	return graph;
}
void GR_delete(Graph* graph) {
	free(graph->edges);
	free(graph);
}
void GR_insert(Graph* graph, int from, int to) {
	graph->edges[graph->edgecount] = (GNode){ .id = to, .next = &graph->edges[from] };
	graph->edges[from].tail->next = &graph->edges[graph->edgecount];
	graph->edges[from].tail = &graph->edges[graph->edgecount++];
}
int MIN_i32(const int A, const int B) {
	return A <= B ? A : B;
}
int MAX_i32(const int A, const int B) {
	return A >= B ? A : B;
}
int solve28472_build_minimax_tree_dfs_min(Graph* graph, int minimax[], int current, int parent) {
	if (minimax[current] > -1) return minimax[current];

	int min_of_max_value = INF;

	for (GNode* head = &graph->edges[current], *cur = head->next; cur != head; cur = cur->next) {
		int max_value, id = cur->id;

		if (id == parent) continue;

		max_value = solve28472_build_minimax_tree_dfs_max(graph, minimax, id, current);
		min_of_max_value = MIN_i32(min_of_max_value, max_value);
	}

	return minimax[current] = min_of_max_value;
}
int solve28472_build_minimax_tree_dfs_max(Graph* graph, int minimax[], int current, int parent) {
	if (minimax[current] > -1) return minimax[current];

	int max_of_min_value = -INF;

	for (GNode* head = &graph->edges[current], *cur = head->next; cur != head; cur = cur->next) {
		int min_value, id = cur->id;

		if (id == parent) continue;

		min_value = solve28472_build_minimax_tree_dfs_min(graph, minimax, id, current);
		max_of_min_value = MAX_i32(max_of_min_value, min_value);
	}

	return minimax[current] = max_of_min_value;
}
int read_int() {
	int a, b;
	while ((a = getchar()) && a < '0');
	for (b = a & 0xf; (a = getchar()) >= '0'; b = b * 10 + (a & 0xf));
	return b;
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#else
	static char buf_stdin[1 << 18];
	static char buf_stdout[1 << 18];
	setvbuf(stdin, buf_stdin, _IOFBF, sizeof(buf_stdin));
	setvbuf(stdout, buf_stdout, _IOFBF, sizeof(buf_stdout));
#endif
	static int minimax[MAXV + 1];
	int N, R, L, Q;
	Graph* graph;

	N = read_int();
	R = read_int();
	graph = GR_new(N + 1, 2 * (N - 1));
	for (int i = 1; i <= N; i++) minimax[i] = -1;

	for (int i = 0; i < N - 1; i++) {
		int from = read_int();
		int to = read_int();
		GR_insert(graph, from, to);
		GR_insert(graph, to, from);
	}

	L = read_int();

	for (int i = 0; i < L; i++) {
		int leaf = read_int();
		int value = read_int();
		minimax[leaf] = value;
	}

	solve28472_build_minimax_tree_dfs_max(graph, minimax, R, -1);
	Q = read_int();

	for (int i = 0; i < Q; i++) {
		int q = read_int();
		printf("%d\n", minimax[q]);
	}

	GR_delete(graph);
}