#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
1. Каждый узел является красным или черным
2. Корень дерева является черным
3. Каждый лист дерева (EList) является черным
4. Если узел – красный, то оба его дочерних узла (потомка) – черные
5. Для каждого узла все пути от него до листьев, являющихся потомками данного узла, содержат одно и то же количество черных узлов
*/

typedef struct dNode{
    unsigned info;
    struct dNode* next;
} dNode;//data_Node

typedef struct Node{
    int color; // 1-red, 0-black
    unsigned key;
    dNode* data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

void RB_Insert_Fixup(Node** pRoot, Node* x);
void search(Node* tree, unsigned key, Node** pnode);

char* getString(){
    char *str = NULL, c;
    int len = 1;
    str = (char*) malloc(sizeof(char));
    while((c = getchar()) != '\n') {
        str[len - 1] = c;
        len++;
        str = (char*) realloc(str, len);
    }
    str[len - 1] = '\0';
    return str;
}

int get_unsigned(){

    char* string;
    int num;
    int is_num_integer = 0;

    while (is_num_integer != 1){
        string = getString();
        if ( strcmp(string, "0") == 0 ){
            num = 0;
            free(string);
            return num;
        }

        else{
            num = atoi(string);
            free(string);
            if (num  <= 0){
                is_num_integer = 0;
                printf("Введённая строка не является числом. Попробуйте ещё раз.\n");
            }
            else{
                return num;
            }
        }
    }

}

int is_x_EList(Node* x){
    if ( (x->color == 0) && (x->left == NULL) && (x->right == NULL) ){
        return 1;
    }
    return 0;
}

void left_rotate(Node** pRoot, Node* x){
    //x – заданный узел
    Node* y = x->right;// – правое поддерево узла x
    Node* p = x->parent;// – родительский узел узла x
    //1. Формирование связи x – левое поддерево y
    x->right = y->left;
    if (is_x_EList(y->left) == 0) {//если y->left не является EList, то меняем его parent
        y->left->parent = x;
    }
    //2. Формирование связи p – y:
    y->parent = p;
    if (is_x_EList(p) == 1){//Возможно, x был корнем дерева:
        *(pRoot) = y; //y – новый корень дерева
    }
    else{//Переустановить левое или правое поддерево родительского узла x
       if (p->left->key == x->key){
           p->left = y;
       }
       else{
           p->right = y;
       }
    }
    //3. Формирование связи y – x:
    y->left = x;
    x->parent = y;
}

void right_rotate(Node** pRoot, Node* x){
    //x – заданный узел
    Node* y = x->left;// – левое поддерево узла x
    Node* p = x->parent;// – родительский узел узла x
    //1. Формирование связи x – правое поддерево y
    x->left = y->right;
    if (is_x_EList(y->right) == 0) {//если y->right не является EList, то меняем его parent
        y->right->parent = x;
    }

    //2. Формирование связи p – y:
    y->parent = p;
    if (is_x_EList(p) == 1){//Возможно, x был корнем дерева:
        *(pRoot) = y; //y – новый корень дерева
    }
    else{//Переустановить левое или правое поддерево родительского узла x
        if (p->left->key == x->key){
            p->left = y;
        }
        else{
            p->right = y;
        }
    }
    //3. Формирование связи y – x:
    y->right = x;
    x->parent = y;
}

void RB_insert(Node** pRoot, Node* EList, unsigned key, unsigned data){

    Node* Search_Node = NULL;
    Node** pSearch_Node = &Search_Node;
    search(*pRoot, key, pSearch_Node);

    if (Search_Node != NULL){
        dNode* new_data_node = malloc(sizeof(dNode));
        new_data_node->info = data;
        new_data_node->next = Search_Node->data;
        Search_Node->data = new_data_node;
        return;
    }
    //делаем Node который хотим вставить
    Node* x = malloc(sizeof(Node));
    x->key = key;
    dNode* new_data_node = malloc(sizeof(dNode));
    new_data_node->info = data;
    new_data_node->next = NULL;
    x->data = new_data_node;

    //1. Вставка узла в бинарное дерево
    Node* prev = EList;//надо не забыть очистить
    Node* ptr = *pRoot;
    while (is_x_EList(ptr) != 1){//while дерево не пусто
        prev = ptr;
        if (x->key < ptr->key){
            ptr = ptr->left;
        }
        else{
            ptr=ptr->right;
        }
    }
    x->parent = prev;
    if (is_x_EList(prev) == 1){
        *pRoot = x;
    }
    else{
        if (x->key < prev->key){
            prev->left = x;
        }
        else{
            prev->right = x;
        }
    }
    //2. Установить поля left и right нового узла дерева:
    x->left = EList;
    x->right = EList;
    //3. Покрасить узел: x->color = RED
    x->color = 1;
    //4. Выполнить перекраску узлов и повороты дерева: RB_Insert_Fixup(x)
    RB_Insert_Fixup(pRoot, x);
}
/*
1. Каждый узел является красным или черным - не нарушается
2. Корень дерева является черным - может быть нарушено
3. Каждый лист дерева является черным - не нарушается
4. Если узел – красный, то оба его дочерних узла – черные - может быть нарушено
5. Для каждого узла все пути от него до листьев, являющихся потомками данного узла, содержат одно и то же количество черных узлов - не нарушается*/
void RB_Insert_Fixup(Node** pRoot, Node* x){
    while (x->parent->color == 1){//while родительский узел для x - красный
        Node* p1 = x->parent;
        Node* pp = p1->parent;
        if (p1->key == pp->left->key) {
            Node *p2 = pp->right;
            if (p2->color == 1) {//случай 1: перекрасть вершины
                p1->color = 0;
                p2->color = 0;
                pp->color = 1;
                x = pp;
                continue;
            }
            else if (x->key == p1->right->key) {//случай 2
                x = p1;
                left_rotate(pRoot, x);
                p1 = x->parent;
            }
            //случай 3
            p1->color = 0;
            pp->color = 1;
            right_rotate(pRoot, pp);
        }
        else{
            Node *p2 = pp->left;
            if (p2->color == 1) {//случай 1: перекрасть вершины
                p1->color = 0;
                p2->color = 0;
                pp->color = 1;
                x = pp;
                continue;
            }
            else if (x->key == p1->left->key) {//случай 2
                x = p1;
                right_rotate(pRoot, x);
                p1 = x->parent;
            }
            //случай 3
            p1->color = 0;
            pp->color = 1;
            left_rotate(pRoot, pp);
        }
    }
    (*pRoot)->color = 0;
}
void RB_insert_shell(Node** pRoot, Node* EList){
    printf("Введите ключ\n>");
    unsigned key = get_unsigned();
    printf("Введите информацию\n>");
    unsigned data = get_unsigned();
    RB_insert(pRoot, EList, key, data);
}

Node* tree_min(Node* x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}//возможно тут ошибка хз
Node* tree_max(Node* x){
    if (x->right == NULL){
        return NULL;
    }
    while(x->right->right != NULL){
        x = x->right;
    }
    return x;
}

Node* tree_successor(Node* x){
    Node* y = NULL;
    if (x->right != NULL){
        return tree_min(x->right);
    }

    y = x->parent;

    while (y != NULL && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}

void RB_Delete_Fixup(Node** pRoot, Node* x){
    //x – анализируемый узел дерева
    //p = x->parent;// – родительский узел
    //w = p->right (или p->left) – второй потомок узла p
    while (x->key != (*pRoot)->key && x->color == 0){
        Node* p = x->parent;
        if (x->key == p->left->key){
            Node* w = p->right;
            if (w->color == 1){
                w->color = 0;
                w->color = 1;
                left_rotate(pRoot, p);
                w = p->right;
            }
            if (w->left->color == 0 && w->right->color == 0){
                w->color = 1;
                x = p;
            }
            else{
                if (w->right->color == 0){
                    w->color = 1;
                    w->left->color = 0;
                    right_rotate(pRoot, w);
                    w = p->right;
                }
                w->color = p->color;
                p->color = 0;
                w->right->color = 0;
                left_rotate(pRoot, p);
                x = *pRoot;
            }
        }
        else{
            Node* w = p->left;
            if (w->color == 1){
                w->color = 0;
                w->color = 1;
                right_rotate(pRoot, p);
                w = p->left;
            }
            if (w->right->color == 0 && w->left->color == 0){
                w->color = 1;
                x = p;
            }
            else{
                if (w->left->color == 0){
                    w->color = 1;
                    w->right->color = 0;
                    left_rotate(pRoot, w);
                    w = p->left;
                }
                w->color = p->color;
                p->color = 0;
                w->left->color = 0;
                right_rotate(pRoot, p);
                x = *pRoot;
            }
        }
    }
    x->color = 0;
}

void RB_Delete(Node** pRoot, Node* x){

    if (x->data->next != NULL){//если у нас несколько элементов с одинаковыми ключами, то мы удаляем последний.
        dNode* temp = x->data;
        x->data = x->data->next;
        printf("Элемент с ключом \"%u\" и информацией \"%u\" был удалён.\n", x->key, x->data->info);
        free(temp);
        return;
    }

    Node* y;
    Node* p;
    if ( is_x_EList(x->left) == 1 || is_x_EList(x->left) == 1 ){
        y = x;
    }
    else{
        y = tree_successor(x);
    }
    if (is_x_EList(y->left) == 0){
        p = y->left;
    }
    else{
        p = y->right;
    }
    p->parent = y->parent;
    if (is_x_EList(y->parent) == 1){
        *pRoot = p;
    }
    else{
        if (y->parent->left->key == y->key){
            y->parent->left = p;
        }
        else{
            y->parent->right = p;
        }
    }
    if (y->key != x->key){
        x->key = y->key;
        x->data = y->data;
    }
    if (y->color == 0){
        RB_Delete_Fixup(pRoot, p);
    }
    printf("Элемент с ключом \"%u\" и информацией \"%u\" был удалён.\n", x->key, x->data->info);
    free(x->data);
    free(x);
}

void RB_Delete_shell(Node** pRoot){
    printf("Введите ключ\n>");
    unsigned key = get_unsigned();
    Node* node = NULL;
    Node** pnode = &node;
    search(*pRoot, key, pnode);
    if (node == NULL){
        printf("Элемента с ключом \"%u\" в дереве нет. Удаление не выполнено.\n", key);
    }
    else{
        RB_Delete(pRoot, node);
    }
}

void search(Node* tree, unsigned key, Node** pnode){

    if (is_x_EList(tree) == 1){
        return;
    }

    if (tree->key == key){
        *pnode = tree;
        return;
    }

    search(tree->left, key, pnode);
    search(tree->right, key, pnode);
}

void search_shell(Node* Root){
    printf("Введите ключ\n>");
    unsigned key = get_unsigned();
    Node* node = NULL;
    Node** pnode = &node;
    search(Root, key, pnode);
    if (node == NULL){
        printf("Элемента с ключом \"%u\" в дереве нет.\n", key);
    }
    else{
        printf("Элемента с ключом \"%u\" в дереве есть.\n", key);
    }

    dNode* cur = node->data;
    while (cur != NULL){
        printf("%u ", cur->info);
        cur = cur->next;
    }
    printf("\n");

}

void print_Tree(Node* tree, int level)
{
    printf("\n");
    int i = level;
    if (tree){
        print_Tree(tree->right, level + 1);
        while (i-- > 0)
            printf("\t\t");

        if (tree->left == NULL || tree->right == NULL){
            printf("EList\n");
        }
        else if (tree->color == 0){
            printf("%d black\n", tree->key);
        }
        else if (tree->color == 1){
            printf("%d red\n", tree->key);
        }
        print_Tree(tree->left, level + 1);
    }
}

unsigned my_pow(unsigned a, unsigned b){
    unsigned result = 1;
    for (int i = 0; i < b; i++){
        result = result * a;
    }
    return result;
}

void traversal(Node* x, unsigned n){

    if (is_x_EList(x) == 1){
        return;
    }
    unsigned num = my_pow(10,n);
    //printf("10**n = %u\n", num);

    if (x->key % num >= 1 && x->key % num <= 9){
        dNode* data = x->data;
        while (data != NULL){
            printf("key: %u info: %u\n", x->key, data->info);
            data=data->next;
        }
    }
    traversal(x->left, n);
    traversal(x->right, n);
}

void special_search(Node* root){
    Node* max_node = tree_max(root);
    if (max_node == NULL){
        printf("Дерево видимо пустое\n");
        return;
    }
    printf("Ключ: %u, информация: ",max_node->key);
    dNode* data = max_node->data;
    while (data != NULL){
        printf("%u ", data->info);
        data=data->next;
    }
    printf("\n");
}

void traversal_shell(Node* root){
    printf("Введите число десятичных разрядов\n>");
    unsigned n = get_unsigned();
    traversal(root, n);
}

void add_from_file(Node** pTree, Node* EList){
    FILE* file;
    unsigned key;
    unsigned data;

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

        key = atoi(str);
        free(str);

        buffer = malloc(sizeof(char)*100);
        fscanf(file, "%s\n", buffer);
        len = (int) strlen(buffer);
        str = malloc(sizeof(char) * (len+1));
        strcpy(str, buffer);
        free(buffer);

        data = atoi(str);
        free(str);

        RB_insert(pTree, EList, key, data);
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

    //printf("505. Просто посмотреть какие элементы есть в дереве\n");
    //printf("404. Очистить экран\n");
    printf("0. Завершение программы\n");
    printf(">");
}//cool

int Menu(Node** pRoot, Node* EList){
    int choice;
    do {
        printMenu();
        scanf("%d", &choice);
        scanf("%*[^\n]");
        scanf("%*c");
        if (choice == 1){
            RB_insert_shell(pRoot, EList);
        }
        else if(choice == 2){
            RB_Delete_shell(pRoot);
        }
        else if(choice == 3){
            traversal_shell(*pRoot);
        }
        else if(choice == 4){
            search_shell(*pRoot);
        }
        else if(choice == 5){
            special_search(*pRoot);
        }
        else if(choice == 6){
            print_Tree(*pRoot, 0);
        }
        else if(choice == 7){
            add_from_file(pRoot, EList);
        }
        else if(choice == 505){

        }
        else if(choice == 404){
            printf("\033c");
        }
    } while (choice != 0);
    printf("The program was stopped\n");
}

void freeTree(Node* tree){
    if (is_x_EList(tree) == 1) return;
    freeTree(tree->left);
    freeTree(tree->right);
    dNode* cur = tree->data;
    while (cur != NULL){
        dNode* temp = cur;
        cur=cur->next;
        free(temp);
    }
    free(tree);
}

int main() {
    Node* EList = malloc(sizeof(Node));
    EList->left = NULL;
    EList->right = NULL;
    EList->parent = NULL;

    EList->color = 0;
    EList->key = 0;

    EList->data = NULL;

    Node* Root = EList;
    Node** pRoot = &Root;
    Menu(pRoot, EList);

    freeTree(*pRoot);
    free(EList);
}


