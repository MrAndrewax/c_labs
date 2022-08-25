//
// Created by andrew on 16.07.22.
//

#include "floyd_warshall.h"


w_Matrix *create_w_Matrix(Graph *graph) {
    w_Matrix* wMatrix = malloc(sizeof(w_Matrix));
    wMatrix->size = graph->v;
    wMatrix->matrix = malloc(sizeof(w_Row)*graph->v);
    for (int i = 0; i < graph->v; i++){
        wMatrix->matrix[i].row = malloc(sizeof(int)*graph->v);
    }
    return wMatrix;
}
w_Matrix *init_w_Matrix(Graph *graph) {
    w_Matrix* wMatrix = create_w_Matrix(graph);


    Edges* edges = create_edges(graph);

    for (int i = 0; i < graph->v; i++){
        for (int j = 0; j < graph->v; j++){
            if (i == j){
                wMatrix->matrix[i].row[j] = 0;
            }

            else if ( (i != j) && (is_edge_in_edges(graph, edges, graph->Garr[i].vertex, graph->Garr[j].vertex) == 1) ){
                wMatrix->matrix[i].row[j] = 1;
            }

            else if ( (i != j) && (is_edge_in_edges(graph, edges, graph->Garr[i].vertex, graph->Garr[j].vertex) == 0) ){
                wMatrix->matrix[i].row[j] = -1;
            }
        }
    }
    free_edges(edges);
    return wMatrix;
}
void print_wMatrix(w_Matrix* wMatrix){
    printf("===========wMatrix===========\n");
    for (int i = 0; i < wMatrix->size; i++){
        for (int j = 0; j < wMatrix->size; j++){
            printf("%3d ", wMatrix->matrix[i].row[j]);
        }
        printf("\n");
    }
    printf("=============================\n");
}
void free_wMatrix(w_Matrix* wMatrix){
    for (int i = 0; i < wMatrix->size; i++){
        free(wMatrix->matrix[i].row);
    }
    free(wMatrix->matrix);
    free(wMatrix);
}



pi_Matrix* create_pi_Matrix(Graph* graph){
    pi_Matrix* piMatrix = malloc(sizeof(pi_Matrix));
    piMatrix->size = graph->v;
    piMatrix->matrix = malloc(sizeof(w_Row)*graph->v);
    for (int i = 0; i < graph->v; i++){
        piMatrix->matrix[i].row = malloc(sizeof(String*)*graph->v);
    }
    return piMatrix;
}
pi_Matrix* init_pi_Matrix(Graph* graph, w_Matrix* wMatrix){
    pi_Matrix* piMatrix = create_pi_Matrix(graph);


    for (int i = 0; i < graph->v; i++){
        for (int j = 0; j < graph->v; j++){
            if (i == j || wMatrix->matrix[i].row[j] == -1){
                piMatrix->matrix[i].row[j] = NULL;
            }
            else if ( (i != j) && wMatrix->matrix[i].row[j] != -1){
                piMatrix->matrix[i].row[j] = malloc(sizeof(String));
                piMatrix->matrix[i].row[j]->len = graph->Garr[i].vertex->len;
                piMatrix->matrix[i].row[j]->str = malloc(sizeof(char)*(piMatrix->matrix[i].row[j]->len +1));
                strcpy(piMatrix->matrix[i].row[j]->str, graph->Garr[i].vertex->str);
            }
        }
    }

    return piMatrix;
}
void print_piMatrix(pi_Matrix* piMatrix){
    printf("===========piMatrix===========\n");
    for (int i = 0; i < piMatrix->size; i++){
        for (int j = 0; j < piMatrix->size; j++){
            if (piMatrix->matrix[i].row[j] == NULL) {
                printf("  0");
            }
            else{
                printf("%3s", piMatrix->matrix[i].row[j]->str);
            }

        }
        printf("\n");
    }
    printf("==============================\n");
}
void free_piMatrix(pi_Matrix* piMatrix){
    for (int i = 0; i < piMatrix->size; i++){
        for (int j = 0; j < piMatrix->size; j++){
            if (piMatrix->matrix[i].row[j] != NULL){
                free(piMatrix->matrix[i].row[j]->str);
                free(piMatrix->matrix[i].row[j]);
            }
        }
        free(piMatrix->matrix[i].row);
    }
    free(piMatrix->matrix);
}

d_Matrix* create_d_Matrix(Graph* graph){
    d_Matrix* dMatrix = malloc(sizeof(d_Matrix));
    dMatrix->size = graph->v;
    dMatrix->matrix = malloc(sizeof(d_Row)*graph->v);
    for (int i = 0; i < graph->v; i++){
        dMatrix->matrix[i].row = malloc(sizeof(int)*graph->v);
    }
    return dMatrix;
}
d_Matrix* init_d_Matrix(Graph* graph, w_Matrix* wMatrix){
    d_Matrix* dMatrix = create_d_Matrix(graph);

    for (int i = 0; i < graph->v; i++){
        for (int j = 0; j < graph->v; j++){
            dMatrix->matrix[i].row[j] = wMatrix->matrix[i].row[j];
        }
    }
    return dMatrix;
}
void print_dMatrix(d_Matrix* dMatrix){
    printf("===========dMatrix===========\n");
    for (int i = 0; i < dMatrix->size; i++){
        for (int j = 0; j < dMatrix->size; j++){
            printf("%3d ", dMatrix->matrix[i].row[j]);
        }
        printf("\n");
    }
    printf("=============================\n");
}
void free_dMatrix(d_Matrix* dMatrix){
    for (int i = 0; i < dMatrix->size; i++){
        free(dMatrix->matrix[i].row);
    }
    free(dMatrix->matrix);
    //free(dMatrix);
}

