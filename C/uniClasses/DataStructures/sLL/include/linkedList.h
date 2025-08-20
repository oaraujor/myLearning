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
void printList(NODE_LL** );
void killList(NODE_LL **);


void apndBegOfList(NODE_LL** list, int *value) {
	/*
	Function to append a value to the linked list.
	[Inserts here]->[]->[]->NULL
	
	args:
		NODE_LL** list - head of the list
		int* value - address of the int variable to be stored;
	*/
	NODE_LL* newNODE_LL;

	newNODE_LL = malloc(sizeof(NODE_LL));
	if(newNODE_LL != NULL) {
		newNODE_LL->value = *value;
		newNODE_LL->next = NULL;
		newNODE_LL->next = *list;
		*list = newNODE_LL;
	}
	else {
		ERROR_MSG
	}
}

void apndEndOfList(NODE_LL **list , int * value)
{
	/*
	Function to append a value to the linked list.
	[]->[]->[Inserts Here]->NULL

	args:
		NODE_LL **list - head of the list
		int *value - address of the int variable to be stored
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

void printList(NODE_LL** list) {
	/*
	Prints the Linked List onto stdin.
	Format: []->[]->[]->NULL
	
	args: NODE **list - head of the list
	returns: Nothing
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
	Kills (Eliminates) all nodes from the Linked List.

	args: NODE **list - head of the list
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
