//
// Created by andrew on 15.07.22.
//

#include "graph.h"

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

    //printf("%s %d\n", string->str, string->len);

    return string;
}

int search(Graph* graph, String* vertex){
    for (int i = 0; i < graph->v; i++){
        if (strcmp(graph->Garr[i].vertex->str, vertex->str) == 0){
            return 1;
        }
    }
    return 0;
}//ищет в основном массиве ячейку с именем vertex->str. если находит, то возвращает 1. Если не находит, то 0. ++++=

int isAdjacent(Graph* graph, String* Main_Vertex, String* Auxiliary_Vertex){
    for (int i = 0; i < graph->v; i++){
        if (strcmp(graph->Garr[i].vertex->str, Main_Vertex->str) == 0){
            Node* cur = graph->Garr[i].adjacent;
            while (cur != NULL){
                if (strcmp(cur->ver->str, Auxiliary_Vertex->str) == 0){
                    return 1;
                }
                cur = cur->next;
            }
            return 0;
        }
    }
    return 0;
}//функция проверяет смежны ли вершины Main_Vertex и Auxiliary_Vertex. Что мы делаем? Находим в графе вершину Main_Vertex. Смотрим какие с ней смежны. Если находим среди них Auxiliary_Vertex, то возвращаем 1. если нет, то ноль.

Graph* init_graph(){
    Graph* graph = NULL;
    graph = malloc(sizeof(Graph));
    graph->v = 0;
    graph->Garr = NULL;
    return graph;
}

void print_Graph(Graph* graph){
    for (int i = 0; i < graph->v; i++) {
        printf("%s", graph->Garr[i].vertex->str);
        Node* cur = graph->Garr[i].adjacent;
        while(cur != NULL){
            printf("-->%s", cur->ver->str);
            cur=cur->next;
        }
        printf("\n");
    }
    printf("\n\n");
}

int add_vertex(Graph* graph, String* new_vertex){
    if (graph->Garr == NULL) {//если граф пустой

        graph->v += 1;

        String* added_vertex = malloc(sizeof(String));
        added_vertex->len = strlen(new_vertex->str);
        added_vertex->str = malloc(sizeof(char) * (added_vertex->len + 1));
        strcpy(added_vertex->str, new_vertex->str);

        graph->Garr = malloc(sizeof(cell));
        graph->Garr->adjacent = NULL;
        graph->Garr->vertex = added_vertex;
        printf("Вершина \"%s\" была успешно добавлена\n", new_vertex->str);
        return 0;
    }

    else if (graph->Garr != NULL){

        int Is_added_vertex_in_graph = search(graph, new_vertex);

        if (Is_added_vertex_in_graph == 1){//если такая вершина уже есть в графе.
            printf("Вершина \"%s\" уже есть в графе\n", new_vertex->str);
            return -1;
        }

        else if (Is_added_vertex_in_graph == 0){//если вершины нет в графе, то добавляем)))

            graph->v += 1;


            String *added_vertex = malloc(sizeof(String));
            added_vertex->len = strlen(new_vertex->str);
            added_vertex->str = malloc(sizeof(char) * (added_vertex->len + 1));
            strcpy(added_vertex->str, new_vertex->str);


            graph->Garr = realloc(graph->Garr, sizeof(cell)*(graph->v));
            graph->Garr[graph->v-1].adjacent = NULL;
            graph->Garr[graph->v-1].vertex = added_vertex;
            printf("Вершина \"%s\" была успешно добавлена\n", new_vertex->str);
            return 0;
        }
    }
}
void add_vertex_shell(Graph* graph){
    printf("Введите имя новой вершины\n>");
    String* new_vertex = getStr();

    add_vertex(graph, new_vertex);

    free(new_vertex->str);
    free(new_vertex);
}

