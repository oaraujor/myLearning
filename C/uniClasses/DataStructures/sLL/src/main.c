#include "linkedList.h"

bool contRunning(const char *);
void showOptions();


int main()
{
	NODE_LL* listNumbers;
	listNumbers = NULL; //empty list
	int option;
	int value;
	bool contMenu, contAppend;

	contMenu = true;
	while(contMenu) {
		system("clear");
		printList(&listNumbers);
		showOptions();
		scanf("%d", &option);
		switch(option) {
			case 1:
				do {
					printf("Enter the int value to append to the beggining of the list: ");
					scanf("%d", &value);
					apndBegOfList(&listNumbers, &value);
					contAppend = contRunning("Append more numbers?\n");
				}while(contAppend);
				break;

			case 2:
				do {
					system("clear");
					printf("Enter the int value to append to the end list: ");
					scanf("%d", &value);
					apndEndOfList(&listNumbers, &value);
					contAppend = contRunning("Append more numbers?\n");
				}while(contAppend);
				break;

			case 3:
				contMenu = false;
				killList(&listNumbers);
				break;

			default:
				printf("Unknown Selection!\n");
				break;
		}

	}
	return 0;
}

void showOptions() {
	printf("Linked List of Integer Numbers\n");
	printf("\t1) Append from Front [Here]->[#]->[#]->NULL\n");
	printf("\t2) Append from End [#]->[#]->[Here]->NULL\n");
	printf("\t3) Exit\n");
	printf("\t>>");
}

bool contRunning(const char *message) {
	int selection;
	do {
		printf("%s", message);
		printf("|1 - Yes | 0 - NO|\n");
		printf(">>> ");
		scanf("%d", &selection);
		if(selection < 0 || selection > 1){
			printf("Invalid option\n");
		}
	}while(selection < 0 || selection > 1);
	if (selection == 1) {
		return true;
	}
	else {
		return false;
	}
}