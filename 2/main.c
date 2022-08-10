#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//noq == number_of_queues
//nop == number of people
#include "queue_list.h"

void print_the_person(tPerson p);
int getdata(int* p_noq, int* p_nop, tPerson** people);
int round_robin(int* arr, int len);


int main(){
    int noq = 0;
    int* p_noq = &noq;

    int nop = 0;
    int* p_nop = &nop;

    tPerson** people;//ïî ñóòè ÿ õî÷ó ñäåëàòü âåêòîð ñ óêàçàòåëÿìè íà ñàìè ñòðóêòóðû Person (÷òîáû èõ ìîæíî áûëî ìåíÿòü)
    /*people - ýòî ìàññèâ, ýëåìåíòû êîòîðîãî - ýòî óêàçàòåëè íà tPerson.*/
    people = (tPerson**) malloc(100*sizeof(tPerson*));//âûäåëÿåì ïàìÿòü íà ñòî ÷åëîâåê. ============================================================
    getdata(p_noq, p_nop, people);

    int qlen[noq]; //êîëè÷åñòâî ýëåìåíò â êàæäîé èç î÷åðåäåé
    for (int i = 0; i < noq; i++){//íà âñÿêèé ñëó÷àé çàïîëíþ íóëÿìè (âäðóã òàì ìóñîð)
        qlen[i] = 0;
    }
    tQueue** qarr;//âåêòîð, ýëåìåíòàìè êîòîðîãî ÿâëÿþòñÿ î÷åðåäè (à î÷åðåäè áóäóò ñîäåðæàòü óêàçàòåëè íà tPerson)
    qarr = (tQueue**) malloc(noq * sizeof(tQueue*));//âûäåëÿåì ïàìÿâòü ïîä ýòîò âåêòîð ============================================================
    for(int i=0;i <noq; i++){
        qarr[i] = (tQueue*) malloc(sizeof(tQueue));//============================================================
        init(qarr[i]);
    }
    //timecycle(people, qarr, qlen, nop, noq);


}
int getdata(int* p_noq, int* p_nop, tPerson** people){
    int temp_noq; //number of queue ÷èñëî î÷åðåäåé
    scanf("%d", &temp_noq);
    *p_noq = temp_noq;

    char string[100];//âñÿ ñòðîêà

    scanf("%[^\n]", string); //ñêàíèì äî êîíöà ñòðîêè
    char* perstr = strtok(string, " ");//äåëèì ïî ïðîáåëàì
    int nop = 0; //number_of_person
    char* array[100];//âåêòîð ñ ðàçáèòûìè ñòðîêàìè //vector_with_seperated_strings

    while(perstr != NULL){//äåëèì âñþ ñòðîêó ïî ïðîáåëàì è ïîëó÷èâøèåñÿ ñòðîêè çàïèõèâàåì â ìàññèâ array.
        array[nop] = perstr;
        perstr = strtok(NULL, " ");
        nop++;
    }//òóò ó íàñ åñòü nop

    for (int i = 0; i < nop; i++){
        people[i] = (tPerson*) malloc(sizeof(tPerson));//============================================================
    }

//    tPerson* people; //vector_with_people
    //people = (tPerson*) malloc(nop*sizeof(tPerson));

    for (int i = 0; i < nop; i++){//äåëèì ñòðîêè èç array ïî / è çàïèõèâàåì â person
        char* p_name = strtok(array[i], "/");
        char name = p_name[0];
        int arrival = atoi(strtok(NULL, "/"));
        int service = atoi(strtok(NULL, "/"));

        (*(people+i))->name = name;
        (*(people+i))->arrival = arrival;
        (*(people+i))->service = service;
    }

    for (int i = 0; i < nop; i++){
        print_the_person(**(people+i));
    }
    *p_nop = nop;
    return 0;
}
int round_robin(int* arr, int len){
    for (int i = 1; i < len; i++){
        if (arr[i] < arr[0]) return i;
    }
    return 0;
}
int timecycle(tPerson** people, tQueue** qarr, int qlen[], int nop, int noq){
    int current_time = 0;
    int change = 0;
    while(current_time < 100){
        for (int i = 0; i < nop; i++){
            if( (*(people+i))->arrival == current_time){
                change = 1;
                int j = round_robin(qlen, noq);
                //((*(people+i))->service)++;
                push(qarr[j], (*(people+i)));
                qlen[j]++;
            }
        }

        for(int i=0; i<noq; i++){            //åñëè ïåðâûé ýëåìåíò î÷åðåäè ðàâåí íóëè òî óäàëÿåì åãî, èíà÷å âû÷èòàåì åäèíè÷êó change = 1  //âû÷èòàåì åäèíè÷êó êàæäûé õîä èç ïåðâûõ ÷óâàêîâ â î÷åðåäÿõ
            tPerson* elem = get(qarr[i]);
            if (elem == NULL){
                continue;
            }
            else if ( elem->service == 0 ){
                pop(qarr[i]);
                change = 1;
            }
            else (elem->service)--;
        }



        if (change == 1){ //øîòà ïðèíòèì
            printf("Time: %d\n", current_time);
            for (int i = 0; i < noq; i++){
                printf("Queue%d ", i+1);
                print(qarr[i]);
                printf("\n");
            }
            printf("\n");
        }
        change = 0;
        current_time++;
    }
}
void print_the_person(tPerson p){printf("%c/%d/%d\n", p.name, p.arrival, p.service);}