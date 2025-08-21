#include "linkedList.h"

bool contRunning(const char *);
void showMenu(const char *);


int main()
{
	NODE_LL* listNumbers;
	listNumbers = NULL; //empty list
	int menuOption;
	int value, status;
	size_t sizeofList;
	bool contMenu, contAppend;

	sizeofList = 0;
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
				//INSERT MIDDLE
				break;
			
			case 3:
				do {
					system("clear");
					printf("Enter the int value to append to the end list: ");
					scanf("%d", &value);
					apndEndOfList(&listNumbers, &value);
					contAppend = contRunning("Append more numbers?\n");
				}while(contAppend);
				break;
				
				case 4:
					//REMOVE FROM BEGGINING
					break;

				case 5:
					//REMOVE FROM THE MIDDLE
					break;

				case 6:
					do {
						system("clear");
						printf("DELETING THE LAST ELEMENT OF THE LIST...\n");
						status = rmEndNodeOfList(&listNumbers);
						if(status == 1){
							printList(&listNumbers);
						}
						else{
							printf("Could not delete last element of the list\n");
							//TODO: implement deleting the last when return 0;
						}
						contAppend = contRunning("Delete another element?\n");
					}while(contAppend);
					break;

				case 7:
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