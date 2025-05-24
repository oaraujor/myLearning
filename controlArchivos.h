#ifndef CTR_ARCHIVOS
#define CTR_ARCHIVOS

#define ARCHIVO_PACIENTES "data/pacientes.dat"

#include "structuras.h"
#include "utilidades.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void listarPacientes(FILE *, size_t *);
void eliminarPacientes(FILE *, size_t *);
bool buscarEditarPacientes(FILE *);
void eliminarRegistro(FILE *, int *);

FILE *cargarPacientes(size_t *);
FILE *iniArchivoP();


void listarPacientes(FILE *archivo, size_t *tamano) /*FUNCIONA NO MOVER*/
{
    Paciente p;
    char in;

    if (*tamano != 0)
    {
        system("cls");
        rewind(archivo);
        printf("LISTADO DE PACIENTES\n");
        printf("================================================================================================================\n");
        printf("| %-15s | %-30s | %-4s | %-6s | %-15s | %-10s | %-12s |\n", 
               "Folio", "Nombre", "Edad", "Genero", "Estado", "Servicio", "Consultorio");
        printf("================================================================================================================\n");
    
        while(fread(&p, sizeof(Paciente), 1, archivo) == 1)
        {
            if(p.servicio != -1)
                printf("| %-15s | %-30s | %-4d | %-6c | %-15s | %-10s | %-12d |\n", p.folio, p.nombre, p.edad, p.genero, p.direccionP.estado, (p.servicio == 0 ? "Consulta" : ROJO"Emergencia"NORMAL), p.numConsultorios);
        }        
        printf("================================================================================================================\n");
	    printf("Presione ENTER para continuar...");
        fflush(stdin);
	    scanf("%c", &in);
        system("cls");
    }
    else
    {
    	system("cls");
        printf(ROJO"No hay pacientes registrados\n\n"NORMAL);
	}
    
}

bool buscarEditarPacientes(FILE *archivo)
{
    /*
    TODO
    */
}

void eliminarPacientes(FILE *archivoBdPacientes, size_t *tamano)
{
    Paciente pLeer;
    char nombreAbuscar[MAX_CADENA], folioAbuscar[MAX_FOLIO], opcion, si_no;
    int lugar;
    bool encontrado = false, cont;

    system("cls");
    do
    {
        
        do
        {
            printf("a. Eliminar por FOLIO\n");
            printf("b. Eliminar por NOMBRE\n");
            printf("Ingrese la opcion: ");
            fflush(stdin);

            scanf("%c", &opcion);
            if (opcion != 'a' && opcion != 'b')
                printf(ROJO"Porfavor ingrese 'a' o 'b'"NORMAL); 
        }while (opcion != 'a' && opcion != 'b');
        
        switch(opcion)
        {
            case 'a':
                rewind(archivoBdPacientes);
                printf("Por favor ingrese el Folio del paciente a eliminar (ej. AAA-0123456789): ");
                fflush(stdin);
                fgets(folioAbuscar, sizeof(folioAbuscar), stdin);
                folioAbuscar[strcspn(folioAbuscar, "\n")] = '\0';
        
                lugar = 0;
                while(fread(&pLeer, sizeof(Paciente), 1, archivoBdPacientes) == 1 && !encontrado && lugar < *tamano)
                {
                    if(strcmp(pLeer.folio, folioAbuscar) == 0)
                        encontrado = true;
                    else
                        lugar++;
                }

            break;

            case 'b':

                leerCadena("Por favor ingrese el nombre del paciente a eliminar: ", nombreAbuscar);
                lugar = 0;
                while(fread(&pLeer, sizeof(Paciente), 1, archivoBdPacientes) == 1 && !encontrado && lugar < *tamano)
                {
                    if(strcmp(pLeer.nombre, nombreAbuscar) == 0)
                        encontrado = true;
                    else
                        lugar++;
                }
            break;

            default:
                printf(ROJO"Por favor ingrese 'a' o 'b'\n"NORMAL);
            break;
        }

        if(!encontrado)
        {
            printf(ROJO"No se encontro el paciente. Intente de nuevo\n"NORMAL);
        }
        else
        {
            eliminarRegistro(archivoBdPacientes, &lugar);
            printf(ROJO"Paciente eliminado correctamente\n"NORMAL);

        }

        do
        {
            fflush(stdin);
            printf("Desea borrar otro paciente\n");
            scanf(" %c", &si_no);
            si_no = tolower(si_no);

            if (si_no != 's' && si_no != 'n')
                printf(ROJO"Porfavor ingrese 's' o 'n'"NORMAL);     
        }while(si_no != 's' && si_no != 'n');

        if(si_no == 's')
            cont = true;
        else
            cont = false;

    }while(cont);
    
}

void eliminarRegistro(FILE *archivoBdPacientes, int *numRegistro)
{
    int i;
    Paciente p = {"", -1,"",{"",0,"","",""},0,'0',"",0};

    rewind(archivoBdPacientes);
    fseek(archivoBdPacientes, sizeof(Paciente) * (*numRegistro), SEEK_SET);
    fwrite(&p, sizeof(Paciente), 1, archivoBdPacientes);
}

FILE *iniArchivoP()   /*FUNCIONA NO MOVER*/
{
    FILE *archivo;
    int i;
    Paciente p = {"", -1,"",{"",0,"","",""},0,'0',"",0};

    archivo = fopen(ARCHIVO_PACIENTES, "wb");

    if(archivo != NULL)
    {
        for(i = 0; i < MAX_PACIENTES; i++)
        {
            fwrite(&p, sizeof(Paciente), 1, archivo);
        }
    }

    return archivo;
}


FILE *cargarPacientes(size_t *tamano) /*FUNCIONA NO MOVER*/
{
    FILE *archivoP;
    Paciente p;

    archivoP = fopen(ARCHIVO_PACIENTES, "rb+");
    
    *tamano = 0;
    if(archivoP != NULL)
    {
        while(fread(&p, sizeof(Paciente), 1, archivoP) == 1)
    	{
            if(p.servicio != -1)
            {
                (*tamano)++;
            }
		}
    }
    else
    {
        archivoP = iniArchivoP();
        *tamano = 0;
    }
    rewind(archivoP);
    return archivoP;
}

#endif
