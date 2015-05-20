#include <stdio.h>
#include <stdlib.h>

typedef struct userNode {
    int id;
    char name[20];
    struct userNode *next;
    struct userNode *sameRoom;
} USERNODE;

typedef struct roomNode {
    int id;
    USERNODE *userList;
    struct roomNode *next;
} ROOMNODE;

typedef struct msgNode {
    MSG *msgChat;
    USERNODE *user;
    ROOMNODE *room;
    struct msgNode *next;
} MSGNODE;

ROOMNODE *pushRoom(ROOMNODE *head, int id);
MSGNODE *pushMsg(MSGNODE *head, MSG *msgChat);
USERNODE *pushUser(USERNODE *head, int id);
ROOMNODE *getRoomByID(ROOMNODE *head, int id);
