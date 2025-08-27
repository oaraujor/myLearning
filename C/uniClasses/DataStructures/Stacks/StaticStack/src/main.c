#include "utils.h"
#include "staticStack.h"

//The following libraries are already linked under "utils.h"
//#include <stdio.h>
//#include <stdbool.h>
//#include <string.h>
//#include <ctype.h>
//#include <stdlib.h>

int main() {
	bool cont = true;
	int STACK[STACK_N] = {0}, front = -1, last = 0, op, num;

	CLEAR_SCREEN

	do
	{
		showMenu("txt/menu.txt");
		scanf("%d", &op);

		switch (op) {
			case 1:
				CLEAR_SCREEN
				printf(GREEN"Enter the number to add to the stack: "NORMAL);
				scanf("%d", &num);
				insertSstack(STACK, &front, num);
				printSstack(STACK, &front, &last);
				EnterToContinue();
				CLEAR_SCREEN
				break;

			case 2:
				CLEAR_SCREEN
				num = popSstack(STACK, &front, &last);
				if (num == -99999) {
					printf(RED"The stack is empty\n"NORMAL);
					EnterToContinue();
					CLEAR_SCREEN
				}
				else {
					CLEAR_SCREEN
					printf(GREEN"Popped from the stack: %d\n"NORMAL, num);
					printSstack(STACK, &front, &last);
					EnterToContinue();
					CLEAR_SCREEN
				}
				break;

			case 3:
				cont = false;
				printf("EXITING...\n");
				break;

			default:
				CLEAR_SCREEN
				printf(RED"Invalid option\n"NORMAL);
				break;
		}
	} while (cont);
	
	return 0;
}
