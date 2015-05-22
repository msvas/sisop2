#include "chat.h"
#include "list.h"

MSGNODE *pushMsg(MSGNODE *head, MSG *msgChat, USERNODE *user, ROOMNODE *room); {
  MSGNODE *current;

    if(head == NULL)
        head = malloc(sizeof(MSGNODE));

    current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(MSGNODE));
    current->next->msgChat = msgChat;
    current->next->next = NULL;

    return head;
}

ROOMNODE *pushRoom(ROOMNODE *head, int id, char roomName[20]) {
  ROOMNODE *current;

    if(head == NULL) {
        head = malloc(sizeof(ROOMNODE));
        head->id = id;
        strcpy(head->name, roomName);
        head->next = NULL;
        current = head;
    }
    else {
      current = head;

      while (current->next != NULL) {
          current = current->next;
      }

      current->next = malloc(sizeof(ROOMNODE));
      current->next->id = id;
      strcpy(current->next->name, roomName);
      current->next->next = NULL;
      current = current->next;
    }

    return current;
}

USERNODE *pushUser(USERNODE *head, int id, int socket) {
  USERNODE *current;

    if(head == NULL) {
      head = malloc(sizeof(USERNODE));
      head->id = id;
      head->socket = socket;
      head->roomID = 0;
      head->next = NULL;
      current = head;
    }
    else {
      current = head;

      while (current->next != NULL) {
          current = current->next;
      }

      current->next = malloc(sizeof(USERNODE));
      current->next->id = id;
      current->next->socket = socket;
      current->next->roomID = 0;
      current->next->next = NULL;
      current = current->next;
      //printf("Created user with id %i and socket %i\n", current->next->id, current->next->socket);
    }

    return current;
}

ROOMNODE *getRoomByID(ROOMNODE *head, int id) {
  ROOMNODE *current;

    if(head == NULL)
        return NULL;

    current = head;

    while ((current->next != NULL) && (current->id != id)) {
        current = current->next;
    }

    return current;
}

USERNODE *getUserByID(USERNODE *head, int id) {
  USERNODE *current;

    if(head == NULL)
        return NULL;

    current = head;

    while ((current->next != NULL) && (current->id != id)) {
        current = current->next;
    }

    return current;
}

ROOMNODE *getRoomByName(ROOMNODE *head, char roomName[20]) {
  ROOMNODE *current;

    if(head == NULL)
        return NULL;

    current = head;

    while (current != NULL) {
      if(strcmp(roomName, current->name) == 0)
        return current;
      current = current->next;
    }

    return NULL;
}
