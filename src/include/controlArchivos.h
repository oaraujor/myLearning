#ifndef CTR_ARCHIVOS
#define CTR_ARCHIVOS

#include "structuras.h"
#include "controlArchivos.h"

void listarPacientes();
void eliminarPacientes();
void guardarPaciente(Paciente *);

bool buscarEditarPacientes();
bool iniArchivoP(void);
bool cargarPacientes(Paciente *, size_t *);



#endif