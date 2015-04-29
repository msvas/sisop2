#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

typedef enum {
    EATING = 0, 
    THINKING = 1, 
    HUNGRY = 2
} phil_state_t;

typedef struct thread_data {
    int philId;
    phil_state_t philState;
    sem_t *chopsticks;
} THREAD_DATA;

int handlePhils(int n);
void *philActions(void *threadarg);
void printStates();