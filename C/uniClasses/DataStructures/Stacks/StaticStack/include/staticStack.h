#ifndef STATIC_STACK
#define STATIC_STACK

#include <stdio.h>

#define STACK_N 5

void insertSstack(int *, int *, int);
int popSstack(int *, int *, int *);
void printSstack(int *, int *, int *);



void insertSstack(int * STACK, int *front, int number) {
    if(*front >= STACK_N - 1) {
        printf("STACK IS FULL!\n");
    }
    else {
        (*front)++;
        *(STACK + *front) = number;
    }
}

int popSstack(int *STACK, int *front, int *last) {
    int number;

    if (*front < *last) {
        return -99999; // flag
    }
    else {
        number = *(STACK + *front);
        (*front)--;
        return number;
    }
}

void printSstack(int *STACK, int *front, int *last) {
    int curr_place = 0, number;

    if (*front < *last) {
        printf("STACK IS EMPTY\n");
    }
    else {
        while (curr_place <= *front) {
            number = *(STACK + curr_place);
            printf("%d -> ", number);
            curr_place++;
        }
        printf("END OF STACK\n");
    }
}

#endif

