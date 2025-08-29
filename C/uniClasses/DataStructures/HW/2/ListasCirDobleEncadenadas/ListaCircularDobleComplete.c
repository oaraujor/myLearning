#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

//macro para el borrado de pantalla dependiendo el S.O.
#ifdef _WIN32
    #define CLEAR_SCREEN system("cls");
#else
    #define CLEAR_SCREEN system("clear");
#endif

//definicion de nodo
typedef struct __nodo {
    int valor;
    struct __nodo *siguiente;
    struct __nodo *anterior;
} NODO;

//prototipos
void insertarNodo(NODO **, int);
void eliminarNodo(NODO **, int );
void caminarFrente(NODO **, int );
void caminarAtras(NODO **, int );
void imprimirListaReversa(NODO **);
void imprimirListaFrente(NODO **);
bool buscarNodo(NODO **, int);
int leerEntero(const char *);


int main() {

	int opcionMenu, numero;
	bool cont = true;
	NODO *listaCir;
	listaCir = NULL;
	CLEAR_SCREEN

	do {
		imprimirListaFrente(&listaCir);
		opcionMenu = leerEntero("---MENU: Listas Circulares Doblemente Encadenadas---\n"
							"1) Insertar elemento a la lista\n"
							"2) Eliminar elemento a la lista\n"
							"3) Buscar en la lista\n"
							"4) Caminar Hacia el Frente\n"
							"5) Caminar Hacia Atras\n"
							"6) Imprimir Lista por el Frente\n"
							"7) Imprimir Lista por Atras\n"
							"8) Salir\n"
							">>>>");
		
		switch (opcionMenu) {
			case 1:
				//insertar dato
				CLEAR_SCREEN
				numero = leerEntero("Ingrese el numero a insertar en la lista: ");
				CLEAR_SCREEN
				imprimirListaFrente(&listaCir);
				insertarNodo(&listaCir, numero);
				break;
			case 2:
				//eliminar dato
				CLEAR_SCREEN
				numero = leerEntero("Ingrese el numero a eliminar en la lista: ");
				CLEAR_SCREEN
				imprimirListaFrente(&listaCir);
				eliminarNodo(&listaCir, numero);
				break;
			case 3:
				//buscar dato
				CLEAR_SCREEN
				numero = leerEntero("Ingrese el numero a buscar en la lista: ");
				CLEAR_SCREEN
				buscarNodo(&listaCir, numero);
				break;
			case 4:
				//caminar hacia enfrente
				CLEAR_SCREEN
				numero = leerEntero("Ingrese el numero de pasos a caminar hacia enfrente: ");
				CLEAR_SCREEN
				imprimirListaFrente(&listaCir);
				caminarFrente(&listaCir, numero);
				break;
			case 5:
				//caminar hacia atras
				CLEAR_SCREEN
				numero = leerEntero("Ingrese el numero de pasos a caminar hacia atras: ");
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
				printf("OPCION NO RECONOCIDA!\n");
				break;
			}
	} while (cont);
	return 0;
}
//funcion para leer enteros y validar que sea int unicamente
int leerEntero(const char* mensaje) {
    char aux[' '];
    int i, auxLen, num;
    bool numCorrecto;
    do {
        fflush(stdin);
        printf("%s", mensaje);
        gets(aux);
        auxLen = strlen(aux);
        for(i = 0; i < auxLen; i++) {
            if(isdigit(aux[i])) {
                numCorrecto = true;
            }
            else {
                numCorrecto = false;
            }
            if(numCorrecto == false) {
				CLEAR_SCREEN
                printf("Dato Incorrecto!\n");
                break;
            }
        }
        if(auxLen == 0) {
            numCorrecto = false;
        }
    }while(!numCorrecto);
    num = atoi(aux);
    return num;
}

