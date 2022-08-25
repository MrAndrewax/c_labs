#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define LEN 8
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

/*
int searcht(Node* x, String* key){
    if (x == NULL){
        return 0;
    }
    if (strcmp(x->key->str, key->str) == 0){
        return 1;
    }
    int res;

    if (strcmp(x->key->str, key->str) < 0){
        res = search(x->left, key);
    }
    else if (strcmp(x->key->str, key->str) < 0){
        res = search(x->right, key);
    }
}
*/

int search(Node* x, String* key){
    while (x != NULL){
        if (strcmp(x->key->str, key->str) == 0){
            return 1;
        }
        else if (strcmp(x->key->str, key->str) > 0){
            x = x->left;
        }
        else{//if (strcmp(x->key->str, key->str) < 0)
            x = x->right;
        }
    }
    return 0;
}

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

String* randS()
{
    String* string = malloc(sizeof(String));
    int i;
    char s[LEN];
    for (i = 0; i < LEN - 1; i++)
        s[i] = 'a' + rand()%26;
    s[i] = '\0';

    string->len = LEN;//(int) strlen(s);

    string->str = malloc(sizeof(char) * (LEN + 1));

    strcpy(string->str, s);

    return string;
}

void createTree(Node** pTree, int size){
    int i = 0;
    while ( i < size ){
        String* string = randS();
        add(pTree, string, string);
        free(string->str);
        free(string);
        i++;
    }
}

void traverse(Node* root, int* i){
    if (root == NULL) return;
    traverse(root->left, i);
    (*i)++;
    traverse(root->right, i);
}

void tim(){
    Node* tree = NULL;

    int size = 50000;
    int n = 42;
    int i = 1;

    int start;
    int end;
    int result;

    FILE* searchFile;
    searchFile = fopen("search.csv", "a");

    while (i < n){
        printf("Создано дерево размера %d\n", size * i);
        createTree(&tree, size * i);//создаём дерево
        //putTree(tree, 0);
        //printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        //теперь надо сделать 100 измерений.
        fprintf(searchFile, "\n%d\n", size * i);
        for (int j = 0; j < 30; j++){

            String* string = randS();
            add(&tree, string, string);
            //printf("добавил элемент %s\n", string->str);
            //putTree(tree, 0);printf("\n\n\n\n\n\n\n\n\n\n");


            start = clock();
            search(tree, string);
            end = clock();
            //printf("k = %d\n", k);
            //printf("k = %d\n", k);
            //printf("k == %d\n", k);
            /*
            if (k == 1){
                printf("нашёл элемент %s\n", string->str);
            }
            else if (k == 0){
                printf("не нашёл элемент %s\n", string->str);
            }*/
            delete(&tree, string);
            //printf("удалил элемент %s\n", string->str);
            //putTree(tree, 0);printf("\n\n\n\n\n\n\n\n\n\n");

            free(string->str);
            free(string);
            result = end - start;
            //printf("%d\n", result);
            fprintf(searchFile, "%d,", result);
        }
        //putTree(tree, 0);
        freeTree(tree);
        tree = NULL;
        i++;
    }
    fclose(searchFile);
}

int main() {
    tim();
    return 0;
}

