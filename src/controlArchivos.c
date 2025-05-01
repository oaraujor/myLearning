#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "structuras.h"
#include "controlArchivos.h"

#define ARCHIVO_PACIENTES "data/pacientes.dat"

void listarPacientes()//tentativo
{
    FILE *archivo = fopen(ARCHIVO_PACIENTES, "r");
    Paciente paciente;
    int id = 1;

    if(archivo != NULL)
    {
        printf("\n--- LISTADO DE PACIENTES ---\n");
        while(fread(&paciente, sizeof(Paciente), 1, archivo))
        {
            printf("ID: %d\n", id);
            printf("Nombre: %s\n", paciente.nombre);
            printf("Servicio: %s\n", paciente.servicio == 0 ? "Consulta" : "Emergencia");
            printf("Edad: %d\n", paciente.edad);
            printf("Genero: %c\n", paciente.genero);
            printf("Consultorio: %d\n", paciente.numConsultorios);
            printf("Direccion: %s %d, %s, %s, %s\n", 
                   paciente.direccionP.calle,
                   paciente.direccionP.numero,
                   paciente.direccionP.colonia,
                   paciente.direccionP.municipio,
                   paciente.direccionP.estado);
            printf("Sintomas: %c\n", paciente.sintomas);
            printf("--------------------------\n");
            id++;
        }
        fclose(archivo);
    }
    else
    {
        printf("\033[31mNo hay pacientes registrados.\033[0m\n");
    }
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

bool iniArchivoP(void)
{
    FILE *archivo;
    int i;
    Paciente p = {"", 2,"",{"",0,"","",""},0,'0',"",0};
    bool existeArchivo;

    archivo = fopen(ARCHIVO_PACIENTES, "wb");

    if(archivo == NULL)
        existeArchivo = false;
    else
    {
        for(i = 0; i < MAX_PACIENTES; i++)
            fwrite(&p, sizeof(Paciente), 1, archivo);
        fclose(archivo);
        existeArchivo = true;
    }
    return existeArchivo;
}

void guardarPaciente(Paciente *paciente) //tentativo
{
    FILE *archivo;
    archivo = fopen(ARCHIVO_PACIENTES, "a");

    if(archivo != NULL)
    {
        fwrite(paciente, sizeof(Paciente), 1, archivo);
        fclose(archivo);
        printf("\033[32mPaciente registrado correctamente.\033[0m\n");
    }
    else
        printf("\033[31mERROR al abrir archivo para guardar paciente.\033[0m\n");
}
bool cargarPacientes(Paciente *pacientes, size_t *tamano)
{
    FILE *archivoP;
    Paciente p;
    bool existeArchivo = false;

    archivoP = fopen(ARCHIVO_PACIENTES, "rb");
    
    *(tamano) = 0;//inicializar contador de registros
    if(archivoP != NULL)//si ya existe el archivo con registros
    {
    	while(fread(&p, sizeof(Paciente), 1, archivoP) == 1)
    	{
        	if(p.servicio == 1 || p.servicio == 0) //si el registro es valido
        		*(tamano)++;
        	*(pacientes + *(tamano)) = p;
		}
        existeArchivo = true;
        fclose(archivoP);
    }
    else
        existeArchivo = iniArchivoP();
    
    return existeArchivo;
}
