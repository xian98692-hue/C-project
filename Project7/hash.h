#include"stdint.h"
uint32_t hash_string(const char* s);

uint32_t hash_fnv1a(const void* data, size_t len);

typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

typedef struct HashTable {
    int size;         // 桶的数量
    int count;        // 当前元素个数
    Node** buckets;   // 桶数组（指针数组）
} HashTable;

HashTable* create_hashtable(int size);

void insert(HashTable* table, const char* key, int value);