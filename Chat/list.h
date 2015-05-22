#include <stdio.h>
#include <stdlib.h>

typedef struct userNode {
    int id;
    int roomID;
    int socket;
    char name[20];
    struct userNode *next;
} USERNODE;

typedef struct roomNode {
    int id;
    char name[20];
    struct roomNode *next;
} ROOMNODE;

typedef struct msgNode {
    MSG *msgChat;
    USERNODE *user;
    ROOMNODE *room;
    struct msgNode *next;
} MSGNODE;

ROOMNODE *pushRoom(ROOMNODE *head, int id, char roomName[20]);
MSGNODE *pushMsg(MSGNODE *head, MSG *msgChat);
USERNODE *pushUser(USERNODE *head, int id, int socket);
ROOMNODE *getRoomByID(ROOMNODE *head, int id);
USERNODE *getUserByID(USERNODE *head, int id);
ROOMNODE *getRoomByName(ROOMNODE *head, char roomName[20]);
