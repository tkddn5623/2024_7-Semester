#define HASH_EMPTY_$$$$ (1 << 31)

struct string_slice {
	const char* ptr;
	int length;
	unsigned int hash;
};

typedef struct {
	@@@@ key;
	int value;
} Hashtable_keypair_$$$$;

typedef struct {
	Hashtable_keypair_$$$$* bucket;
	int bucketbits;
	int bucketload;
} Hashtable_$$$$;

int tiny_hash_slice(const struct string_slice s, int bits) { // For Rabin-Karp
	return s.hash & ((1 << bits) - 1);
}
int tiny_hash_str(const char str[], int bits) {
	unsigned int h = 0;
	char ch;
	while ((ch = *str++)) { h = h * 5381u + ch; }
	return h & ((1 << bits) - 1);
}
int tiny_hash_i64(unsigned long long k, int bits) {
	return (k * 12345678912345678921LLu) >> (64 - bits);
}
int tiny_hash_i32(unsigned int k, int bits) {
	return (k * 1234567891u) >> (32 - bits);
}
Hashtable_$$$$* Hashtable_new_$$$$() {
	Hashtable_$$$$* ht = calloc(1, sizeof(Hashtable_$$$$)); if (!ht) exit(1);
	ht->bucket = calloc(16, sizeof(Hashtable_keypair_$$$$));  if (!ht->bucket) exit(1);
	ht->bucketbits = 4;
	for (int sz = 16, i = 0; i < sz; i++) { ht->bucket[i].key = HASH_EMPTY_$$$$; }
	return ht;
}
void Hashtable_delete_$$$$(Hashtable_$$$$* ht) {
	free(ht->bucket);
	free(ht);
}
int Hashtable_compare_$$$$(const @@@@ A, const @@@@ B) {
	return A - B;
	// return strncmp(A.ptr, B.ptr, A.length);
}
int Hashtable_compare_null_$$$$(const @@@@ A) {
	return A - HASH_EMPTY_$$$$;
}
void Hashtable_resize_$$$$(Hashtable_$$$$* ht) {
	const int bits2 = ht->bucketbits + 1, sz = 1 << bits2;
	Hashtable_keypair_$$$$* bucket2 = calloc(sz, sizeof(Hashtable_keypair_$$$$)); if (!bucket2) exit(1);
	for (int i = 0; i < sz; i++) { bucket2[i].key = HASH_EMPTY_$$$$; }
	for (int j = sz / 2, i = 0; i < j; i++) {
		if (!Hashtable_compare_null_$$$$(ht->bucket[i].key)) continue;
		for (int index = tiny_hash_%%%%(ht->bucket[i].key, bits2); ; index = (index + 1) & (sz - 1)) {
			if (!Hashtable_compare_null_$$$$(bucket2[index].key)) { bucket2[index] = ht->bucket[i]; break; }
		}
	}
	free(ht->bucket);
	ht->bucket = bucket2;
	ht->bucketbits = bits2;
}
Hashtable_keypair_$$$$* Hashtable_find_$$$$(const Hashtable_$$$$* ht, @@@@ key) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_%%%%(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		@@@@ key2 = ht->bucket[index].key;
		if (!Hashtable_compare_null_$$$$(key2) || !Hashtable_compare_$$$$(key, key2)) return &ht->bucket[index];
	}
	return NULL;
}
int Hashtable_insert_or_change_$$$$(Hashtable_$$$$* ht, @@@@ key, int value) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_%%%%(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		@@@@ key2 = ht->bucket[index].key;
		if (!Hashtable_compare_null_$$$$(key2)) {
			ht->bucket[index] = (Hashtable_keypair_$$$$){ key,value };
			if (++ht->bucketload > sz / 2) Hashtable_resize_$$$$(ht);
			return 0;
		}
		if (!Hashtable_compare_$$$$(key, key2)) { ht->bucket[index].value += value; return 1; }
	}
}


/*
* Above: When there is unused key (save memory)
* Below: When there is no unused key (need 1 ~ 4 bytes)
*/


typedef struct {
	@@@@ key;
	int value;
	int valid;
} Hashtable_keypair_$$$$;

typedef struct {
	Hashtable_keypair_$$$$* bucket;
	int bucketbits;
	int bucketload;
} Hashtable_$$$$;

int tiny_hash_%%%%(const char str[], int bits) {
	unsigned int h = 0;
	char ch;
	while ((ch = *str++)) { h = h * 9181u + ch; }
	return h & ((1 << bits) - 1);
}
int tiny_hash_i64(unsigned long long k, int bits) {
	return (k * 12345678912345678921llu) >> (64 - bits);
}
int tiny_hash_i32(unsigned int k, int bits) {
	return (k * 1234567891u) >> (32 - bits);
}
Hashtable_$$$$* Hashtable_new_$$$$() {
	Hashtable_$$$$* ht = calloc(1, sizeof(Hashtable_$$$$)); if (!ht) exit(1);
	ht->bucket = calloc(16, sizeof(Hashtable_keypair_$$$$));  if (!ht->bucket) exit(1);
	ht->bucketbits = 4;
	return ht;
}
void Hashtable_delete_$$$$(Hashtable_$$$$* ht) {
	free(ht->bucket);
	free(ht);
}
int Hashtable_compare_$$$$(const @@@@ A, const @@@@ B) {
	return A - B;
	/*while (*A && *A == *B) A++, B++;
	return *A - *B;*/
}
void Hashtable_resize_$$$$(Hashtable_$$$$* ht) {
	const int bits2 = ht->bucketbits + 1, sz = 1 << bits2;
	Hashtable_keypair_$$$$* bucket2 = calloc(sz, sizeof(Hashtable_keypair_$$$$)); if (!bucket2) exit(1);
	for (int j = sz / 2, i = 0; i < j; i++) {
		if (!ht->bucket[i].valid) continue;
		for (int index = tiny_hash_%%%%(ht->bucket[i].key, bits2); ; index = (index + 1) & (sz - 1)) {
			if (!bucket2[index].valid) { bucket2[index] = ht->bucket[i]; break; }
		}
	}
	free(ht->bucket);
	ht->bucket = bucket2;
	ht->bucketbits = bits2;
}
Hashtable_keypair_$$$$* Hashtable_find_$$$$(const Hashtable_$$$$* ht, @@@@ key) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_%%%%(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		@@@@ key2 = ht->bucket[index].key;
		if (!ht->bucket[index].valid || !Hashtable_compare_$$$$(key, key2)) return &ht->bucket[index];
	}
	return NULL;
}
int Hashtable_insert_or_change_$$$$(Hashtable_$$$$* ht, @@@@ key, int value) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_%%%%(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		@@@@ key2 = ht->bucket[index].key;
		if (!ht->bucket[index].valid) {
			ht->bucket[index] = (Hashtable_keypair_$$$$){ key,value,1 };
			if (++ht->bucketload > sz / 2) Hashtable_resize_$$$$(ht);
			return 0;
		}
		if (!Hashtable_compare_$$$$(key, key2)) { ht->bucket[index].value += value; return 1; }
	}
}


/*
* 2024-01-16 Tue
*
* The performance of linear probing is better than I think.
* Especially when I consider cache hits ratio.
*
* 2024-01-26 Fri
* Simple string hash func added.
*
* 2024.2.12 Mon
* Resizeable hash table supported.
*
* 2024.2.20 Tue
* Added support for cases where there is no unused key.
*
* 2024.5.8 Wed
* C++ style template added.
*
* 2024.8.8 Thu
* Now It is ready for the case where a struct comes.
*/