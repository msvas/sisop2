#ifndef COMMUNICATION_H_ 
#define COMMUNICATION_H_

#include <stdlib.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

typedef struct mBuffer
{
    int mtype;
    int lineResult[2];
} BUFFER;

int manageMQ(int cols);
void sendMessage(BUFFER postBox);
void rcvMessage(BUFFER *postBox);

#endif