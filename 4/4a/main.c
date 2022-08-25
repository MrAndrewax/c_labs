#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//у меня был некрасивый add (элемент равный первому неправильно добавлялся) +
//что такое прямой порядок следования ключей +
//надо убрать ограничение на длину строки в функции getStr +
//добавить обработку ctrl c
//короче нужен безопасный ввод
//добавить getint в Menu

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

String* getStr();//ввод строки
void print(Node* tree);//центрированный обход дерева
void beautyPrint(Node* tree);
void freeTree(Node* tree);//очищаем память.

//1. добавление нового элемента
/*Добавление нового элемента в дерево без нарушения свойств упорядоченности.
Если запись с данным ключом уже присутствует в дереве, а дублирование ключей не допускается,
то необходимо обновить значение информационного поля существующей записи, а старое вернуть в качестве результата.*/
void add(Node** proot, String* key, String* data);
void add_shell(Node** ptree);

//2. удаление элемента
/*Удаление элемента, заданного своим ключом, без нарушения свойств упорядоченности дерева.
Если в дереве присутствуют несколько элементов с указанным ключом, то необходимо удалить наиболее старый из них.*/
void search_by_key_with_parent(Node* root, Node** p_res, Node** p_par, String* key);
void search_min_with_par(Node* root, Node** p_min, Node** p_par_min);
void delete(Node** proot, String* key);
int delete_shell(Node** ptree);

//3. обход
/*Вывод всего содержимого дерева в прямом порядке следования ключей, не входящих в заданный диапазон.*/
void traversal(Node* tree, String* key1, String* key2);
void traversal_shell(Node* tree);

//4. поиск элемента по ключу;
/*Поиск информации по заданному ключу.
Если элементов с требуемым значением ключа может быть несколько, то необходимо в качестве результата вернуть их все.
Возврат необходимо осуществлять при помощи вектора указателей, возврат копий элементов не допускается.*/
Node** search_by_key(Node* tree, String* key, Node** arr, int* pCounter);
void search_by_key_shell(Node* tree);

//5. специальный поиск элемента.
/*Поиск элемента с наибольшим значением ключа, не превышающим заданное
(если таких элементов несколько — действовать по аналогии с операцией поиска по ключу).*/
Node** spec_search(Node* tree, String* key, String* cur_max, Node** arr, int* pcounter);
void spec_search_shell(Node* tree);

//6. форматированный вывод дерева «в виде дерева»
void putTree(Node* tree, int level);

//7.загрузка дерева из текстового файла
void add_from_file(Node** pTree);


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
}

