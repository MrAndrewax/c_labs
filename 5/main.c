#include "graph.h"
#include "bfs.h"
#include "bellman_ford.h"
#include "floyd_warshall.h"

//надо будет добавить кучу проверок на ввод. Если ввести одинаковые вершины, если ввести пустую строку и тд тп.
//одно и то же ребро можно добавлять сколько угодно раз. БАГ.

void printMenu(){
    printf("\nЧто изволите, сударь?\n");
    printf("1. добавление новой вершины\n");
    printf("2. добавление нового ребра между двумя заданными вершинами\n");
    printf("3. удаление заданной вершины\n");
    printf("4. удаление заданного ребра\n");
    printf("5. вывод графа в виде матрицы или списков смежности\n");

    printf("6. поиск пути между двумя вершинами графа\n");
    printf("7. Поиск кратчайшего пути между двумя заданными вершинами графа, использующий алгоритм Беллмана-Форда\n");
    printf("8. Поиск первых трёх кратчайших путей между двумя любыми вершинами графа\n");

    printf("404. Очистить экран\n");
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
        else if(choice == 2){
            add_edge_shell(graph);
        }
        else if(choice == 3){
            delete_vertex_shell(graph);
        }
        else if(choice == 4){
            delete_edge_shell(graph);
        }
        else if(choice == 5){
            print_Graph(graph);
        }
        else if(choice == 6){
            bfs_shell(graph);
        }
        else if(choice == 7){
            bellman_ford_shell(graph);
        }
        else if(choice == 8){
            floyd_warshall_shell(graph);
        }
        else if(choice == 404){
            printf("\033c");
        }
    } while (choice != 0);
    printf("The program was stopped\n");
}
int main(){
    Graph* graph = init_graph();
    Menu(graph);
    freeGraph(graph);
}