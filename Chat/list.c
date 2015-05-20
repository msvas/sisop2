#include "chat.h"
#include "list.h"

MSGNODE *pushMsg(MSGNODE *head, MSG *msgChat) {
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

ROOMNODE *pushRoom(ROOMNODE *head, int id) {
  ROOMNODE *current;

    if(head == NULL)
        head = malloc(sizeof(ROOMNODE));

    current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(ROOMNODE));
    current->next->id = id;
    current->next->next = NULL;

    return head;
}

USERNODE *pushUser(USERNODE *head, int id, int socket) {
  USERNODE *current;

    if(head == NULL)
        head = malloc(sizeof(USERNODE));

    current = head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(USERNODE));
    current->next->id = id;
    current->next->socket = socket;
    current->next->roomID = 0;
    current->next->next = NULL;

    return head;
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
