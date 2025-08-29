#ifndef LCD
#define LCD

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct __nodo {
    int valor;
    struct __nodo *siguiente;
    struct __nodo *anterior;
} NODO;

void insertarNodo(NODO **, int);
bool buscarNodo(NODO **, int);
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

#endif