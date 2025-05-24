#ifndef CTR_ARCHIVOS
#define CTR_ARCHIVOS

#define ARCHIVO_PACIENTES "data/pacientes.dat"

#include "structuras.h"
#include "utilidades.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void listarPacientes(FILE *, size_t *);
void eliminarPacientes(FILE *, size_t *);
void buscarEditarPacientes(FILE *, size_t *);
void eliminarRegistro(FILE *, int *);
void mostrarSintomas(char *);
void editarP(FILE *, int *, Paciente );

bool buscarFolio(char *, FILE *, int *);

FILE *cargarPacientes(size_t *);
FILE *iniArchivoP();


void listarPacientes(FILE *archivo, size_t *tamano) /*FUNCIONA NO MOVER*/
{
    Paciente p;
    char in;

    if (*tamano != 0)
    {
        system("cls");
        rewind(archivo);
        printf("LISTADO DE PACIENTES\n");
        printf("================================================================================================================\n");
        printf("| %-15s | %-30s | %-4s | %-6s | %-15s | %-10s | %-12s |\n", 
               "Folio", "Nombre", "Edad", "Genero", "Estado", "Servicio", "Consultorio");
        printf("================================================================================================================\n");
    
        while(fread(&p, sizeof(Paciente), 1, archivo) == 1)
        {
            if(p.servicio != -1)
                printf("| %-15s | %-30s | %-4d | %-6c | %-15s | %-10s | %-12d |\n", p.folio, p.nombre, p.edad, p.genero, p.direccionP.estado, (p.servicio == 0 ? "Consulta" : ROJO"Emergencia"NORMAL), p.numConsultorios);
        }        
        printf("================================================================================================================\n");
	    printf("Presione ENTER para continuar...");
        fflush(stdin);
	    scanf("%c", &in);
        system("cls");
    }
    else
    {
    	system("cls");
        printf(ROJO"No hay pacientes registrados\n\n"NORMAL);
	}
    
}

void buscarEditarPacientes(FILE *archivoBdPacientes, size_t *tamano)
{
    Paciente pLeer;
    char folioAbuscar[MAX_FOLIO], nombreAbuscar[MAX_CADENA], opcion, si_no, in;
    bool encontrado = false, cont;
    int lugar;

    system("cls");
    do
    {
        lugar = 0;
        do
        {
            printf("a. Buscar por FOLIO\n");
            printf("b. Buscar por NOMBRE\n");
            printf("Ingrese la opcion: ");
            fflush(stdin);

            scanf("%c", &opcion);
            if (opcion != 'a' && opcion != 'b')
                printf(ROJO"Porfavor ingrese 'a' o 'b'"NORMAL);

        }while (opcion != 'a' && opcion != 'b');
        
        switch(opcion)
        {
            case 'a':
                printf("Por favor ingrese el Folio del paciente a buscar (ej. AAA-0123456789): ");
                fflush(stdin);
                fgets(folioAbuscar, sizeof(folioAbuscar), stdin);
                folioAbuscar[strcspn(folioAbuscar, "\n")] = '\0';
                encontrado = buscarFolio(folioAbuscar, archivoBdPacientes, &lugar);

            break;

            case 'b':

                leerCadena("Por favor ingrese el nombre del paciente a buscar: ", nombreAbuscar);
                lugar = 0;
                rewind(archivoBdPacientes);
                while(fread(&pLeer, sizeof(Paciente), 1, archivoBdPacientes) == 1 && !encontrado)
                {
                    if(strcmp(pLeer.nombre, nombreAbuscar) == 0)
                        encontrado = true;
                    else
                        lugar++;
                }
            break;
                
            default:
                system("cls");
                printf(ROJO"Por favor ingrese 'a' o 'b'\n"NORMAL);
            break;

        }

        if(encontrado)
        {
            rewind(archivoBdPacientes);
            fseek(archivoBdPacientes, sizeof(Paciente) * lugar, SEEK_SET);
            fread(&pLeer, sizeof(Paciente), 1, archivoBdPacientes);
            system("cls");
            printf("Folio del Paciente: %s\n", pLeer.folio);
            printf("Nombre del Paciente: %s\n", pLeer.nombre);
            printf("Edad del Paciente: %d\n", pLeer.edad);
            printf("Genero del Paciente: %s\n", (pLeer.genero == 'M' ? "Masculino" : "Femenino"));
            printf("Direccion:\n");
            printf("\tCalle y numero: %s #%d\n", pLeer.direccionP.calle, pLeer.direccionP.numero);
            printf("\tColonia: %s\n", pLeer.direccionP.colonia);
            printf("\tMunicipio: %s\n", pLeer.direccionP.municipio);
            printf("\tEstado: %s\n", pLeer.direccionP.estado);
            printf("Servicio: %s\n", (pLeer.servicio == 0 ? "Consulta" : "Emergencia"));
            mostrarSintomas(pLeer.sintomas);
            printf("Presione ENTER para continuar...");
            fflush(stdin);
	        scanf("%c", &in);
            system("cls");

            do
            {
                fflush(stdin);
                printf("\nDesea editar el paciente(s/n)\n");
                scanf(" %c", &si_no);
                si_no = tolower(si_no);

                if (si_no != 's' && si_no != 'n')
                    printf(ROJO"Porfavor ingrese 's' o 'n'"NORMAL);     
            }while(si_no != 's' && si_no != 'n');

            if(si_no == 's')
                editarP(archivoBdPacientes, &lugar, pLeer);
        }
        else
        {
            printf(ROJO"No se encontro ningun paciente\n"NORMAL);
        }

        do
        {
            fflush(stdin);
            printf("Desea buscar otro paciente (s/n)\n");
            scanf(" %c", &si_no);
            si_no = tolower(si_no);

            if (si_no != 's' && si_no != 'n')
                printf(ROJO"Porfavor ingrese 's' o 'n'\n"NORMAL);

        }while(si_no != 's' && si_no != 'n');

        if(si_no == 's')
            cont = true;
        else
            cont = false;
            
    }while(cont);

}

