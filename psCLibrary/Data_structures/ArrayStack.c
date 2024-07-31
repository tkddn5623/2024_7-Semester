typedef struct {
	@@@@* items;
	int top;
	int capacity;
} Stack_$$$$;

Stack_$$$$* Stack_new_$$$$() {
	Stack_$$$$* pstack = malloc(sizeof(Stack_$$$$)); if (!pstack) exit(1);
	pstack->items = calloc(16, sizeof(@@@@)); if (!pstack->items) exit(1);
	pstack->top = -1;
	pstack->capacity = 16;
	return pstack;
}
void Stack_delete_$$$$(Stack_$$$$* pstack) {
	free(pstack->items);
	free(pstack);
}
int Stack_empty_$$$$(const Stack_$$$$* pstack) {
	return pstack->top == -1;
}
void Stack_push_$$$$(Stack_$$$$* pstack, @@@@ item) {
	if (pstack->top == pstack->capacity - 1 && !(pstack->items = realloc(pstack->items, (pstack->capacity *= 2) * sizeof(@@@@)))) exit(1);
	pstack->items[++pstack->top] = item;
}
@@@@ Stack_pop_$$$$(Stack_$$$$* pstack) {
	return pstack->items[pstack->top--];
}
@@@@ Stack_top_$$$$(const Stack_$$$$* pstack) {
	return pstack->items[pstack->top];
}


/*
* 2024.1.20.
* Function names imitates C++ STL methods.
*
* 2024.2.10.
* Now, the stack supports automatic resize.
*
* 2024.3.13.
* fix typo.
*
* 2024.5.8.
* Remake like C++ style
*/