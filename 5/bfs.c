//
// Created by andrew on 15.07.22.
//

#include "bfs.h"

Queue_bfs* init_queue_bfs(){
    Queue_bfs* queue = malloc(sizeof(Queue_bfs));
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void push(Queue_bfs* queue, String* v){
    //printf("Пытаемся добавить в очередь: %s\n", v->str);
    if (queue->head == NULL){

        qNode* newNode = malloc(sizeof(qNode));
        newNode->vertex = malloc(sizeof(String));
        newNode->vertex->len = v->len;
        newNode->vertex->str = malloc(sizeof(char) * (newNode->vertex->len + 1));
        strcpy(newNode->vertex->str, v->str);
        newNode->next = NULL;

        queue->head = newNode;
        queue->tail = newNode;
        //printf("добавилась в начало: %s\n", v->str);
        return;
    }

    else{
        qNode* newNode = malloc(sizeof(qNode));
        newNode->vertex = malloc(sizeof(String));
        newNode->vertex->len = v->len;
        newNode->vertex->str = malloc(sizeof(char) * (newNode->vertex->len + 1));
        strcpy(newNode->vertex->str, v->str);
        newNode->next = NULL;

        queue->tail->next = newNode;
        queue->tail = newNode;
        //printf("добавилась %s\n", v->str);
        return;
    }
}

String* pop(Queue_bfs* queue){
    if (queue->head == NULL){
        return NULL;
    }
    else{
        String* v = malloc(sizeof(String));
        v->len = queue->head->vertex->len;
        v->str = malloc(sizeof(char) * (v->len + 1));
        strcpy(v->str, queue->head->vertex->str);

        qNode* temp = queue->head;
        queue->head = queue->head->next;
        free(temp->vertex->str);
        free(temp->vertex);
        free(temp);

        if (queue->head == NULL){
            queue->tail = NULL;
        }
        return v;
    }
}

int is_vertex_in_queue(Graph* graph, Queue_bfs* queue, String* vertex){
    qNode* cur = queue->head;
    while (cur != NULL){
        if (strcmp(cur->vertex->str, vertex->str) == 0){
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

void print_queue_bfs(Graph* graph, Queue_bfs* queue){
    qNode* cur = queue->head;

    if (cur == NULL){
        printf("The queue is empty\n");
        return;
    }
    printf("Queue: ");
    while (cur != NULL){
        printf("%s ", cur->vertex->str);
        cur=cur->next;
    }
    printf("\n\n");
}
void print_color_bfs(Graph* graph, color_cell* color){
    printf("=========COLOR=========\n");
    for (int i = 0; i < graph->v; i++){
        if (color[i].color == 0){
            printf("Vertex: %s, color: white\n", color[i].vertex->str);
        }
        else if (color[i].color == 1){
            printf("Vertex: %s, color: grey\n", color[i].vertex->str);
        }
        else if (color[i].color == 2){
            printf("Vertex: %s, color: black\n", color[i].vertex->str);
        }
    }
    printf("\n");
}
void print_dist_bfs(Graph* graph, distance_cell* d){
    printf("=========DIST=========\n");
    for (int i = 0; i < graph->v; i++){
        printf("Vertex: %s, dist: %d\n", d[i].vertex->str, d[i].distance);
    }
    printf("\n");
}
void print_pred_bfs(Graph* graph, predecessor_cell* pred){
    printf("=========PRED=========\n");
    for (int i = 0; i < graph->v; i++){
        if (pred[i].pred_vertex == NULL) {
            printf("Vertex: %s, pred_Vertex: NULL\n", pred[i].vertex->str);
        }
        else{
            printf("Vertex: %s, pred_Vertex: %s\n", pred[i].vertex->str, pred[i].pred_vertex->str);
        }
    }
    printf("\n");
}
void print_all_arrays(Graph* graph, Queue_bfs* queue, color_cell* color, distance_cell* d, predecessor_cell* pred){
    print_queue_bfs(graph, queue);
    print_color_bfs(graph, color);
    print_dist_bfs(graph, d);
    print_pred_bfs(graph, pred);
    printf("\n");
}

int init_bfs(Graph* graph, Queue_bfs* queue, color_cell* color, distance_cell* d, predecessor_cell* pred, String* v1){
    for (int i = 0; i < graph->v; i++) {
        String *cv = malloc(sizeof(String));
        cv->len = graph->Garr[i].vertex->len;
        cv->str = malloc(sizeof(char) * (cv->len + 1));
        strcpy(cv->str, graph->Garr[i].vertex->str);
        color[i].vertex = cv;
        color[i].color = 0;


        String *dv = malloc(sizeof(String));
        dv->len = graph->Garr[i].vertex->len;
        dv->str = malloc(sizeof(char) * (dv->len + 1));
        strcpy(dv->str, graph->Garr[i].vertex->str);
        d[i].vertex = dv;
        d[i].distance = -1;


        String* pv = malloc(sizeof(String));
        pv->len = graph->Garr[i].vertex->len;
        pv->str = malloc(sizeof(char) * (pv->len + 1));
        strcpy(pv->str, graph->Garr[i].vertex->str);
        pred[i].vertex = pv;
        pred[i].pred_vertex = NULL;

        if (strcmp(v1->str, graph->Garr[i].vertex->str) == 0) {
            color[i].color = 1;
            d[i].distance = 0;
        }
    }
}

int bfs(Graph* graph, Queue_bfs* queue, color_cell* color, distance_cell* d, predecessor_cell* pred, String* v1){

    push(queue, v1);
    int counter = 0;
    //bfs
    while(queue->head != NULL){//while Очередь не пуста
        if (counter > 10){ break;}
        counter+=1;
        //printf("counter: %d\n", counter);
        //print_all_arrays(graph, queue, color, d, pred);

        String* u = pop(queue);//u - очередная вершина из очереди
        for (int i = 0; i < graph->v; i++){//находим индекс u
            if (strcmp(u->str, graph->Garr[i].vertex->str) == 0){
                Node* cur = graph->Garr[i].adjacent;//пробегаемся по вершинам, смежным с u.
                while (cur != NULL){//v = cur->ver - смежные с U вершины.
                    for (int j = 0; j < graph->v; j++){
                        if ( (strcmp(cur->ver->str, graph->Garr[j].vertex->str) == 0) && (color[j].color == 0) ){
                            color[j].color = 1;//красим v в серый цвет
                            push(queue, graph->Garr[j].vertex);
                            d[j].distance = d[i].distance + 1;

                            String* u_copy = malloc(sizeof(String));
                            u_copy->len = graph->Garr[i].vertex->len;
                            u_copy->str = malloc(sizeof(char) * (u_copy->len + 1));
                            strcpy(u_copy->str, graph->Garr[i].vertex->str);
                            pred[j].pred_vertex = u_copy;
                        }
                    }
                    cur = cur->next;
                }
                color[i].color = 2;
            }
        }
        free(u->str);
        free(u);

    }


    //print_all_arrays(graph, queue, color, d, pred);
    //free_bfs(graph, queue, color, d, pred);
}

void print_bfs(Graph* graph, predecessor_cell* pred, String* v1, String* v2){
    if (strcmp(v1->str, v2->str) == 0) {
        printf("%s  ", v2->str);
    }
    else{
        for (int i = 0; i < graph->v; i++){
            if (strcmp(v2->str, pred[i].vertex->str) == 0){
                if (pred[i].pred_vertex == NULL){
                    printf("Пути нет\n");
                    return;
                }
                else{
                    print_bfs(graph, pred, v1, pred[i].pred_vertex);
                    printf("%s  ", v2->str);
                    return;
                }
            }
        }
    }
}

void free_queue_bfs(Queue_bfs* queue){
    qNode* cur = queue->head;
    while (cur != NULL){
        qNode* temp = cur;
        cur=cur->next;
        free(temp->vertex->str);
        free(temp->vertex);
        free(temp);
    }
    free(queue);
    queue = NULL;
}
void free_color(Graph* graph, color_cell* color){
    for (int i = 0; i < graph->v; i++){
        free(color[i].vertex->str);
        free(color[i].vertex);
    }
    free(color);
}
void free_dist(Graph* graph, distance_cell* d){
    for (int i = 0; i < graph->v; i++) {
        free(d[i].vertex->str);
        free(d[i].vertex);
    }
    free(d);
}
void free_pred(Graph* graph, predecessor_cell* pred){
    for (int i =0; i < graph->v; i++){
        free(pred[i].vertex->str);
        free(pred[i].vertex);
        if (pred[i].pred_vertex != NULL ){
            free(pred[i].pred_vertex->str);
            free(pred[i].pred_vertex);
        }
    }
    free(pred);
}
void free_bfs(Graph* graph, Queue_bfs* queue, color_cell* color, distance_cell* d, predecessor_cell* pred){
    free_queue_bfs(queue);
    free_color(graph, color);
    free_dist(graph, d);
    free_pred(graph, pred);
}

int bfs_shell(Graph* graph){
    printf("Введите название первой вершины\n>");
    String* v1 = getStr();
    printf("Введите название второй вершины\n>");
    String* v2 = getStr();

    int Is_v1_in_graph = search(graph, v1);
    int Is_v2_in_graph = search(graph, v2);

    if (Is_v1_in_graph == 0 && Is_v2_in_graph == 1){
        printf("Вершины \"%s\" в графе нет. Поиск не был выполнен.\n", v1->str);
        free(v1->str);
        free(v1);
        free(v2->str);
        free(v2);
    }
    else if (Is_v1_in_graph == 1 && Is_v2_in_graph == 0){
        printf("Вершины \"%s\" в графе нет. Поиск не был выполнен.\n", v2->str);
        free(v1->str);
        free(v1);
        free(v2->str);
        free(v2);
    }
    else if (Is_v1_in_graph == 0 && Is_v2_in_graph == 0){
        printf("Вершин \"%s\" и \"%s\" в графе нет. Поиск не был выполнен.\n", v1->str, v2->str);
        free(v1->str);
        free(v1);
        free(v2->str);
        free(v2);
    }
    else{
        Queue_bfs* queue = init_queue_bfs();
        color_cell* color = malloc(sizeof(color_cell) * graph->v);
        distance_cell* d = malloc(sizeof(distance_cell) * graph->v);
        predecessor_cell* pred = malloc(sizeof(predecessor_cell) * graph->v);

        init_bfs(graph, queue, color, d, pred, v1);

        bfs(graph, queue, color, d, pred, v1);

        print_bfs(graph, pred, v1, v2);

        free_bfs(graph, queue, color, d, pred);
        free(v1->str);
        free(v1);
        free(v2->str);
        free(v2);
    }

}