#ifndef AVIACION
#define AVIACION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define NORMAL "\033[0m"
#define VERDE "\033[0;32m"
#define BLANCO "\033[0;37m"
#define ROJO "\033[0;31m"
#define CYAN "\033[0;36m"
#define AMARILLO "\033[0;33m"

#define DESTINOS 4
#define VUELOS 3
#define MAX_PEDIDOS 100
#define VALIDAR_RANGO(valor, min, max) ((valor) >= (min) && (valor) <= (max))

typedef struct {
    int plazas; // plazas disponibles
} Vuelo;

typedef struct {
    Vuelo vuelos[VUELOS];
} Destino;

typedef struct {
    int numeroPedido;
    int destino;
    int vuelo;
    int cantidadPasajes;
    int rechazado; // 1 si rechazado, 0 si aceptado
} Pedido;

#endif