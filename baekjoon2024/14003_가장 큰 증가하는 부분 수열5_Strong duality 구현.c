#include <stdio.h>
#include <stdlib.h>

#define MAXN (1000000)

struct pair {
	int value;
	int prev_stack_length;
};

typedef struct {
	struct pair* items;
	int top;
	int capacity;
} Stack_pair;

Stack_pair* Stack_new_pair() {
	Stack_pair* pstack = malloc(sizeof(Stack_pair)); if (!pstack) exit(1);
	pstack->items = calloc(4, sizeof(struct pair)); if (!pstack->items) exit(1);
	pstack->top = -1;
	pstack->capacity = 4;
	return pstack;
}
void Stack_delete_pair(Stack_pair* pstack) {
	free(pstack->items);
	free(pstack);
}
int Stack_empty_pair(const Stack_pair* pstack) {
	return pstack->top == -1;
}
void Stack_push_pair(Stack_pair* pstack, struct pair item) {
	if (pstack->top == pstack->capacity - 1
		&& !(pstack->items = realloc(pstack->items, (pstack->capacity *= 2) * sizeof(struct pair))))
		exit(1);
	pstack->items[++pstack->top] = item;
}
struct pair Stack_pop_pair(Stack_pair* pstack) {
	return pstack->items[pstack->top--];
}
struct pair Stack_top_pair(const Stack_pair* pstack) {
	return pstack->items[pstack->top];
}
int Stack_size_pair(const Stack_pair* pstack) {
	return pstack->top + 1;
}
int Binary_equal_or_greater(const int arr[], int left, int right, int key) {
	int pos = -1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] >= key) {
			pos = mid;
			right = mid - 1;
		}
		else left = mid + 1;
	}
	return pos;
}
int Binary_greatest_less(const int arr[], int left, int right, int key) {
	int pos = -1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (arr[mid] >= key) right = mid - 1;
		else {
			pos = mid;
			left = mid + 1;
		}
	}
	return pos;
}
void solve12015(int arr[], int N) {
	static Stack_pair* stack[MAXN] = { 0 };
	static int memo[MAXN] = { 0 };
	int memo_len = 0;
	static int answer[MAXN] = { 0 };

	memo[memo_len++] = arr[0];
	stack[0] = Stack_new_pair();
	Stack_push_pair(stack[0], (struct pair) { arr[0], 0 });

	for (int i = 1; i < N; i++) {
		int pos = -1;

		if (memo[memo_len - 1] >= arr[i])
			pos = Binary_equal_or_greater(memo, 0, memo_len - 1, arr[i]);
		else {
			pos = memo_len++;
			stack[pos] = Stack_new_pair();
		}

		memo[pos] = arr[i];

		if (pos - 1 >= 0)
			Stack_push_pair(stack[pos], (struct pair) { arr[i], Stack_size_pair(stack[pos - 1]) });
		else
			Stack_push_pair(stack[pos], (struct pair) { arr[i] });
	}

#ifndef ONLINE_JUDGE
	// Debug information
	printf("/// Debug ///\n");
	for (int i = 0; i < memo_len; i++) {
		printf("%d th stack: ", i);
		for (int j = Stack_size_pair(stack[i]) - 1; j >= 0; j--) {
			printf("[%d:%d] ", stack[i]->items[j].value, stack[i]->items[j].prev_stack_length);
		}
		printf("\n");
	}
	printf("/// Debug done ///\n");
#endif

	printf("%d\n", memo_len);

	for (int j = Stack_size_pair(stack[memo_len - 1]), i = memo_len - 1; i >= 0; i--) {
		answer[i] = stack[i]->items[j - 1].value;
		j = stack[i]->items[j - 1].prev_stack_length;
	}

	for (int i = 0; i < memo_len; i++) {
		printf("%d ", answer[i]);
	}

	printf("\n");

	for (int i = 0; i < memo_len; i++) {
		Stack_delete_pair(stack[i]);
	}
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	static int arr[MAXN];
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	solve12015(arr, N);
}