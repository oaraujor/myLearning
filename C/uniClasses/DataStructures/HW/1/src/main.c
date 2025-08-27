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

int leerEntero(int , int, const char* , const char* );
void inicializarPlazas(Destino*);
void procesarPedidos(Destino* , Pedido* , int);
void mostrarPlazasRestantes(Destino*);
void mostrarPedidosRechazados(Pedido* , int);
void realizarPedido(Pedido *, int *);
bool continuarSiNo(const char *);
void enterEspera();
void mostrarTodosLosPedidos(Pedido* , int);


int main() {

    bool menuContinuar;
    char opcion;
    Destino destinos[DESTINOS];
    Pedido pedidos[MAX_PEDIDOS];
    int numPedidos = 0;
    menuContinuar = true;

    system("clear");
    inicializarPlazas(destinos);


    do {
        system("clear");
        printf("---Menu--\n");
        printf("a) Realizar un Pedido de Plazas\n");
        printf("b) Procesar Todos los Pedidos\n");
        printf("c) Mostrar Informacion de las Plazas y Destinos\n");
        printf("d) Salir\n");
        printf("Seleccion de opcion: \n");
        fflush(stdin);
        opcion = getchar();

        switch (opcion) {

            case 'a':
                realizarPedido(pedidos, &numPedidos);
                break;

            case 'b':
                procesarPedidos(destinos, pedidos, numPedidos);
                printf("PEDIDOS PROCESADOS\n");
                enterEspera();
                break;

            case 'c':
                system("clear");
                fflush(stdin);
                mostrarTodosLosPedidos(pedidos, numPedidos);
                printf("\n");
                mostrarPedidosRechazados(pedidos, numPedidos);
                printf("\n");
                mostrarPlazasRestantes(destinos);
                printf("\n");

                enterEspera();
                break;

            case 'd':
                menuContinuar = false;
                printf("Terminando programa...\n");
                break;

            default:
                system("clear");
                printf(ROJO"OPCION ERRONEA!"NORMAL);
                break;
                
        }

    } while(menuContinuar);

    return 0;
}

// Función para validar la entrada de un entero en rango
int leerEntero(int min, int max, const char* mensajeExito, const char* mensajeError) {
    char aux[' '];
    int i, auxLen, num;
    bool numCorrecto;

    do {
        do {
            printf(VERDE"%s"NORMAL, mensajeExito);
            fflush(stdin);
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
                    system("clear");
                    printf(ROJO"%s\n"NORMAL, mensajeError);
                    break;
                }
            }
            if(auxLen == 0) {
                numCorrecto = false;
            }
        }while(!numCorrecto);

        num = atoi(aux);
        if(!VALIDAR_RANGO(num, min, max)) {
            system("clear");
            printf(ROJO"%s\n"NORMAL, mensajeError);
        }
    }while(!VALIDAR_RANGO(num, min, max));
        
    return num;
}

// Función para inicializar plazas disponibles
void inicializarPlazas(Destino* destinos) {
    int i = 0, j = 0;

    for (i = 0; i < DESTINOS; i++) {
        for (j = 0; j < VUELOS; j++) {
            system("clear");
            printf("Inicializando plazas\n");
            printf(VERDE"Destino #%d | Vuelo #%d\n"NORMAL, i + 1, j + 1);
            ((destinos + i)->vuelos + j)->plazas = leerEntero(1, 500, "Ingrese el numero de asientos/plazas (1 - 500): ", "ERROR, NUMERO INGRESADO NO VALIDO (1 - 500)!");
        }
    }
}

// Procesa pedidos y actualiza destinos usando apuntadores
void procesarPedidos(Destino* destinos, Pedido* pedidos, int numPedidos) {
    int i = 0;
    int d, v;
    for (i = 0; i < numPedidos; i++) {
        d = (pedidos + i)->destino - 1;
        v = (pedidos + i)->vuelo - 1;
        if ((pedidos + i)->cantidadPasajes <= ((destinos + d)->vuelos + v)->plazas) {
            ((destinos + d)->vuelos + v)->plazas -= (pedidos + i)->cantidadPasajes;
            (pedidos + i)->rechazado = 0; 
        }
        else {
            system("clear");
            printf("Pedido %d: NO HAY CANTIDAD DE PLAZAS DISPONIBLES\n", (pedidos + i)->numeroPedido);
            (pedidos + i)->rechazado = 1;
        }
    }
}

