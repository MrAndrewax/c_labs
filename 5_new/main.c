#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

char* getStr(){
    char *str = NULL, c;
    int len = 1;
    str = malloc(sizeof(char));
    while((c = getchar()) != '\n') {
        str[len - 1] = c;
        len++;
        str = realloc(str, len);
    }
    str[len - 1] = '\0';

    return str;
}
int get_int(){
    int res;
    scanf("%d", &res);
    scanf("%*[^\n]");
    scanf("%*c");
    return res;
}

typedef struct adjNode{
    struct adjNode* next;
    int vertex;//номер вершины
} adjNode;
typedef struct Graph{
    int vertex_count;
    adjNode** vertices;
    char** vertex_names;
} Graph;

typedef struct qNode{
    int vertex;
    struct qNode* next;
} qNode;
typedef struct Queue{
    qNode* head;
    qNode* tail;
} Queue;

typedef struct eNode{
    int v1;
    int v2;
    struct eNode* next;
} eNode;
typedef struct Edges{
    eNode* head;
} Edges;

typedef struct Way{
    int v1;
    int v2;
} Way;

Graph* init_graph();
int get_number_of_vertex(Graph* graph, char* ver_name);
int is_vertex_in_graph(Graph* graph, int v);
int is_edge_in_graph(Graph* graph, int v1, int v2);
void add_vertex(Graph* graph, char* vertex_name);
void add_vertex_shell(Graph* graph);
void delete_vertex(Graph* graph, int v);
void delete_vertex_shell(Graph* graph);
void delete_edge(Graph* graph, int v1, int v2);
void delete_edge_shell(Graph* graph);
int is_edge_in_graph_with_msg(Graph* graph, int v1, int v2);
int add_edge(Graph* graph, int v1, int v2);
void add_edge_shell(Graph* graph);
void print_graph(Graph* graph);
void free_graph(Graph* graph);

Queue* init_Queue();
void free_Queue(Queue* queue);
void push(Queue* queue, int vertex);
int pop(Queue* queue, int* pres);
void print_path(Graph* graph, int* pred, int s, int v);
void bfs(Graph* graph, int s, int f);
void bfs_shell(Graph* graph);

void add_edge_in_edges(Edges* edges, int v1, int v2);
int is_edge_in_edges(Edges* edges, int v1, int v2);
void free_edges(Edges* edges);
Edges* get_edges(Graph* graph);
void print_edges(Graph* graph, Edges* edges);
void bellman_ford(Graph* graph, int s, int f);
void bellman_ford_shell(Graph* graph);
int print_matrix(Graph* graph, int** matrix);
int** copy_matrix(int** matrix, int size);
void free_matrix(int** matrix, int size);
int* matrix_to_array(int** matrix, int size);
void sort_array(int* arr, int size);
void print_array(int* arr, int size);
int cmp_ways(Way way1, Way way2);
int is_way_in_ways(Way* ways, int ways_size, Way way);
Way get_way_by_value(int** matrix, int size,  int value, int num);
void print_ways(Graph* graph, Way* ways, int ways_size);
void shortest_path(Graph* graph, int** pred, int** d, int v1, int v2);
void print_floyd_warshall_matrix(Graph* graph, int** pred, int** d);
void floyd_warshall_init(Graph* graph, int** pred, int** d);
void floyd_warshall(Graph* graph);
void floyd_warshall_shell(Graph* graph);


Graph* init_graph(){
    Graph* graph = malloc(sizeof(Graph));
    graph->vertex_count = 0;
    graph->vertices = NULL;
    graph->vertex_names = NULL;
    return graph;
}

int get_number_of_vertex(Graph* graph, char* ver_name){
    int v = -1;
    for (int i = 0; i < graph->vertex_count; i++){
        if (strcmp(ver_name, graph->vertex_names[i]) == 0){
            v = i;
        }
    }
    return v;
}

int is_vertex_in_graph(Graph* graph, int v){
    if (v < 0){
        return 0;
    }
    return 1;
}
int is_edge_in_graph(Graph* graph, int v1, int v2){
    if (is_vertex_in_graph(graph, v1) && is_vertex_in_graph(graph, v2)){
        adjNode* cur = graph->vertices[v1];
        while (cur != NULL){
            if (cur->vertex == v2){
                return 1;
            }
            cur=cur->next;
        }
    }
    return 0;
}