void add_edge(Graph *graph, String *v1, String *v2){
    int Is_v1_in_graph = search(graph, v1);     //проверяем есть ли первая вершина в графе
    int Is_v2_in_graph = search(graph, v2);     //проверяем есть ли вторая вершина в графе
    if (Is_v1_in_graph == 0 && Is_v2_in_graph == 1){
        printf("Вершины \"%s\" в графе нет, добавление грани (%s, %s) не выполнено.\n", v1->str, v1->str, v2->str);
    }
    else if (Is_v1_in_graph == 1 && Is_v2_in_graph == 0){
        printf("Вершины \"%s\" в графе нет, добавление грани (%s, %s) не выполнено.\n", v2->str, v1->str, v2->str);
    }
    else if (Is_v1_in_graph == 0 && Is_v2_in_graph == 0){
        printf("Вершин \"%s\" и \"%s\" в графе нет, добавление грани (%s, %s) не выполнено.\n", v1->str, v2->str, v1->str, v2->str);
    }
    else if (Is_v1_in_graph == 1 && Is_v2_in_graph == 1){
        for (int i = 0; i < graph->v; i++){
            if (strcmp(graph->Garr[i].vertex->str, v1->str) == 0){
                //маленькая проверочка на то, есть ли грань в графе
                Node* cur = graph->Garr[i].adjacent;
                while (cur != NULL){
                    if (strcmp(cur->ver->str, v2->str) == 0){
                        printf("Грань (%s, %s) уже есть в графе. Добавление не выполнено.\n", v1->str, v2->str);
                        return;
                    }
                    cur = cur->next;
                }


                String* v2_copy = malloc(sizeof(String));
                v2_copy->len = strlen(v2->str);
                v2_copy->str = malloc(sizeof(char) * (v2_copy->len + 1));
                strcpy(v2_copy->str, v2->str);

                Node* newNode = malloc(sizeof(Node));
                newNode->next = graph->Garr[i].adjacent;
                newNode->ver = v2_copy;
                graph->Garr[i].adjacent = newNode;
            }

            if (strcmp(graph->Garr[i].vertex->str, v2->str) == 0){

                String* v1_copy = malloc(sizeof(String));
                v1_copy->len = strlen(v1->str);
                v1_copy->str = malloc(sizeof(char) * (v1_copy->len + 1));
                strcpy(v1_copy->str, v1->str);

                Node* newNode = malloc(sizeof(Node));
                newNode->next = graph->Garr[i].adjacent;
                newNode->ver = v1_copy;
                graph->Garr[i].adjacent = newNode;
            }
        }
        printf("Добавлена грань (%s, %s)\n", v1->str, v2->str);
    }
}
void add_edge_shell(Graph* graph){
    printf("Введите название первой вершины\n>");
    String* ver1 = getStr();

    printf("Введите название второй вершины\n>");
    String* ver2 = getStr();


    add_edge(graph, ver1, ver2);

    free(ver1->str);
    free(ver1);
    free(ver2->str);
    free(ver2);
}

void delete_vertex(Graph* graph, String* v){
    int is_v_in_graph = search(graph, v);
    if ( is_v_in_graph == 0 ){
        printf("Вершины \"%s\" в графе нет\n", v->str);
        return;
    }
    else{
        for (int i = 0; i < graph->v; i++) {
            if (strcmp(graph->Garr[i].vertex->str, v->str) == 0) {
                Node *cur = graph->Garr[i].adjacent;
                while (cur != NULL) {
                    Node *tempNode = cur;
                    cur = cur->next;
                    free(tempNode->ver->str);
                    free(tempNode->ver);
                    free(tempNode);
                }
                graph->Garr[i].adjacent = NULL;
                free(graph->Garr[i].vertex->str);
                free(graph->Garr[i].vertex);

                graph->Garr[i] = graph->Garr[graph->v - 1];
                graph->v = graph->v - 1;
                graph->Garr = realloc(graph->Garr, sizeof(cell) * (graph->v));
            }
        }
        for (int i = 0; i < graph->v; i++) {
            int are_vi_and_vdeleted_adjacent = isAdjacent(graph, graph->Garr[i].vertex, v);
            if (are_vi_and_vdeleted_adjacent == 1){
                if (strcmp(graph->Garr[i].adjacent->ver->str, v->str) == 0){
                    Node* temp = graph->Garr[i].adjacent;
                    graph->Garr[i].adjacent = graph->Garr[i].adjacent->next;
                    free(temp->ver->str);
                    free(temp->ver);
                    free(temp);
                }
                else{
                    Node* cur = graph->Garr[i].adjacent;
                    while (1){
                        if ( strcmp(cur->next->ver->str, v->str) == 0 ){
                            Node* temp = cur->next;
                            cur->next = cur->next->next;
                            free(temp->ver->str);
                            free(temp->ver);
                            free(temp);
                            break;
                        }
                        cur=cur->next;
                    }
                }
            }
        }
    }
    printf("Вершина \"%s\" была успешна удалена", v->str);
}
void delete_vertex_shell(Graph* graph){
    printf("Введите имя вершины, которую хотите удалить\n>");
    String* new_vertex = getStr();

    delete_vertex(graph, new_vertex);

    free(new_vertex->str);
    free(new_vertex);
}

