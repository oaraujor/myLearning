#include "structuras.h"
#include "utilidades.h"
#include "controlArchivos.h"

#include <stdio.h>
#include <stdbool.h>

int main()
{
    int opcion;
    bool verifArchivo;
    Paciente pacientes[MAX_PACIENTES];
    size_t tamanoP;

    if (cargarPacientes(pacientes, &tamanoP) != false)
    {
        do
        {
            printf("\tMENU\n");
            printf("1) Alta de Pacientes\n");
            printf("2) Busqueda o edicion de paciente\n");
            printf("3) Listado de pacientes\n");
            printf("4) Baja de paciente\n");
            printf("5) Salir\n");
            
            scanf("%d", &opcion);
    
            switch(opcion)
            {
                case 1:
                    if(tamanoP < MAX_PACIENTES)
                        leerPaciente(pacientes, &tamanoP);
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
    }
    else
        printf("ERROR: Algo salio mal al inicar el programa.\n");

    return 0;

}
