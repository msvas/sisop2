#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

typedef struct msgBuffer_t {
    int userID;
    int connected;
    char userName[20];
    char message[140];
} MSG;
