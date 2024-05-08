#define MAXCOL (26)

typedef struct _TreeNode {
	int next[MAXCOL];
	int state;
} TNode;

typedef struct {
	TNode* nodes;
	int len;
	int capacity;
} Trie;

Trie* Trie_new() {
	Trie* t = malloc(sizeof(Trie)); if (!t) exit(1);
	t->nodes = calloc(16, sizeof(TNode)); if (!t->nodes) exit(1);
	t->len = 1;
	t->capacity = 16;
	return t;
}
void Trie_delete(Trie* trie) {
	free(trie->nodes);
	free(trie);
}
void Trie_insert(Trie* trie, const char* str) {
	int value, cur, len = trie->len;
	for (cur = 0; (value = *str++ - '0') >= 0; cur = trie->nodes[cur].next[value]) {
		if (trie->nodes[cur].next[value] == 0) {
			if (len == trie->capacity && !(trie->nodes = realloc(trie->nodes, (trie->capacity *= 2) * sizeof(TNode)))) exit(1);
			trie->nodes[len] = (TNode){ 0 };
			trie->nodes[cur].next[value] = len++;
			trie->nodes[cur].state |= 0x2;

		}
	}
	trie->nodes[cur].state |= 0x1;
	trie->len = len;
}

/*
int _Trie_search(TNode* trie_nodes, int cur) {
	if (trie_nodes[cur].state == 0x3) return 0;
	else if (trie_nodes[cur].state == 0x2) {
		for (int i = 0; i < MAXCOL; i++) {
			if (trie_nodes[cur].next[i] && !_Trie_search(trie_nodes, trie_nodes[cur].next[i])) return 0;
		}
	}
	return 1;
}
*/


/*
* 2023.7.19 Wed
* 2024.1.27 Sat
* pointer array changed to int array (as real DFA)
*
* 2024.2.13 Tue
* Resizable trie
*
* 2024.5.9 Thu
* Non-resizable mode has been removed.
*/