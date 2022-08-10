#include <stdio.h>
#include <stdlib.h>

//ñîáðàòü â áèáëèîòåêè
//makefile
//êîìïèëÿòîð gcc äëÿ windows

#include "queue_list.h"
void init(tQueue* queue){
    queue->head = NULL;
    queue->tail = NULL;
}

int isempty(tQueue* queue){
    if(queue->head == NULL) return 1;
    else return 0;
}




void deallocate(tQueue* queue){//ñäåëàòü òî æå ñàìîå ÷åðåç ðåêóðñèþ :D
    tNode** pointer_to_head = &queue->head;
    tNode* curr = *pointer_to_head;
    while (curr != NULL){
        tNode* aux = curr;//auxiliary - âñïîìîãàòåëüíûé;
        curr = curr->next;
        free(aux);
    }
    *pointer_to_head = NULL;
}

void push(tQueue* queue, Data new_data){
    tNode** pointer_to_head = &queue->head;
    tNode** pointer_to_tail = &queue->tail;
    if (*pointer_to_head == NULL){
        tNode* new_node = malloc(sizeof(tNode));
        new_node->next = NULL;
        new_node->data = new_data;
        *pointer_to_head = new_node;
        *pointer_to_tail = new_node;
    }
    else{
        tNode* new_node = malloc(sizeof(tNode));
        new_node->next = NULL;
        new_node->data = new_data;
        (*pointer_to_tail)->next = new_node;
        *pointer_to_tail = new_node;
    }
}
Data pop(tQueue* queue){
    tNode** pointer_to_head = &queue->head;
    tNode** pointer_to_tail = &queue->tail;
    if((*pointer_to_head) == NULL){
        return NULL;
    }
    Data deleted_value = (*pointer_to_head)->data;
    tNode* tempNode = (*pointer_to_head)->next;
    free(*pointer_to_head);
    *pointer_to_head = tempNode;

    if (*pointer_to_head == NULL) *pointer_to_tail = NULL;
    return deleted_value;
}

Data get(tQueue* queue){
    tNode** pointer_to_head = &queue->head;
    if((*pointer_to_head) == NULL){
        return NULL;
    }
    Data data = (*pointer_to_head)->data;
    return data;
}

void print(tQueue* queue){//I like it.
    tNode* head = queue->head;
    if (head == NULL){
        printf(" ");
        return;
    }
    tNode* current = head;
    while(current != NULL){
        printf("%c ", current->data->name);
        current = current->next;
    }
}
