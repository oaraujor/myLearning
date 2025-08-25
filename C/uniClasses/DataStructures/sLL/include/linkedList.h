#ifndef sLL
#define sLL

#define ERROR_MSG printf("Error with malloc\n");

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NODE_LL {
	int value;
	struct NODE_LL *next;
} NODE_LL;

void apndBegOfList(NODE_LL**, int*);
void apndEndOfList(NODE_LL**, int*);
void apndMidOfList(NODE_LL **, int *, unsigned int *);// <----- to do

int rmBegNodeOfList(NODE_LL **);
int rmEndNodeOfList(NODE_LL **);
int rmMidNodeOfList(NODE_LL **, int *);

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


void apndMidOfList(NODE_LL **list, int *value, unsigned int *pos) {
	/*
		Desc: Function to isert a value somewhere in the middle of the linked list.
		Visual: [0]->[1]->[Inserts Here]->[2]->[]->[]->NULL
		
		args:
			NODE_LL **list : address to the head of the list
			int *value : address of the int variable to be stored
			size_t *pos : position in the linked list to be inserted in
		return: Nothing to be returned
	*/
	NODE_LL *newNode, *current, *prev;
	unsigned int count = 0;
	newNode = malloc(sizeof(NODE_LL));
	if(newNode != NULL) {
		newNode->value = *value;
		newNode->next = NULL;
		current = *list;
		prev = NULL;
		while(current != NULL) {
			if(count != *pos){
				prev = current;
				current = current->next;
				count++;
			}
			else{
				newNode->next = current;
				prev->next = newNode;
				(*pos)++;
			}
		}
		if(current == NULL) { // if list is empty, the new node is the first element
			*list = newNode;
			(*pos)++;
		}
	}
	else{
		ERROR_MSG
	}

	return;
}


int rmBegNodeOfList(NODE_LL **list) {
	/*
		Desc: Function to remove the first element of the list
		Visual: [Removes This]->[]->[]->NULL
		list->[prev]->[curr]->[]->NULL
		args:
			NODE_LL *list : address to the head of the list
		return: 1 if sucessfull | 0 if the list was empty
	*/

	NODE_LL *curr, *prev;
	prev =  NULL;
	curr = NULL;
	if (*list != NULL) {
		prev = *list;
		curr = prev->next;
		*list = curr;
		free(prev);
		return 1;
	}
	else {
		return 0;
	}
}

int rmEndNodeOfList(NODE_LL **list) {
	/*
		Desc: Function to remove the last element of the list
		Visual: []->[]->[Removes This]->NULL
		args:
			NODE_LL *list : address to the head of the list
		return: 1 if sucessfull | 0 if the list was empty
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

int rmMidNodeOfList(NODE_LL **list, int *value) {
	/*
		Desc: Function to remove the last element of the list
		Visual: []->[]->[Removes This]->[]->[]->NULL
		args:
			NODE_LL *list : address to the head of the list
			int *value : address to the value to be deleted
		return: 1 if sucessfull | 0 if the list was empty
	*/

	NODE_LL *curr, *prev, *temp;
	prev = *list;
	curr = (*list)->next;

	while(curr != NULL && curr->value != *value) {
		prev = curr;
		curr = curr->next;
	}
	if (curr != NULL) {
		temp = curr;
		prev->next = curr->next;
		free(temp);
		return 1;
	}
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
	int i = 0;

	while(curr != NULL) {
		printf("[%d|%d]-->", i, curr->value);
		curr = curr->next;
		i++;
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
