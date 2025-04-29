#include <stdio.h>
#include <stdlib.h>
#include "src/include/structuras.h"
#include "src/include/utilidades.h"
#include "src/include/controlArchivos.h"


#define ARCHIVO_PACIENTES "data/pacientes.dat"
#define MAX_PACIENTES 100

int main()
{
    int opcion, verifArchivo;
    Paciente pacientes[MAX_PACIENTES];//arreglo de pacientes, con direcion de memoria fija
    size_t tamanoP = 0; //control del tamano del arreglo de Pacientes

    verifArchivo = iniArchivoP();
    /*Probablemente iniArchivo se elimine o edite, para checar si el archivo
    ya tiene datos. Si ya existe el archivo y contiene datos, se deberan de
    cargar los datos al arreglo y actualizar el tamano sin inicializarlo en 0,
    e inicializar el tamano. Si el programa es ejetutado por primera vez, normal*/
    if(!verifArchivo)
        printf("Error al abrir el registro de pacientes\n");
    else
    {
        do
        {
            system("clear");
            printf("\tMENU\n");
            printf("1) Alta de Pacientes\n");
            printf("2) Busqueda o edicion de paciente\n");
            printf("3) Listado de pacientes\n");
            printf("4) Baja de paciente\n");
            printf("5) Salir\n");
    
            switch(opcion)
            {
                case 1:
                    system("clear");
                    if(tamanoP < MAX_PACIENTES)
                        leerPacientes(pacientes, &tamanoP);
                    else
                        printf("ERROR: Maxima capacidad de pacientes!\n");    
                    break;
                case 2:
                    system("clear");
                    buscarEditarPacientes();
                    break;
                case 3:
                    system("clear");
                    listarPacientes();
                    break;
                case 4:
                    system("clear");
                    eliminarPacientes();
                    break;
                case 5:
                    system("clear");
                    printf("Saliendo del programa...\n");
                    break;
                default:
                    system("clear");
                    printf("Opcion no valida");
                    break;
    
            }
        }while(opcion != 5);
    }

    return 0;

}