typedef struct {
	int value;
	int priority;
} HNode;

typedef struct {
	HNode* items;
	int size;
	int capacity;
} Heap;

Heap* Heap_new() {
	Heap* pheap = calloc(1, sizeof(Heap)); if (!pheap) exit(1);
	pheap->items = calloc(16, sizeof(HNode)); if (!pheap->items) exit(1);
	pheap->capacity = 16;
	return pheap;
}
void Heap_delete(Heap* pheap) {
	free(pheap->items);
	free(pheap);
}
int Heap_empty(const Heap* pheap) {
	return pheap->size == 0;
}
int Heap_compare(const HNode _A, const HNode _B) {
	return _A.priority - _B.priority;
}
void Heap_push(Heap* pheap, HNode item) {
	if (pheap->size == pheap->capacity - 1) {
		pheap->items = realloc(pheap->items, (pheap->capacity *= 2) * sizeof(HNode)); if (!pheap->items) exit(1);
	}
	int parent, child = pheap->size + 1;
	while (child > 1) {
		if (Heap_compare(pheap->items[(parent = child / 2)], item) <= 0) break;
		pheap->items[child] = pheap->items[parent];
		child = parent;
	}
	pheap->items[child] = item;
	pheap->size++;
}
HNode Heap_pop(Heap* pheap) {
	const int size = pheap->size;
	const HNode top = pheap->items[1];
	const HNode last = pheap->items[size];
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

// Above: Graph traversal version
// Below: Template version

typedef struct {
	int value;
	int priority;
} $$$$;

typedef struct {
	$$$$* items;
	int size;
	int capacity;
} Heap_$$$$;

Heap_$$$$* Heap_new_$$$$(int max) {
	Heap_$$$$* pheap = calloc(1, sizeof(Heap_$$$$)); if (!pheap) exit(1);
	pheap->items = calloc(max + 1, sizeof($$$$)); if (!pheap->items) exit(1);
	pheap->capacity = max + 1;
	return pheap;
}
void Heap_delete_$$$$(Heap_$$$$* pheap) {
	free(pheap->items);
	free(pheap);
}
int Heap_empty_$$$$(const Heap_$$$$* pheap) {
	return pheap->size == 0;
}
int Heap_compare_$$$$(const $$$$ _A, const $$$$ _B) {
	return _A.priority - _B.priority;
}
void Heap_push_$$$$(Heap_$$$$* pheap, $$$$ item) {
	if (pheap->size == pheap->capacity - 1) {
		pheap->items = realloc(pheap->items, (pheap->capacity *= 2) * sizeof($$$$)); if (!pheap->items) exit(1);
	}
	int parent, child = pheap->size + 1;
	while (child > 1) {
		if (Heap_compare_$$$$(pheap->items[(parent = child / 2)], item) <= 0) break;
		pheap->items[child] = pheap->items[parent];
		child = parent;
	}
	pheap->items[child] = item;
	pheap->size++;
}
$$$$ Heap_pop_$$$$(Heap_$$$$* pheap) {
	const int size = pheap->size;
	const $$$$ top = pheap->items[1];
	const $$$$ last = pheap->items[size];
	int child, parent = 1;
	while ((child = parent * 2) <= size) {
		if (child < size && Heap_compare_$$$$(pheap->items[child + 1], pheap->items[child]) < 0) child++;
		if (Heap_compare_$$$$(last, pheap->items[child]) <= 0) break;
		pheap->items[parent] = pheap->items[child];
		parent = child;
	}
	pheap->items[parent] = last;
	pheap->size--;
	return top;
}


/*
* 2024-01-04: Modify to cleaner code
* 2024.02.02: Unnecessary variables deleted
* 2024.02.10: Automatic resize support
* 2024.02.26: Compare function is added (I envy generic programming languages) 
* 2024.05.08: Template version added
*/