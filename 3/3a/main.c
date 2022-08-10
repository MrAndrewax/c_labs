#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 16

//всё идеально, не ломай

typedef char* Data;//data - строка
typedef char* KeyType1;
typedef struct KeySpace1 PointerType1;

typedef struct Item {
    Data data;
    KeyType1 key1;
    PointerType1* p1;
} Item;

typedef struct KeySpace1{
    KeyType1 key1;
    struct Item* item;
    struct KeySpace1* next;
} KeySpace1;


typedef struct Table{
    KeySpace1* ks1;
    int msize1;
} Table;

int search1(Table* table, char* key1);
int add(Table* table, KeyType1 key1, Data data);
int delete(Table* table, KeyType1 key1);
int freeTable(Table* table);
int printTable1(Table* table);
Table* specSearch(Table* table, KeyType1 firstKey, KeyType1 lastKey);

int search1(Table* table, char* key1){//верни указатель.
    int index = 1;
    for(KeySpace1* curr = table->ks1; curr != NULL; curr = curr->next){
        if (strncmp(curr->key1, key1, MAX_STR) == 0){
            return index;
        }
        index++;
    }
    return 0;
}

char* searchMenu(Table* table, char* key1){
    for(KeySpace1* curr = table->ks1; curr != NULL; curr = curr->next){
        if (strncmp(curr->key1, key1, MAX_STR) == 0){
            char* result = malloc(sizeof(char)*MAX_STR);
            strcpy(result, curr->item->data);
            return result;
        }
    }
    return NULL;
}

int add(Table *table, KeyType1 key1, Data data) {

    if (search1(table, key1) != 0)  return -1;
    KeySpace1* newNode = malloc(sizeof(KeySpace1));//создали нод

    Item* pItem = malloc(sizeof(Item));
    pItem->data = malloc(MAX_STR*sizeof(char)); strcpy(pItem->data, data);
    pItem->key1 = malloc(MAX_STR*sizeof(char)); strcpy(pItem->key1, key1);

    PointerType1* p1 = newNode;
    pItem->p1 = p1;

    newNode->item = pItem;
    newNode->key1 = malloc(sizeof(KeyType1)); strcpy(newNode->key1, key1);
    newNode->next = table->ks1;
    table->ks1 = newNode;
    return 0;
}

int printTable1(Table* table){
    printf("\n\t\tPrinting table as 1\n");
    printf("Start***************************\n\n");

    for(KeySpace1* curr = table->ks1; curr != NULL; curr = curr->next){
        printf("Key1: %s\tData: %s\n", curr->key1, /*(*(curr->item->p2)).key,*/ curr->item->data);
        printf("\n\n");
    }

    printf("End***************************\n\n");
    return 0;
}

int freeTable(Table* table){
    KeySpace1* curr = table->ks1;
    KeySpace1* temp;
    while (curr != NULL) {
        temp = curr;
        curr = curr->next;
        free(temp->item->data);
        free(temp->item->key1);
        free(temp->item);
        free(temp->key1);
        free(temp);
    }
    free(table);
    return 0;
}

int delete(Table* table, KeyType1 key1){
    int position = search1(table, key1);//position - Это НАТУРАЛЬНЫЙ номер нода в списке.
    if (position == 0){
        printf("Элемента с ключом %s в таблице нет :(", key1);
        return 0;
    }
    else if (strncmp(table->ks1->key1, key1, MAX_STR) == 0){
        KeySpace1* temp = table->ks1->next;

        free(table->ks1->item->data);
        free(table->ks1->item->key1);
        free(table->ks1->item);

        free(table->ks1->key1);
        free(table->ks1);
        table->ks1 = temp;

        return 1;
    }
    else{
        KeySpace1* curKS1 = table->ks1; //начиная с самого первого нода, пройдёмся по всем, пока не найдём тот, который нужно удалить.
        while (strncmp(curKS1->next->key1, key1, MAX_STR) != 0) curKS1=curKS1->next;
        KeySpace1* tempKS1 = curKS1->next;
        curKS1->next = curKS1->next->next;

        free(tempKS1->item->data);
        free(tempKS1->item->key1);
        free(tempKS1->item);
        free(tempKS1->key1);
        free(tempKS1);
        return 1;
    }
    return 404;
}