void old_add(Node** pTree, String* key, String* data){

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
void add(Node** proot, String* key, String* data){

    //формируем новый узел
    Node* new_node = malloc(sizeof(Node));
    new_node->key = malloc(sizeof(String));
    new_node->key->str = malloc(sizeof(char) * ( key->len + 1) );
    strcpy(new_node->key->str, key->str);
    new_node->key->len = key->len;
    new_node->data = malloc(sizeof(String));
    new_node->data->str = malloc(sizeof(char) * (data->len + 1) );
    strcpy(new_node->data->str, data->str);
    new_node->data->len = data->len;
    new_node->left = NULL;
    new_node->right = NULL;

    if ( (*proot) == NULL) {//если дерево пустое
        (*proot) = new_node;//делаем новый элемент корнем, root = x
        return;
    }

    //если дерево не пустое:
    Node* cur = (*proot);
    Node* par = NULL;

    //находим куда именно надо вставить новый узел
    while (cur != NULL){
        par = cur;
        if (strcmp(new_node->key->str, cur->key->str) == 0){
            if (cur->right != NULL && strcmp(new_node->key->str, cur->right->key->str) == 0){
                cur=cur->right;
                continue;
            }
            break;
        }
        else if (strcmp(new_node->key->str, cur->key->str) < 0){
            cur=cur->left;
        }
        else if (strcmp(new_node->key->str, cur->key->str) > 0){
            cur=cur->right;
        }
    }

    //сейчас вставляем new_node под par
    if (strcmp(new_node->key->str, par->key->str) == 0){
        new_node->right = par->right;
        par->right = new_node;
        return;
    }
    else if (strcmp(new_node->key->str, par->key->str) < 0){
        par->left = new_node;
        return;
    }
    else if (strcmp(new_node->key->str, par->key->str) > 0){
        par->right = new_node;
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

void search_by_key_with_parent(Node* root, Node** p_res, Node** p_par, String* key){
    while (root != NULL) {
        if (strcmp(root->key->str, key->str) == 0){
            *p_res = root;
            return;
        }
        else if (strcmp(root->key->str, key->str) > 0){
            *p_par = root;
            root = root->left;
        }
        else if (strcmp(root->key->str, key->str) < 0){
            *p_par = root;
            root = root->right;
        }
    }
}
void search_min_with_par(Node* root, Node** p_min, Node** p_par_min){
    while (root->left != NULL){
        *p_par_min = root;
        root=root->left;
    }
    *p_min = root;
}
void delete(Node** proot, String* key){

    Node* rem_node = NULL;
    Node* par = NULL;

    search_by_key_with_parent(*proot, &rem_node, &par, key);

    if (rem_node == NULL){
        printf("Элемент с ключом %s в дереве отсутствует\n", key->str);
        return;
    }

    else if (rem_node != NULL && par == NULL){//это корень
        if (rem_node->left == NULL && rem_node->right == NULL){//если у удаляемого элемента нет ни одного ребенка
            free(rem_node->data->str);
            free(rem_node->key->str);
            free(rem_node->data);
            free(rem_node->key);
            free(rem_node);
            *proot = NULL;
            return;
        }
        else if (rem_node->left == NULL && rem_node->right != NULL){//если у удаляемого элемента только левый ребенок
            *proot = rem_node->right;
            free(rem_node->data->str);
            free(rem_node->key->str);
            free(rem_node->data);
            free(rem_node->key);
            free(rem_node);
            return;
        }
        else if (rem_node->left != NULL && rem_node->right == NULL){//если у удаляемого элемента только правый ребенок
            *proot = rem_node->left;
            free(rem_node->data->str);
            free(rem_node->key->str);
            free(rem_node->data);
            free(rem_node->key);
            free(rem_node);
            return;
        }
        else{//если у удаляемого элемента два ребёнка
            Node* min = NULL;
            Node* par_min = NULL;
            search_min_with_par(rem_node->right, &min, &par_min);
            if (par_min == NULL){
                min->left = rem_node->left;
                *proot = min;
                free(rem_node->data->str);
                free(rem_node->key->str);
                free(rem_node->data);
                free(rem_node->key);
                free(rem_node);
                return;
            }
            par_min->left = min->right;
            min->left = rem_node->left;
            min->right = rem_node->right;
            *proot = min;
            free(rem_node->data->str);
            free(rem_node->key->str);
            free(rem_node->data);
            free(rem_node->key);
            free(rem_node);
            return;
        }
    }

    //если это не корень
    if (rem_node->left == NULL && rem_node->right == NULL){//если у удаляемого элемента нет ни одного ребенка
        if (strcmp(rem_node->key->str, par->key->str) < 0){
            par->left = NULL;
        }
        else if (strcmp(rem_node->key->str, par->key->str) > 0){
            par->right = NULL;
        }
        free(rem_node->data->str);
        free(rem_node->key->str);
        free(rem_node->data);
        free(rem_node->key);
        free(rem_node);
        return;
    }
    else if (rem_node->left == NULL && rem_node->right != NULL){//если у удаляемого элемента только левый ребенок
        if (strcmp(rem_node->key->str, par->key->str) < 0){

            par->left = rem_node->right;
        }
        else if (strcmp(rem_node->key->str, par->key->str) > 0){
            par->right = rem_node->right;
        }
        free(rem_node->data->str);
        free(rem_node->key->str);
        free(rem_node->data);
        free(rem_node->key);
        free(rem_node);
        return;
    }
    else if (rem_node->left != NULL && rem_node->right == NULL){//если у удаляемого элемента только правый ребенок
        if (strcmp(rem_node->key->str, par->key->str) < 0){
            par->left = rem_node->left;
        }
        else if (strcmp(rem_node->key->str, par->key->str) > 0){
            par->right = rem_node->left;
        }
        free(rem_node->data->str);
        free(rem_node->key->str);
        free(rem_node->data);
        free(rem_node->key);
        free(rem_node);
        return;
    }
    else{//если у удаляемого элемента два ребёнка
        Node* min = NULL;
        Node* par_min = NULL;
        search_min_with_par(rem_node->right, &min, &par_min);

        if (par_min == NULL){
            min->left = rem_node->left;
            if (strcmp(rem_node->key->str, par->key->str) < 0){
                par->left = min;
            }
            else if (strcmp(rem_node->key->str, par->key->str) > 0){
                par->right = min;
            }
            free(rem_node->data->str);
            free(rem_node->key->str);
            free(rem_node->data);
            free(rem_node->key);
            free(rem_node);
            return;
        }

        par_min->left = min->right;
        min->left = rem_node->left;
        min->right = rem_node->right;

        if (strcmp(rem_node->key->str, par->key->str) < 0){
            par->left = min;
        }
        else if (strcmp(rem_node->key->str, par->key->str) > 0){
            par->right = min;
        }
        free(rem_node->data->str);
        free(rem_node->key->str);
        free(rem_node->data);
        free(rem_node->key);
        free(rem_node);
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

void old_delete(Node** ptree, String* key){
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
int old_delete_shell(Node** ptree){

    printf("Введите ключ\n>");
    String* key = getStr();

    delete(ptree, key);

    free(key->str);
    free(key);
    return 1;
}

void traversal(Node* tree, String* key1, String* key2){

    if (tree == NULL) return;

    if ( (strcmp(tree->key->str, key1->str) >= 0) && (strcmp(tree->key->str, key2->str) <= 0) ){
        printf("Key: %s, Data: %s\n", tree->key->str, tree->data->str);
    }
    traversal(tree->left, key1, key2);
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

void putTree(Node* tree, int level)
{
    int i = level;
    if (tree){
        putTree(tree->right, level + 1);
        while (i-- > 0)
            printf("\t\t");
        printf("%s/%s\n", tree->key->str, tree->data->str);
        putTree(tree->left, level + 1);
    }
}

void add_from_file(Node** pTree){
    FILE* file;
    String* key;
    String* data;

    char* buffer;
    int len;
    char* str;

    file = fopen("/home/andrew/labs/4/4a/file.txt", "r");

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
    printf("===============================================\n");
    printf("Что изволите, сударь?\n");
    printf("1. добавление нового элемента\n");
    printf("2. удаление элемента\n");
    printf("3. обход\n");
    printf("4. поиск элемента по ключу\n");
    printf("5. специальный поиск элемента\n");
    printf("6. форматированный вывод дерева «в виде дерева»\n");
    printf("7. загрузка дерева из текстового файла\n");
    printf("===============================================\n");
    //printf("404. Очистить экран\n");
    //прямой обход
    //центрированный обход
    //концевой обход
    //очистка дерева
    printf("0. Завершение программы\n");
    printf("===============================================\n");
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
    tree = NULL;
    return 0;
}
