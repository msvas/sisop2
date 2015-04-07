#include "communication.h"

int mqid;
BUFFER auxBuffer;

int manageMQ(int cols)
{
    key_t key;
    
    key = ftok("filename", 2);
    mqid = msgget(key, 0666 | IPC_CREAT);
    
    (auxBuffer.lineResult) = malloc(cols * sizeof(int));

    return mqid;
}

void sendMessage(BUFFER postBox)
{  
    printf("Enviado: %i, %i\n", *(postBox.lineResult), postBox.mtype);
    memcpy(auxBuffer.lineResult, postBox.lineResult, 3*sizeof(int));
    auxBuffer.mtype = postBox.mtype;
    if(msgsnd(mqid, &auxBuffer, 3*sizeof(int), 0)==-1) {
        printf("Oh dear, something went wrong! %s\n", strerror(errno));
    }
    /*if(msgrcv(mqid, &auxBuffer, 10000, 0,  0)==-1) {
        printf("Oh dear, something went wrong! %s\n", strerror(errno));
    }*/       
    
}

int *rcvMessage(int line, BUFFER postBox, int cols)
{        
    //auxBuffer.lineResult = malloc(cols * sizeof(int));
    if(msgrcv(mqid, &auxBuffer, 3*sizeof(int), 0,  0)==-1) {
        printf("Oh dear, something went wrong! %s\n", strerror(errno));
    }
    //msgrcv(mqid, &auxBuffer, sizeof(*(auxBuffer.lineResult)), 0,  0);
    printf("Recebido: %i, %i\n", *(auxBuffer.lineResult), auxBuffer.mtype);
    return auxBuffer.lineResult;
}