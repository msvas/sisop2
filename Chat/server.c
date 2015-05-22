#include "chat.h"
#include "list.h"
#include "server.h"

#define PORT 4000

USERNODE *userData;
ROOMNODE *roomsData;
MSG *buffer;
int totalUsers, totalRooms;

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
      if(buffer->connected == -1)
          closeSocket = 1;
      else {
        if(!processMessage(newSock))
          sendAllRoom();
      }
    }


    close(newSock);
    pthread_exit(NULL);
}

int processMessage(int socket)
{
  char auxString[20];
  USERNODE *user;

  if(strstr(buffer->message, "/help") != NULL) {
    strcpy(buffer->userName, "Help");
    sprintf(buffer->message, "'/join roomname' - joins a room called 'roomname' \n(creates one if the name does not exist)");
    write(socket, buffer, sizeof(MSG));
    strcpy(buffer->userName, "Help");
    sprintf(buffer->message, "'/username newname' - changes user name to 'newname'");
    write(socket, buffer, sizeof(MSG));
    return 1;
  } else if(strstr(buffer->message, "/join ") != NULL) {
    strtok(buffer->message, " ");
    strcpy(auxString, strtok(NULL, " "));
    if(!joinRoom(auxString)) {
      createRoom(auxString);
      strcpy(buffer->userName, "Created room");
      sprintf(buffer->message, "%s", auxString);
      write(socket, buffer, sizeof(MSG));
    } else {
      strcpy(buffer->userName, "Joined room");
      sprintf(buffer->message, "%s\nSay hi!", auxString);
      write(socket, buffer, sizeof(MSG));
    }
    return 1;
  } else if(strstr(buffer->message, "/username ") != NULL) {
    strtok(buffer->message, " ");
    strcpy(auxString, strtok(NULL, " "));
    user = getUserByID(userData, buffer->userID);
    strcpy(user->name, auxString);
    strcpy(buffer->userName, "Name changed to");
    sprintf(buffer->message, "%s", auxString);
    write(socket, buffer, sizeof(MSG));
    return 1;
  }
  return 0;
}

int joinRoom(char roomName[20])
{
  ROOMNODE *room;
  USERNODE *user;

  room = getRoomByName(roomsData, roomName);
  if(room != NULL) {
    user = getUserByID(userData, buffer->userID);
    user->roomID = room->id;
    return 1;
  } else {
    return 0;
  }
}

void createRoom(char roomName[20])
{
  ROOMNODE *room;
  USERNODE *user;

  room = pushRoom(roomsData, totalRooms, roomName);
  user = getUserByID(userData, buffer->userID);
  user->roomID = room->id;
  totalRooms++;
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
    totalUsers = 0;
    totalRooms = 0;
    roomsData = pushRoom(roomsData, totalRooms, "");
    totalRooms++;

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
