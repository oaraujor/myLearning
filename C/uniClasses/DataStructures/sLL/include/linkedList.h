#ifndef sLL
#define sLL

#define ERROR_MSG printf("Error with malloc\n");

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	int value;
	struct node *next;
} NODE_LL;

void apndBegOfList(NODE_LL**, int*);
void apndEndOfList(NODE_LL**, int*);
void apndMidOfList(NODE_LL **);
int rmBegNodeOfList(NODE_LL **);
int rmEndNodeOfList(NODE_LL **);
int rmMidNodeOfList(NODE_LL **);
void printList(NODE_LL** );
void killList(NODE_LL **);


void apndBegOfList(NODE_LL** list, int *value) {
	/*
		Desc: Function to append a value to the linked list.
		Visual: [Inserts here]->[]->[]->NULL
	
		args:
			NODE_LL** list : address to the head of the list
			int* value : address of the int variable to be stored
	*/
	NODE_LL* newNode;

	newNode = malloc(sizeof(NODE_LL));
	if(newNode != NULL) {
		newNode->value = *value;
		newNode->next = NULL;
		newNode->next = *list;
		*list = newNode;
	}
	else {
		ERROR_MSG
	}
}

void apndEndOfList(NODE_LL **list , int * value)
{
	/*
	Desc: Function to append a value to the linked list.
	Visual: []->[]->[Inserts Here]->NULL

	args:
		NODE_LL **list : address to the head of the list
		int *value : address of the int variable to be stored
	*/

	NODE_LL *newNODE, *prevNODE, *currNODE;

	newNODE = malloc(sizeof(NODE_LL));
	if(newNODE != NULL) {
		newNODE->value = *value;
		newNODE->next = NULL;
		prevNODE = NULL;
		currNODE = *list;
		while(currNODE != NULL) {
			prevNODE = currNODE;
			currNODE = currNODE->next;
		}
		if (prevNODE == NULL) {
			*list = newNODE;
		}
		else {
			prevNODE->next = newNODE;
		}
	}
	else {
		ERROR_MSG
	}

}

/*
void insertMiddle(NODE_LL **list, int *value, size_t *pos){
	*
		Desc: Function to isert a value somewhere in the middle of the linked list.
		Visual: [0]->[1]->[Inserts Here]->[2]->[]->[]->NULL
		
		args:
			NODE_LL **list : address to the head of the list
			int *value - address of the int variable to be stored
			size_t *pos - position in the linked list to be inserted in
		return: Nothing to be returned
	*
	size_t count = 0;
	NODE_LL *newNode, *current, *prev; 
	newNode = malloc(sizeof(NODE_LL));
	if(newNode != NULL) {
		newNode->value = *value;
		newNode->next = NULL;
		current = *list;
		while(current != NULL && count < *pos) {
			if(count == *pos){
				
			}
			else{
				current = current->next;
			}
		}
		if(current = NULL) { // if list is empty, the new node is the first element
			*list = newNode;
		}
	}
	else{
		ERROR_MSG
	}

	return;
}
*/

int rmBegNodeOfList(NODE_LL **list) {
	/*
		Desc: Function to remove the first element of the list
		Visual: [Removes This]->[]->[]->NULL
		args:
			NODE_LL *list : address to the head of the list
		return: 1 if successful | 0 if the list was empty
	*/
	return 0;
}

int rmEndNodeOfList(NODE_LL **list) {
	/*
		Desc: Function to remove the last element of the list
		Visual: []->[]->[Removes This]->NULL
		args:
			NODE_LL *list : address to the head of the list
		return: 1 if successful | 0 if the list was empty
	*/

	NODE_LL *prev, *curr, *temp;
	prev = NULL;
	curr = *list;

	if (curr->next != NULL) {
		while(curr ->next != NULL) {
			prev = curr;
			curr = curr->next;
		}
		temp = curr;
		prev->next = NULL;
		free(temp);
		return 1;
	}
	return 0;
}

int rmMidNodeOfList(NODE_LL **list) {
	/*
		Desc: Function to remove some element in the middle of the list
		Visual: []->[Removes Some]->[]->[]->NULL
		args:
			NODE_LL *list : address to the head of the list
		return: 1 if successful | 0 if the list was empty
	*/
	return 0;
}

void printList(NODE_LL** list) {
	/*
		Desc: Prints the Linked List onto stdin.
		Visual: []->[]->[]->NULL
		
		args:
			NODE **list : address to the head of the list
		return: Nothing to return
	*/

	NODE_LL *curr;
	
	curr = *list;

	while(curr != NULL) {
		printf("[%d]-->", curr->value);
		curr = curr->next;
	}
	printf("NULL\n");
}

void killList(NODE_LL **list) {
	/*
		Desc: Kills (Eliminates) all nodes from the Linked List.
		args: NODE **list - address to the head of the list
		returns: Nothing
	*/
	NODE_LL *curr = NULL, *temp = NULL;
	curr = *list;

	while(curr != NULL) {
		temp = curr->next;
		free(curr);
		curr = temp;
	}

}

#endif
