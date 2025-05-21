#ifndef CTR_ARCHIVOS
#define CTR_ARCHIVOS

#define ARCHIVO_PACIENTES "data/pacientes.dat"

#include "structuras.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void listarPacientes(FILE *, size_t *);
void eliminarPacientes(FILE *);
void guardarPaciente(FILE *, Paciente *);
bool buscarEditarPacientes(FILE *);
FILE *cargarPacientes(size_t *);

void listarPacientes(FILE *archivo, size_t *tamano) /*<<<<<<< FUNCIONA NO MOVER*/
{
    Paciente p;
    char in;

    if (*tamano != 0)
    {
        system("cls");
        rewind(archivo);
        printf("\t\tLISTADO DE PACIENTES\n");
        printf("================================================================================================================\n");
        printf("| %-15s | %-30s | %-4s | %-6s | %-15s | %-10s | %-12s |\n", 
               "Folio", "Nombre", "Edad", "Genero", "Estado", "Servicio", "Consultorio");
        printf("================================================================================================================\n");
    
        while (fread(&p, sizeof(Paciente), 1, archivo) == 1)
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
		TODO - en forma archivos
    */
}

void eliminarPacientes(FILE *archivo)
{
    /*
    	TODO - en forma archivos
    */
}

FILE *iniArchivoP()   /*<<<<<<< FUNCIONA NO MOVER*/
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

void guardarPaciente(FILE *archivo, Paciente *p) /*<<<<<<< FUNCIONA NO MOVER*/
{
    int lugar;
    bool cont = true;
    Paciente pLeer;

    rewind(archivo);
    lugar = 0;
    while(fread(&pLeer, sizeof(Paciente), 1, archivo) == 1 && cont)
    {
        if(pLeer.servicio == -1)
            cont = false;
        else
        	lugar++;
    }
    rewind(archivo);
    fseek(archivo, sizeof(Paciente) * lugar, SEEK_SET);
    fwrite(p, sizeof(Paciente), 1, archivo);

}

FILE *cargarPacientes(size_t *tamano) /*<<<<<<< FUNCIONA NO MOVER*/
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
        *(tamano) = 0;
    }
    rewind(archivoP);
    return archivoP;
}

#endif
