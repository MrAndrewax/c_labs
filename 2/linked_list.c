
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int print_list(tNode* head){//I like it.
    if (head == NULL){
        printf("This list is empty.\n\n");
        return -1;
    }
    printf("List: ");
    tNode* current = head;
    while(current != NULL){
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n\n");
}

void InsertAtEnd(tNode* head, int new_value){
    tNode* current = head;

    while (current->next != NULL){ //äîõîäèì äî êîíöà. òåïåðü current ÿâëÿåòñÿ óêàçàòåëåì íà ïîñëåäíèé node
        current = current->next;
    }

    current->next = malloc(sizeof(tNode));//ñîçäà¸ì íîâûé íîóä
    current->next->val = new_value;
    current->next->next = NULL;
}

void InsertAtHead(tNode** pointer_to_head, int new_value){//òî æå ñàìîå ÷òî è push. ìíå íðàâèòñÿ.
    tNode* new_node = malloc(sizeof(tNode));
    new_node->next = *pointer_to_head;
    new_node->val = new_value;
    *pointer_to_head = new_node;
}

void InsertByIndex(tNode* head, int index, int new_value){//íàäî ñèëüíî ïîäóìàòü
    tNode* current = head;
    int i = 0;
    while(i<index){
        current = current->next;
        i++;
    }
    tNode* new_node = NULL;
    new_node = malloc(sizeof(tNode));
    new_node->next = NULL;
    new_node->val = new_value;
    new_node->next = current->next;
    current->next = new_node;
}

int Search(tNode* head, int index){//useless íî ìíå íðàâèòñÿ
    tNode* current = head;
    int i = 0;
    while(i<index){
        current = current->next;
        i++;
    }
    printf("%d\n", current->val);
    return current->val;
}


int isEmpty(tNode* head){//áàëä¸æ
    if (head == NULL) return 1;
    else return 0;
}


int DeleteAtHead(tNode** pointer_to_head){//âðîäå íðàâèòñÿ, íî íàäî åùå ïîäóìàòü...
    if((*pointer_to_head) == NULL){
        printf("This list is empty!");
        return -1;
    }
    int deleted_value = (*pointer_to_head)->val;
    tNode* tempNode = (*pointer_to_head)->next;
    free(*pointer_to_head);
    *pointer_to_head = tempNode;
    return deleted_value;
}

int DeleteAtEnd(tNode* head){//çà÷åì íî îê ïóñòü áóäåò ñëîæíîñòü Î(n)
    tNode* current = head;
    while(current->next->next != NULL){
        current = current->next;
    }
    int deleted_value = current->next->val;
    free(current->next);
    current->next = NULL;
    return deleted_value;
}

int Delete(tNode* head, int index){//ñîðè íî ëåíü äóìàòü
    tNode* current = head;
    int i = 0;
    while(i < index - 1){
        current = current->next;
        i++;
    }
    int deleted_value = current->next->val;
    tNode* tempNode = current->next->next;
    free(current->next);
    current->next = tempNode;
    printf("%d\n", deleted_value);
    return deleted_value;
}