#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXLEN (200000)
#define POLY_COEF (5381)
#define HASH_EMPTY (NULL)

struct string_slice {
	const char* ptr;
	int length;
	unsigned int hash;
};

typedef struct {
	struct string_slice key;
	// int value;
} Hashtable_keypair;

typedef struct {
	Hashtable_keypair* bucket;
	int bucketbits;
	int bucketload;
} Hashtable;


// Useful functions
int tiny_hash_slice(const struct string_slice s, int bits) {
	return s.hash & ((1 << bits) - 1);
}
Hashtable* Hashtable_new() {
	Hashtable* ht = calloc(1, sizeof(Hashtable)); if (!ht) exit(1);
	ht->bucket = calloc(16, sizeof(Hashtable_keypair));  if (!ht->bucket) exit(1);
	ht->bucketbits = 4;
	for (int sz = 16, i = 0; i < sz; i++) { ht->bucket[i].key.ptr = HASH_EMPTY; }
	return ht;
}
void Hashtable_delete(Hashtable* ht) {
	free(ht->bucket);
	free(ht);
}
int Hashtable_compare(const struct string_slice A, const struct string_slice B) {
	return strncmp(A.ptr, B.ptr, A.length);
}
int Hashtable_compare_null(const struct string_slice A) {
	return !(A.ptr == HASH_EMPTY);
}
void Hashtable_resize(Hashtable* ht) {
	const int bits2 = ht->bucketbits + 1, sz = 1 << bits2;
	Hashtable_keypair* bucket2 = calloc(sz, sizeof(Hashtable_keypair)); if (!bucket2) exit(1);
	for (int i = 0; i < sz; i++) { bucket2[i].key.ptr = HASH_EMPTY; }
	for (int j = sz / 2, i = 0; i < j; i++) {
		if (!Hashtable_compare_null(ht->bucket[i].key)) continue;
		for (int index = tiny_hash_slice(ht->bucket[i].key, bits2); ; index = (index + 1) & (sz - 1)) {
			if (!Hashtable_compare_null(bucket2[index].key)) { bucket2[index] = ht->bucket[i]; break; }
		}
	}
	free(ht->bucket);
	ht->bucket = bucket2;
	ht->bucketbits = bits2;
}
Hashtable_keypair* Hashtable_find(const Hashtable* ht, struct string_slice key) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_slice(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		struct string_slice key2 = ht->bucket[index].key;
		if (!Hashtable_compare_null(key2) || !Hashtable_compare(key, key2)) return &ht->bucket[index];
	}
	return NULL;
}
int Hashtable_insert_or_change(Hashtable* ht, struct string_slice key) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_slice(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		struct string_slice key2 = ht->bucket[index].key;
		if (!Hashtable_compare_null(key2)) {
			ht->bucket[index] = (Hashtable_keypair){ key };
			if (++ht->bucketload > sz / 2) Hashtable_resize(ht);
			return 0;
		}
		if (!Hashtable_compare(key, key2)) { return 1; }
	}
}
void IO_getline(char* dest, int max) {
	for (*dest = 0, fgets(dest, max, stdin); *dest >= ' '; dest++);; *dest = 0;
}


// Solving functions
int solve3033_attempt(const char str[], const int L, const int K) {
	Hashtable* ht = Hashtable_new();
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