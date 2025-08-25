/*
    Una compania de aviacion tiene cuatro destinos (enum 1-4) con tres vuelos cada uno (numerados del 1-3).
    Se ingresa la informacion de las plazas disponibles en cada uno de los doce vuelos. Posteriormente llegan 
    pedidos de pasajes de los que se ingresa:
        NO. de Pedidio
        No. de Destino
        No. de Vuelo
        Cantidad de pasajes requeridos
    Si la cantidad de pasajes pedidos es superior a la disponibilidad existente en ese vuelo y para ese destino
    se rechaza el pedido indicando la leyenda: NO HAY CANTIDAD DE PLAZAS DISPONIBLES
    Se pide informar:
        La cantidad de pasajes sobrantes en cada vuelo.
        Los numeros de pedidos rechazados con la cantidad de pasajes solicitados.
*/

#include "vuelos.h"
#include <stdio.h>
#include <stdlib.h>

int leerEntero(int, int, const char*);
void inicializarPlazas(Destino*);
int procesarPedidos(Destino* , Pedido* , int);
void mostrarPlazasRestantes(Destino*);
void mostrarPedidosRechazados(Pedido* , int);
void mostrarPedidosRechazados(Pedido* , int );


int main() {
    Destino destinos[DESTINOS];
    Pedido pedidos[MAX_PEDIDOS];
    int numPedidos = 0, continuar = 1;

    // Inicializar plazas
    inicializarPlazas(destinos);

    // Ingreso de pedidos
    printf("\n--- Ingreso de pedidos ---\n");
    while (continuar && numPedidos < MAX_PEDIDOS) {
        pedidos[numPedidos].numeroPedido = leerEntero(1, 9999, "Ingrese número de pedido");
        pedidos[numPedidos].destino = leerEntero(1, DESTINOS, "Ingrese destino");
        pedidos[numPedidos].vuelo = leerEntero(1, VUELOS, "Ingrese vuelo");
        pedidos[numPedidos].cantidadPasajes = leerEntero(1, 500, "Ingrese cantidad de pasajes requeridos");
        pedidos[numPedidos].rechazado = 0; // default
        numPedidos++;
        printf("¿Desea ingresar otro pedido? (1=Sí, 0=No): ");
        scanf("%d", &continuar);
        while(getchar() != '\n');
    }

    // Procesar pedidos
    procesarPedidos(destinos, pedidos, numPedidos);

    // Informes
    mostrarPlazasRestantes(destinos);
    mostrarPedidosRechazados(pedidos, numPedidos);

    return 0;
}

// Función para validar la entrada de un entero en rango
int leerEntero(int min, int max, const char* mensaje) {
    int valor, ok;
    do {
        printf("%s (%d-%d): ", mensaje, min, max);
        ok = scanf("%d", &valor);
        while(getchar() != '\n'); // Limpiar buffer
        if (ok == 1 && valor >= min && valor <= max)
            return valor;
        printf("Valor inválido. Intente de nuevo.\n");
    } while (1);

    /*
    #include<stdio.h>
//#include<stdlib.h>
#include<string.h>
#include<ctype.h>
char Aux[' '];
int i,p,y,num;
int main()
{
	do{
        printf("\n Introduzca un valor numerico: ");	
        fflush(stdin);
        gets(Aux);//se lee los datos introducidos
        y = strlen(Aux);
        for(i=0;i < y;i++)
        {
            if(isdigit(Aux[i]))
                p = 1;	
            else
                p = 0;
            if(p == 0)
            {
            printf("\n\n Error,dato mal introducido\n\n ");
            break;
            }
        }
        if(y==0)
            p=0;
	}while(p==0);

    num = atoi(Aux);
    printf("\n\n\n\t Valor leido: %d",num);
}
    */
}

// Función para inicializar plazas disponibles
void inicializarPlazas(Destino* destinos) {
    for (int i = 0; i < DESTINOS; i++) {
        for (int j = 0; j < VUELOS; j++) {
            char msg[50];
            sprintf(msg, "Ingrese plazas para destino %d, vuelo %d", i+1, j+1);
            destinos[i].vuelos[j].plazas = leerEntero(0, 500, msg);
        }
    }
}

// Procesa pedidos y actualiza destinos usando apuntadores
int procesarPedidos(Destino* destinos, Pedido* pedidos, int numPedidos) {
    int rechazados = 0;
    for (int i = 0; i < numPedidos; i++) {
        int d = pedidos[i].destino - 1;
        int v = pedidos[i].vuelo - 1;
        // Validar índices
        if (d < 0 || d >= DESTINOS || v < 0 || v >= VUELOS) {
            printf("Pedido %d: Destino o vuelo inválido. Rechazado.\n", pedidos[i].numeroPedido);
            pedidos[i].rechazado = 1;
            rechazados++;
            continue;
        }
        if (pedidos[i].cantidadPasajes <= destinos[d].vuelos[v].plazas) {
            destinos[d].vuelos[v].plazas -= pedidos[i].cantidadPasajes;
            pedidos[i].rechazado = 0;
        } else {
            printf("Pedido %d: NO HAY CANTIDAD DE PLAZAS DISPONIBLES\n", pedidos[i].numeroPedido);
            pedidos[i].rechazado = 1;
            rechazados++;
        }
    }
    return rechazados;
}

// Mostrar plazas sobrantes
void mostrarPlazasRestantes(Destino* destinos) {
    printf("\n--- Plazas sobrantes por vuelo ---\n");
    for (int i = 0; i < DESTINOS; i++) {
        for (int j = 0; j < VUELOS; j++) {
            printf("Destino %d, Vuelo %d: %d plazas\n", i+1, j+1, destinos[i].vuelos[j].plazas);
        }
    }
}

// Mostrar pedidos rechazados
void mostrarPedidosRechazados(Pedido* pedidos, int numPedidos) {
    printf("\n--- Pedidos rechazados ---\n");
    int hay = 0;
    for (int i = 0; i < numPedidos; i++) {
        if (pedidos[i].rechazado) {
            printf("Pedido Nro %d: %d pasajes solicitados (Destino %d, Vuelo %d)\n",
                pedidos[i].numeroPedido, pedidos[i].cantidadPasajes,
                pedidos[i].destino, pedidos[i].vuelo);
            hay = 1;
        }
    }
    if (!hay) {
        printf("Ningún pedido fue rechazado.\n");
    }
}