struct string_slice {
	const char* ptr;
	int length;
	unsigned int hash;
};

typedef struct _Hashtable_keypair_$$$$ {
	union { struct { @@@@ key; int value; }; struct _Hashtable_keypair_$$$$* tail; };
	struct _Hashtable_keypair_$$$$* next;
} Hashtable_keypair_$$$$;

typedef struct {
	Hashtable_keypair_$$$$* bucket;
	int bucketbits;
	int edgesize;
	int edgecount;
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
Hashtable_$$$$* Hashtable_new_$$$$(int bucketbits, int edgesize) {
	Hashtable_$$$$* ht = malloc(sizeof(Hashtable_$$$$)); if (!ht) exit(1);
	ht->bucket = calloc(edgesize + (1 << bucketbits), sizeof(Hashtable_keypair_$$$$));  if (!ht->bucket) exit(1);
	ht->bucketbits = bucketbits;
	ht->edgesize = edgesize + (1 << bucketbits);
	ht->edgecount = 1 << bucketbits;
	for (int sz = 1 << bucketbits, i = 0; i < sz; i++) {
		ht->bucket[i].tail = &ht->bucket[i];
		ht->bucket[i].next = &ht->bucket[i];
	}
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
Hashtable_keypair_$$$$* Hashtable_find_$$$$(const Hashtable_$$$$* ht, @@@@ key) {
	int index = tiny_hash_%%%%(key, ht->bucketbits);
	for (Hashtable_keypair_$$$$* head = &ht->bucket[index], *cur = head->next; cur != head; cur = cur->next) {
		if (!Hashtable_compare_$$$$(cur->key, key)) return cur;
	}
	return NULL;
}
int Hashtable_insert_or_change_$$$$(Hashtable_$$$$* ht, @@@@ key, int value) {
	int index = tiny_hash_%%%%(key, ht->bucketbits);
	for (Hashtable_keypair_$$$$* head = &ht->bucket[index], *cur = head->next; cur != head; cur = cur->next) {
		if (!Hashtable_compare_$$$$(cur->key, key)) {
			cur->value += value;
			return 1;
		}
	}
	ht->bucket[ht->edgecount] = (Hashtable_keypair_$$$$){ .key = key, .value = value, .next = &ht->bucket[index] };
	ht->bucket[index].tail->next = &ht->bucket[ht->edgecount];
	ht->bucket[index].tail = &ht->bucket[ht->edgecount++];
	return 0;
}


/*
* 2024.8.10 Sat
* Separate chaining reborn.
*
* 2024.8.12 Mon
* Separated into version 1 for the large size key
* and version 2 for the 4-byte key
*/