void add_vertex(Graph* graph, char* vertex_name){

    int v = get_number_of_vertex(graph, vertex_name);
    int is_v_in_graph = is_vertex_in_graph(graph, v);

    if (is_v_in_graph == 1){
        printf("Вершина \"%s\" уже есть в графе\n", vertex_name);
        return;
    }

    if (graph->vertices == NULL){
        graph->vertex_count = 1;
        graph->vertices = malloc(sizeof(adjNode*));
        graph->vertices[0] = NULL;
        graph->vertex_names = malloc(sizeof(char**));
        graph->vertex_names[0] = malloc(sizeof(char) * (strlen(vertex_name) + 1));
        strcpy(graph->vertex_names[0], vertex_name);
        return;
    }
    graph->vertex_count++;
    graph->vertices = realloc(graph->vertices, sizeof(adjNode*) * graph->vertex_count);
    graph->vertices[graph->vertex_count-1] = NULL;

    graph->vertex_names = realloc(graph->vertex_names, sizeof(char**) * graph->vertex_count);
    graph->vertex_names[graph->vertex_count-1] = malloc(sizeof(char) * (strlen(vertex_name) + 1));
    strcpy(graph->vertex_names[graph->vertex_count-1], vertex_name);
}
void add_vertex_shell(Graph* graph){
    printf("Введите название вершины\n>");
    char* v_name = getStr();

    add_vertex(graph, v_name);
    free(v_name);
}

void delete_vertex(Graph* graph, int v){
    adjNode** new_vertices = malloc(sizeof(adjNode*) * (graph->vertex_count - 1));
    char** new_vertex_names = malloc(sizeof(char*) * (graph->vertex_count - 1));


    int j = 0;
    int is_main_v_deleted = 0;

    for (int i = 0; i < graph->vertex_count; i++){
        if (i == v){//Надо очистить вершину. И удалить эту вершину из списков смежности других вершин.
            adjNode* cur = graph->vertices[v];//cur - это элементы списка смежности вершины v.

            while (cur != NULL){
                adjNode* rem_node = cur;
                cur=cur->next;
                free(rem_node);
            }
            is_main_v_deleted = 1;
        }
        else{
            new_vertices[j] = graph->vertices[i];
            new_vertex_names[j] = graph->vertex_names[i];
            j++;
        }
    }

    for (int i = 0; i < graph->vertex_count - 1; i++){
        printf("%d-->%s\n", i, new_vertex_names[i]);
    }
    printf("\n");

    free(graph->vertices);
    free(graph->vertex_names[v]);
    free(graph->vertex_names);
    graph->vertices = new_vertices;
    graph->vertex_names = new_vertex_names;
    graph->vertex_count--;

    //теперь надо удалить v из списков смежности других вершин

    for (int i = 0; i < graph->vertex_count; i++){
        adjNode* u = graph->vertices[i];

        if (u->vertex == v){//если v является первой в списке смежности вершины u.
            graph->vertices[i] = graph->vertices[i]->next;
            free(u);
            continue;
        }

        else{
            adjNode* prev = NULL;
            while (u != NULL){
                if (u->vertex == v){
                    prev->next = prev->next->next;
                    free(u);
                    break;
                }
                prev = u;
                u=u->next;
            }
        }

    }
    for (int i = 0; i < graph->vertex_count; i++) {
        if (i >= v){
            adjNode* u = graph->vertices[i];
            while (u != NULL){
                u->vertex--;
                u=u->next;
            }
        }
    }
}
void delete_vertex_shell(Graph* graph){
    printf("Введите название вершины\n>");
    char* v_name = getStr();
    int v = get_number_of_vertex(graph, v_name);
    if (v < 0 || v >= graph->vertex_count){
        printf("Вершины \"%s\" нет в графе\nУдаление не выполнено", v_name);
    }
    else{
        delete_vertex(graph, v);
        printf("Вершина \"%s\" удалена", v_name);
    }
    free(v_name);
}

void delete_edge(Graph* graph, int v1, int v2){
    for (int i = 0; i < graph->vertex_count; i++){
        if (i == v1){
            adjNode* u = graph->vertices[i];
            if (u->vertex == v2){//если v является первой в списке смежности вершины u.
                graph->vertices[i] = graph->vertices[i]->next;
                free(u);
                continue;
            }
            else{
                adjNode* prev = NULL;
                while (u != NULL){
                    if (u->vertex == v2){
                        prev->next = prev->next->next;
                        free(u);
                        break;
                    }
                    prev = u;
                    u=u->next;
                }
            }
        }
        else if (i == v2){
            adjNode* u = graph->vertices[i];
            if (u->vertex == v1){//если v является первой в списке смежности вершины u.
                graph->vertices[i] = graph->vertices[i]->next;
                free(u);
                continue;
            }
            else{
                adjNode* prev = NULL;
                while (u != NULL){
                    if (u->vertex == v1){
                        prev->next = prev->next->next;
                        free(u);
                        break;
                    }
                    prev = u;
                    u=u->next;
                }
            }
        }
    }
}
void delete_edge_shell(Graph* graph){
    printf("Введите название вершины\n>");
    char* v1_name = getStr();
    printf("Введите название вершины\n>");
    char* v2_name = getStr();
    int v1 = get_number_of_vertex(graph, v1_name);
    int v2 = get_number_of_vertex(graph, v2_name);

    if (is_edge_in_graph(graph, v1, v2)){
        delete_edge(graph, v1, v2);
    }
    else{
        printf("Ребра в графе нет\n");
    }
    free(v1_name);
    free(v2_name);
}

