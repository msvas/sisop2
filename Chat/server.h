#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void readMessage(void *argSock);
void sendAllRoom();
USERNODE *createUser(int socket);
int processMessage(int socket);
int joinRoom(char roomName[20]);
void createRoom(char roomName[20]);
