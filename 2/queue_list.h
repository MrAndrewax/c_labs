#ifndef QUEUE_LIST_H_INCLUDED
#define QUEUE_LIST_H_INCLUDED

typedef struct Person{
    char name;
    int arrival;
    int service;
} tPerson;

typedef tPerson* Data;

typedef struct Node{//ÿ÷åéêà
    struct Node* next; //óêàçàòåëü íà ñëåäóþùóþ ÿ÷åéêó
    Data data;// çíà÷åíèå ÿ÷åéêè (value)
}tNode;

typedef struct Queue{
    tNode* head;
    tNode* tail;
} tQueue;



void init(tQueue*);
void push(tQueue*, Data);
int isempty(tQueue*);
void print(tQueue*);
Data pop(tQueue*);
Data get(tQueue*);
#endif // QUEUE_LIST_H_INCLUDED