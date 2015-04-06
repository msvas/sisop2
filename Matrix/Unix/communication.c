#include "communication.h"

int mqid;
BUFFER auxBuffer;

int manageMQ()
{
    key_t key;
    
    key = ftok(".", 'm');
    mqid = msgget(key, IPC_CREAT | 0644);

    return mqid;
}

void sendMessage(BUFFER postBox)
{
    auxBuffer.mtype = postBox.mtype;
    
    
    if(msgsnd(mqid, &auxBuffer, sizeof(BUFFER), 0)==-1) {
        printf("Oh dear, something went wrong! %s\n", strerror(errno));
    }
}

int *rcvMessage(int line)
{    
    //printf("%i\n", msgrcv(mqid, &auxBuffer, sizeof(auxBuffer), 0,  0));
    return auxBuffer.lineResult;
}