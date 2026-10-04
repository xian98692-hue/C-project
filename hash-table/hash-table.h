typedef unsigned int elementtype;
struct Node {
	struct Node* next;
	elementtype val;
};

struct hash_table {
	struct Node** buckets;
	int tablesize;
};
int hash(elementtype val);
struct hash_table* insert_table(elementtype val, struct hash_table* table);
