#include <stdio.h>
#include "structuras.h"
#include "utilidades.h"
#include <string.h>
#include <stdbool.h>

#define VALIDAR_RANGO(ptr, min, max) (*(ptr) >= (min) && *(ptr) <= (max)) //remplazo a funciones de validar opcion


void leerPaciente(Paciente *pacientes, size_t *tamano)
{
    Paciente *pacienteActual;
    bool continuar;

    printf("\tAlta de PAcientes\n");

    do
    {
        pacienteActual = pacientes + *(tamano);

        leerEntero("Servcio (0 - Consulta | 1 - Emergencia): ", &pacienteActual->servicio, 0, 1);
        leerCadena("Nombre de Paciente: ", pacienteActual->nombre);
        leerDireccion(&pacienteActual->direccionP);
        leerEntero("Edad (1-100):", &pacienteActual->edad, 1, 100);
        leergenero(&pacienteActual->genero);
        leerSintomas(pacienteActual->sintomas);
        leerConsultorio(&pacienteActual->numConsultorios);

        continuar = contAgreg("alumno");
        if(continuar == true)
            *(tamano)++;
    }while(continuar && *(tamano) < 100);
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
    int i;
    char buffer[50];
    bool esValida = true;

    do
    {
        printf(mensaje);
        fflush(stdin);
        fgets(buffer, sizeof(buffer), stdin);
        i = 0;
        while(cadena[i] != '\0' && esValida && i < 50)
        {
            if(!((cadena[i] >= 'a' && cadena[i] <= 'z') || (cadena[i] >= 'A' && cadena[i] <= 'Z') || cadena[i] == ' '))
                esValida = false;
            i++;
        }
        if(!esValida)
            printf("\033[31m%s Invalida\033[0m\n\a", mensaje);
        else
            strcpy(cadena, buffer);
    } while(!esValida); 
}

void leerDireccion(Direccion *direccion)
{
    printf("Direccion:\n");

    leerCadena("Calle: ", direccion->calle);
    
    printf("Numero: "); //ver si se puede validar de alguna forma
    scanf("%d", &direccion->numero);
    
    leerCadena("Colonia: ", direccion->colonia);
    leerCadena("Municipio : ", direccion->municipio);
    leerCadena("Estado: ", direccion->estado);
}

void leergenero(char *genero)
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

void leerSintomas(int *idPaciente, )
{
    return;//
}


