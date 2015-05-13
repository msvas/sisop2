#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    MSG *msgChat;
    struct node *next;
} NODE;

NODE *push(NODE *head, MSG *msgChat);