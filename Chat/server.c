#include "chat.h"
#include "list.h"
#include "server.h"

#define PORT 4000

USERNODE *userData;
ROOMNODE *roomsData;
MSG *buffer;
int totalUsers;

void readMessage(void *argSock) {
    int sendControl, newSock, *auxInt;
    int closeSocket = 0;
    USERNODE *newUser;

    auxInt = (int *) argSock;
    newSock = *auxInt;

    newUser = createUser(newSock);
    sprintf(buffer->message, "Welcome, %s! Write /help for commands\n\n", newUser->name);
    strcpy(buffer->userName, newUser->name);
    buffer->userID = newUser->id;
    write(newSock, buffer, sizeof(MSG));
    while(!closeSocket)
    {
      bzero(buffer, sizeof(MSG));
      printf("Fora %i\n", newSock);
      sendControl = read(newSock, buffer, sizeof(MSG));
      if (sendControl < 0)
          error("ERROR reading from socket");
      //processMessage();
      sendAllRoom();
      if(buffer->connected == -1)
        closeSocket = 1;
    }


    close(newSock);
    pthread_exit(NULL);
}

void processMessage()
{

}

void sendAllRoom()
{
  int room;
  USERNODE *user;
  USERNODE *current;

  user = getUserByID(userData, buffer->userID);
  room = user->roomID;

  current = userData;
  printf("Dentro %i\n", current->socket);
  while ((current != NULL))
  {
    if(current->roomID == room)
    {
      strcpy(buffer->userName, user->name);
      write(current->socket, buffer, sizeof(MSG));
      printf("Enviar %i, %s\n", current->socket, buffer->message);
    }
    current = current->next;
  }
  bzero(buffer, sizeof(MSG));
}

USERNODE *createUser(int socket)
{
  USERNODE *newUser;

  newUser = pushUser(userData, totalUsers, socket);
  sprintf(newUser->name, "User%i", newUser->id);
  totalUsers++;

  if(userData == NULL)
    userData = newUser;

  return newUser;
}

int main(int argc, char *argv[])
{
    int sock, newSock, sizeRemote;
    int k, i;
    int *threadArgs[5];
    pthread_t threads[5];
    struct sockaddr_in local, remote;

    buffer = malloc(sizeof(MSG));
    //userData = malloc(sizeof(USERNODE));
    roomsData = malloc(sizeof(ROOMNODE));
    totalUsers = 0;

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
