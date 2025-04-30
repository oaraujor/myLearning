#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "structuras.h"
#include "utilidades.h"
#include "controlArchivos.h"

#define VALIDAR_RANGO(ptr, min, max) (*(ptr) >= (min) && *(ptr) <= (max)) //remplazo a funciones de validar opcion

void leerPaciente(Paciente *pacientes, size_t *tamano)
{
    Paciente *pacienteActual;
    bool continuar, errorSint;

    
    do
    {
        system("clear");
        printf("\tAlta de Pacientes - Pacientes ingresados: %zu/50\n", tamano);
        pacienteActual = pacientes + *(tamano);
        
        leerEntero("Servcio (0 - Consulta | 1 - Emergencia): ", &pacienteActual->servicio, 0, 1);
        leerCadena("Nombre de Paciente: ", pacienteActual->nombre);
        generarFolio(&pacienteActual->folio, pacienteActual->nombre);
        leerDireccion(&pacienteActual->direccionP);
        leerEntero("Edad (1-100):", &pacienteActual->edad, 1, 100);
        leergenero(&pacienteActual->genero);
        leerEntero("Numero de consultorio disponible (1-50): ", &pacienteActual->numConsultorios, 1, 50);//<------------------------------------

        errorSint = leerSintomas(pacienteActual->sintomas, pacienteActual->folio);
        if(errorSint)
        {
            printf("Sintomas registrados correctamente");
            guardarPaciente(pacienteActual);//por ver <--------------------------------
            printf("El paciente ha sido registrado correctamente\n");
            printf("FOLIO: %s\n", pacienteActual->folio);
        }
        else
            printf("Ocurrio un error al ingresar los sintomas");

        continuar = contAgreg("paciente");
        if(continuar == true)
            *(tamano)++;
    }while(continuar && *(tamano) < MAX_PACIENTES);
}

void leerEntero(const char* mensaje, int *numero, int min, int max)
{
    do
    {
        printf(mensaje);
        scanf("%d", numero);
        if(!VALIDAR_RANGO(numero, min, max))
        printf("\033[31m%s Invalido | %d - %d.\033[0m\a\n", mensaje, min, max);
    }while(!VALIDAR_RANGO(numero, min, max));
}

void leerCadena(const char *mensaje, char *cadena)
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
                if (!espacioPrevio)
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

        if (!esValida || strlen(limpio) == 0)
            printf("\033[31m%s Invalida\033[0m\n\a", mensaje);
        else
        {
            // Capitalizar la primera letra de cada palabra
            nuevaPalabra = true;
            i = 0;
            while(limpio[i] != '\0')
            {
                if (isspace((unsigned char)limpio[i]))
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

void leerDireccion(Direccion *direccion)
{
    printf("Direccion:\n");

    leerCadena("Calle: ", direccion->calle);
    
    printf("Numero: ");
    scanf("%d", &direccion->numero);
    
    leerCadena("Colonia: ", direccion->colonia);
    leerCadena("Municipio : ", direccion->municipio);
    leerCadena("Estado: ", direccion->estado);
}

void leerGenero(char *genero)
{
    char entrada;
    bool valido;

    do
    {
        printf("\tGenero (M/F): ");
        scanf(" %c", &entrada);

        valido = (entrada == 'M' || entrada == 'F' || entrada == 'm' || entrada == 'f');

        if(valido)
            *genero = (entrada >= 'a') ? entrada - 32 : entrada;
        else
            printf("\033[31mGenero Invalido. Solo M o F.\033[0m\n\a}");

    }while(!valido);
}

bool leerSintomas(char *sintomas, char *folio)
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
        printf("Ingrese los sintomas del paciente. Ingrese FIN en una nueva linea para terminar: \n");
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

bool contAgreg(const char *persona)
{
    char seguir[3];
    int i;

    do
    {
        printf("¿Desea agregar otro %s? (Si/No): ", persona);
        fflush(stdin);
        gets(seguir);
        i = 0;
        while (seguir[i] != '\0')
        {
            seguir[i] = tolower(seguir[i]);
            i++;
        }
        if (strcmp(seguir, "si") != 0 && strcmp(seguir, "no") != 0)
            printf("\033[31mIngrese si/no.\033[0m\a\n");

    } while (strcmp(seguir, "si") != 0 && strcmp(seguir, "no") != 0);

    if(strcmp(seguir, "si") == 0)
        return true;
    else
        return false;
}

void generarFolio(char *folio, const char *nombre)
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

//<-------------------- falta lo de los consultorios