//funcion para insertar un nuevo elemento a la lista circular
void insertarNodo(NODO **listaCircular, int numero) {
    NODO *nuevoNodo, *actual, *sigNodoDeActual;
    nuevoNodo = malloc(sizeof(NODO));

    if (nuevoNodo == NULL) {
        printf("No se pudo crear un nuevo nodo\n");
    }
    else {
        nuevoNodo->valor = numero;
        actual = *listaCircular;
        
        if (actual != NULL) {
            sigNodoDeActual = actual->siguiente;
            nuevoNodo->anterior = actual;
            nuevoNodo->siguiente = sigNodoDeActual;
            actual->siguiente = nuevoNodo;
            sigNodoDeActual->anterior = nuevoNodo;
        }
        else {
            //lista vacia
            *listaCircular = nuevoNodo;
            nuevoNodo->siguiente = nuevoNodo;
            nuevoNodo->anterior = nuevoNodo;
        }
    }

    return;
}

//funcion para buscar nodo en la lista 
bool buscarNodo(NODO **listaCircular, int numeroBuscar) {
    NODO *actual;
    actual = *listaCircular;
    bool encontrado = false;

    if(actual != NULL) {
        do {
            if (actual->valor == numeroBuscar) {
                printf("Dato encontrado!\n");
                encontrado = true;
            }
            actual = actual->siguiente;
        }while (actual != *listaCircular);
        
    }
    else {
        printf("Lista Circular Vacia!\n");
        encontrado = false;
    }
    if (encontrado == false) {
        printf("Dato no encontrado\n");
    }
    return encontrado;
}

//funcion para eliminar un elemento de la lista circular
void eliminarNodo(NODO **listaCircular, int numeroBuscar) {
    NODO *actual, *nodoBorrar;
    actual = *listaCircular;
    nodoBorrar = NULL;

    //buscar nodo
    if(actual != NULL) {
        do {
            if (actual->valor == numeroBuscar) {
                nodoBorrar = actual;
            }
            actual = actual->siguiente;
        }while (actual != *listaCircular);
        
    }
    else {
        printf("Lista Circular Vacia!\n");
    }
    if (nodoBorrar != NULL) {
        if (nodoBorrar->siguiente == nodoBorrar) {
            *listaCircular = NULL;
        }
        else {
            nodoBorrar->anterior->siguiente = nodoBorrar->siguiente;
            nodoBorrar->siguiente->anterior = nodoBorrar->anterior;
            if (nodoBorrar == *listaCircular)
                *listaCircular = nodoBorrar->siguiente;
        }
        free(nodoBorrar);
    }
    
}

//elemento para mover el puntero cabezera n pasos enfrente
void caminarFrente(NODO **listaCircular, int pasos) {
    NODO *actual;
    actual = *listaCircular;
    int i = 0;

    if (*listaCircular != NULL){
        for (i = 0; i < pasos; i++) {
            actual = actual->siguiente;
        }
        *listaCircular = actual;
    }
    else {
        printf("Lista Circular Vacia!\n");
    }
}

//elemento para mover el puntero cabezera n pasos atras
void caminarAtras(NODO **listaCircular, int pasos) {
    NODO *actual;
    actual = *listaCircular;
    int i = 0;
    
    if (*listaCircular != NULL){
        for (i = 0; i < pasos; i++) {
            actual = actual->anterior;
        }
        *listaCircular = actual;
    }
    else {
        printf("Lista Circular Vacia!\n");
    }
}

//funcion para imprimir la lista por enfrente
void imprimirListaFrente(NODO **listaCircular) {
    NODO *referencia;
    referencia = NULL;

    referencia = *listaCircular;
    if (referencia != NULL){
        //no esta vacia
        do {
            printf("[%d]<->", referencia->valor);
            referencia = referencia->siguiente;

        } while (referencia != *listaCircular);
        printf("[%d]\n",referencia->valor);
    }
    else {
        printf("[]\n");
    }
    return;
}

//funcion para imprimir la lista en reversa
void imprimirListaReversa(NODO **listaCircular) {
    NODO *referencia;
    referencia = NULL;

    referencia = *listaCircular;
    if (referencia != NULL){
        //no esta vacia
        do {
            printf("[%d]<->", referencia->valor);
            referencia = referencia->anterior;

        } while (referencia != *listaCircular);
        printf("[%d]\n",referencia->valor);
    }
    else {
        printf("[]\n");
    }
    return;
}