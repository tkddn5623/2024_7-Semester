/*
* Depending on the total memory usage, the time changes to 160ms, 100ms, and 88ms.
* 2^19, 2^18, 200000
* If I optimize for O3, it's 76ms
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXLEN (200000)
#define POLY_COEF (5381)

struct string_slice {
	const char* ptr;
	int length;
	unsigned int hash;
};

typedef struct _Hashtable_keypair {
	union { struct string_slice key; struct _Hashtable_keypair* tail; };
	struct _Hashtable_keypair* next;
} Hashtable_keypair;

typedef struct {
	Hashtable_keypair* bucket;
	int bucketbits;
	int edgesize;
	int edgecount;
} Hashtable;


// Useful functions
int tiny_hash_slice(const struct string_slice s, int bits) {
	return s.hash & ((1 << bits) - 1);
}
Hashtable* Hashtable_new(int bucketbits, int edgesize) {
	Hashtable* ht = malloc(sizeof(Hashtable)); if (!ht) exit(1);
	ht->bucket = calloc(edgesize + (1 << bucketbits), sizeof(Hashtable_keypair));  if (!ht->bucket) exit(1);
	ht->bucketbits = bucketbits;
	ht->edgesize = edgesize + (1 << bucketbits);
	ht->edgecount = 1 << bucketbits;
	for (int sz = 1 << bucketbits, i = 0; i < sz; i++) {
		ht->bucket[i].tail = &ht->bucket[i];
		ht->bucket[i].next = &ht->bucket[i];
	}
	return ht;
}
void Hashtable_delete(Hashtable* ht) {
	free(ht->bucket);
	free(ht);
}
int Hashtable_compare(const struct string_slice A, const struct string_slice B) {
	return strncmp(A.ptr, B.ptr, A.length);
}
Hashtable_keypair* Hashtable_find(const Hashtable* ht, struct string_slice key) {
	int index = tiny_hash_slice(key, ht->bucketbits);
	for (Hashtable_keypair* head = &ht->bucket[index], *cur = head->next; cur != head; cur = cur->next) {
		if (!Hashtable_compare(cur->key, key)) return cur;
	}
	return NULL;
}
int Hashtable_insert_or_change(Hashtable* ht, struct string_slice key) {
	int index = tiny_hash_slice(key, ht->bucketbits);
	for (Hashtable_keypair* head = &ht->bucket[index], *cur = head->next; cur != head; cur = cur->next) {
		if (!Hashtable_compare(cur->key, key)) return 1;
	}
	ht->bucket[ht->edgecount] = (Hashtable_keypair){ .key = key, .next = &ht->bucket[index] };
	ht->bucket[index].tail->next = &ht->bucket[ht->edgecount];
	ht->bucket[index].tail = &ht->bucket[ht->edgecount++];
	return 0;
}
void IO_getline(char* dest, int max) {
	for (*dest = 0, fgets(dest, max, stdin); *dest >= ' '; dest++);; *dest = 0;
}


// Solving functions
int solve3033_attempt(const char str[], const int L, const int K) {
	Hashtable* ht = Hashtable_new(18, 200000);
	unsigned int power = 1, hash = 0;
	int exist = 0;

	for (int i = 0; i < K; i++) {
		hash = hash * POLY_COEF + str[i];
		power = power * POLY_COEF;
	}

	Hashtable_insert_or_change(ht, (struct string_slice) { &str[0], K, hash });

	for (int i = 1; i <= L - K; i++) {
		hash = ((hash * POLY_COEF) + (1 * str[i + K - 1]) - (power * str[i - 1]));

		if (Hashtable_insert_or_change(ht, (struct string_slice) { &str[i], K, hash })) {
			exist = 1;
			break;
		}
	}

	Hashtable_delete(ht);
	return exist;
}
void solve3033(const char str[], const int L) {
	int left = 1, right = L, answer = 0;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (solve3033_attempt(str, L, mid)) {
			answer = mid;
			left = mid + 1;
		}
		else right = mid - 1;
	}

	printf("%d\n", answer);
}
int main() {
#ifndef ONLINE_JUDGE
	freopen("i.txt", "r", stdin);
#endif
	static char str[MAXLEN + 2];
	int L;
	scanf("%d ", &L);
	IO_getline(str, sizeof(str));
	solve3033(str, L);
}