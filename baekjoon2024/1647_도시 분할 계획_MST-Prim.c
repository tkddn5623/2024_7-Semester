#include <stdio.h>
#include <stdlib.h>

#define MAXV    (100000)
#define MAXCOST (1000)

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

struct hnode {
	int value;
	int priority;
};

typedef struct {
	struct hnode* items;
	int size;
	int capacity;
} Heap_hnode;

Heap_hnode* Heap_new() {
	Heap_hnode* pheap = calloc(1, sizeof(Heap_hnode)); if (!pheap) exit(1);
	pheap->items = calloc(16, sizeof(struct hnode)); if (!pheap->items) exit(1);
	pheap->capacity = 16;
	return pheap;
}
void Heap_delete(Heap_hnode* pheap) {
	free(pheap->items);
	free(pheap);
}
int Heap_empty(const Heap_hnode* pheap) {
	return pheap->size == 0;
}
int Heap_compare(const struct hnode _A, const struct hnode _B) {
	return _A.priority - _B.priority; // Minheap
}
void Heap_push(Heap_hnode* pheap, struct hnode item) {
	if (pheap->size == pheap->capacity - 1 && !(pheap->items = realloc(pheap->items, (pheap->capacity *= 2) * sizeof(struct hnode)))) exit(1);
	int parent, child = pheap->size + 1;
	while (child > 1) {
		if (Heap_compare(pheap->items[(parent = child / 2)], item) <= 0) break;
		pheap->items[child] = pheap->items[parent];
		child = parent;
	}
	pheap->items[child] = item;
	pheap->size++;
}
struct hnode Heap_pop(Heap_hnode* pheap) {
	const int size = pheap->size;
	struct hnode const top = pheap->items[1];
	struct hnode const last = pheap->items[size];
	int child, parent = 1;
	while ((child = parent * 2) <= size) {
		if (child < size && Heap_compare(pheap->items[child + 1], pheap->items[child]) < 0) child++;
		if (Heap_compare(last, pheap->items[child]) <= 0) break;
		pheap->items[parent] = pheap->items[child];
		parent = child;
	}
	pheap->items[parent] = last;
	pheap->size--;
	return top;
}
Graph* Graph_new(int vtxsize, int edgesize) {
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
void Graph_delete(Graph* graph) {
	free(graph->edges);
	free(graph);
}
void Graph_insert(Graph* graph, int from, int to, int weight) {
	graph->edges[graph->edgecount] = (GNode){ .id = to, .weight = weight, .next = &graph->edges[from] };
	graph->edges[from].tail->next = &graph->edges[graph->edgecount];
	graph->edges[from].tail = &graph->edges[graph->edgecount++];
}
void solve1647(Graph* graph) {
	static int dist[MAXV + 1];
	static int visited[MAXV + 1];
	int mst_length = 0;
	int weight_max = -1;

	for (int j = graph->vtxsize, i = 1; i < j; i++) {
		visited[i] = 0;
		dist[i] = MAXCOST + 1;
	}

	dist[1] = 0;

	Heap_hnode* heap = Heap_new();
	Heap_push(heap, (struct hnode) { 1, 0 });

	while (!Heap_empty(heap)) {
		struct hnode e = Heap_pop(heap);

		if (visited[e.value]) continue;

		visited[e.value] = 1;
		mst_length += e.priority;
		if (weight_max < e.priority) weight_max = e.priority;

		for (GNode* head = &graph->edges[e.value], *cur = head->next; cur != head; cur = cur->next) {
			int weight = cur->weight, id = cur->id;
			if (!visited[id] && weight < dist[id]) {
				dist[id] = weight;
				Heap_push(heap, (struct hnode) { id, weight });
				
			}
		}
	}

	Heap_delete(heap);
	printf("%d\n", mst_length - weight_max);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	int V, E;

	scanf("%d%d", &V, &E);
	Graph* G = Graph_new(V + 1, E * 2);

	for (int i = 0; i < E; i++) {
		int from, to, weight;
		scanf("%d%d%d", &from, &to, &weight);
		Graph_insert(G, from, to, weight);
		Graph_insert(G, to, from, weight);
	}
	solve1647(G);
}