void eliminarPacientes(FILE *archivoBdPacientes, size_t *tamano)
{
    Paciente pLeer;
    char folioAbuscar[MAX_FOLIO], si_no;
    int lugar;
    bool encontrado = false, cont;

    system("cls");
    do
    {
        printf("Por favor ingrese el Folio del paciente a eliminar (ej. AAA-0123456789): ");
        fflush(stdin);
        fgets(folioAbuscar, sizeof(folioAbuscar), stdin);
        folioAbuscar[strcspn(folioAbuscar, "\n")] = '\0';

        lugar = buscarFolio(folioAbuscar, archivoBdPacientes, &lugar);
        eliminarRegistro(archivoBdPacientes, &lugar);
        printf(ROJO"Paciente eliminado correctamente\n"NORMAL);

        do
        {
            fflush(stdin);
            printf("Desea borrar otro paciente(s/n)\n");
            scanf(" %c", &si_no);
            si_no = tolower(si_no);

            if (si_no != 's' && si_no != 'n')
                printf(ROJO"Porfavor ingrese 's' o 'n'"NORMAL);     
        }while(si_no != 's' && si_no != 'n');

        if(si_no == 's')
            cont = true;
        else
            cont = false;

    }while(cont);
    
}

void eliminarRegistro(FILE *archivoBdPacientes, int *numRegistro)
{
    int i;
    Paciente p = {"", -1,"",{"",0,"","",""},0,'0',"",0};

    rewind(archivoBdPacientes);
    fseek(archivoBdPacientes, sizeof(Paciente) * (*numRegistro), SEEK_SET);
    fwrite(&p, sizeof(Paciente), 1, archivoBdPacientes);
}

FILE *iniArchivoP()
{
    FILE *archivo;
    int i;
    Paciente p = {"", -1,"",{"",0,"","",""},0,'0',"",0};

    archivo = fopen(ARCHIVO_PACIENTES, "wb");

    if(archivo != NULL)
    {
        for(i = 0; i < MAX_PACIENTES; i++)
        {
            fwrite(&p, sizeof(Paciente), 1, archivo);
        }
    }

    return archivo;
}

FILE *cargarPacientes(size_t *tamano)
{
    FILE *archivoP;
    Paciente p;

    archivoP = fopen(ARCHIVO_PACIENTES, "rb+");
    
    *tamano = 0;
    if(archivoP != NULL)
    {
        while(fread(&p, sizeof(Paciente), 1, archivoP) == 1)
    	{
            if(p.servicio != -1)
            {
                (*tamano)++;
            }
		}
    }
    else
    {
        archivoP = iniArchivoP();
        *tamano = 0;
    }
    rewind(archivoP);
    return archivoP;
}

void mostrarSintomas(char *pwdSintomaPaciente)
{
    FILE *sintomasP;
    char lineas[1024];

    sintomasP = fopen(pwdSintomaPaciente, "r");
    if(sintomasP != NULL)
    {
        printf(VERDEINT"\nSintomas del Paciente:\n"NORMAL);
        while(fgets(lineas, sizeof(lineas), sintomasP) != NULL)
        {
            printf("%s", lineas);
        }
        printf(VERDEINT"-----------------------------------------\n"NORMAL);
        fclose(sintomasP);
    }
    else
        printf(ROJO"Ocurrio un error al leer los Sintomas\n"NORMAL);
}

bool buscarFolio(char *folioAbuscar, FILE *archivoBdPacientes, int *lugar)
{
    Paciente pLeer;
    bool encontrado;

    *lugar = 0;
    rewind(archivoBdPacientes);
    while(fread(&pLeer, sizeof(Paciente), 1, archivoBdPacientes) == 1 && !encontrado)
    {
        if(strcmp(pLeer.folio, folioAbuscar) == 0)
            encontrado = true;
        else
            (*lugar)++;
    }
    return encontrado;
}

void editarP(FILE *archivoBdPacientes, int *posicion, Paciente p)
{
    bool errorSint, guardar;
    system("cls");

    printf("Folio del Paciente: %s\n", p.folio);
    printf("Nombre del Paciente: %s\n", p.nombre);

    leerEntero("Nueva edad (1-100):", &p.edad, 1, 100);
    leerDireccion(&p.direccionP);
    leerEntero("Servicio: (0 - Consulta | 1 - Emergencia): ", &p.servicio, 0, 1);
    leerEntero("Numero de consultorio disponible (1-9): ", &p.numConsultorios, 1, 9);
    
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
        system("cls");
        fseek(archivoBdPacientes, sizeof(Paciente) * (*posicion), SEEK_SET);
        fwrite(&p, sizeof(Paciente), 1, archivoBdPacientes);
        printf(VERDEINT"El paciente ha sido editado correctamente\n"NORMAL);
    }
    else
    {
        system("cls");
        printf(ROJO"DATOS DESCARTADOS\n\n"NORMAL);
    }
}

#endif
