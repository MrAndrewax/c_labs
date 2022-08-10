#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//у меня был некрасивый add (элемент равный первому неправильно добавлялся) +
//что такое прямой порядок следования ключей +
//надо убрать ограничение на длину строки в функции getStr +
//добавить обработку ctrl c
//короче нужен безопасный ввод


typedef struct String{
    char* str;
    int len;
}String;

typedef struct Node{
    String* key;
    String* data;
    struct Node* left;
    struct Node* right;
} Node;

String* getStr();

void print(Node* tree);
void beautyPrint(Node* tree);
void freeTree(Node* tree);
void add(Node** pTree, String* key, String* data);
void add_shell(Node** ptree);
void delete(Node** ptree, String* key);
int delete_shell(Node** ptree);
void traversal(Node* tree, String* key1, String* key2);
void traversal_shell(Node* tree);
Node** search_by_key(Node* tree, String* key, Node** arr, int* pCounter);
void search_by_key_shell(Node* tree);
void putTree(Node* tree, int level);
void printMenu();
int Menu(Node** pTree);

String* getStr(){
    char *str = NULL, c;
    int len = 1;
    str = malloc(sizeof(char));
    while((c = getchar()) != '\n') {
        str[len - 1] = c;
        len++;
        str = realloc(str, len);
    }
    str[len - 1] = '\0';


    String* string = malloc(sizeof(String));
    string->len = len - 1;
    string->str = malloc(sizeof(char) * (string->len +1));
    strcpy(string->str, str);
    free(str);

    printf("%s %d\n", string->str, string->len);

    return string;
}

void print(Node* tree){
    if (tree == NULL) return;
    print(tree->left);
    printf("Key: %s, Data: %s\n", tree->key->str, tree->data->str);
    print(tree->right);
}
void beautyPrint(Node* tree){
    printf("\n=============Tree=============\n");
    print(tree);
    printf("==============================\n");
    printf("\n");
}//прямой обход

void freeTree(Node* tree){
    if (tree == NULL) return;
    freeTree(tree->left);
    freeTree(tree->right);
    free(tree->key->str);
    free(tree->key);
    free(tree->data->str);
    free(tree->data);
    free(tree);
    tree = NULL;
}

//1. добавление нового элемента
void add(Node** pTree, String* key, String* data){

    if ( (*pTree) == NULL){
        Node* newNode = malloc(sizeof(Node));

        newNode->key = malloc(sizeof(String));
        newNode->key->str = malloc(sizeof(char) * ( key->len + 1) );
        strcpy(newNode->key->str, key->str);
        newNode->key->len = key->len;

        newNode->data = malloc(sizeof(String));
        newNode->data->str = malloc(sizeof(char) * (data->len + 1) );
        strcpy(newNode->data->str, data->str);
        newNode->data->len = data->len;

        newNode->left = NULL;
        newNode->right = NULL;
        (*pTree) = newNode;
        return;
    }


    if (strcmp(key->str, (*pTree)->key->str) < 0){
        add( &((*pTree)->left), key, data);
    }


    if (strcmp(key->str, (*pTree)->key->str) > 0){
        add( &((*pTree)->right), key, data);
    }


    if (strcmp(key->str, (*pTree)->key->str) == 0){

        if ( ((*pTree)->right != NULL) && strcmp(key->str, (*pTree)->right->key->str) == 0){
            add( &((*pTree)->right), key, data);
            return;
        }

        Node* newNode = malloc(sizeof(Node));

        newNode->key = malloc(sizeof(String));
        newNode->key->str = malloc( sizeof(char) * ( key->len + 1) );
        strcpy(newNode->key->str, key->str);
        newNode->key->len = key->len;

        newNode->data = malloc(sizeof(String));
        newNode->data->str = malloc(sizeof(char) * (data->len + 1) );
        strcpy(newNode->data->str, data->str);
        newNode->data->len = data->len;

        newNode->left = NULL;
        newNode->right = (*pTree)->right;

        (*pTree)->right = newNode;
        return;
    }
}
void add_shell(Node** ptree){

    printf("Введите ключ\n>");
    String* key = getStr();
    printf("Введите информацию\n>");
    String* data = getStr();


    add(ptree, key, data);
    printf("Элемент с ключом \"%s\" и информацией \"%s\" добавлен.\n", key->str, data->str);

    free(key->str);
    free(data->str);
    free(key);
    free(data);
}