int is_edge_in_graph_with_msg(Graph* graph, int v1, int v2){
    if ( ( (graph->vertex_count <= v1 || v1 < 0) && (graph->vertex_count <= v2 || v2 < 0) ) ){ //(graph->nof < from && graph->nof < to) || (from < 0 && to < 0)                 //( (graph->nof < from || from < 0) && (graph->nof < to || to < 0) )
        printf("Вершин \"%d\" и \"%d\" в графе нет.\n", v1, v2);
        printf("Добавление дуги (%s, %s) не выполнено\n", graph->vertex_names[v1], graph->vertex_names[v2]);
        return 0;
    }
    if (graph->vertex_count <= v1 || v1 < 0){
        printf("Вершины \"%d\" в графе нет.\n", v1);
        printf("Добавление ребра (%s, %s) не выполнено\n", graph->vertex_names[v1], graph->vertex_names[v2]);
        return 1;
    }
    if (graph->vertex_count <= v2 || v2 < 0){
        printf("Вершины \"%d\" в графе нет.\n", v2);
        printf("Добавление ребра (%s, %s) не выполнено\n", graph->vertex_names[v1], graph->vertex_names[v2]);
        return 1;
    }
    adjNode* cur = graph->vertices[v1];
    while (cur != NULL){
        if (cur->vertex == v2){
            printf("дуга (%d, %d) уже есть в графе\n", v1, v2);
            printf("Добавление ребра (%s, %s) не выполнено\n", graph->vertex_names[v1], graph->vertex_names[v2]);
            return 1;
        }
        cur=cur->next;
    }
    return 0;
}

int add_edge(Graph* graph, int v1, int v2){

    adjNode* new_node_v2 = malloc(sizeof(adjNode));
    new_node_v2->vertex = v2;
    new_node_v2->next = graph->vertices[v1];
    graph->vertices[v1] = new_node_v2;

    adjNode* new_node_v1 = malloc(sizeof(adjNode));
    new_node_v1->vertex = v1;
    new_node_v1->next = graph->vertices[v2];
    graph->vertices[v2] = new_node_v1;

    return 0;
}
void add_edge_shell(Graph* graph){
    if (graph == NULL){
        printf("Graph is not initialized\n");
        return;
    }
    else if (graph->vertex_count == 0){
        printf("Graph is empty\n");
        return;
    }

    else if (graph->vertex_count == 1){
        printf("There is only one vertex in the graph\n");
        return;
    }

    printf("Введите первую вершину\n>");
    char* v1_name = getStr();
    printf("Введите вторую вершину\n>");
    char* v2_name = getStr();

    int v1 = get_number_of_vertex(graph, v1_name);
    int v2 = get_number_of_vertex(graph, v2_name);

    if (v1 == v2){
        printf("Ошибка! Вы ввели одну и ту же вершину.\n");
        printf("Давайте дружно сделаем вид, что граф не содержит петель!!! Спасибо за понимание)))\n");
        free(v1_name);
        free(v2_name);
        return;
    }

    int is_edge_in_graph = is_edge_in_graph_with_msg(graph, v1, v2);
    if (is_edge_in_graph == 0){
        add_edge(graph, v1, v2);
        printf("Ребро (%s, %s) добавлено\n", graph->vertex_names[v1], graph->vertex_names[v2]);
    }
    free(v1_name);
    free(v2_name);
}

