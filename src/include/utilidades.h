#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "structuras.h"

void leerPaciente(Paciente const *, size_t *);
void leerEntero(const char* , int *, int , int );
void leerCadena(const char *, char *);
void leerDireccion(Direccion *);
void leergenero();
void leerSintomas();
void leerConsultorio();

#endif