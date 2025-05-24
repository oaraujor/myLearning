#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "structuras.h"
#include "utilidades.h"

#define VALIDAR_RANGO(ptr, min, max) (*(ptr) >= (min) && *(ptr) <= (max))

void leerPaciente(FILE *, size_t *);
void leerEntero(const char* , int *, int , int );
void leerCadena(const char *, char *);
void leerDireccion(Direccion *);
void leerGenero(char *);
void generarFolio(char *, char *);
void guardarPaciente(FILE *, Paciente *);

bool leerSintomas(char *, char *);
bool contAgreg(const char *);
bool guardarPregunta();


void leerPaciente(FILE *bdPacientes, size_t *tamano) /*<<<<<<< OCTAVIO ESTA TRABAJANDO EN ESTO NO MOVER*/
{
    Paciente p;
    bool continuar, errorSint, guardar;

    do
    {
        system("cls");
        printf("\tAlta de Pacientes - Pacientes ingresados: %zu/50\n", *tamano);

        leerCadena("Nombre de Paciente: ", p.nombre);
        leerEntero("Edad (1-100):", &p.edad, 1, 100);
        leerGenero(&p.genero);
        leerDireccion(&p.direccionP);
        leerEntero("Servicio: (0 - Consulta | 1 - Emergencia): ", &p.servicio, 0, 1);
        leerEntero("Numero de consultorio disponible (1-9): ", &p.numConsultorios, 1, 9);/*<------------ver despues------------------------*/
        generarFolio(p.folio, p.nombre);
        
		errorSint = leerSintomas(p.sintomas, p.folio);
        if(errorSint)
        {
        	printf(VERDEINT"Sintomas registrados correctamente\n"NORMAL);
            guardar = guardarPregunta();
        }
        else
        	printf(ROJO"Ocurrio un error al ingresar los sintomas\n"NORMAL);
        if(guardar)
        {
            guardarPaciente(bdPacientes, &p);
            system("cls");
            printf(VERDEINT"El paciente ha sido registrado correctamente\n"NORMAL);
            printf("FOLIO: %s\n\n", p.folio);
        }
        else
        {
            system("cls");
            printf(ROJO"DATOS DESCARTADOS\n\n"NORMAL);
        }
        continuar = contAgreg("paciente");
        if(guardar == true)
            (*tamano)++;
    }while(continuar && *(tamano) < MAX_PACIENTES);
}

void leerEntero(const char* mensaje, int *numero, int min, int max) /*<<<<<<< FUNCIONA NO MOVER*/
{
    do
    {
        printf(mensaje);
        scanf("%d", numero);
        if(!VALIDAR_RANGO(numero, min, max))
            printf(ROJO"OPCION INVALIDA | (%d - %d)\n"NORMAL, mensaje, min, max);
    }while(!VALIDAR_RANGO(numero, min, max));
}

void leerCadena(const char *mensaje, char *cadena) /*<<<<<<< FUNCIONA NO MOVER*/
{
    char buffer[MAX_CADENA];
    char limpio[MAX_CADENA];
    bool esValida;
    int inicio, fin, j, i;
    bool espacioPrevio;
    bool nuevaPalabra;

    do
    {
        esValida = true;
        printf("%s", mensaje);
        fflush(stdin);
        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        inicio = 0, fin = strlen(buffer) - 1;
        while(isspace((unsigned char)buffer[inicio]))
            inicio++;
        while(fin >= inicio && isspace((unsigned char)buffer[fin]))
            fin--;

        j = 0;
        espacioPrevio = false;
        i = inicio;
        while(i <= fin && esValida)
        {
            if (isspace((unsigned char)buffer[i]))
            {
                if(!espacioPrevio)
                {
                    limpio[j] = ' ';
                    j++;
                    espacioPrevio = true;
                }
            }
            else
            {
                if(!isalpha((unsigned char)buffer[i]))
                    esValida = false;
                else
                {
                    limpio[j] = buffer[i];
                    j++;
                    espacioPrevio = false;
                }
            }
            i++;
        }

        limpio[j] = '\0';

        if(!esValida || strlen(limpio) == 0)
            printf(ROJO"%s Invalida"NORMAL, mensaje);
        else
        {
            nuevaPalabra = true;
            i = 0;
            while(limpio[i] != '\0')
            {
                if(isspace((unsigned char)limpio[i]))
                    nuevaPalabra = true;
                else
                {
                    limpio[i] = nuevaPalabra ? toupper(limpio[i]) : tolower(limpio[i]);
                    nuevaPalabra = false;
                }
                i++;
            }
            strcpy(cadena, limpio);
        }

    }while(!esValida);
}