//2. удаление элемента
void delete(Node** ptree, String* key){
    //сначала разберёмся с корнем.
    if ( (strcmp((*ptree)->key->str, key->str) == 0) ) {//плохое условие для корня.

        if ((*ptree)->left == NULL && (*ptree)->right == NULL) {//если дерево состоит только из вершины
            printf("Удалена вершина с ключом \"%s\" и информацией \"%s\"", (*ptree)->key->str, (*ptree)->data->str);
            free((*ptree)->key->str);
            free((*ptree)->key);
            free((*ptree)->data->str);
            free((*ptree)->data);
            free((*ptree));
            (*ptree) = NULL;
            return;
        }

        if ((*ptree)->left != NULL && (*ptree)->right == NULL &&
            (strcmp((*ptree)->key->str, (*ptree)->right->key->str) != 0)) {//если у вершины есть ТОЛЬКО левое поддерево
            printf("Удалена вершина с ключом \"%s\" и информацией \"%s\"", (*ptree)->key->str, (*ptree)->data->str);

            Node *temp = (*ptree)->left;

            free((*ptree)->key->str);
            free((*ptree)->key);
            free((*ptree)->data->str);
            free((*ptree)->data);
            free((*ptree));

            (*ptree) = temp;
            return;
        }

        if ((*ptree)->left == NULL && (*ptree)->right != NULL) {//если у вершины есть ТОЛЬКО правое поддерево
            printf("Удалена вершина с ключом \"%s\" и информацией \"%s\"", (*ptree)->key->str, (*ptree)->data->str);

            Node *temp = (*ptree)->right;

            free((*ptree)->key->str);
            free((*ptree)->key);
            free((*ptree)->data->str);
            free((*ptree)->data);
            free((*ptree));

            (*ptree) = temp;

            return;
        }

        if ((*ptree)->left != NULL && (*ptree)->right != NULL) {//если у вершины есть оба поддерева
            printf("Удалена вершина с ключом \"%s\" и информацией \"%s\"", (*ptree)->key->str, (*ptree)->data->str);

            if (strcmp((*ptree)->key->str, (*ptree)->right->key->str) == 0) {

                Node *temp = (*ptree)->right;
                temp->left = (*ptree)->left;

                free((*ptree)->key->str);
                free((*ptree)->key);
                free((*ptree)->data->str);
                free((*ptree)->data);
                free((*ptree));

                (*ptree) = temp;
                return;
            }

            if (strcmp((*ptree)->key->str, (*ptree)->right->key->str) != 0) {

                Node *par = (*ptree);
                Node *cur = (*ptree)->right;

                while (cur->left != NULL) {
                    par = cur;
                    cur = cur->left;
                }
                //теперь cur указывает на элемент, который заменит вершину

                cur->left = (*ptree)->left;
                cur->right = (*ptree)->right;

                par->left = NULL;

                free((*ptree)->key->str);
                free((*ptree)->key);
                free((*ptree)->data->str);
                free((*ptree)->data);
                free((*ptree));

                (*ptree) = cur;
                return;
            }

        }
    }

    if (strcmp(key->str, (*ptree)->key->str) < 0){
        delete( &((*ptree)->left), key);
        return;
    }


    if (strcmp(key->str, (*ptree)->key->str) > 0){
        delete( &((*ptree)->right), key);
        return;
    }
}
int delete_shell(Node** ptree){

    printf("Введите ключ\n>");
    String* key = getStr();

    delete(ptree, key);

    free(key->str);
    free(key);
    return 1;
}

//3. обход
void traversal(Node* tree, String* key1, String* key2){

    if (tree == NULL) return;
    traversal(tree->left, key1, key2);

    if ( (strcmp(tree->key->str, key1->str) >= 0) && (strcmp(tree->key->str, key2->str) <= 0) ){
        printf("Key: %s, Data: %s\n", tree->key->str, tree->data->str);
    }

    traversal(tree->right, key1, key2);
}
void traversal_shell(Node* tree){
    printf("Введите первый ключ\n>");
    String* key1 = getStr();
    printf("Введите второй ключ\n>");
    String* key2 = getStr();

    traversal(tree, key1, key2);

    free(key1->str);
    free(key2->str);
    free(key1);
    free(key2);
}

//4. поиск элемента по ключу;
Node** search_by_key(Node* tree, String* key, Node** arr, int* pCounter){
    if (tree == NULL){
        return arr;
    }

    if (strcmp(tree->key->str, key->str) == 0){
        *pCounter += 1;
        if (*pCounter == 1){
            *arr = tree;
        }
        else{
            arr = realloc(arr, sizeof(Node*) * (*pCounter));
            //printf("Я перевыделил память на %d ячейки\n", *pCounter);
            *(arr+ (*pCounter) - 1) = tree;
        }
    }

    arr = search_by_key(tree->left, key, arr, pCounter);
    arr = search_by_key(tree->right, key, arr, pCounter);
    return arr;
}
void search_by_key_shell(Node* tree){
    int Counter = 0;
    int* pCounter = &Counter;
    Node** arr = malloc(sizeof(Node*));
    printf("Введите ключ\n>");
    String* key = getStr();

    arr = search_by_key(tree, key, arr, pCounter);

    printf("Кол-во найден элементов: %d\n", *pCounter);


    for (int i = 0; i < (*pCounter); i++){
        printf("%d\t%s\n", (i+1), arr[i]->data->str);
    }


    free(arr);
    free(key->str);
    free(key);
}

