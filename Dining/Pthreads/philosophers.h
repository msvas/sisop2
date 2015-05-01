#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef enum {
    EATING = 0, 
    THINKING = 1, 
    HUNGRY = 2
} phil_state_t;

typedef struct thread_data {
    int philId;
    phil_state_t *philStates;
    pthread_cond_t *conditions;
} THREAD_DATA;

int handlePhils(int n);
void *philActions(void *threadarg);
void printStates();
int checkForks(int i);
void getForks(int thisId);
void freeForks(int thisId);