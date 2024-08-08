typedef struct {
	@@@@* items;
	int capacity;
	int front;
	int rear;
} Queue_$$$$;

Queue_$$$$* Queue_new_$$$$() {
	Queue_$$$$* pqueue = calloc(1, sizeof(Queue_$$$$)); if (!pqueue) exit(1);
	pqueue->items = calloc(16, sizeof(@@@@)); if (!pqueue->items) exit(1);
	pqueue->capacity = 16;
	return pqueue;
}
void Queue_delete_$$$$(Queue_$$$$* pqueue) {
	free(pqueue->items);
	free(pqueue);
}
int Queue_empty_$$$$(const Queue_$$$$* pqueue) {
	return pqueue->front == pqueue->rear;
}
void Queue_resize_$$$$(Queue_$$$$* pqueue) {
	const int front = pqueue->front, rear = pqueue->rear, capacity = pqueue->capacity;
	if (front - rear == 1 || front - rear == 1 - capacity) {
		pqueue->items = realloc(pqueue->items, (pqueue->capacity = capacity * 2) * sizeof(@@@@)); if (!pqueue->items) exit(1);
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
void Queue_push_$$$$(Queue_$$$$* pqueue, @@@@ item) {
	Queue_resize_$$$$(pqueue);
	const int rear = pqueue->rear;
	pqueue->rear = (rear + 1) & (pqueue->capacity - 1);
	pqueue->items[rear] = item;
}
@@@@ Queue_pop_$$$$(Queue_$$$$* pqueue) {
	const int front = pqueue->front;
	pqueue->front = (front + 1) & (pqueue->capacity - 1);
	return pqueue->items[front];
}
@@@@ Queue_front_$$$$(const Queue_$$$$* pqueue) {
	return pqueue->items[pqueue->front];
}
int Queue_size_$$$$(const Queue_$$$$* pqueue) {
	return (pqueue->rear - pqueue->front + pqueue->capacity) & (pqueue->capacity - 1);
}


/*
* 2024.01.04 Thu
* The optimized Queue:
* By replacing the % operation with bitwise &,
* performance is very close to linear queue.
*
* 2024.01.08 Mon
* Camel cases changed to snake cases
*
* 2024.1.22 Mon
* AQ_front moved below.
*
* 2024.2.11 Sun
* Dynamic resize support (But, unlike stack and heap, it is slow)
*
* 2024.05.08
* Remake like C++ STL
*/