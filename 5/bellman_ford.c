//
// Created by andrew on 15.07.22.
//

#include "bellman_ford.h"

int is_edge_in_edges(Graph* graph, Edges* edges, String* v1, String* v2){
    eNode* cur = edges->head;
    while (cur != NULL) {
        if (strcmp(cur->edge->v1->str, v1->str) == 0 && strcmp(cur->edge->v2->str, v2->str) == 0){
            return 1;
        }
        else if (strcmp(cur->edge->v1->str, v2->str) == 0 && strcmp(cur->edge->v2->str, v1->str) == 0){
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

void add_edge_to_edges(Edges* edges, String* v1, String* v2, int ind1, int ind2){
    Edge* edge = malloc(sizeof(Edge));
    edge->v1 = malloc(sizeof(String));
    edge->v1->len = v1->len;
    edge->v1->str = malloc(sizeof(char)*(edge->v1->len + 1));
    strcpy(edge->v1->str, v1->str);
    edge->ind1 = ind1;

    edge->v2 = malloc(sizeof(String));
    edge->v2->len = v2->len;
    edge->v2->str = malloc(sizeof(char)*(edge->v2->len + 1));
    strcpy(edge->v2->str, v2->str);
    edge->ind2 = ind2;

    eNode* newNode = malloc(sizeof(eNode));
    newNode->edge = edge;
    newNode->next = edges->head;

    edges->head =  newNode;
}

Edges* create_edges(Graph* graph){
    Edges* edges = malloc(sizeof(Edges));
    edges->head = NULL;
    for (int i = 0; i < graph->v; i++){
        Node* cur = graph->Garr[i].adjacent;
        while(cur != NULL){
            for (int j = 0; j < graph->v; j++){
                if (strcmp(graph->Garr[j].vertex->str, cur->ver->str) == 0){
                    if (is_edge_in_edges(graph, edges, graph->Garr[i].vertex, graph->Garr[j].vertex) == 0){
                        add_edge_to_edges(edges, graph->Garr[i].vertex, graph->Garr[j].vertex, i, j);
                    }
                }
            }
            cur=cur->next;
        }
    }
    return edges;
}

void print_edges(Edges* edges){
    eNode* cur = edges->head;
    if (cur == NULL){
        printf("No edges\n");
        return;
    }
    while (cur != NULL){
        printf("(%s, %s)  ", cur->edge->v1->str, cur->edge->v2->str);
        cur=cur->next;
    }
    printf("\n");
}

void free_edges(Edges* edges){
    eNode* cur = edges->head;
    while (cur != NULL){
        eNode* temp = cur;
        cur=cur->next;
        free(temp->edge->v1->str);
        free(temp->edge->v1);
        free(temp->edge->v2->str);
        free(temp->edge->v2);
        free(temp->edge);
        free(temp);
    }
    free(edges);
    edges = NULL;
}

int init_bellman_ford(Graph* graph, distance_cell* d, predecessor_cell* pred,  String* v1){
    for (int i = 0; i < graph->v; i++){
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
            d[i].distance = 0;
        }
    }
}

int bellman_ford(Graph *graph, distance_cell *d, predecessor_cell *pred, Edges *edges, String *v1) {
    for (int i =0; i < graph->v; i++){
        eNode* cur = edges->head;
        while (cur != NULL){

            //printf("i = %d, edge = (%s, %s)\n", i, cur->edge->v1->str, cur->edge->v2->str);
            //printf("graph[ind1] = %s, graph[ind2] = %s\n", graph->Garr[cur->edge->ind1].vertex->str, graph->Garr[cur->edge->ind2].vertex->str);
            //print_dist_bfs(graph, d);
            //print_pred_bfs(graph, pred);

            if ( d[cur->edge->ind1].distance != -1 && d[cur->edge->ind2].distance == -1 ){
                d[cur->edge->ind2].distance = d[cur->edge->ind1].distance + 1;

                if (pred[cur->edge->ind2].pred_vertex != NULL){
                    free(pred[cur->edge->ind2].pred_vertex->str);
                    free(pred[cur->edge->ind2].pred_vertex);
                }

                pred[cur->edge->ind2].pred_vertex = malloc(sizeof(String));
                pred[cur->edge->ind2].pred_vertex->len = cur->edge->v1->len;
                pred[cur->edge->ind2].pred_vertex->str = malloc(sizeof(char) * (pred[cur->edge->ind2].pred_vertex->len + 1));
                strcpy(pred[cur->edge->ind2].pred_vertex->str, cur->edge->v1->str);
            }

            else if ( d[cur->edge->ind1].distance == -1 && d[cur->edge->ind2].distance != -1 ){
                d[cur->edge->ind1].distance = d[cur->edge->ind2].distance + 1;

                if (pred[cur->edge->ind1].pred_vertex != NULL){
                    free(pred[cur->edge->ind1].pred_vertex->str);
                    free(pred[cur->edge->ind1].pred_vertex);
                }

                pred[cur->edge->ind1].pred_vertex = malloc(sizeof(String));
                pred[cur->edge->ind1].pred_vertex->len = cur->edge->v2->len;
                pred[cur->edge->ind1].pred_vertex->str = malloc(sizeof(char) * (pred[cur->edge->ind1].pred_vertex->len + 1));
                strcpy(pred[cur->edge->ind1].pred_vertex->str, cur->edge->v2->str);
            }

            else if ( d[cur->edge->ind1].distance > d[cur->edge->ind2].distance + 1 ){
                d[cur->edge->ind1].distance = d[cur->edge->ind2].distance + 1;

                if (pred[cur->edge->ind1].pred_vertex != NULL){
                    free(pred[cur->edge->ind1].pred_vertex->str);
                    free(pred[cur->edge->ind1].pred_vertex);
                }

                pred[cur->edge->ind1].pred_vertex = malloc(sizeof(String));
                pred[cur->edge->ind1].pred_vertex->len = cur->edge->v2->len;
                pred[cur->edge->ind1].pred_vertex->str = malloc(sizeof(char) * (pred[cur->edge->ind1].pred_vertex->len + 1));
                strcpy(pred[cur->edge->ind1].pred_vertex->str, cur->edge->v2->str);

            }
            else if ( d[cur->edge->ind2].distance > d[cur->edge->ind1].distance + 1 ){
                d[cur->edge->ind2].distance = d[cur->edge->ind1].distance + 1;

                if (pred[cur->edge->ind2].pred_vertex != NULL){
                    free(pred[cur->edge->ind2].pred_vertex->str);
                    free(pred[cur->edge->ind2].pred_vertex);
                }

                pred[cur->edge->ind2].pred_vertex = malloc(sizeof(String));
                pred[cur->edge->ind2].pred_vertex->len = cur->edge->v1->len;
                pred[cur->edge->ind2].pred_vertex->str = malloc(sizeof(char) * (pred[cur->edge->ind2].pred_vertex->len + 1));
                strcpy(pred[cur->edge->ind2].pred_vertex->str, cur->edge->v1->str);
            }
                cur=cur->next;
        }
    }
}
//bellman ford algorithm

int bellman_ford_shell(Graph* graph){
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
        distance_cell* d = malloc(sizeof(distance_cell) * graph->v);
        predecessor_cell* pred = malloc(sizeof(predecessor_cell) * graph->v);

        init_bellman_ford(graph, d, pred, v1);
        Edges* edges = create_edges(graph);
        bellman_ford(graph, d, pred, edges, v1);

        for (int i = 0; i < graph->v; i++){
            if ( strcmp(d[i].vertex->str, v2->str) == 0){
                if (d[i].distance  == -1){
                    break;
                }
                printf("Кратчайший путь от %s до %s имеет длину %d\n", v1->str, v2->str, d[i].distance);
                break;
            }
        }

        print_bfs(graph, pred, v1, v2);
        printf("\n");

        free_dist(graph, d);
        free_pred(graph, pred);
        free_edges(edges);
        free(v1->str);
        free(v1);
        free(v2->str);
        free(v2);
    }
}

