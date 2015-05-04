#include "communication.h"

int mqid;

int manageMQ(int cols)
{
    key_t key;
    
    key = ftok("filename", 2);
    mqid = msgget(key, 0666 | IPC_CREAT);

    return mqid;
}

void sendMessage(BUFFER postBox)
{  
    //printf("Enviado: %i (%i, %i)\n", postBox.mtype, postBox.lineResult[0], postBox.lineResult[1]);
    if(msgsnd(mqid, &postBox, sizeof(BUFFER), 0)==-1) {
        printf("Oh dear, something went wrong! %s\n", strerror(errno));
    }
    /*if(msgrcv(mqid, &auxBuffer, 10000, 0,  0)==-1) {
        printf("Oh dear, something went wrong! %s\n", strerror(errno));
    }*/       
    
}

void rcvMessage(BUFFER *postBox)
{   
    if(msgrcv(mqid, postBox, sizeof(BUFFER), 0,  0)==-1) {
        printf("Oh dear, something went wrong! %s\n", strerror(errno));
    }
    //printf("Recebido: %i (%i, %i)\n", postBox->mtype, postBox->lineResult[0], postBox->lineResult[1]);
}



