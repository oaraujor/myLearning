#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdbool.h>
#include "colors.h"

#define ERROR_MSG printf(RED"ERROR\n"NORMAL);
#define CLEAR_SCREEN system("clear"); //change "clear" to "cls" if working with Windows.

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
    printf(GREEN"Press ENTER to continue..."NORMAL);
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
        printf(GREEN"%s"NORMAL, message);
        fflush(stdin);
        gets(usr_in);
        i = 0;
        while(usr_in[i] != '\0') {
            usr_in[i] = tolower(usr_in[i]);
            i++;
        }
        if(strcmp(usr_in, "si") != 0 && strcmp(usr_in, "no") != 0) {
            CLEAR_SCREEN
            printf(RED"%s\n"NORMAL, messageError);
        }
    } while(strcmp(usr_in, "si") != 0 && strcmp(usr_in, "no") != 0);

    if (strcmp(usr_in, "si") == 0) {
        return true;
    }
    else {
        return false;
    }
}


#endif