int is_edge_in_graph(Graph* graph, String* v1, String* v2){
    //сначала проверяем есть ли такие вершины в графе.
    int is_v1_in_graph = search(graph, v1);
    int is_v2_in_graph = search(graph, v2);
    if (is_v1_in_graph == 1 && is_v2_in_graph == 1){
        int is_v1_v2_adjacent = isAdjacent(graph, v1, v2);
        return is_v1_v2_adjacent;
    }
    else{
        if (is_v1_in_graph == 0 && is_v2_in_graph == 0){
            printf("Таких вершин в графе нет.\n");
            return 0;
        }
        else if (is_v1_in_graph == 0){
            printf("Вершины \"%s\" в графе нет.\n", v1->str);
            return 0;
        }
        else if (is_v2_in_graph == 0){
            printf("Вершины \"%s\" в графе нет.\n", v2->str);
            return 0;
        }
    }
}
void delete_edge(Graph* graph, String* v1, String* v2){
    if (is_edge_in_graph(graph,v1,v2)){
        for (int i = 0; i < graph->v; i++){

            if (strcmp(graph->Garr[i].vertex->str, v1->str) == 0){

                if (strcmp(graph->Garr[i].adjacent->ver->str, v2->str) == 0){
                    Node* temp = graph->Garr[i].adjacent;
                    graph->Garr[i].adjacent = graph->Garr[i].adjacent->next;
                    free(temp->ver->str);
                    free(temp->ver);
                    free(temp);
                }

                else{
                    Node* cur = graph->Garr[i].adjacent;
                    while (1){
                        if ( strcmp(cur->next->ver->str, v2->str) == 0 ){
                            Node* temp = cur->next;
                            cur->next = cur->next->next;
                            free(temp->ver->str);
                            free(temp->ver);
                            free(temp);
                            break;
                        }
                        cur=cur->next;
                    }
                }
            }


            if (strcmp(graph->Garr[i].vertex->str, v2->str) == 0){

                if (strcmp(graph->Garr[i].adjacent->ver->str, v1->str) == 0){
                    Node* temp = graph->Garr[i].adjacent;
                    graph->Garr[i].adjacent = graph->Garr[i].adjacent->next;
                    free(temp->ver->str);
                    free(temp->ver);
                    free(temp);
                }

                else{
                    Node* cur = graph->Garr[i].adjacent;
                    while (1){
                        if ( strcmp(cur->next->ver->str, v1->str) == 0 ){
                            Node* temp = cur->next;
                            cur->next = cur->next->next;
                            free(temp->ver->str);
                            free(temp->ver);
                            free(temp);
                            break;
                        }
                        cur=cur->next;
                    }
                }
            }
        }
        printf("Грань (%s, %s) успешно удалена\n", v1->str, v2->str);
    }
    else{
        printf("Грани (%s, %s) в графе нет\n", v1->str, v2->str);
    }
}
void delete_edge_shell(Graph* graph){
    printf("Введите название первой вершины\n>");
    String* ver1 = getStr();

    printf("Введите название второй вершины\n>");
    String* ver2 = getStr();


    delete_edge(graph, ver1, ver2);

    free(ver1->str);
    free(ver1);
    free(ver2->str);
    free(ver2);
}

void freeGraph(Graph* graph){
    for (int i = 0; i < graph->v; i++){
        Node* cur = graph->Garr[i].adjacent;
        while(cur != NULL){
            Node* tempNode = cur;
            cur = cur->next;
            free(tempNode->ver->str);
            free(tempNode->ver);
            free(tempNode);
        }
        free(graph->Garr[i].vertex->str);
        free(graph->Garr[i].vertex);
    }
    free(graph->Garr);
    free(graph);
    graph = NULL;
}
