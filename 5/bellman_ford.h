//
// Created by andrew on 15.07.22.
//

#ifndef INC_5_BELLMAN_FORD_H
#define INC_5_BELLMAN_FORD_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "bfs.h"

typedef struct Edge{
    String* v1;
    int ind1;
    String* v2;
    int ind2;
} Edge;

typedef struct eNode{//eNode = edge_node
    struct eNode* next;
    Edge* edge;
} eNode;

typedef struct Edges{
    eNode* head;
} Edges;

int is_edge_in_edges(Graph* graph, Edges* edges, String* v1, String* v2);
void add_edge_to_edges(Edges* edges, String* v1, String* v2, int ind1, int ind2);
Edges* create_edges(Graph* graph);
void print_edges(Edges* edges);
void free_edges(Edges* edges);
int init_bellman_ford(Graph* graph, distance_cell* d, predecessor_cell* pred,  String* v1);
int bellman_ford(Graph* graph, distance_cell* d, predecessor_cell* pred,  Edges* edges, String* v1);
int bellman_ford_shell(Graph* graph);

#endif //INC_5_BELLMAN_FORD_H