//5. специальный поиск элемента.
Node** spec_search(Node* tree, String* key, String* cur_max, Node** arr, int* pcounter){
    if (tree == NULL){
        return arr;
    }
    if (strcmp(key->str, tree->key->str) >= 0){
        if (*pcounter == 0){
            *pcounter = 1;
            free(cur_max->str);
            cur_max->len = tree->key->len;
            cur_max->str = malloc(sizeof(cur_max->len));
            strcpy(cur_max->str, tree->key->str);
            *arr = tree;
        }

        else{
            if (strcmp(cur_max->str, tree->key->str) >= 0){
                *pcounter += 1;
                arr = realloc(arr, sizeof(Node*) * (*pcounter));
                *(arr+ (*pcounter) - 1) = tree;
            }

            if (strcmp(cur_max->str, tree->key->str) < 0){

                *pcounter = 1;
                free(cur_max->str);
                cur_max->len = tree->key->len;
                cur_max->str = malloc(sizeof(cur_max->len));
                strcpy(cur_max->str, tree->key->str);

                free(arr);
                arr = malloc(sizeof(Node*));
                *arr = tree;
            }

        }
    }

    arr = spec_search(tree->left, key, cur_max, arr, pcounter);
    arr = spec_search(tree->right, key, cur_max, arr, pcounter);
    return arr;
}
void spec_search_shell(Node* tree){
    printf("Введите ключ\n>");
    String* key = getStr();

    String* cur_max = malloc(sizeof(String));
    cur_max->str = malloc(1);

    Node** arr = malloc(sizeof(Node*));
    int counter = 0;
    int* pcounter = &counter;

    arr = spec_search(tree, key, cur_max, arr, pcounter);



    if (*pcounter == 0){
        printf("Элементов, удовлетворяющих условию нет\n");
    }
    else{
        printf("max_cur: %s\n", cur_max->str);
        printf("counter: %d\n", *pcounter);
        for (int i = 0; i < (*pcounter); i++){
            printf("Номер ключа: %d Ключ: %s Информация: %s\n", (i+1), arr[i]->key->str, arr[i]->data->str);


        }
    }


    free(cur_max->str);
    free(cur_max);
    free(arr);
    free(key->str);
    free(key);
}

//6. форматированный вывод дерева «в виде дерева»
void putTree(Node* tree, int level)
{
    int i = level;
    if (tree){
        putTree(tree->right, level + 1);
        while (i-- > 0)
            printf("\t\t");
        printf("%s\n", tree->key->str);
        putTree(tree->left, level + 1);
    }
}

//7.загрузка дерева из текстового файла
void add_from_file(Node** pTree){
    FILE* file;
    String* key;
    String* data;

    char* buffer;
    int len;
    char* str;

    file = fopen("file.txt", "r");

    while ( !feof(file) ) {

        buffer = malloc(sizeof(char)*100);
        fscanf(file, "%s\n", buffer);
        len = (int) strlen(buffer);
        str = malloc(sizeof(char) * (len+1));
        strcpy(str, buffer);
        free(buffer);

        key = malloc(sizeof(String));
        key->str = str;
        key->len = (int) strlen(str);

        buffer = malloc(sizeof(char)*100);
        fscanf(file, "%s\n", buffer);
        len = (int) strlen(buffer);
        str = malloc(sizeof(char) * (len+1));
        strcpy(str, buffer);
        free(buffer);

        data = malloc(sizeof(String));
        data->str = str;
        data->len = (int) strlen(str);

        add(pTree, key, data);



        free(key->str);
        free(data->str);
        free(key);
        free(data);
    }

    fclose(file);
}

void printMenu(){
    printf("\nЧто изволите, сударь?\n");
    printf("1. добавление нового элемента\n");
    printf("2. удаление элемента\n");
    printf("3. обход\n");
    printf("4. поиск элемента по ключу\n");
    printf("5. специальный поиск элемента\n");
    printf("6. форматированный вывод дерева «в виде дерева»\n");
    printf("7. загрузка дерева из текстового файла\n");

    printf("505. Просто посмотреть какие элементы есть в дереве\n");
    printf("404. Очистить экран\n");
    printf("0. Завершение программы\n");
    printf(">");
}//cool

int Menu(Node** pTree){
    int choice;
    do {
        printMenu();
        scanf("%d", &choice);
        scanf("%*[^\n]");
        scanf("%*c");
        if (choice == 1){
            add_shell(pTree);
        }
        else if(choice == 2){
            delete_shell(pTree);
        }
        else if(choice == 3){
            traversal_shell(*pTree);
        }
        else if(choice == 4){
            search_by_key_shell(*pTree);
        }
        else if(choice == 5){
            spec_search_shell(*pTree);
        }
        else if(choice == 6){
            putTree(*pTree, 0);
        }
        else if(choice == 7){
            add_from_file(pTree);
        }
        else if(choice == 505){
            beautyPrint(*pTree);
        }
        else if(choice == 404){
            printf("\033c");
        }
    } while (choice != 0);
    printf("The program was stopped\n");
}

int main() {
    Node* tree = NULL;
    Menu(&tree);
    freeTree(tree);
    return 0;
}
