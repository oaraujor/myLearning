#ifndef STRUCTURAS
#define STRUCTURAS

#define MAX_CADENA 50
#define MAX_PACIENTES 50
#define MAX_DIR 34
#define MAX_FOLIO 15
#define DIR_BASE "data/pacientes/"
#define EXTENSION_P ".txt"

typedef struct
{
    char calle[MAX_CADENA];
    int numero;
    char colonia[MAX_CADENA];
    char municipio[MAX_CADENA];
    char estado[MAX_CADENA];
} Direccion;

typedef struct
{
    char folio[MAX_FOLIO];
    int servicio;
    char nombre[MAX_CADENA];
    Direccion direccionP;
    int edad;
    char genero;
    char sintomas[MAX_DIR];
    int numConsultorios; //<-------------------------------------
} Paciente;

#endif