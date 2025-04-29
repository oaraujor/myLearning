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
    char nombre[50];
    Direccion direccionP;
    int edad; //validar < 100
    char genero; //M masculino, //F femenino
    char sintomas[20]; // direccion del archivo
    /*sintomas tendra una cadena con la ruta a la
    carpeta data/p/ donde se almacenaran los archivos
    de texto donde se tendra la redaccion de los 
    sintomas. Esto para no tener un char de mas
    de 100 y hacerlo mas facil de leer y actualizar*/
    int numConsultorios;
} Paciente;

#endif