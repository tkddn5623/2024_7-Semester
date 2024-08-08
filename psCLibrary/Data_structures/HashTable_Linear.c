#define HASH_EMPTY (1 << 31)

typedef struct {
	@@@@ key;
	int value;
} Keypair_$$$$;

typedef struct {
	Keypair_$$$$* bucket;
	int bucketbits;
	int bucketload;
} Hashtable_$$$$;

int tiny_hash_str(const char str[], int bits) {
	unsigned int h = 0;
	char ch;
	while ((ch = *str++)) { h = h * 9181u + ch; }
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
	ht->bucket = calloc(16, sizeof(Keypair_$$$$));  if (!ht->bucket) exit(1);
	ht->bucketbits = 4;
	for (int sz = 16, i = 0; i < sz; i++) { ht->bucket[i].key = HASH_EMPTY; }
	return ht;
}
void Hashtable_delete_$$$$(Hashtable_$$$$* ht) {
	free(ht->bucket);
	free(ht);
}
int Hashtable_compare_$$$$(const @@@@ _A, const @@@@ _B) {
	return _A - _B;
	/*while (*_A && *_A == *_B) _A++, _B++;
	return *_A - *_B;*/
}
void Hashtable_resize_$$$$(Hashtable_$$$$* ht) {
	const int bits2 = ht->bucketbits + 1, sz = 1 << bits2;
	Keypair_$$$$* bucket2 = calloc(sz, sizeof(Keypair_$$$$)); if (!bucket2) exit(1);
	for (int i = 0; i < sz; i++) { bucket2[i].key = HASH_EMPTY; }
	for (int j = sz / 2, i = 0; i < j; i++) {
		if (ht->bucket[i].key == HASH_EMPTY) continue;
		for (int index = tiny_hash_str(ht->bucket[i].key, bits2); ; index = (index + 1) & (sz - 1)) {
			if (bucket2[index].key == HASH_EMPTY) { bucket2[index] = ht->bucket[i]; break; }
		}
	}
	free(ht->bucket);
	ht->bucket = bucket2;
	ht->bucketbits = bits2;
}
Keypair_$$$$* Hashtable_find_$$$$(const Hashtable_$$$$* ht, @@@@ key) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_str(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		@@@@ key2 = ht->bucket[index].key;
		if (key2 == HASH_EMPTY || !Hashtable_compare_$$$$(key, key2)) return &ht->bucket[index];
	}
	return NULL;
}
void Hashtable_insert_or_change_$$$$(Hashtable_$$$$* ht, @@@@ key, int value) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_str(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		@@@@ key2 = ht->bucket[index].key;
		if (key2 == HASH_EMPTY) {
			ht->bucket[index] = (Keypair_$$$$){ key,value };
			if (++ht->bucketload > sz / 2) Hashtable_resize_$$$$(ht);
			return;
		}
		if (!Hashtable_compare_$$$$(key, key2)) { ht->bucket[index].value += value; return; }
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
} Keypair_$$$$;

typedef struct {
	Keypair_$$$$* bucket;
	int bucketbits;
	int bucketload;
} Hashtable_$$$$;

int tiny_hash_str(const char str[], int bits) {
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
	ht->bucket = calloc(16, sizeof(Keypair_$$$$));  if (!ht->bucket) exit(1);
	ht->bucketbits = 4;
	return ht;
}
void Hashtable_delete_$$$$(Hashtable_$$$$* ht) {
	free(ht->bucket);
	free(ht);
}
int Hashtable_compare_$$$$(const @@@@ _A, const @@@@ _B) {
	return _A - _B;          // Integer
	//while (*_A && *_A == *_B) _A++, _B++;
	//return *_A - *_B;      // String
}
void Hashtable_resize_$$$$(Hashtable_$$$$* ht) {
	const int bits2 = ht->bucketbits + 1, sz = 1 << bits2;
	Keypair_$$$$* bucket2 = calloc(sz, sizeof(Keypair_$$$$)); if (!bucket2) exit(1);
	for (int j = sz / 2, i = 0; i < j; i++) {
		if (!ht->bucket[i].valid) continue;
		for (int index = tiny_hash_str(ht->bucket[i].key, bits2); ; index = (index + 1) & (sz - 1)) {
			if (!bucket2[index].valid) { bucket2[index] = ht->bucket[i]; break; }
		}
	}
	free(ht->bucket);
	ht->bucket = bucket2;
	ht->bucketbits = bits2;
}
Keypair_$$$$* Hashtable_find_$$$$(const Hashtable_$$$$* ht, @@@@ key) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_str(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		@@@@ key2 = ht->bucket[index].key;
		if (!ht->bucket[index].valid || !Hashtable_compare_$$$$(key, key2)) return &ht->bucket[index];
	}
	return NULL;
}
void Hashtable_insert_or_change_$$$$(Hashtable_$$$$* ht, @@@@ key, int value) {
	for (int sz = 1 << ht->bucketbits, index = tiny_hash_str(key, ht->bucketbits); ; index = (index + 1) & (sz - 1)) {
		@@@@ key2 = ht->bucket[index].key;
		if (!ht->bucket[index].valid) {
			ht->bucket[index] = (Keypair_$$$$){ key,value,1 };
			if (++ht->bucketload > sz / 2) Hashtable_resize_$$$$(ht);
			return;
		}
		if (!Hashtable_compare_$$$$(key, key2)) { ht->bucket[index].value += value; return; }
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
*/