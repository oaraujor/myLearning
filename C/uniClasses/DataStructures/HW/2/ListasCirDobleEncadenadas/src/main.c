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
	CLEAR_SCREEN

	do {
		imprimirListaFrente(&listaCir);
		printf("\n");
		showMenu("txt/menu.txt");
		scanf("%d", &opcionMenu);
		
		switch (opcionMenu) {
			case 1:
				//insertar dato
				CLEAR_SCREEN
				printf("Ingrese el numero a insertar en la lista: ");
				scanf("%d", &numero);
				CLEAR_SCREEN
				imprimirListaFrente(&listaCir);
				insertarNodo(&listaCir, numero);
				break;
			case 2:
				//eliminar dato
				CLEAR_SCREEN
				printf("Ingrese el numero a eliminar en la lista: ");
				scanf("%d", &numero);
				CLEAR_SCREEN
				imprimirListaFrente(&listaCir);
				eliminarNodo(&listaCir, numero);
				break;
			case 3:
				//buscar dato
				CLEAR_SCREEN
				printf("Ingrese el numero a buscar en la lista: ");
				scanf("%d", &numero);
				CLEAR_SCREEN
				buscarNodo(&listaCir, numero);
				break;
			case 4:
				//caminar hacia enfrente
				CLEAR_SCREEN
				printf("Ingrese el numero de pasos a caminar hacia enfrente: ");
				scanf("%d", &numero);
				CLEAR_SCREEN
				imprimirListaFrente(&listaCir);
				caminarFrente(&listaCir, numero);
				break;
			case 5:
				//caminar hacia atras
				CLEAR_SCREEN
				printf("Ingrese el numero de pasos a caminar hacia atras: ");
				scanf("%d", &numero);
				CLEAR_SCREEN
				imprimirListaFrente(&listaCir);
				caminarAtras(&listaCir, numero);
				break;
			case 6:
				//imprimir hacia frente
				CLEAR_SCREEN
				imprimirListaFrente(&listaCir);
				break;
			case 7:
				//imprimir hacia atras
				CLEAR_SCREEN
				imprimirListaReversa(&listaCir);
				break;
			case 8:
				cont = false;
				printf("Saliendo del programa...\n");
				break;
				
			default:
				CLEAR_SCREEN
				printf(RED"OPCION NO RECONOCIDA!\n"NORMAL);
				break;
			}

	} while (cont);
	

	return 0;
}
