#ifndef CTR_ARCHIVOS
#define CTR_ARCHIVOS

#define ARCHIVO_PACIENTES "data/pacientes.dat"

#include "structuras.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void listarPacientes(FILE *archivo, size_t *tamano);
void eliminarPacientes();
void guardarPaciente(FILE *, Paciente *);
bool buscarEditarPacientes();
FILE *cargarPacientes(size_t *);

void listarPacientes(FILE *archivo, size_t *tamano)
{
    Paciente p;
    int count = 0;

    system("cls");
    rewind(archivo);

    if (*tamano != 0)
    {
        printf("\t\tLISTADO DE PACIENTES\n");
        printf("================================================================================================================\n");
        printf("| %-5s | %-20s | %-4s | %-6s | %-15s | %-10s | %-12s |\n", 
               "Folio", "Nombre", "Edad", "Genero", "Estado", "Servicio", "Consultorio");
        printf("================================================================================================================\n");
    
        while (fread(&p, sizeof(Paciente), 1, archivo) == 1)
        {
            printf("| %-5d | %-20s | %-4d | %-6c | %-15s | %-10s | %-12d |\n", p.folio, p.nombre, p.edad, p.genero, p.direccionP.estado, (p.servicio == 0 ? "Consulta" : "Emergencia"), p.numConsultorios);
        }        
        printf("================================================================================================================\n");
    }
    else
        printf(ROJO"No hay pacientes registrados\n"NORMAL);
}


bool buscarEditarPacientes()//por hacer
{
    /*
    FILE *archivo = fopen(ARCHIVO_PACIENTES, "r+b");
    Paciente paciente;
    int idBuscar;
    bool encontrado = false;
    int id = 1;

    if(archivo != NULL)
    {
        printf("Ingrese el ID del paciente a buscar/editar: ");
        scanf("%d", &idBuscar);

        while(fread(&paciente, sizeof(Paciente), 1, archivo))
        {
            if(id == idBuscar)
            {
                printf("\nPaciente encontrado:\n");
                printf("Nombre: %s\n", paciente.nombre);
                printf("Edad: %d\n", paciente.edad);
                printf("Consultorio: %d\n", paciente.numConsultorios);

                printf("\n-- Modificando datos --\n");
                leerCadena("Nuevo nombre: ", paciente.nombre);
                leerEntero("Nueva edad (1-100): ", &paciente.edad, 1, 100);
                leerEntero("Nuevo consultorio (1-50): ", &paciente.numConsultorios, 1, 50);

                fseek(archivo, -sizeof(Paciente), SEEK_CUR);
                fwrite(&paciente, sizeof(Paciente), 1, archivo);
                encontrado = true;
                break;
            }
            id++;
        }

        fclose(archivo);

        if(!encontrado)
            printf("\033[31mPaciente no encontrado.\033[0m\n");
    }
    else
    {
        printf("\033[31mError al abrir archivo.\033[0m\n");
    }

    return encontrado;
    */
}

void eliminarPacientes() //tentativo
{
    /*
    FILE *archivo = fopen(ARCHIVO_PACIENTES, "rb");
    FILE *temp = fopen("temp.txt", "wb");
    Paciente paciente;
    int idEliminar;
    int id = 1;

    if(archivo != NULL && temp != NULL)
    {
        printf("Ingrese el ID del paciente a eliminar: ");
        scanf("%d", &idEliminar);

        while(fread(&paciente, sizeof(Paciente), 1, archivo))
        {
            if(id != idEliminar)
            {
                fwrite(&paciente, sizeof(Paciente), 1, temp);
            }
            id++;
        }

        fclose(archivo);
        fclose(temp);

        remove(ARCHIVO_PACIENTES);
        rename("temp.txt", ARCHIVO_PACIENTES);

        printf("\033[32mPaciente eliminado (si existía).\033[0m\n");
    }
    else
    {
        printf("\033[31mError al procesar archivos.\033[0m\n");
    }
    */
}

FILE *iniArchivoP()
{
    FILE *archivo;
    int i;
    Paciente p = {"", 2,"",{"",0,"","",""},0,'0',"",0};

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

void guardarPaciente(FILE *archivo, Paciente *p)
{
    int lugar;
    bool cont = true;
    Paciente pLeer;

    rewind(archivo);
    lugar = 0;
    while(fread(&pLeer, sizeof(Paciente), 1, archivo) == 1 && cont)
    {
        if(pLeer.servicio == 2)
            cont = false;
        lugar++;
    }
    //rewind(archivo);

    fseek(archivo, sizeof(Paciente) * lugar, SEEK_SET);
    fwrite(p, sizeof(Paciente), 1, archivo);

}

FILE *cargarPacientes(size_t *tamano)
{
    FILE *archivoP;
    Paciente p;

    archivoP = fopen(ARCHIVO_PACIENTES, "rb+");
    
    *tamano = 0;
    if(archivoP != NULL)
    {
        while(fread(&p, sizeof(Paciente), 1, archivoP) == 1)
    	{
            if(p.servicio == 1 || p.servicio == 0)
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