void print_graph(Graph* graph){
    if (graph == NULL){
        printf("Graph is not initialized\n");
        return;
    }
    else if (graph->vertex_count == 0){
        printf("Graph is empty\n");
        return;
    }

    for (int i = 0; i < graph->vertex_count; i++){
        printf("%s ", graph->vertex_names[i]);

        adjNode* cur = graph->vertices[i];
        while (cur != NULL){
            printf("%s ", graph->vertex_names[cur->vertex]);
            cur=cur->next;
        }
        printf("\n");
    }
}
void free_graph(Graph* graph){

    for (int i = 0; i < graph->vertex_count; i++){
        free(graph->vertex_names[i]);
    }
    free(graph->vertex_names);


    for (int i = 0; i < graph->vertex_count; i++){
        adjNode* cur = graph->vertices[i];
        while (cur != NULL){
            adjNode* temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
    free(graph->vertices);
    free(graph);
}

void fast_add0(Graph* graph){
    add_vertex(graph, "a");
    add_vertex(graph, "b");
    add_vertex(graph, "c");
    add_vertex(graph, "d");

    add_vertex(graph, "e");
    add_vertex(graph, "f");
    add_vertex(graph, "g");
    add_vertex(graph, "h");

    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 0, 3);

    add_edge(graph, 1, 4);
    add_edge(graph, 1, 5);

    add_edge(graph, 2, 4);
    add_edge(graph, 2, 5);
    add_edge(graph, 2, 6);

    add_edge(graph, 3, 5);
    add_edge(graph, 3, 6);

    add_edge(graph, 4, 7);

}//нет проверки на дублирующиеся вершины.
void fast_add1(Graph* graph){
    add_vertex(graph, "1");
    add_vertex(graph, "2");
    add_vertex(graph, "3");
    add_vertex(graph, "4");
    add_vertex(graph, "5");
    add_vertex(graph, "6");
    add_vertex(graph, "7");
    add_vertex(graph, "8");
    add_vertex(graph, "9");
    add_vertex(graph, "10");
    add_vertex(graph, "11");
    add_vertex(graph, "12");
    add_vertex(graph, "13");

    add_edge(graph, 0, 1);
    add_edge(graph, 0, 3);
    add_edge(graph, 0, 5);
    add_edge(graph, 0, 6);

    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);

    add_edge(graph, 2, 4);
    add_edge(graph, 2, 10);

    add_edge(graph, 3, 4);
    add_edge(graph, 3, 6);

    add_edge(graph, 4, 6);
    add_edge(graph, 4, 7);
    add_edge(graph, 4, 10);

    add_edge(graph, 5, 6);

    add_edge(graph, 6, 7);

    add_edge(graph, 7, 8);
    add_edge(graph, 7, 9);

    add_edge(graph, 8, 10);
    add_edge(graph, 8, 11);

    add_edge(graph, 10, 11);
    add_edge(graph, 10, 12);
    add_edge(graph, 11, 12);

}
void fast_add3(Graph* graph){
    add_vertex(graph, "a");
    add_vertex(graph, "b");
    add_vertex(graph, "c");
    add_vertex(graph, "d");
    add_vertex(graph, "e");
    add_vertex(graph, "g");
    add_vertex(graph, "h");
    add_vertex(graph, "i");

    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 3);
    add_edge(graph, 2, 4);
    add_edge(graph, 4, 5);
    add_edge(graph, 4, 7);
    add_edge(graph, 5, 6);
    add_edge(graph, 5, 7);
    add_edge(graph, 6, 7);
}
void fast_add_small(Graph* graph){
    add_vertex(graph, "1");
    add_vertex(graph, "2");
    add_vertex(graph, "3");
    add_vertex(graph, "4");

    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 0, 3);
    add_edge(graph, 2, 3);
}



Queue* init_Queue(){
    Queue* queue = malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}
void free_Queue(Queue* queue){
    qNode* cur = queue->head;
    while (cur != NULL){
        qNode* temp = cur;
        cur=cur->next;
        free(temp);
    }
    free(queue);
}
void push(Queue* queue, int vertex){

    qNode* new_node = malloc(sizeof(qNode));
    new_node->next = NULL;
    new_node->vertex = vertex;

    if (queue->head == NULL){
        queue->head = new_node;
        queue->tail = new_node;
        return;
    }

    queue->tail->next = new_node;
    queue->tail = new_node;
}
int pop(Queue* queue, int* pres){
    if (queue->head == NULL){
        return 1;
    }

    qNode* rem_node = queue->head;
    *pres = rem_node->vertex;

    queue->head = queue->head->next;

    if (queue->head == NULL){
        queue->tail = NULL;
    }

    free(rem_node);
    return 0;
}

