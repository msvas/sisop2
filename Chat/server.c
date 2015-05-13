#include "chat.h"
#include "list.h"

#define PORT 4000

NODE *chatData;
MSG *buffer;

void readMessage(void *argSock) {
    int sendControl, newSock, *auxInt;
    
    auxInt = (int *) argSock;
    newSock = *auxInt;

    bzero(buffer, sizeof(MSG));
    
    sendControl = read(newSock, buffer, sizeof(MSG));
    if (sendControl < 0) 
        error("ERROR reading from socket");
    //printf("Here is the message: %s\n", buffer->message);
    
    chatData = push(chatData, buffer);
    
    close(newSock);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int sock, newSock, sizeRemote;
    int k, i;
    int *threadArgs[5];
    pthread_t threads[5];
    struct sockaddr_in local, remote;
    
    buffer = malloc(sizeof(MSG));
    
    for(i = 0; i < 5; i++) {
        threadArgs[i] = malloc(sizeof(int));
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error("socket");
    }
    
    local.sin_family = AF_INET;
    local.sin_port = AF_INET;
    local.sin_port = htons(PORT);
    local.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(sock, (struct sockaddr *)&local, sizeof(local)) == -1) {
        error("bind");
    }

    if (listen(sock, 5) == -1) {
        error("listen");
    }

    sizeRemote = sizeof(remote);
    
    i = 0;
    while (1) {
        newSock = accept(sock, (struct sockaddr *) &remote, &sizeRemote);
        bzero(buffer, sizeof(MSG));
        
        if (newSock < 0)
            error("ERROR on accept");
        
        *threadArgs[i % 5] = newSock;
        pthread_create(&threads[i % 5], NULL, readMessage, (void *) threadArgs[i % 5]);
        i++;
    }

    return 0;
}