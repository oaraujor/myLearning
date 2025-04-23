#include <stdio.h>
#include "structuras.h"
#include <string.h>
#include <stdbool.h>

#define VALIDAR_RANGO(ptr, min, max) (*(ptr) >= (min) && *(ptr) <= (max)) //remplazo a funciones de validar opcion

void leerPaciente(Paciente const *pacientes, size_t *tamano)
{
    Paciente *pacienteActual;
    bool continuar;

    printf("\tAlumnos\n");

    do
    {
        pacienteActual = pacientes + *(tamano);

        leerEntero("Servio (0 - Consulta | 1 - Emergencia): ", &pacienteActual->servicio, 0, 1);
        leerCadena("Nombre de Paciente: ", pacienteActual->nombre);
        leerDireccion(&pacienteActual->direccionP);
        leerEntero("Edad (1-100):", &alumnoActual->edad, 1, 100);
        leergenero();
        leerSintomas();
        leerConsultorio();

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
    bool esValida = true;

    do
    {
        printf(mensaje);
        fflush(stdin);
        gets(cadena);
        i = 0;
        while(cadena[i] != '\0' && esValida)
        {
            if(!((cadena[i] >= 'a' && cadena[i] <= 'z') || (cadena[i] >= 'A' && cadena[i] <= 'Z') || cadena[i] == ' '))
                esValida = false;
            i++;
        }
        if(!esValida)
            printf("\033[31m%s Invalida\033[0m\n\a", mensaje);
    } while(!esValida); 
}

void leerDireccion(Direccion *direccion)
{
    Direccion direccionPaciente;

    printf("Direccion:\n");
    do
    {
        printf("Calle (50 Char): ");
        gets(direccionPaciente.calle); //50
        if(!strlen(direccionPaciente.calle < 50));
            printf("\033[31mIngrese un estado valido.\033[0m\a\n");
    }while(!strlen(direccionPaciente.estado < 50));

    printf("Numero: "); //ver si se puede validar de alguna forma
    scanf("%d", direccionPaciente.numero);

    do
    {
        printf("Colonia (50 Char): ");
        gets(direccionPaciente.colonia);//50
        if(!strlen(direccionPaciente.colonia < 50));
            printf("\033[31mIngrese un estado valido.\033[0m\a\n");
    }while(!strlen(direccionPaciente.colonia) < 50);

    do
    {
        printf("Municipio (50 Char): ");
        gets(direccionPaciente.municipio);//50
        if(!strlen(direccionPaciente.municipio < 50));
            printf("\033[31mIngrese un municipio valido.\033[0m\a\n");
    }while(!strlen(direccionPaciente.municipio));

    do
    {
        printf("Estado (50 Char):");
        gets(direccionPaciente.estado);//50
        if(!strlen(direccionPaciente.estado < 50));
        printf("\033[31mIngrese un estado valido.\033[0m\a\n");
    }while(!strlen(direccionPaciente.estado < 50));
    *direccion = direccionPaciente;
}

void leergenero(void)
{
    return; //falta
}

void leerSintomas()
{
    return; //falta
}

void leerConsultorio()
{
    return; //falta
}