// Mostrar plazas sobrantes
void mostrarPlazasRestantes(Destino* destinos) {
    int i = 0, j = 0;
    printf("--- Plazas sobrantes por vuelo ---\n");
    for (i = 0; i < DESTINOS; i++) {
        for (j = 0; j < VUELOS; j++) {
            printf("Destino %d, Vuelo %d: %d plazas\n", i + 1, j + 1, ((destinos + i)->vuelos + j)->plazas);
        }
    }
}

// Mostrar pedidos rechazados
void mostrarPedidosRechazados(Pedido* pedidos, int numPedidos) {
    printf("--- Pedidos rechazados ---\n");
    int i;
    bool hay;

    i = 0;
    for (i = 0; i < numPedidos; i++) {
        if ((pedidos + i)->rechazado) {
            printf("Pedido Nro %d: %d pasajes solicitados (Destino %d, Vuelo %d)\n",
                (pedidos + i)->numeroPedido, (pedidos + i)->cantidadPasajes,
                (pedidos + i)->destino, (pedidos + i)->vuelo);
            hay = true;
        }
    }
    if (!hay) {
        printf("Ningun pedido fue rechazado.\n");
    }
}

bool continuarSiNo(const char *mensaje) {
    char seguir[3];
    int i;
    do
    {
        printf(VERDE"%s"NORMAL, mensaje);
        fflush(stdin);
        gets(seguir);
        i = 0;
        while(seguir[i] != '\0') {
            seguir[i] = tolower(seguir[i]);
            i++;
        }
        if(strcmp(seguir, "si") != 0 && strcmp(seguir, "no") != 0) {
            system("clear");
            printf(ROJO"DATO ERRONEO! INGRESE SI O NO\n"NORMAL);
        }
    }while(strcmp(seguir, "si") != 0 && strcmp(seguir, "no") != 0);

    if(strcmp(seguir, "si") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//funcion para realizar pedidios
void realizarPedido(Pedido * pedidos, int *numPedidos) {

    bool continuar;
    continuar = true;

    do {
        system("clear");
        printf(VERDE"--- Ingreso de pedidos ---\n"NORMAL);
        (pedidos + *numPedidos)->numeroPedido = leerEntero(1, 9999, "Ingrese numero de pedido (1 - 999): ", "ERROR, NUMERO INGRESADO NO VALIDO (1-999)");
        (pedidos + *numPedidos)->destino = leerEntero(1, DESTINOS, "Ingrese destino (1 - 4): ", "ERROR, NUMERO INGRESADO NO VALIDO (1 - 4)");
        (pedidos + *numPedidos)->vuelo = leerEntero(1, VUELOS, "Ingrese vuelo (1 - 3): ", "ERROR, NUMERO INGRESADO NO VALIDO (1 - 3)");
        (pedidos + *numPedidos)->cantidadPasajes = leerEntero(1, 500, "Ingrese cantidad de pasajes requeridos: ", "ERROR, NUMERO INGRESADO NO VALIDO (1 - 500)");
        (pedidos + *numPedidos)->rechazado = 0; // default
        (*numPedidos)++;
        continuar = continuarSiNo("Ingresar otro pedido? (Si, No): ");
        if (*numPedidos >= MAX_PEDIDOS) {
            printf(ROJO"NO SE PUEDEN HACER MAS PEDIDOS, CANTIDAD MAXIMA DE PEDIDOS ALCANZADA\n"NORMAL);
        }
    } while (continuar && *numPedidos < MAX_PEDIDOS);

}

void enterEspera() {
    printf("Presione ENTER para continuar...");
    while (getchar() != '\n');
    getchar();
}

void mostrarTodosLosPedidos(Pedido* pedidos, int numPedidos) {
    int i = 0;
    printf("--- Todos los pedidos ---\n");
    if (numPedidos == 0) {
        printf(ROJO"No hay pedidos realizados.\n"NORMAL);
        return;
    }
    for (i = 0; i < numPedidos; i++) {
        printf("Pedido Nro %d: %d pasajes solicitados (Destino %d, Vuelo %d) - %s\n",
            (pedidos + i)->numeroPedido,
            (pedidos + i)->cantidadPasajes,
            (pedidos + i)->destino,
            (pedidos + i)->vuelo,
            (pedidos + i)->rechazado ? ROJO"RECHAZADO"NORMAL : VERDE"ACEPTADO"NORMAL);
    }
}
