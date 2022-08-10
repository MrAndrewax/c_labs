//
// Created by andrew on 16.07.22.
//

#ifndef INC_5_FLOYD_WARSHALL_H
#define INC_5_FLOYD_WARSHALL_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "bfs.h"
#include "bellman_ford.h"

typedef struct w_Row{
    int* row;
} w_Row;
typedef struct w_Matrix{
    int size;
    w_Row* matrix;
} w_Matrix;

typedef struct pi_Row{
    String** row;//массив строк
} pi_Row;
typedef struct pi_Matrix{
    int size;
    pi_Row* matrix;
} pi_Matrix;

typedef struct d_Row{
    int* row;
} d_Row;
typedef struct d_Matrix{
    int size;
    d_Row* matrix;
} d_Matrix;

w_Matrix* create_w_Matrix(Graph* graph);
w_Matrix* init_w_Matrix(Graph* graph);
void print_wMatrix(w_Matrix* wMatrix);
void free_wMatrix(w_Matrix* wMatrix);


pi_Matrix* create_pi_Matrix(Graph* graph);
pi_Matrix* init_pi_Matrix(Graph* graph, w_Matrix* wMatrix);
void print_piMatrix(pi_Matrix* piMatrix);
void free_piMatrix(pi_Matrix* piMatrix);


d_Matrix* create_d_Matrix(Graph* graph);
d_Matrix* init_d_Matrix(Graph* graph, w_Matrix* wMatrix);
void print_dMatrix(d_Matrix* dMatrix);
void free_dMatrix(d_Matrix* dMatrix);


int floyd_warshall(Graph* graph, d_Matrix* dMatrix, pi_Matrix* piMatrix);
int floyd_warshall_shell(Graph* graph);
#endif //INC_5_FLOYD_WARSHALL_H
