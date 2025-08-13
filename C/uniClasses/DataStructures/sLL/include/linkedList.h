#ifndef sLL
#define sLL
#include <stdio.h>

typedef struct LLNode {
	int value;
	struct LLNode *next;
} LLNode;

void initList(LLNode* );
void updateValueNode(LLNode* );

void initList(LLNode* node) { //init the first node of the linkedList
	node->next = NULL;
}

void updateValueNode(LLNode* node) { //simple function to update node value
	int valueIn;
	printf("insert int value to store in node\n");
	scanf("%d", &valueIn);
	node->value = valueIn;
}


#endif
