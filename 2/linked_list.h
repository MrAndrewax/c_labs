
#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

typedef struct Node{//ÿ÷åéêà
    struct Node* next; //óêàçàòåëü íà ñëåäóþùóþ ÿ÷åéêó
    int val;// çíà÷åíèå ÿ÷åéêè (value)
}tNode;

int print_list(tNode*);//ãîòîâî
void InsertAtEnd(tNode*, int);
void InsertAtHead(tNode**, int);
void InsertByIndex(tNode*, int, int);
int DeleteAtHead(tNode**);
int DeleteAtEnd(tNode*);
int Delete();
int Search();
int isEmpty();

#endif // LINKED_LIST_H_INCLUDED