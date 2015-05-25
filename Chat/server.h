#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <semaphore.h>

typedef struct thread_data{
   int  socket;
   MSG *buffer;
} MSGBUFFER;

void readMessage(void *argSock);
void sendAllRoom(MSG *buffer);
USERNODE *createUser(int socket);
int processMessage(int socket, MSG *buffer);
int joinRoom(char roomName[20], MSG *buffer);
void createRoom(char roomName[20], MSG *buffer);
void getAllMsgs(int roomID, int socket, MSG *buffer);
