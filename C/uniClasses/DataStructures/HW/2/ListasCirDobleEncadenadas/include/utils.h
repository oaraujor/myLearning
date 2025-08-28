#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define ERROR_MSG printf("ERROR\n");
#define VALIDAR_RANGO(valor, min, max) ((valor) >= (min) && (valor) <= (max))

#ifdef _WIN32
    #define CLEAR_SCREEN system("cls");
#else
    #define CLEAR_SCREEN system("clear");
#endif

void showMenu(const char *);
void EnterToContinue();
bool continueYesNO(const char *, const char *);


/*
    Desc:   Function to show a menu from a txt file.
            First line of the file will print as the menu title.
            After the title, it will treat each line as options appending 1,2,3 ... to eachline on stdout.
    args:   const char *filename : path to a file to be displayed
    Return: Nothing to be returned.
*/
void showMenu(const char *filename) {

    FILE* fileMenu;
    fileMenu = fopen(filename, "r");
    char buffer[256];
    size_t count = 0;

    if (fileMenu != NULL){
        while(fgets(buffer, sizeof(buffer), fileMenu) != NULL) {
            if (count != 0) {
                printf("\t%zu) ", count);
            }
            printf("%s", buffer);
            count++;
        }
    }
    else {
        ERROR_MSG
    }
    printf("\n\t>>> ");
    fclose(fileMenu);
}

/*
    Desc:   Function to stop flow after printing something.
    args:   NONE
    Return: NONE
*/
void EnterToContinue() {
    printf("Press ENTER to continue...");
    while (getchar() != '\n');
    getchar();
}

/*
    Desc:   Function to prompt the user for yes or no input. Handles upper/lowercases
    args:   const char *message : message prompt to ask user for yes or no.
            const char *messageError : Error message to be displayed when wrong input.
    Return: true : yes
            false : no
*/
bool continueYesNO(const char *message, const char *messageError) {
    char usr_in[6];
    int i;

    do
    {
        printf("%s", message);
        fflush(stdin);
        gets(usr_in);
        i = 0;
        while(usr_in[i] != '\0') {
            usr_in[i] = tolower(usr_in[i]);
            i++;
        }
        if(strcmp(usr_in, "si") != 0 && strcmp(usr_in, "no") != 0) {
            CLEAR_SCREEN
            printf("%s\n", messageError);
        }
    } while(strcmp(usr_in, "si") != 0 && strcmp(usr_in, "no") != 0);

    if (strcmp(usr_in, "si") == 0) {
        return true;
    }
    else {
        return false;
    }
}

int leerEntero(int min, int max, const char* mensajeExito, const char* mensajeError) {
    char aux[' '];
    int i, auxLen, num;
    bool numCorrecto;
    do {
        do {
            printf("%s", mensajeExito);
            fflush(stdin);
            gets(aux);
            auxLen = strlen(aux);
            for(i = 0; i < auxLen; i++) {
                if(isdigit(aux[i])) {
                    numCorrecto = true;
                }
                else {
                    numCorrecto = false;
                }
                if(numCorrecto == false) {
                    system("clear");
                    printf("%s\n", mensajeError);
                    break;
                }
            }
            if(auxLen == 0) {
                numCorrecto = false;
            }
        }while(!numCorrecto);
        num = atoi(aux);
        if(!VALIDAR_RANGO(num, min, max)) {
            system("clear");
            printf("%s\n", mensajeError);
        }
    } while(!VALIDAR_RANGO(num, min, max));
    return num;
}


#endif
