//
// Created by andrew on 15.07.22.
//

#ifndef INC_5_GRAPH_H
#define INC_5_GRAPH_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct String{
    char* str;
    int len;
}String;

typedef struct Node{
    String* ver;
    struct Node* next;
} Node;
typedef struct cell{
    Node* adjacent;
    String* vertex;
} cell; //ячейка одного массива. Она содержит название вершины и ссылку на вершины смежные с данной.

typedef struct Graph{
    int v;//number_of_vertices
    cell* Garr;//Graph_array
} Graph;//граф представляет собой динамический массив CELLов длины v.

typedef struct distance_cell{
    String* vertex;
    int distance;
} distance_cell;
typedef struct predecessor_cell{
    String* vertex;
    String* pred_vertex;
} predecessor_cell;

String* getStr();
int search(Graph* graph, String* vertex);
int isAdjacent(Graph* graph, String* Main_Vertex, String* Auxiliary_Vertex);
Graph* init_graph();

//добавление новой вершины. Пользователь вводит вершину (строку произвольной длины) и она добавляется в граф. Дублирование вершин не допускается.
//1. добавление новой вершины;
int add_vertex(Graph* graph, String* new_vertex);
void add_vertex_shell(Graph* graph);
//2. добавление нового ребра между двумя заданными вершинами;
void add_edge(Graph *graph, String *v1, String *v2);
void add_edge_shell(Graph* graph);
//3. удаление заданной вершины;
void delete_vertex(Graph* graph, String* v);
void delete_vertex_shell(Graph* graph);
//4. удаление заданного ребра;
int is_edge_in_graph(Graph* graph, String* v1, String* v2);
void delete_edge(Graph* graph, String* v1, String* v2);
void delete_edge_shell(Graph* graph);
//5. вывод графа в виде матрицы или списков смежности.
void print_Graph(Graph* graph);
//очистка графа
void freeGraph(Graph* graph);


#endif //INC_5_GRAPH_H