#include "lcd.h"
#include "utils.h"
#include "colors.h"
//The following libraries are already linked under "utils.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <ctype.h>
//#include <string.h>

int main() {

	int opcionMenu, numero;
	bool cont = true;

	NODO *listaCir;
	listaCir = NULL;

	do {
		CLEAR_SCREEN
		printf("LISTA:\n");
		imprimirListaFrente(&listaCir);

		showMenu("txt/menu.txt");
		scanf("%d", &opcionMenu);
		
		switch (opcionMenu) {
			case 1:
				CLEAR_SCREEN
				printf("Ingrese el numero a insertar en la lista: ");
				scanf("%d", &numero);
				insertarNodo(&listaCir, numero);
				break;
			case 2:
				CLEAR_SCREEN
				break;
			case 3:
				CLEAR_SCREEN
				break;
			case 4:
				CLEAR_SCREEN
				break;
			case 5:
				CLEAR_SCREEN
				break;
			case 6:
				cont = false;
				printf("Saliendo del programa...\n");
				break;
				
			default:
				CLEAR_SCREEN
				printf(RED"OPCION NO RECONOCIDA!\n"NORMAL);
				EnterToContinue();
				break;
			}

	} while (cont);
	

	return 0;
}
