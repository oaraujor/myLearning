#include <stdio.h>
#include "src/structuras.h"

#define MAX_PACIENTES 100

void main()
{
    int opcion;
    Paciente const pacientes[MAX_PACIENTES];//arreglo de pacientes, con direcion de memoria fija
    size_t tamanoP = 0; //control del tamano del arreglo de Pacientes

    do
    {

        printf("\tMENU]\n");
        printf("1) Alta de Pacientes\n");
        printf("2) Busqueda o edicion de paciente");
        printf("3) Listado de pacientes");
        printf("4) Baja de paciente");
        printf("5) Salir");
        break;

        switch(opcion)
        {
            case 1:
                if(tamanoP < MAX_PACIENTES)
                    leerPacientes(pacientes, &tamanoP);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                printf("Opcion no valida");
                break;

        }
    }while(opcion != 5);

}