Table* specSearch(Table* table, KeyType1 firstKey, KeyType1 lastKey){

    if (strncmp(firstKey, lastKey, MAX_STR) > 0) return NULL;
    else if (strncmp(firstKey, lastKey, MAX_STR) == 0) return NULL;

    Table* newTable = malloc(sizeof(KeySpace1));
    newTable->ks1 = NULL;
    KeySpace1* curr = table->ks1;
    printf("%s %s", firstKey, lastKey);
    while(curr != NULL){
        //printf("Current key: %s\tСравнение с первым:%d\tСравнение со вторым: %d\n", curr->key1, strncmp(curr->key1, firstKey, MAX_STR), strncmp(curr->key1, lastKey, MAX_STR));
        if ( (strncmp(curr->key1, firstKey, MAX_STR) > 0) && (strncmp(curr->key1, lastKey, MAX_STR) < 0)){
            printf("%s - добавлен\n",  curr->key1);

            Item *pItem = malloc(sizeof(Item));
            pItem->data = malloc(MAX_STR*sizeof(char)); strcpy(pItem->data, curr->item->data);
            pItem->key1 = malloc(MAX_STR*sizeof(char));
            KeySpace1* newNode = malloc(sizeof(KeySpace1));
            pItem->p1 = newNode;
            newNode->key1 = malloc(sizeof(KeyType1)); strcpy(newNode->key1, curr->key1);
            newNode->item = pItem;
            newNode->next = newTable->ks1;
            newTable->ks1 = newNode;
        }
        curr = curr->next;
    }
    return newTable;
}



void fastAdd(Table* table){
    add(table, "ke11", "inf1");
    add(table, "ke12", "inf2");
    add(table, "ke12", "inf2q");
    add(table, "ke12", "inf2w");
    add(table, "ke12", "inf2e");
    add(table, "ke12", "inf23");
    add(table, "ke13", "inf3");
    add(table, "ke14", "inf4");
    add(table, "key15", "inf5");
    add(table, "key16", "inf6");
    add(table, "key17", "inf7");
    add(table, "key17", "inf71");
    add(table, "key17", "inf7");
    add(table, "key17", "inf73");
}


void printMenu(){
    printf("\nЧто изволите, сударь?\n");
    printf("1. включение нового элемента в таблицу\n");
    printf("2. поиск в таблице элемента\n");
    printf("3. удаление из таблицы элемента\n");
    printf("4. суперхакерский поиск(specsearch)\n");
    printf("6. вывод содержимого таблицы на экран\n");
    printf("404. Очистить экран\n");
    printf("0. Завершение программы\n");
    printf(">");

}

void Menu(Table* table){
    int choice;
    int error;
    char* searchedString;

    KeyType1 key1;
    KeyType1 key2;
    Data data;
    int AddChecker;
    int DeleteChecker;
    char* SearchCheck;
    do {
        printMenu();
        scanf("%d", &choice);
        if (choice == 1){
            key1 = malloc(MAX_STR*sizeof(char));
            data = malloc(MAX_STR*sizeof(char));
            printf("Введите ключ\n>");
            scanf("%s", key1);
            printf("Введите информацию\n>");
            scanf("%s", data);
            AddChecker = add(table, key1, data);
            if (AddChecker == 0) printf("Элемент %s %s добавлен\n\n", key1, data);
            free(key1);
            free(data);
        }
        else if(choice == 2) {
            key1 = malloc(MAX_STR*sizeof(char));
            printf("Введите ключ\n>");
            scanf("%s", key1);
            SearchCheck = searchMenu(table, key1);
            if (SearchCheck == NULL){
                printf("Элемент с таким ключом не найден \n");
            }
            else{
                printf("Элемент с таким ключом найден! Вот же он: %s\n", SearchCheck);
                free(SearchCheck);
            }
            free(key1);

        }
        else if(choice == 3){
            key1 = malloc(MAX_STR*sizeof(char));
            printf("Введите ключ\n>");
            scanf("%s", key1);

            DeleteChecker = delete(table, key1);
            if (DeleteChecker == 1){
                printf("Элемент был успешно удалён\n\n");
            }
            else printf("Такого элемента и нет в таблице\n\n");
            free(key1);
        }
        else if(choice == 4){
            key1 = malloc(MAX_STR*sizeof(char));
            key2 = malloc(MAX_STR*sizeof(char));

            printf("Введите первый ключ\n>");
            scanf("%s", key1);
            printf("Введите второй ключ\n>");
            scanf("%s", key2);

            Table* newTable = specSearch(table, key1, key2);
            if (newTable == NULL){
                printf("Первый ключ должен быть \"меньше\" первого!!!\n");
                free(key1);
                free(key2);
            }
            else{
                printTable1(newTable);
                freeTable(newTable);
                free(key1);
                free(key2);
            }
        }
        else if(choice == 6){
            printTable1(table);
        }
        else if(choice == 404){
            printf("\033c");
        }
        else if(choice == 505){
            add(table, "ke11", "inf1");
            add(table, "ke12", "inf2");
            add(table, "ke13", "inf3");
            add(table, "ke14", "inf4");
            add(table, "key15", "inf5");
            add(table, "key16", "inf6");
            add(table, "key17", "inf7");
        }
        else if(choice == 506){
            add(table, "same", "safinf1");
            add(table, "same", "inasff2");
            add(table, "same", "inf3asf");
            add(table, "same", "inf4af");
            add(table, "sam5", "infasfasf5");
            add(table, "same6", "inf6asfasf");
            add(table, "same", "iasfasfnf7");
        }
    } while (choice != 0);
    printf("The program was stopped");
}

int main() {

    Table* table = malloc(sizeof(Table));
    table->ks1 = NULL;
    Menu(table);
    freeTable(table);
    return 0;
}
