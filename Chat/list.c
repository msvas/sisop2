#include "chat.h"
#include "list.h"

NODE *push(NODE *head, MSG *msgChat) {
    NODE *current;
    
    if(head == NULL)
        head = malloc(sizeof(NODE));
    
    current = head;
    
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(NODE));
    current->next->msgChat = msgChat;
    current->next->next = NULL;
    
    return head;
}