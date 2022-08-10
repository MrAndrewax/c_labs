//
// Created by andrew on 15.07.22.
//

#ifndef INC_5_BFS_H
#define INC_5_BFS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

typedef struct color_cell{
    String* vertex;
    int color; //0 - белый; 1 - серый; 2 - чёрный
} color_cell;

typedef struct qNode{
    String* vertex;
    struct qNode* next;
} qNode;

typedef struct Queue_bfs{
    qNode* head;
    qNode* tail;
} Queue_bfs;

Queue_bfs* init_queue_bfs();
void push(Queue_bfs* queue, String* v);
String* pop(Queue_bfs* queue);
int is_vertex_in_queue(Graph* graph, Queue_bfs* queue, String* vertex);
void print_queue_bfs(Graph* graph, Queue_bfs* queue);
void print_color_bfs(Graph* graph, color_cell* color);
void print_dist_bfs(Graph* graph, distance_cell* d);
void print_pred_bfs(Graph* graph, predecessor_cell* pred);
void print_all_arrays(Graph* graph, Queue_bfs* queue, color_cell* color, distance_cell* d, predecessor_cell* pred);
int init_bfs(Graph* graph, Queue_bfs* queue, color_cell* color, distance_cell* d, predecessor_cell* pred, String* v1);
int bfs(Graph* graph, Queue_bfs* queue, color_cell* color, distance_cell* d, predecessor_cell* pred, String* v1);
void print_bfs(Graph* graph, predecessor_cell* pred, String* v1, String* v2);
void free_queue_bfs(Queue_bfs* queue);
void free_color(Graph* graph, color_cell* color);
void free_dist(Graph* graph, distance_cell* d);
void free_pred(Graph* graph, predecessor_cell* pred);
void free_bfs(Graph* graph, Queue_bfs* queue, color_cell* color, distance_cell* d, predecessor_cell* pred);
int bfs_shell(Graph* graph);

#endif //INC_5_BFS_H
