#include "graph.h"
#include "bfs.h"
#include "bellman_ford.h"
#include "floyd_warshall.h"
//gcc -g graph.c bfs.c bellman_ford.c floyd_warshall.c main.c
//надо будет добавить кучу проверок на ввод. Если ввести одинаковые вершины, если ввести пустую строку и тд тп.
//одно и то же ребро можно добавлять сколько угодно раз. БАГ.

String* char_to_String(char* str){
    String* string = malloc(sizeof(String));
    string->len = (int) strlen(str);
    string->str = malloc(sizeof(char) * (string->len + 1));
    strcpy(string->str, str);
    return string;
}

void fast_vertex_add(Graph* graph, char* str){
    String* string = char_to_String(str);
    add_vertex(graph, string);
    free(string->str);
    free(string);
}

void fast_edge_add(Graph* graph, char* v1, char* v2){
    String* ver1 = char_to_String(v1);
    String* ver2 = char_to_String(v2);
    add_edge(graph, ver1, ver2);
    free(ver1->str);
    free(ver1);
    free(ver2->str);
    free(ver2);
}

void fast_add1(Graph* graph){
    fast_vertex_add(graph, "1");
    fast_vertex_add(graph, "2");
    fast_vertex_add(graph, "3");
    fast_vertex_add(graph, "4");
    fast_vertex_add(graph, "5");
    fast_vertex_add(graph, "6");
    fast_vertex_add(graph, "7");
    fast_vertex_add(graph, "8");
    fast_vertex_add(graph, "9");
    fast_vertex_add(graph, "10");
    fast_vertex_add(graph, "11");
    fast_vertex_add(graph, "12");
    fast_vertex_add(graph, "13");

    fast_edge_add(graph, "1", "2");
    fast_edge_add(graph, "1", "12");
    fast_edge_add(graph, "1", "13");

    fast_edge_add(graph, "2", "3");
    fast_edge_add(graph, "2", "6");
    fast_edge_add(graph, "2", "11");

    fast_edge_add(graph, "3", "4");
    fast_edge_add(graph, "3", "9");

    fast_edge_add(graph, "4", "5");
    fast_edge_add(graph, "4", "9");
    fast_edge_add(graph, "4", "10");

    fast_edge_add(graph, "5", "10");

    fast_edge_add(graph, "6", "7");
    fast_edge_add(graph, "6", "8");
    fast_edge_add(graph, "6", "9");
    fast_edge_add(graph, "6", "11");

    fast_edge_add(graph, "7", "8");
    fast_edge_add(graph, "7", "9");
    fast_edge_add(graph, "7", "11");
    fast_edge_add(graph, "7", "12");

    fast_edge_add(graph, "8", "9");
    fast_edge_add(graph, "8", "10");
    fast_edge_add(graph, "11", "12");
    fast_edge_add(graph, "12", "13");
}

void fast_add2(Graph* graph){//f
    fast_vertex_add(graph, "1");
    fast_vertex_add(graph, "2");
    fast_vertex_add(graph, "3");
    fast_vertex_add(graph, "4");
    fast_vertex_add(graph, "5");
    fast_vertex_add(graph, "6");
    fast_vertex_add(graph, "7");
    fast_vertex_add(graph, "8");
    fast_vertex_add(graph, "9");
    fast_vertex_add(graph, "10");
    fast_vertex_add(graph, "11");
    fast_vertex_add(graph, "12");
    fast_vertex_add(graph, "13");

    fast_edge_add(graph, "1", "2");
    fast_edge_add(graph, "1", "4");
    fast_edge_add(graph, "1", "6");
    fast_edge_add(graph, "1", "7");

    fast_edge_add(graph, "2", "3");
    fast_edge_add(graph, "2", "4");

    fast_edge_add(graph, "3", "5");
    fast_edge_add(graph, "3", "11");


    fast_edge_add(graph, "4", "5");
    fast_edge_add(graph, "4", "7");

    fast_edge_add(graph, "5", "7");
    fast_edge_add(graph, "5", "8");
    fast_edge_add(graph, "5", "11");

    fast_edge_add(graph, "6", "7");

    fast_edge_add(graph, "7", "8");

    fast_edge_add(graph, "8", "9");
    fast_edge_add(graph, "8", "10");

    fast_edge_add(graph, "9", "10");
    fast_edge_add(graph, "9", "12");

    fast_edge_add(graph, "11", "12");
    fast_edge_add(graph, "11", "13");

    fast_edge_add(graph, "12", "13");

}

void fast_add3(Graph* graph){
    fast_vertex_add(graph, "a");
    fast_vertex_add(graph, "b");
    fast_vertex_add(graph, "c");
    fast_vertex_add(graph, "d");
    fast_vertex_add(graph, "e");
    fast_vertex_add(graph, "g");
    fast_vertex_add(graph, "h");
    fast_vertex_add(graph, "i");


    fast_edge_add(graph, "a", "b");
    fast_edge_add(graph, "a", "c");
    fast_edge_add(graph, "b", "c");
    fast_edge_add(graph, "c", "d");
    fast_edge_add(graph, "c", "e");
    fast_edge_add(graph, "e", "g");
    fast_edge_add(graph, "e", "i");
    fast_edge_add(graph, "g", "h");
    fast_edge_add(graph, "g", "i");
    fast_edge_add(graph, "h", "i");

}


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
    printf("9. Добавить готовый граф\n");
    printf("10. Добавить готовый граф\n");
    printf("11. Добавить готовый граф\n");
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
        else if(choice == 9){
            fast_add1(graph);
        }
        else if(choice == 10){
            fast_add2(graph);
        }
        else if(choice == 11){
            fast_add3(graph);
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