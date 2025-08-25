#ifndef AVIACION
#define AVIACION

#define DESTINOS 4
#define VUELOS 3
#define MAX_PEDIDOS 100

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