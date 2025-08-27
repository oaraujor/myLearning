#ifndef STATIC_QUEUE
#define STATIC_QUEUE

#include <stdio.h>

#define QUEUE_N 5

void insertSQueue(int *, int *, int );
int popSQueue(int *, int *, int * );



void insertSQueue(int * queue, int *front, int number) {
    if(*front >= QUEUE_N - 1) {
        printf("QUEUE IS FULL!\n");
    }
    else {
        (*front)++;
        *(queue + *front) = number;
    }
}

int popSQueue(int * queue, int *front, int * final){
    int number;

    if(*final > *front) {
        return -99999;
    }
    else {
        number = *(queue + *(final));
        (*final)++;
        return number;
    }
}

#endif

