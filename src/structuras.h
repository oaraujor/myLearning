#ifndef STRUCTURAS
#define STRUCTURAS

#include <stdio.h>

typedef struct
{
    char calle[50];
    int numero;
    char colonia[50];
    char municipio[50];
    char estado[50];
} Direccion;

typedef struct
{
    int servicio; //1 consulta, 0 emergencia
    char nombre[100];
    Direccion direccionP;
    int edad; //validar < 100
    char genero; //M masculino, //F femenino
    //sintomas
    int numConsultorios;
    
} Paciente;

#endif