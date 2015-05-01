#include "philosophers.h"

pthread_cond_t *conditions;
phil_state_t *philStates;
pthread_mutex_t mutex, monitor;
THREAD_DATA *threadParams;
int totalPhils;

int handlePhils(int n)
{
    //THREAD_DATA threadParams[n];
    pthread_t philosophers[n];
    int i;
    
    conditions = malloc(sizeof(pthread_cond_t) * n);
    philStates = malloc(sizeof(phil_state_t) * n);
    threadParams = malloc(sizeof(THREAD_DATA) * n);
    totalPhils = n;
    
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&monitor, NULL);
    
    for(i = 0; i < n; i++)
    {
        pthread_cond_init(&conditions[i], NULL);
        threadParams[i].conditions = conditions;
        threadParams[i].philId = i;
        threadParams[i].philStates = philStates;
        philStates[i] = THINKING;
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
    
    threadParams->philStates[thisId] = THINKING;
    //printf("%i\n", threadParams->philId);
    
    
    while (1)
    {
        seconds = (rand() % 10) + 1;
        printStates();
        //printf("%i\n", seconds); 
        switch (threadParams->philStates[thisId])
        {
            case EATING:
                //printf("1\n");
                sleep(seconds);
                threadParams->philStates[thisId] = (rand() % 2) + 1;
                pthread_mutex_lock(&monitor);
                freeForks(thisId);
                pthread_mutex_unlock(&monitor);
                break;
            case THINKING:
                //printf("2\n");
                sleep(seconds);
                threadParams->philStates[thisId] = (rand() % 2) + 1;
                break;
            case HUNGRY:
                //printf("3\n");
                pthread_mutex_lock(&monitor);
                getForks(thisId);
                pthread_mutex_unlock(&monitor);
                break;
        }
    }
    pthread_exit(NULL);
}

int checkForks(int i) 
{
    if(philStates[i] == HUNGRY)
    {
        if(philStates[(i + 1) % totalPhils] != EATING)
        {
            if(philStates[(i - 1 + totalPhils) % totalPhils] != EATING)
            {
                philStates[i] = EATING;
                pthread_cond_signal(&conditions[i]);
                return 1;
            }
        }
    }

    return 0;
}


void getForks(int thisId)
{
    if(!checkForks(thisId)) 
    {
        pthread_cond_wait(&conditions[thisId], &monitor);
    }
}

void freeForks(int thisId)
{
    checkForks((thisId - 1 + totalPhils) % totalPhils);
    checkForks((thisId + 1) % totalPhils);
}

void printStates()
{
    int i, totalE = 0;
    
    pthread_mutex_lock(&mutex);
    for(i = 0; i < totalPhils; i++)
    {
        switch (philStates[i])
        {
            case EATING:
                totalE++;
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
    //printf("%i", totalE);
    printf("\n");
    pthread_mutex_unlock(&mutex);
}


int main (int argc, char *argv[])
{
    handlePhils(atoi(argv[argc-1]));
    return 0;
}