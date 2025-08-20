#include "linkedList.h"

bool contRunning(const char *);
void showMenu(const char *);


int main()
{
	NODE_LL* listNumbers;
	listNumbers = NULL; //empty list
	int menuOption;
	int value;
	//size_t sizeofList;
	bool contMenu, contAppend;

	//sizeofList = 0;
	contMenu = true;
	while(contMenu) {
		system("clear");
		printList(&listNumbers);
		showMenu("txtFiles/mainMenu.txt");
		scanf("%d", &menuOption);
		switch(menuOption) {
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

void showMenu(const char *filename) {
	/*
	*/
	FILE* fileMenu;
	fileMenu = fopen(filename, "r");
	char buffer[256];
	size_t count = 0;
	
	if (fileMenu != NULL){
		while(fgets(buffer, sizeof(buffer), fileMenu) != NULL) {
			if (count != 0) {
				printf("\t%zu - ", count);
			}
			printf("%s", buffer);
			count++;
		}
	}
	else {
		ERROR_MSG
	}
	printf("\n\t>>> ");
	fclose(fileMenu);
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