void leerDireccion(Direccion *direccion) /*<<<<<<< FUNCIONA NO MOVER*/
{
    printf("Direccion:\n");

    leerCadena("Calle: ", direccion->calle);
    
    printf("Numero: ");
    scanf("%d", &direccion->numero);
    
    leerCadena("Colonia: ", direccion->colonia);
    leerCadena("Municipio : ", direccion->municipio);
    leerCadena("Estado: ", direccion->estado);
}

void leerGenero(char *genero) /*<<<<<<< FUNCIONA NO MOVER*/
{
    char entrada;
    bool valido;

    do
    {
        printf("Genero (M/F): ");
        scanf(" %c", &entrada);

        valido = (entrada == 'M' || entrada == 'F' || entrada == 'm' || entrada == 'f');

        if(valido)
            *genero = (entrada >= 'a') ? entrada - 32 : entrada;
        else
            printf(ROJO"Genero Invalido. Solo M o F."NORMAL);

    }while(!valido);
}

bool leerSintomas(char *sintomas, char *folio) /*<<<<<<< FUNCIONA NO MOVER*/
{
    FILE *archivoFolio; 
    int i, j;
    bool continuar, exitoSintomas;
    
    i = 0;
    while(DIR_BASE[i] != '\0')
    {
        sintomas[i] = DIR_BASE[i];
        i++;
    }
    j = 0;
    while(folio[j] != '\0' && i < MAX_DIR-1)
    {
        sintomas[i] = folio[j];
        i++;
        j++;
    }
    j = 0;
    while(EXTENSION_P[j] != '\0' && i < MAX_DIR-1)
    {
        sintomas[i] = EXTENSION_P[j];
        i++;
        j++;
    }

    sintomas[i] = '\0';

    archivoFolio = fopen(sintomas, "w");
    if(archivoFolio == NULL)
        exitoSintomas = false;
    else
    {
        char linea[1024];
        continuar = true;
        system("CLS");
        printf(VERDEINT"Ingrese los sintomas del paciente. Ingrese FIN en una nueva linea para terminar: \n"NORMAL);
        fflush(stdin);
        while(continuar && fgets(linea, sizeof(linea), stdin))
        {
            if(strcmp(linea, "FIN\n") == 0 || strcmp(linea, "FIN\r\n") == 0)
                continuar = false;
            else
                fputs(linea, archivoFolio);
        }
        exitoSintomas = true;
    }
    fclose(archivoFolio);
    return exitoSintomas;
}

bool contAgreg(const char *persona) /*<<<<<<< FUNCIONA NO MOVER*/
{
    char seguir[3];
    int i;

    do
    {
        printf("Desea agregar otro %s? (Si/No): ", persona);
        fflush(stdin);
        gets(seguir);
        i = 0;
        while(seguir[i] != '\0')
        {
            seguir[i] = tolower(seguir[i]);
            i++;
        }
        if(strcmp(seguir, "si") != 0 && strcmp(seguir, "no") != 0)
            printf(ROJO"Ingrese si/no\n"NORMAL);

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


void generarFolio(char *folio, char *nombre) /*FUNCIONA NO MOVER*/
{
    int i = 0, j = 0;

    while(nombre[i] != '\0')
    {
        if((nombre[i] >= 'A' && nombre[i] <= 'Z') && j < MAX_FOLIO-1)
        {
            folio[j] = nombre[i];
            j++;
        }
        i++;
    }

    if(j < MAX_FOLIO-1)
        folio[j] = '-';
        j++;

    srand(time(NULL));

    while(j < MAX_FOLIO-1)
    {
        folio[j] = '0' + (rand() % 10);
        j++;
    }
    folio[j] = '\0';
}

bool guardarPregunta()
{
    char seguir[3];
    int i;

    do
    {
        printf("Desea guardar el paciente ingresado? (si|no)\n");
        fflush(stdin);
        fgets(seguir, sizeof(seguir), stdin);

        i = 0;
        while (seguir[i] != '\0')
        {
            seguir[i] = tolower(seguir[i]);
            i++;
        }
        if (strcmp(seguir, "si") != 0 && strcmp(seguir, "no") != 0)
        {
            system("cls");
            printf(ROJO"Ingrese si/no\n"NORMAL);
        }

    }while (strcmp(seguir, "si") != 0 && strcmp(seguir, "no") != 0);

    if(strcmp(seguir, "si") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void guardarPaciente(FILE *archivo, Paciente *p) /*FUNCIONA NO MOVER*/
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

#endif
