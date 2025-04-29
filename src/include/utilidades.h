#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "utilidades.h"
#include "structuras.h"
#include <stdbool.h>

void leerPaciente(Paciente const *, size_t *);
void leerEntero(const char* , int *, int , int );
void leerCadena(const char *, char *);
void leerDireccion(Direccion *);
void leerGenero(char *);
void leerSintomas(int *, char *);
bool contAgreg(const char *);

#endif