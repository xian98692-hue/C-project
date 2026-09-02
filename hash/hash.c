#include"hash.h"//哈希函数可以得到一个尽可能独特的值
uint32_t hash_string(const char* s) {
    uint32_t  hash = 0;
    if (!s) return 0;
    while (*s) {
        hash = hash * 31 + (uint8_t)(*s++);
    }
    return hash;
}


uint32_t hash_fnv1a(const void* data, size_t len) {
    uint32_t hash = 2166136261u;
    const uint8_t* bytes = (const uint8_t*)data;
    for (size_t i = 0; i < len; i++) {
        hash ^= bytes[i];
        hash *= 16777619u;
    };
    return hash;
}

HashTable* create_hashtable(int size) {
    HashTable* t = malloc(sizeof(HashTable));
    t->size = size;
    t->count = 0;
    t->buckets = calloc(size, sizeof(Node*));
    return t;
}

void insert(HashTable* table, const char* key, int value) {

    unsigned int idx = hash_fnv1a(key, table->size);
    Node* cur = table->buckets[idx];

    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            cur->value = value;   // 更新已有值
            return;
        }
        cur = cur->next;
    }

    // 新建节点并插入链表头部
    Node* node = malloc(sizeof(Node));
    node->key = strdup(key);      // 深拷贝键
    node->value = value;
    node->next = table->buckets[idx];
    table->buckets[idx] = node;
    table->count++;
}