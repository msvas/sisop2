#include "philosophers.h"

sem_t *chopsticks;
pthread_mutex_t mutex;
THREAD_DATA *threadParams;
int totalPhils;

int handlePhils(int n)
{
    //THREAD_DATA threadParams[n];
    pthread_t philosophers[n];
    int i;
    
    chopsticks = malloc(sizeof(sem_t) * n);
    threadParams = malloc(sizeof(THREAD_DATA) * n);
    totalPhils = n;
    
    pthread_mutex_init(&mutex, NULL);
    
    for(i = 0; i < n; i++)
    {
        sem_init(&chopsticks[i], 0, 1);
        threadParams[i].chopsticks = chopsticks;
        threadParams[i].philId = i;
        threadParams[i].philState = THINKING;
        //printf("%i\n", threadParams[n].philId);
    }
    
    for(i = 0; i < n; i++)
    {
        pthread_create(&philosophers[i], NULL, philActions, (void *) &threadParams[i]);
    }
    
    for(i = 0; i < n; i++)
    {
        pthread_join(philosophers[i], NULL);
    }
}

void *philActions(void *threadarg)
{
    int thisId, seconds;
    THREAD_DATA *threadParams;
    
    threadParams = (THREAD_DATA *) threadarg;
    thisId = threadParams->philId;
    
    threadParams->philState = (rand() % 2) + 1;
    //printf("%i\n", threadParams->philId);
    
    
    while (1)
    {
        seconds = (rand() % 10) + 1;
        printStates();
        //printf("%i\n", seconds); 
        switch (threadParams->philState)
        {
            case EATING:
                //printf("1\n");
                sleep(seconds);
                sem_post(&(threadParams->chopsticks[thisId]));
                sem_post(&(threadParams->chopsticks[(thisId + 1) % 5]));
                threadParams->philState = (rand() % 2) + 1;
                break;
            case THINKING:
                //printf("2\n");
                sleep(seconds);
                threadParams->philState = (rand() % 2) + 1;
                break;
            case HUNGRY:
                //printf("3\n");
                sem_wait(&(threadParams->chopsticks[thisId]));
                sem_wait(&(threadParams->chopsticks[(thisId + 1) % 5]));
                threadParams->philState = EATING;
                break;
        }
    }
    pthread_exit(NULL);
}

void printStates()
{
    int i;
    
    pthread_mutex_lock(&mutex);
    for(i = 0; i < totalPhils; i++)
    {
        switch (threadParams[i].philState)
        {
            case EATING:
                printf("E ");
                break;
            case THINKING:
                printf("T ");
                break;
            case HUNGRY:
                printf("H ");
                break;
        }
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
}


int main()
{
    handlePhils(5);
    return 0;
}