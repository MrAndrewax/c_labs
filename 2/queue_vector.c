/*#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#define QMAX 100
#include "queue_vector.h"
//front – ïîçèöèÿ ïåðâîãî ýëåìåíòà â î÷åðåäè;
//rear – ïîçèöèÿ ïîñëåäíåãî ýëåìåíòà â î÷åðåäè
//Èçíà÷àëüíî front=1 è rear=0.
//Î÷åðåäü ïóñòà, åñëè rear<frnt.
//î÷åðåäü ïîëíà åñëè rear = QMAX - 1
void init(tQueue* queue){
  queue->front = 1;
  queue->rear = 0;
  return;
}
void push(tQueue *queue, Data new_value){
  if(queue->rear < QMAX-1) {
    queue->rear++;
    queue->qu[queue->rear] = new_value;
  }
  else printf("The queue is full!\n");
  return;
}
int isempty(tQueue* queue){
    if(queue->rear < queue->front)    return 1;
    else  return 0;
}
void print(tQueue *queue){
    if(isempty(queue)==1) {
        printf(" ");
        return;
    }
    else{
        //printf("Queue: ");
        for(int i = queue->front; i <= queue->rear; i++)
            printf("%c ",queue->qu[i]->name);
        return;
    }
}
Data pop(tQueue* queue){
    Data deleted_value;
    if(isempty(queue) == 1) return NULL;
    deleted_value = queue->qu[queue->front];
    queue->front++;
    return deleted_value;
}
Data get(tQueue* queue){
    Data value;
        if(isempty(queue) == 1) {
        return NULL;
    }
    value = queue->qu[queue->front];
    return value;
}
*/