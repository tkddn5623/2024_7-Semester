#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN (200000)
#define POLYCOEF (5381)
#define HASH_MSB_BITS (19)
#define HASH_BLOCK_SIZE (1 << HASH_MSB_BITS)

typedef char* Element;

typedef struct {
    int bucketsize;
    Element* bucket;
} Hashtable;

int tiny_hash_i32(unsigned int k) {
    return (k * 2654435769u) >> (32 - HASH_MSB_BITS);
}
Hashtable* HT_new(int required_bucketsize) {
    Hashtable* ht;
    int bucketsize;
    for (int i = 4; (bucketsize = 1 << i) < required_bucketsize; i++);
    if (!(ht = calloc(1, sizeof(Hashtable)))) exit(1);
    if (!(ht->bucket = calloc(bucketsize, sizeof(Element)))) exit(1);
    ht->bucketsize = bucketsize;
    return ht;
}
void HT_delete(Hashtable* ht) {
    free(ht->bucket);
    free(ht);
}
Element* HT_find(const Hashtable* ht, const Element key, int key_length, int index) {
    for (int sz = ht->bucketsize; ; index = (index + 1) & (sz - 1)) {
        Element key2 = ht->bucket[index];
        if (key2 == NULL) return &ht->bucket[index];
        if (!strncmp(key2, key, key_length)) return NULL;
    }
    return NULL;
}
void HT_flush(Hashtable* ht) {
    for (int j = ht->bucketsize, i = 0; i < j; i++) { ht->bucket[i] = NULL; }
}
void stdin_getline(char* dest) {
    for (*dest = 0, fgets(dest, MAXLEN + 2, stdin); *dest & ~0x1f; dest++); 
    *dest = 0;
}
int solve3033(char text[], const int N) {
    Hashtable* table = HT_new(HASH_BLOCK_SIZE);
    int L = 1, R = N, answer = 0;

    while (L <= R) {
        int length = L + (R - L) / 2;
        unsigned int power = 1, hash = 0;

        for (int i = 0; i < length; i++) {
            hash = (hash * POLYCOEF + text[i]) & (HASH_BLOCK_SIZE - 1);
            power = (power * POLYCOEF) & (HASH_BLOCK_SIZE - 1);
        }

        *HT_find(table, &text[0], length, hash) = &text[0];

        for (int i = 1; i <= N - length; i++) {
            Element* table_search;

            hash = (hash * POLYCOEF + text[i + length - 1] - text[i - 1] * power) & (HASH_BLOCK_SIZE - 1);

            if ((table_search = HT_find(table, &text[i], length, hash))) {
                *table_search = &text[i];
            }
            else {
                answer = length;
                L = length + 1;
                break;
            }
        }

        if (answer < length) R = length - 1;

        HT_flush(table);
    }
    HT_delete(table);
    return answer;
}
int main() {
    int N;
    static char text[MAXLEN + 2];
    scanf("%d ", &N);
    stdin_getline(text);
    printf("%d\n", solve3033(text, N));
}

