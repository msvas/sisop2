#include "chat.h"
#include "list.h"
#include "server.h"

#define PORT 4000

USERNODE *userData;
ROOMNODE *roomsData;
MSGNODE *msgData;
int totalUsers, totalRooms;
sem_t userSem, roomsSem, msgSem;

void readMessage(void *argSock) {
    int sendControl, newSock;
    int closeSocket = 0;
    MSGBUFFER *auxBuff;
    MSG *buffer;
    USERNODE *newUser;

    auxBuff = (MSGBUFFER *) argSock;
    newSock = auxBuff->socket;
    buffer = auxBuff->buffer;

    sem_wait(&userSem);
    newUser = createUser(newSock);
    sprintf(buffer->message, "Welcome, %s! Write /help for commands\n\n", newUser->name);
    strcpy(buffer->userName, newUser->name);
    buffer->userID = newUser->id;
    sem_post(&userSem);
    write(newSock, buffer, sizeof(MSG));
    bzero(buffer, sizeof(MSG));
    while(!closeSocket)
    {
      bzero(buffer, sizeof(MSG));
      sendControl = read(newSock, buffer, sizeof(MSG));
      if (sendControl < 0)
          error("ERROR reading from socket");
      if(buffer->connected == -1)
          closeSocket = 1;
      else {
        if(!processMessage(newSock, buffer))
          sendAllRoom(buffer);
      }
    }

    close(newSock);
    pthread_exit(NULL);
}

int processMessage(int socket, MSG *buffer)
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
    if(!joinRoom(auxString, buffer)) {
      createRoom(auxString, buffer);
      strcpy(buffer->userName, "Created room");
      sprintf(buffer->message, "%s", auxString);
      write(socket, buffer, sizeof(MSG));
    }
    return 1;
  } else if(strstr(buffer->message, "/username ") != NULL) {
    strtok(buffer->message, " ");
    strcpy(auxString, strtok(NULL, " "));
    sem_wait(&userSem);
    user = getUserByID(userData, buffer->userID);
    strcpy(user->name, auxString);
    strcpy(buffer->userName, "Name changed to");
    sprintf(buffer->message, "%s", auxString);
    sem_post(&userSem);
    write(socket, buffer, sizeof(MSG));
    return 1;
  }
  return 0;
}

int joinRoom(char roomName[20], MSG *buffer)
{
  ROOMNODE *room;
  USERNODE *user;

  sem_wait(&roomsSem);
  room = getRoomByName(roomsData, roomName);
  if(room != NULL) {
    sem_wait(&userSem);
    user = getUserByID(userData, buffer->userID);
    strcpy(buffer->userName, "Joined room");
    sprintf(buffer->message, "%s\nSay hi!", roomName);
    write(user->socket, buffer, sizeof(MSG));
    user->roomID = room->id;
    getAllMsgs(room->id, user->socket, buffer);
    sem_post(&roomsSem);
    sem_post(&userSem);
    return 1;
  } else {
    sem_post(&roomsSem);
    return 0;
  }
}

void getAllMsgs(int roomID, int socket, MSG *buffer)
{
  MSGNODE *current;

  sem_wait(&msgSem);
  current = msgData;

  while ((current != NULL))
  {
    if(current->roomID == roomID)
    {
      memcpy(buffer, current->msgChat, sizeof(MSG));
      write(socket, buffer, sizeof(MSG));
    }
    current = current->next;
  }
  sem_post(&msgSem);
}

void createRoom(char roomName[20], MSG *buffer)
{
  ROOMNODE *room;
  USERNODE *user;

  sem_wait(&roomsSem);
  room = pushRoom(roomsData, totalRooms, roomName);
  sem_wait(&userSem);
  user = getUserByID(userData, buffer->userID);
  user->roomID = room->id;
  sem_post(&userSem);
  totalRooms++;
  sem_post(&roomsSem);
}

void sendAllRoom(MSG *buffer)
{
  int room;
  USERNODE *user;
  USERNODE *current;

  sem_wait(&userSem);
  user = getUserByID(userData, buffer->userID);
  room = user->roomID;

  sem_wait(&msgSem);
  strcpy(buffer->userName, user->name);
  msgData = pushMsg(msgData, buffer, user, room);
  sem_post(&msgSem);

  current = userData;
  while ((current != NULL))
  {
    if(current->roomID == room)
    {
      write(current->socket, buffer, sizeof(MSG));
    }
    current = current->next;
  }
  sem_post(&userSem);
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
    pthread_t threads[5];
    MSGBUFFER threadArgs[5];
    struct sockaddr_in local, remote;

    sem_init(&msgSem, 0, 1);
    sem_init(&userSem, 0, 1);
    sem_init(&roomsSem, 0, 1);
    totalUsers = 0;
    totalRooms = 0;
    roomsData = pushRoom(roomsData, totalRooms, "");
    totalRooms++;

    for(i = 0; i < 5; i++) {
        threadArgs[i].buffer = malloc(sizeof(MSG));
        bzero(threadArgs[i].buffer, sizeof(MSG));
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

        if (newSock < 0)
            error("ERROR on accept");

        threadArgs[i % 5].socket = newSock;
        pthread_create(&threads[i % 5], NULL, readMessage, (void *) &threadArgs[i % 5]);
        i++;
    }

    return 0;
}