void print_path(Graph* graph, int* pred, int s, int v){
    if (s == v){
        printf("%s ", graph->vertex_names[s]);
    }
    else{
        if (pred[v] == -1){
            printf("Путь из \"%s\" в \"%s\" отсутствует\n", graph->vertex_names[s], graph->vertex_names[v]);
        }
        else{
            print_path(graph, pred, s, pred[v]);
            printf("%s ", graph->vertex_names[v]);
        }
    }
}
void bfs(Graph* graph, int s, int f){
    //init
    int* color = malloc(sizeof(int) * graph->vertex_count);
    int* d = malloc(sizeof(int) * graph->vertex_count);
    int* pred = malloc(sizeof(int) * graph->vertex_count);
    Queue* queue = init_Queue();

    for (int i = 0; i < graph->vertex_count; i++){
        color[i] = 0;
        d[i] = INT_MAX;
        pred[i] = -1;
    }

    color[s] = 1;
    d[s] = 0;
    push(queue, s);

    //обработка
    while (queue->head != NULL){
        int v = -1;
        pop(queue, &v);

        adjNode* u = graph->vertices[v];
        while (u != NULL){
            if (color[u->vertex] == 0){
                color[u->vertex] = 1;
                d[u->vertex] = d[v] + 1;
                pred[u->vertex] = v;
                push(queue, u->vertex);
            }

            u = u->next;
        }
        color[v] = 2;
    }

    print_path(graph, pred, s, f);
    printf("\n");


    free(color);
    free(d);
    free(pred);
    free_Queue(queue);

}
void bfs_shell(Graph* graph){
    printf("Введите первую вершину\n>");
    char* v1_name = getStr();
    printf("Введите вторую вершину\n>");
    char* v2_name = getStr();

    int v1 = get_number_of_vertex(graph, v1_name);
    int v2 = get_number_of_vertex(graph, v2_name);

    if (is_vertex_in_graph(graph, v1) && is_vertex_in_graph(graph, v2)){
        bfs(graph, v1, v2);
    }
    else{
        printf("BFS не был запущен, потому что какой-то из вершин нет в графе\n");
    }

    free(v1_name);
    free(v2_name);
}



void add_edge_in_edges(Edges* edges, int v1, int v2){
    eNode* new_node = malloc(sizeof(eNode));
    new_node->v1 = v1;
    new_node->v2 = v2;
    new_node->next = edges->head;
    edges->head = new_node;
}
int is_edge_in_edges(Edges* edges, int v1, int v2){
    eNode* cur = edges->head;
    while (cur != NULL){
        if ( (v1 == cur->v1 && v2 == cur->v2) || (v1 == cur->v2 && v2 == cur->v1) ){
            return 1;
        }
        cur=cur->next;
    }
    return 0;
}
void free_edges(Edges* edges){
    eNode* cur = edges->head;
    while (cur != NULL){
        eNode* temp = cur;
        cur=cur->next;
        free(temp);
    }
    free(edges);
}
Edges* get_edges(Graph* graph){
    Edges* edges = malloc(sizeof(Edges));
    edges->head = NULL;

    for (int v1 = 0; v1 < graph->vertex_count; v1++){
        adjNode* v2 = graph->vertices[v1];
        while (v2 != NULL){
            if (is_edge_in_edges(edges, v1, v2->vertex) == 0){
                add_edge_in_edges(edges, v1, v2->vertex);
            }
            v2 = v2->next;
        }


    }
    return edges;
}
void print_edges(Graph* graph, Edges* edges){
    eNode* cur = edges->head;
    while (cur != NULL){
        printf("(%s, %s)\n", graph->vertex_names[cur->v1], graph->vertex_names[cur->v2]);
        cur=cur->next;
    }
}
void bellman_ford(Graph* graph, int s, int f){
    //init
    int* d = malloc(sizeof(int) * graph->vertex_count);
    int* pred = malloc(sizeof(int) * graph->vertex_count);
    for (int i = 0; i < graph->vertex_count; i++){
        d[i] = INT_MAX;
        pred[i] = -1;
    }
    d[s] = 0;
    //обработка
    Edges* edges = get_edges(graph);
    print_edges(graph, edges);

    for (int i = 1; i < graph->vertex_count; i++) {
        eNode* edge = edges->head;
        while (edge != NULL){

            if (d[edge->v1] == INT_MAX && d[edge->v2] == INT_MAX){
                edge=edge->next;
                continue;
            }
            else if (d[edge->v1] == INT_MAX && d[edge->v2] != INT_MAX){
                d[edge->v1] = d[edge->v2] + 1;
                pred[edge->v1] = edge->v2;
            }
            else if (d[edge->v1] != INT_MAX && d[edge->v2] == INT_MAX){
                d[edge->v2] = d[edge->v1] + 1;
                pred[edge->v2] = edge->v1;
            }
            else if (d[edge->v1] > d[edge->v2] + 1){
                d[edge->v1] = d[edge->v2] + 1;
                pred[edge->v1] = edge->v2;
            }
            else if (d[edge->v2] > d[edge->v1] + 1){
                d[edge->v2] = d[edge->v1] + 1;
                pred[edge->v2] = edge->v1;
            }
            edge=edge->next;
        }
    }
    printf("pred: ");
    for (int i = 0; i < graph->vertex_count; i++) {
        printf("%d ", pred[i]);
    }
    printf("\n");
    printf("d: ");
    for (int i = 0; i < graph->vertex_count; i++) {
        printf("%d ", d[i]);
    }
    printf("\n");
    print_path(graph, pred, s, f);
    printf("\n");

    free_edges(edges);
    free(d);
    free(pred);
}
void bellman_ford_shell(Graph* graph){
    printf("Введите первую вершину\n>");
    char* v1_name = getStr();
    printf("Введите вторую вершину\n>");
    char* v2_name = getStr();

    int v1 = get_number_of_vertex(graph, v1_name);
    int v2 = get_number_of_vertex(graph, v2_name);

    if (v1 == v2){
        printf("Ошибка! Вы ввели одну и ту же вершину\n");
        free(v1_name);
        free(v2_name);
        return;
    }

    if (is_vertex_in_graph(graph, v1) && is_vertex_in_graph(graph, v2)){
        bellman_ford(graph, v1, v2);
    }
    else{
        printf("Bellman ford не был запущен, потому что какой-то из вершин нет в графе\n");
    }

    free(v1_name);
    free(v2_name);
}

