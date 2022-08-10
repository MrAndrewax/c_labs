

#ifndef QUEUE_VECTOR_H_INCLUDED
#define QUEUE_VECTOR_H_INCLUDED

typedef struct Person{
    char name;
    int arrival;
    int service;
} tPerson;

typedef tPerson* Data;
//ifdef
typedef struct Queue{
    Data qu[100];//âûäåëåíèå äèíàìè÷åñêîé ïàìÿòè
    int rear;
    int front;
} tQueue;
//ñòðóòóðó âûíåñè â ñèøíûé ôàéë
void init(tQueue*);
void push(tQueue*, Data);
int isempty(tQueue*);
void print(tQueue*);
Data pop(tQueue*);
Data get(tQueue*);
#endif // QUEUE_VECTOR_H_INCLUDED