int floyd_warshall(Graph* graph, d_Matrix* dMatrix, pi_Matrix* piMatrix){
    for (int k = 1; k < graph->v; k++){

        pi_Matrix* new_piMatrix = create_pi_Matrix(graph);
        d_Matrix* new_dMatrix = create_d_Matrix(graph);

        for (int i = 0; i < graph->v; i++){
            for (int j = 0; j < graph->v; j++){

                if ( (dMatrix->matrix[i].row[k] == - 1) || (dMatrix->matrix[k].row[j] == - 1) ){
                    //pi(k)[i][j] = pi(k-1)[i][j]
                    if (piMatrix->matrix[i].row[j] == NULL){
                        new_piMatrix->matrix[i].row[j] = NULL;
                    }
                    else{
                        new_piMatrix->matrix[i].row[j] = malloc(sizeof(String));
                        new_piMatrix->matrix[i].row[j]->len = piMatrix->matrix[i].row[j]->len;
                        new_piMatrix->matrix[i].row[j]->str = malloc(sizeof(char)*(new_piMatrix->matrix[i].row[j]->len + 1));
                        strcpy(new_piMatrix->matrix[i].row[j]->str, piMatrix->matrix[i].row[j]->str);
                    }
                }
                else if (dMatrix->matrix[i].row[j] == - 1){//продолжаем возиться с бесконечностью
                    if (piMatrix->matrix[k].row[j] == NULL){
                        new_piMatrix->matrix[i].row[j] = NULL;
                    }
                    else {
                        new_piMatrix->matrix[i].row[j] = malloc(sizeof(String));
                        new_piMatrix->matrix[i].row[j]->len = piMatrix->matrix[k].row[j]->len;
                        new_piMatrix->matrix[i].row[j]->str = malloc(sizeof(char)*(new_piMatrix->matrix[i].row[j]->len + 1));
                        strcpy(new_piMatrix->matrix[i].row[j]->str, piMatrix->matrix[k].row[j]->str);
                    }
                }

                else if (dMatrix->matrix[i].row[j] <= dMatrix->matrix[i].row[k] + dMatrix->matrix[k].row[j]){
                    if (piMatrix->matrix[i].row[j] == NULL){
                        new_piMatrix->matrix[i].row[j] = NULL;
                    }
                    else{
                        new_piMatrix->matrix[i].row[j] = malloc(sizeof(String));
                        new_piMatrix->matrix[i].row[j]->len = piMatrix->matrix[i].row[j]->len;
                        new_piMatrix->matrix[i].row[j]->str = malloc(sizeof(char)*(new_piMatrix->matrix[i].row[j]->len + 1));
                        strcpy(new_piMatrix->matrix[i].row[j]->str, piMatrix->matrix[i].row[j]->str);
                    }
                }
                else if (dMatrix->matrix[i].row[j] > dMatrix->matrix[i].row[k] + dMatrix->matrix[k].row[j]){
                    if (piMatrix->matrix[k].row[j] == NULL){
                        new_piMatrix->matrix[i].row[j] = NULL;
                    }
                    else {
                        new_piMatrix->matrix[i].row[j] = malloc(sizeof(String));
                        new_piMatrix->matrix[i].row[j]->len = piMatrix->matrix[k].row[j]->len;
                        new_piMatrix->matrix[i].row[j]->str = malloc(sizeof(char)*(new_piMatrix->matrix[i].row[j]->len + 1));
                        strcpy(new_piMatrix->matrix[i].row[j]->str, piMatrix->matrix[k].row[j]->str);
                    }
                }
            }
        }



        for (int i = 0; i < graph->v; i++) {
            for (int j = 0; j < graph->v; j++) {

                if ( (dMatrix->matrix[i].row[k] == - 1) || (dMatrix->matrix[k].row[j] == - 1) ){
                    new_dMatrix->matrix[i].row[j] = dMatrix->matrix[i].row[j];
                }

                else if (dMatrix->matrix[i].row[j] == - 1){
                    new_dMatrix->matrix[i].row[j] = dMatrix->matrix[i].row[k] + dMatrix->matrix[k].row[j];
                }

                else if (dMatrix->matrix[i].row[j] <= dMatrix->matrix[i].row[k] + dMatrix->matrix[k].row[j]){
                    new_dMatrix->matrix[i].row[j] = dMatrix->matrix[i].row[j];
                }
                else if (dMatrix->matrix[i].row[j] > dMatrix->matrix[i].row[k] + dMatrix->matrix[k].row[j]){
                    new_dMatrix->matrix[i].row[j] = dMatrix->matrix[i].row[k] + dMatrix->matrix[k].row[j];
                }
            }
        }


        free_piMatrix(piMatrix);
        piMatrix->size = new_piMatrix->size;
        piMatrix->matrix = new_piMatrix->matrix;
        free(new_piMatrix);

        free_dMatrix(dMatrix);
        dMatrix->matrix = new_dMatrix->matrix;
        dMatrix->size =  new_dMatrix->size;
        free(new_dMatrix);



    }
}
int floyd_warshall_shell(Graph* graph){
    w_Matrix* wMatrix = init_w_Matrix(graph);
    d_Matrix* dMatrix = init_d_Matrix(graph, wMatrix);
    pi_Matrix * piMatrix = init_pi_Matrix(graph, wMatrix);

    print_wMatrix(wMatrix);
    print_dMatrix(dMatrix);
    print_piMatrix(piMatrix);

    floyd_warshall(graph, dMatrix, piMatrix);

    print_wMatrix(wMatrix);
    print_dMatrix(dMatrix);
    print_piMatrix(piMatrix);


    free_dMatrix(dMatrix);
    free(dMatrix);
    free_piMatrix(piMatrix);
    free(piMatrix);
    free_wMatrix(wMatrix);
}