int print_matrix(Graph* graph, int** matrix){
    if (matrix == NULL){
        printf("Matrix is not initialized\n");
        return 1;
    }

    printf("    ");
    for (int i = 0; i < graph->vertex_count; i++){
        printf("%3s ", graph->vertex_names[i]);
    }
    printf("\n\n");
    for (int i = 0; i < graph->vertex_count; i++){
        printf("%3s ", graph->vertex_names[i]);
        for (int j = 0; j < graph->vertex_count; j++){
            if ( matrix[i][j] == INT_MAX){
                printf(" оо ");
            }
            else{
                if (matrix[i][j] != -1 && matrix[i][j] != INT_MAX){
                    printf("%3s ", graph->vertex_names[matrix[i][j]]);
                }
                if (matrix[i][j] == -1){
                    printf("  o ");
                }
            }
        }
        printf("\n");
    }
    return 0;
}
int** copy_matrix(int** matrix, int size){
    int** new_matrix = malloc(sizeof(int*) * size);
    for (int i = 0; i < size; i++){
        new_matrix[i] = malloc(sizeof(int) * size);
        for (int j = 0; j < size; j++){
            new_matrix[i][j] = matrix[i][j];
        }
    }
    return new_matrix;
}
void free_matrix(int** matrix, int size){
    for (int i = 0; i < size; i++){
        free(matrix[i]);
    }
    free(matrix);
}
int* matrix_to_array(int** matrix, int size){
    int k = 0;
    int* array = malloc(sizeof(int) * size * size);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            array[k] = matrix[i][j];
            k++;
        }
    }
    return array;
}
void sort_array(int* arr, int size){
    for(int i = 0 ; i < size - 1; i++) {
        for(int j = 0 ; j < size - i - 1 ; j++) {
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1] ;
                arr[j+1] = tmp;
            }
        }
    }
}
void print_array(int* arr, int size){
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int cmp_ways(Way way1, Way way2){
    if (way1.v1 == way2.v1 && way1.v2 == way2.v2){
        return 1;
    }
    else if (way1.v1 == way2.v2 && way1.v2 == way2.v1){
        return 1;
    }
    return 0;
}//1 если равны. 0 если не равны
int is_way_in_ways(Way* ways, int ways_size, Way way){
    int is_way_in_ways = 0;
    for (int j = 0; j < ways_size; j++){
        if (cmp_ways(way, ways[j]) == 1){
            is_way_in_ways = 1;
            break;
        }
    }
    return is_way_in_ways;
}
Way get_way_by_value(int** matrix, int size,  int value, int num){//num - какой элемент из матрицы нам нужен
    int num2 = 0;
    for (int i =0; i < size; i++){
        for (int j =0; j < size; j++){
            if (matrix[i][j] == value && num == num2){
                Way way;
                way.v1 = i;
                way.v2 = j;
                return way;
            }
            else if (matrix[i][j] == value){
                num2++;
            }
        }
    }
}
void print_ways(Graph* graph, Way* ways, int ways_size){
    for (int j = 0; j < ways_size; j++){
        printf("(%s, %s)\n", graph->vertex_names[ways[j].v1], graph->vertex_names[ways[j].v2]);
    }
}
void shortest_path(Graph* graph, int** pred, int** d, int v1, int v2){
    if (d[v1][v2] == INT_MAX){
        printf("ПУТИ НЕТ\n");
    }
    int c = v1;
    while (c != v2){
        printf("%s ", graph->vertex_names[c]);
        c = pred[c][v2];
    }
    printf("%s ", graph->vertex_names[v2]);
}
void print_floyd_warshall_matrix(Graph* graph, int** pred, int** d){
    printf("============================d============================\n");
    print_matrix(graph, d);
    printf("\n");
    printf("\n");
    //printf("=========================pred============================\n");
    //print_matrix(graph, pred);
    //printf("\n");
}
void floyd_warshall_init(Graph* graph, int** pred, int** d){
    for (int i = 0; i < graph->vertex_count; i++){
        d[i] = malloc(sizeof(int) * graph->vertex_count);
        pred[i] = malloc(sizeof(int) * graph->vertex_count);
        for (int j = 0; j < graph->vertex_count; j++){
            d[i][j] = INT_MAX;
            pred[i][j] = -1;
        }
    }
}
void floyd_warshall(Graph* graph){
    int** d = malloc(sizeof(int*) * graph->vertex_count);
    int** pred = malloc(sizeof(int*) * graph->vertex_count);
    floyd_warshall_init(graph, pred, d);

    for (int i = 0; i < graph->vertex_count; i++){
        adjNode* cur = graph->vertices[i];
        while (cur != NULL){
            d[i][cur->vertex] = 1;
            pred[i][cur->vertex] = cur->vertex;
            cur = cur->next;
        }
        d[i][i] = 0;
    }
    print_floyd_warshall_matrix(graph, pred, d);
    for (int k = 1; k < graph->vertex_count; k++){
        int** new_pred = copy_matrix(pred, graph->vertex_count);
        int** new_d = copy_matrix(d, graph->vertex_count);
        for (int i = 0; i < graph->vertex_count; i++){
            for (int j = 0; j < graph->vertex_count; j++){
                if (d[i][j] == INT_MAX && (d[i][k] == INT_MAX || d[k][j] == INT_MAX ) ){
                    new_pred[i][j] = pred[i][j];
                }
                else if (d[i][j] == INT_MAX && d[i][k] != INT_MAX && d[k][j] != INT_MAX){
                    //printf("d[i][j] = %d\nd[i][k] = %d\nd[k][j] = %d\npred[k][j] = %d\n", d[i][j], d[i][k], d[k][j], pred[k][j]);
                    new_pred[i][j] = pred[k][j];
                }
                else if (d[i][j] != INT_MAX && (d[i][k] == INT_MAX || d[k][j] == INT_MAX )){
                    new_pred[i][j] = pred[i][j];
                }
                else if (d[i][j] <= d[i][k] + d[k][j]){
                    new_pred[i][j] = pred[i][j];
                }
                else if (d[i][j] > d[i][k] + d[k][j]){
                    new_pred[i][j] = pred[k][j];
                }
                /////////////////////////////////////////////////////////////
                if (d[i][k] == INT_MAX || d[k][j] == INT_MAX){
                    new_d[i][j] = d[i][j];
                }
                else if (d[i][k] != INT_MAX && d[k][j] != INT_MAX){
                    if (d[i][j] > d[i][k] + d[k][j]){
                        new_d[i][j] = d[i][k] + d[k][j];
                    }
                    else if (d[i][j] <= d[i][k] + d[k][j]){
                        new_d[i][j] = d[i][j];
                    }
                }
            }
        }
        free_matrix(d, graph->vertex_count);
        free_matrix(pred, graph->vertex_count);

        d = new_d;
        pred = new_pred;
    }
    printf("\n000000000000000000000000000000000000000000000000000000000000000\n");
    printf("0000000000000000000000___FLOYD_WARSHALL___000000000000000000000\n");
    printf("000000000000000000000000000000000000000000000000000000000000000\n\n");
    print_floyd_warshall_matrix(graph, pred, d);

    int* arr = matrix_to_array(d, graph->vertex_count);
    sort_array(arr, graph->vertex_count* graph->vertex_count);

    int counter = 0;//количество разных нормальный путей
    for (int i = 0; i < graph->vertex_count* graph->vertex_count; i++){
        if (arr[i] != 0 && arr[i] != INT_MAX){
            counter++;
        }
    }
    counter = counter / 2;

    if (counter < 3){
        printf("Алгоритм floyd_warshall выполнен\n");
        printf("В графе нет трёх различных путей\n");
        printf("Задайте другой граф\n");
        free(arr);
        free_matrix(d, graph->vertex_count);
        free_matrix(pred, graph->vertex_count);
        return;
    }

    Way* ways = malloc(sizeof(Way)*3);
    int busy = 0;
    for (int i = 0; i < 3; i++){
        ways[i].v1 = -1;
        ways[i].v2 = -1;
    }
    for (int i = 0; i < graph->vertex_count * graph->vertex_count; i++){
        if (busy == 3){
            break;
        }
        if (arr[i] != INT_MAX && arr[i] != 0){
            int check = 0;
            int k = 0;
            while (check != 1){
                Way way = get_way_by_value(d, graph->vertex_count, arr[i], k);
                if (busy == 0){
                    ways[0] = way;
                    busy++;
                    check = 1;
                }
                else{
                    int way_in_ways = is_way_in_ways(ways, busy, way);
                    if (is_way_in_ways(ways, busy, way) == 0){
                        ways[busy] = way;
                        busy++;
                        check = 1;
                    }
                }
                k++;
            }

        }
    }

    for (int i = 0; i < 3; i++){
        printf("Кратчайший путь №%d: между вершинами %s и %s\n", i+1, graph->vertex_names[ways[i].v1], graph->vertex_names[ways[i].v2]);
        shortest_path(graph, pred, d, ways[i].v1, ways[i].v2);
        printf("\n");
    }

    free(ways);
    free(arr);
    free_matrix(d, graph->vertex_count);
    free_matrix(pred, graph->vertex_count);
}
void floyd_warshall_shell(Graph* graph){
    //printf("Введите первую вершину\n>");
    //char* v_name = getStr();
    //int v = get_number_of_vertex(graph, v_name);
    //if (is_vertex_in_graph(graph, v)){

    if (graph == NULL){
        printf("The graph is not initialized\n");
        printf("Алгоритм Флойда-Варшалла не был запущен\n");
        return;
    }
    else if (graph->vertex_count < 2){
        printf("В графе недостаточно вершин (меньше 2)\n");
        printf("Алгоритм Флойда-Варшалла не был запущен\n");
        return;
    }

    floyd_warshall(graph);

    //free(v_name);
}


void printMenu(){
    printf("\nЧто изволите, сударь?\n");
    printf("1. добавление новой вершины\n");
    printf("2. добавление нового ребра между двумя заданными вершинами\n");
    printf("3. удаление заданной вершины\n");
    printf("4. удаление заданного ребра\n");
    printf("5. вывод графа в виде матрицы или списков смежности\n");
    printf("6. BFS\n");
    printf("7. bellman_ford\n");
    printf("8. floyd_warshall\n");
    //printf("6. поиск пути между двумя вершинами графа\n");
    //printf("7. Поиск кратчайшего пути между двумя заданными вершинами графа, использующий алгоритм Беллмана-Форда\n");
    //printf("8. Поиск первых трёх кратчайших путей между двумя любыми вершинами графа\n");
    printf("9. fast_add1()\n");
    //printf("10. fast_add2()\n");
    printf("11. fast_add3()\n");
    printf("12. fast_add_small()\n");
    //printf("404. Очистить экран\n");
    printf("0. Завершение программы\n");
    printf(">");
}//cool
int Menu(Graph* graph){
    int choice;
    do {
        printMenu();
        scanf("%d", &choice);
        scanf("%*[^\n]");
        scanf("%*c");
        if (choice == 1){
            add_vertex_shell(graph);
        }
        else if (choice == 2){
            add_edge_shell(graph);
        }
        else if (choice == 3){
            delete_vertex_shell(graph);
        }
        else if (choice == 4){
            delete_edge_shell(graph);
        }
        else if (choice == 5){
            print_graph(graph);
        }
        else if (choice == 6){
            bfs_shell(graph);
        }
        else if (choice == 7){
            bellman_ford_shell(graph);
        }
        else if (choice == 8){
            floyd_warshall_shell(graph);
        }
        else if (choice == 9){
            fast_add1(graph);
        }
        else if (choice == 10){
            //fast_add2(graph);
        }
        else if (choice == 11){
            fast_add3(graph);
        }
        else if (choice == 12){
            fast_add_small(graph);
        }
    } while (choice != 0);
    printf("The program was stopped\n");
}



int main(){
    Graph* graph = init_graph();
    Menu(graph);
    free_graph(graph);
    return 0;
}