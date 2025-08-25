#include "linkedList.h"
#include "colors.h"

bool contRunning(const char *);
void showMenu(const char *);


int main()
{
	NODE_LL* listNumbers;
	listNumbers = NULL; //empty list
	int menuOption;
	int value, status;
	unsigned int sizeofList = 0, position;
	bool contMenu, contAppend;

	contMenu = true;
	while(contMenu) {
		system("clear");
		printList(&listNumbers);
		showMenu("txtFiles/mainMenu.txt");
		scanf("%d", &menuOption);
		switch(menuOption) {
			case 1:
				do {
					printList(&listNumbers);
					printf(GREEN"Enter the int value to append to the beggining of the list: "NORMAL);
					scanf("%d", &value);
					apndBegOfList(&listNumbers, &value);
					contAppend = contRunning(CYAN"Append more numbers?\n"NORMAL);
				}while(contAppend);
				break;

			case 2:
				do {
					printList(&listNumbers);
					printf(GREEN"Enter the int value to append to the the list: "NORMAL);
					scanf("%d", &value);
					printf(GREEN"Enter the position where you want to append it: "NORMAL);
					scanf("%u", &position);
					apndMidOfList(&listNumbers, &value, &position);
					contAppend = contRunning(CYAN"Append more numbers?\n"NORMAL);
				}while(contAppend);
				break;
			
			case 3:
				do {
					printList(&listNumbers);
					system("clear");
					printf(GREEN"Enter the int value to append to the end list: "NORMAL);
					scanf("%d", &value);
					apndEndOfList(&listNumbers, &value);
					contAppend = contRunning(CYAN"Append more numbers?\n"NORMAL);
				}while(contAppend);
				break;
				
				case 4:
					do {
						system("clear");
						printf(YELLOW"DELETING THE FIRST ELEMENT OF THE LIST...\n"NORMAL);
						status = rmBegNodeOfList(&listNumbers);
						if(status == 1){
							printList(&listNumbers);
						}
						else{
							printf(RED"Could not delete the first element of the list\n"NORMAL);
							//TODO: implement deleting the last when return 0;
						}
						contAppend = contRunning(CYAN"Delete another element?\n"NORMAL);
					}while(contAppend);
					break;

				case 5:
					do {
						printList(&listNumbers);
						printf(GREEN"Enter the int value to delete from the the list: "NORMAL);
						scanf("%d", &value);
						printf(YELLOW"DELETING THE FIRST ELEMENT OF THE LIST...\n"NORMAL);
						status = rmMidNodeOfList(&listNumbers, &value);
						if (status == 1) {
							printList(&listNumbers);
						}
						else{
							printf(RED"Could not delete value: %d"NORMAL, value);
						}
						contAppend = contRunning(CYAN"Delete more numbers?\n"NORMAL);
					}while(contAppend);
					break;

				case 6:
					do {
						system("clear");
						printf(YELLOW"DELETING THE LAST ELEMENT OF THE LIST...\n"NORMAL);
						status = rmEndNodeOfList(&listNumbers);
						if(status == 1){
							printList(&listNumbers);
						}
						else{
							printf(RED"Could not delete last element of the list\n"NORMAL);
							//TODO: implement deleting the last when return 0;
						}
						contAppend = contRunning(CYAN"Delete another element?\n"NORMAL);
					}while(contAppend);
					break;

				case 7:
					contMenu = false;
					killList(&listNumbers);
					break;

			default:
				printf(RED"Unknown Selection!\n"NORMAL);
				break;
		}

	}
	return 0;
}

void showMenu(const char *filename) {
	/*
		Desc:	Function to show a menu from a txt file.
				Fucntion will skip the first line as this like is the tittle of the menu.
				After the first file, it will treat each line as options appending 1,2,3 ... to eachline on stdout.
		
		args:	const char *filename : path to a file to be displayed
		Return: Nothing to be returned.
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
	/*
		Desc:	Function to get binary input (yes\no)
		args:	const char *message : message to be displayed to stdout.
		Return:
				True : If user selects yes
				False : If user selects no

	*/

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