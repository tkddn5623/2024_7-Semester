#include <stdio.h>
#include <stdlib.h>


#define MAXN (32000)

// ---------------------
// Data structures begin

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

typedef struct {
	int* items;
	int capacity;
	int front;
	int rear;
} Queue;


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


Queue* Queue_new() {
	Queue* pqueue = calloc(1, sizeof(Queue)); if (!pqueue) exit(1);
	pqueue->items = calloc(16, sizeof(int)); if (!pqueue->items) exit(1);
	pqueue->capacity = 16;
	return pqueue;
}
void Queue_delete(Queue* pqueue) {
	free(pqueue->items);
	free(pqueue);
}
int Queue_empty(const Queue* pqueue) {
	return pqueue->front == pqueue->rear;
}
void Queue_resize(Queue* pqueue) {
	const int front = pqueue->front, rear = pqueue->rear, capacity = pqueue->capacity;
	if (front - rear == 1 || front - rear == 1 - capacity) {
		pqueue->items = realloc(pqueue->items, (pqueue->capacity = capacity * 2) * sizeof(int)); if (!pqueue->items) exit(1);
		if (front < rear) return;
		else if (rear <= capacity - front) {
			for (int i = 0; i < rear; i++) { pqueue->items[i + capacity] = pqueue->items[i]; }
			pqueue->rear = rear + capacity;
		}
		else {
			for (int i = front; i < capacity; i++) { pqueue->items[i + capacity] = pqueue->items[i]; }
			pqueue->front = front + capacity;
		}
	}
}
void Queue_push(Queue* pqueue, int item) {
	Queue_resize(pqueue);
	const int rear = pqueue->rear;
	pqueue->rear = (rear + 1) & (pqueue->capacity - 1);
	pqueue->items[rear] = item;
}
int Queue_pop(Queue* pqueue) {
	const int front = pqueue->front;
	pqueue->front = (front + 1) & (pqueue->capacity - 1);
	return pqueue->items[front];
}
int Queue_front(const Queue* pqueue) {
	return pqueue->items[pqueue->front];
}
int Queue_size(const Queue* pqueue) {
	return (pqueue->rear - pqueue->front + pqueue->capacity) & (pqueue->capacity - 1);
}

// Data structures end
// ----------------------
// Problem solvings begin

void Topological_Sort_Indgree(int indgree[], const Graph* graph) {
	const GNode* edges = graph->edges;
	for (int j = graph->edgecount, i = graph->vtxsize; i < j; i++) {
		indgree[edges[i].id]++;
	}
}
void Topological_Sort(int sorted[], const Graph* graph) {
	static int indgree[MAXN + 1];
	const int vtxmax = graph->vtxsize - 1;
	int sorted_len = 0;

	Queue* queue = Queue_new();
	Topological_Sort_Indgree(indgree, graph);

	for (int i = 1; i <= vtxmax; i++) {
		if (indgree[i] > 0) continue;
		Queue_push(queue, i);
	}

	while (!Queue_empty(queue)) {
		int vtx = Queue_pop(queue);
		sorted[sorted_len++] = vtx;
		for (GNode* head = &graph->edges[vtx], *cur = head->next; cur != head; cur = cur->next) {
			if (--indgree[cur->id] > 0) continue;
			Queue_push(queue, cur->id);
		}
	}

	Queue_delete(queue);
}

// Problem solvings done
// ---------------------
// IO section

int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	static int result[MAXN];
	int N, M;

	scanf("%d%d", &N, &M);
	Graph* G = Graph_new(N + 1, M);

	for (int i = 0; i < M; i++) {
		int from, to;
		scanf("%d%d", &from, &to);
		Graph_insert(G, from, to, 0);
	}

	Topological_Sort(result, G);
	Graph_delete(G);

	for (int i = 0; i < N; i++) {
		printf("%d ", result[i]);
	}
}