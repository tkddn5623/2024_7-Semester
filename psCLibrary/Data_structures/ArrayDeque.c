typedef struct {
	@@@@* items;
	int capacity;
	int front;
	int rear;
} Deque_$$$$;

Deque_$$$$* Deque_new_$$$$() {
	Deque_$$$$* pdeque = calloc(1, sizeof(Deque_$$$$)); if (!pdeque) exit(1);
	pdeque->items = calloc(16, sizeof(@@@@)); if (!pdeque->items) exit(1);
	pdeque->capacity = 16;
	return pdeque;
}
void Deque_delete_$$$$(Deque_$$$$* pdeque) {
	free(pdeque->items);
	free(pdeque);
}
int Deque_empty_$$$$(const Deque_$$$$* pdeque) {
	return pdeque->front == pdeque->rear;
}
void Deque_resize_$$$$(Deque_$$$$* pdeque) {
	const int front = pdeque->front, rear = pdeque->rear, capacity = pdeque->capacity;
	if (front - rear == 1 || front - rear == 1 - capacity) {
		pdeque->items = realloc(pdeque->items, (pdeque->capacity = capacity * 2) * sizeof(@@@@)); if (!pdeque->items) exit(1);
		if (front < rear) return;
		else if (rear <= capacity - front) {
			for (int i = 0; i < rear; i++) { pdeque->items[i + capacity] = pdeque->items[i]; }
			pdeque->rear = rear + capacity;
		}
		else {
			for (int i = front; i < capacity; i++) { pdeque->items[i + capacity] = pdeque->items[i]; }
			pdeque->front = front + capacity;
		}
	}
}
void Deque_push_front_$$$$(Deque_$$$$* pdeque, @@@@ item) {
	Deque_resize_$$$$(pdeque);
	const int f_before = (pdeque->front - 1 + pdeque->capacity) & (pdeque->capacity - 1);
	pdeque->front = f_before;
	pdeque->items[f_before] = item;
}
void Deque_push_back_$$$$(Deque_$$$$* pdeque, @@@@ item) {
	Deque_resize_$$$$(pdeque);
	const int rear = pdeque->rear;
	pdeque->rear = (rear + 1) & (pdeque->capacity - 1);
	pdeque->items[rear] = item;
}
@@@@ Deque_pop_front_$$$$(Deque_$$$$* pdeque) {
	const int front = pdeque->front;
	pdeque->front = (front + 1) & (pdeque->capacity - 1);
	return pdeque->items[front];
}
@@@@ Deque_pop_back_$$$$(Deque_$$$$* pdeque) {
	const int r_before = (pdeque->rear - 1 + pdeque->capacity) & (pdeque->capacity - 1);
	pdeque->rear = r_before;
	return pdeque->items[r_before];
}
@@@@ Deque_front_$$$$(const Deque_$$$$* pdeque) {
	return pdeque->items[pdeque->front];
}
@@@@ Deque_back_$$$$(const Deque_$$$$* pdeque) {
	return pdeque->items[(pdeque->rear - 1 + pdeque->capacity) & (pdeque->capacity - 1)];
}
int Deque_size_$$$$(const Deque_$$$$* pdeque) {
	return (pdeque->rear - pdeque->front + pdeque->capacity) & (pdeque->capacity - 1);
}


/*
* 2024-01-08 Mon.
* Improved readability
* Modular operation optimization
*
* 2024.2.11 Sun
* Dynamic resize support (But, unlike stack and heap, it is slow)
*
* 2024.5.8 Wed
* C++ style template imitation
*/