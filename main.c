#include "structuras.h"
#include "utilidades.h"
#include "controlArchivos.h"
#include <stdio.h>
#include <stdbool.h>

int main()
{
    char opcion;
    bool verifArchivo;
    size_t tamanoP;
    FILE *archivoBdPacientes;

    
    archivoBdPacientes = cargarPacientes(&tamanoP); 
    if (archivoBdPacientes != NULL)
    {
        system("cls");
        /*printf("%zu\n", tamanoP);*/
        do
        {
            printf(BLANCO"#########################################\n"NORMAL);
            printf(BLANCO"#"VERDEINT" MENU                                  "BLANCO"#\n"NORMAL);
            printf(BLANCO"#########################################\n"NORMAL);
            printf(BLANCO"#"VERDEINT" 1) Alta de Pacientes                  "BLANCO"#\n"NORMAL);
            printf(BLANCO"#"VERDEINT" 2) Busqueda o edicion de paciente     "BLANCO"#\n"NORMAL);
            printf(BLANCO"#"VERDEINT" 3) Listado de pacientes               "BLANCO"#\n"NORMAL);
            printf(BLANCO"#"VERDEINT" 4) Baja de paciente                   "BLANCO"#\n"NORMAL);
            printf(BLANCO"#"VERDEINT" 5) Salir                              "BLANCO"#\n"NORMAL);
            printf(BLANCO"#########################################\n"NORMAL);
            printf(">>> ");
                    
            scanf(" %c", &opcion);
    
            switch(opcion)
            {
                case '1':
                    if(tamanoP < MAX_PACIENTES)
                        leerPaciente(archivoBdPacientes, &tamanoP);
                        system("cls");
                    else
                        printf("ERROR: Maxima capacidad de pacientes!\n");    
                    break;
                case '2':
                    buscarEditarPacientes(archivoBdPacientes, &tamanoP);
                    break;
                case '3':
                    listarPacientes(archivoBdPacientes, &tamanoP);
                    break;
                case '4':
                    eliminarPacientes(archivoBdPacientes, &tamanoP);
                    break;
                case '5':
                    printf("Saliendo del programa...\n");
                    break;
            }
        }while(opcion != '5');

        fclose(archivoBdPacientes);
    }
    else
        printf(ROJO"ERROR: ALGO SALIO MAL AL INICIAR EL PROGRAMA\n"NORMAL);

    return 0;

}
