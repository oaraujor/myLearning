#include <stdio.h>
#include "src/include/structuras.h"
#include "src/include/utilidades.h"

#define MAX_PACIENTES 100

int main()
{
    int opcion;
    Paciente pacientes[MAX_PACIENTES];//arreglo de pacientes, con direcion de memoria fija
    size_t tamanoP = 0; //control del tamano del arreglo de Pacientes

    do
    {

        printf("\tMENU\n");
        printf("1) Alta de Pacientes\n");
        printf("2) Busqueda o edicion de paciente\n");
        printf("3) Listado de pacientes\n");
        printf("4) Baja de paciente\n");
        printf("5) Salir\n");

        switch(opcion)
        {
            case 1:

                if(tamanoP < MAX_PACIENTES)
                    leerPacientes(pacientes, &tamanoP);
                else
                    printf("ERROR: Maxima capacidad de pacientes!\n");
                    
                break;
            case 2:
                buscarEditarPacientes();
                break;
            case 3:
                listarPacientes();
                break;
            case 4:
                eliminarPacientes();
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opcion no valida");
                break;

        }
    }while(opcion != 5);

    return 0;

}