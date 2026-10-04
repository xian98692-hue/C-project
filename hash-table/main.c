#include"hash-table.h"
#include<stdio.h>
int main() {
	struct hash_table* table = insert_table(1, NULL);
	table = insert_table(12, table);
	printf("%d\n",table->buckets[1]->next->val);
	printf("%d\n", table->buckets[2]->next->val);
	return 0;
}