#include<stdlib.h>
#include<stdio.h>
#include"hash-table.h"
int hash(elementtype val) {
	return val % 10;
};
struct hash_table* insert_table(elementtype val, struct hash_table* table) {
	if (table == NULL) {
		printf("the table is NULL.create new table.\n");
		int idx = hash(val);
		struct hash_table* new_table=(struct hash_table*)malloc(sizeof(struct hash_table));//1 malloc
		if (new_table == NULL) {
			printf("the table malloc return NULL.no result!\n");
			return NULL;
		}
		new_table->tablesize = 10;
		new_table->buckets = (struct Node**)malloc(sizeof(struct Node*) * (new_table->tablesize));//2 malloc
		if (new_table->buckets == NULL) {
			free(new_table);
			printf("the buckets malloc return NULL.no result!\n");
			return NULL;
		}

		for (int i = 0; i < new_table->tablesize; i++) {
			new_table->buckets[i] = (struct Node*)malloc(sizeof(struct Node));//3 malloc
			if (new_table->buckets[i] == NULL) {
				for (int j = 0; j < i; j++) {
					free(new_table->buckets[j]);
				}
				free(new_table->buckets);
				free(new_table);
				return NULL;
				printf("the buckets[i] malloc return NULL.\n");
				return NULL;
			}
			new_table->buckets[i]->val = -999;
			new_table->buckets[i]->next = NULL;
		}
		struct Node* temp = (struct Node*)malloc(sizeof(struct Node));//4 malloc
		if (temp == NULL) {
			for (int k = 0; k < new_table->tablesize; k++) {
				free(new_table->buckets[k]);
			}
			free(new_table->buckets);
			free(new_table);
			printf("the temp malloc NULL.\n");
			return NULL;
		}
		temp->val = val;
		temp->next = NULL;
		new_table->buckets[idx]->next = temp;
		return new_table;
	}
	int idx = hash(val);
	struct Node* node = table->buckets[idx];
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	if (temp == NULL) {
		printf("the temp malloc NULL.\n");
		return NULL;
	}
	temp->val = val;
	temp->next = node->next;
	node->next = temp;
	return table;
}