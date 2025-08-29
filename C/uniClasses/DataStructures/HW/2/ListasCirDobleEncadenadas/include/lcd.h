#ifndef LCD
#define LCD

#include <stdio.h>
#include <stdlib.h>

typedef struct __nodo {
    int valor;
    struct __nodo *siguiente;
    struct __nodo *anterior;
} NODO;

void insertarNodo(NODO **, int);
void buscarNodo();
void eliminarNodo();
void caminarFrente();
void caminarAtras();
void imprimirListaFrente(NODO **);


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
void buscarNodo() {

}
void eliminarNodo() {

}
void caminarFrente() {

}
void caminarAtras() {

}

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
        printf("Lista Circular Vacia!\n");
    }
    return;
}

#endif