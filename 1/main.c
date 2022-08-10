#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
/*Указатель — это переменная, содержащая адрес переменной*/

struct matrix{
    int m; /*количество строк*/
    int *arrn; /*массив, где хранятся количества элементов в каждой из строк матрицы*/
    int **arr; /*матрица*/
    int errors;
/*1 —- EOF
0 —- все хорошо*/
};
struct interr{
    int number;
    int errors;
/*1 —- EOF
0 —- все хорошо*/

};

/*прототипы функий*/
struct interr getint(); /*проверка на правильный ввод целого числа*/
struct interr getpositive(); /*проверка на правильный ввод целого числа*/
struct matrix getmatrix(); /*функция, которая позволяет ввести матрицу*/
void printmatrix(int **, int, int *); /*функция которая выводит матрицу*/
int identicalchar(int *, int); /*считает количество одинаковых элементов в массиве*/
int *getvectorB(int, int *, int **); /*с помощью identicalchar выводите количество одинаковых элементов в каждой из строк*/
void printvector(int *, int); /*выводит вектор В*/
//void clean_vector(int *); /*освобождаем память, выделенную под динамический массив*/
void clean_matrix(int **, int); /*освобождаем память под матрицу*/

int main(){
    setlocale(LC_ALL, "Rus");

    struct matrix matr;
    matr = getmatrix();
    if (matr.errors == 1){
        printf("\nВы досрочно завершили программу!");
        clean_matrix(matr.arr, matr.m);
        free(matr.arrn);
        return 0;
    }
    printmatrix(matr.arr, matr.m, matr.arrn);
    int *vectorB = getvectorB(matr.m, matr.arrn, matr.arr);
    printf("vector B: ");
    printvector(vectorB, matr.m);
    clean_matrix(matr.arr, matr.m);
    free(matr.arrn);
}

struct interr getint(){
    setlocale(LC_ALL, "Rus");

    struct interr result;
    result.errors = 0;

    A:;
    char s[100];
    char c;
    int i = 0;
    while(1){ //этим циклом мы вводим строку
        c = getchar();
        if (c == EOF){
            s[i] = EOF;
            break;
        }
        else if(c == '\n'){
            break;
        }
        s[i] = c;
        i++;
    }

    i = 0;
    if (s[0] == EOF){ //:SALFK:ASFJAS:LKFH:ALKSFHJ:SAHF ДОДЕЛАЙ ывалоывалфопавдфлораылфрадлфоорадлорфывлдорполдлждлпаорвпролдолопарро
        result.errors = 1;
        result.number = 0;
        return result;
    }
    else if ((atoi(s) == 0) && (s[0] != '0')){
        printf("Введите целое число: ");
        goto A;
    }
    else{
        result.number = atoi(s);
//printf("%d", result.number);
        return result;
    }
}

struct interr getpositive(){
    setlocale(LC_ALL, "Rus");

    struct interr result;
    result.errors = 0;

    A:;
    char s[100];
    char c;
    int i = 0;
    while(1){ //этим циклом мы вводим строку
        c = getchar();
        if (c == EOF){
            s[i] = EOF;
            break;
        }
        else if(c == '\n'){
            break;
        }
        s[i] = c;
        i++;
    }

    i = 0;
    if (s[0] == EOF){ //:SALFK:ASFJAS:LKFH:ALKSFHJ:SAHF ДОДЕЛАЙ ывалоывалфопавдфлораылфрадлфоорадлорфывлдорполдлждлпаорвпролдолопарро
        result.errors = 1;
        result.number = 0;
        return result;
    }
    else if ((atoi(s) == 0) && (s[0] != '0')){
        printf("Введите целое положительное число: ");
        goto A;
    }
    else{
        result.number = atoi(s);
        if (result.number > 0){
            result.errors = 0;
            return result;
        }
        else if (result.number <= 0){
            printf("Число должно быть целым и положительным. Введите ваше число: ");
            goto A;
        }
    }
}

struct matrix getmatrix(){
    struct matrix matr; /*объявили матрицу*/
    struct interr numerr;
    setlocale(LC_ALL, "Rus");

    int m; /*количество строк матрицы*/
    int n; /*количество элементов в каждой из строк*/
    int a; /*элемент матрицы*/

    printf("Введите количество строк: ");

    numerr = getpositive(); //вводим количество строк
    if (numerr.errors == 1){
        matr.errors = 1;
        return matr;
    }
    m = numerr.number;
    matr.m = m;

    matr.arrn = (int *)malloc(matr.m * sizeof(int));

    matr.arr = (int **)malloc(matr.m*sizeof(int *));
    for(int i = 0; i < matr.m; i++){
        printf("Введите количество элементов в строке №%d: ", i);
        numerr = getpositive();
        if (numerr.errors == 1){
            matr.errors = 1;
            return matr;
        }
        n = numerr.number;
        *(matr.arrn + i) = n;
        matr.arr[i] = (int *) malloc(n*sizeof(int));
        for (int j = 0; j < n; j++){
            printf("Введите элемент №%d в строке №%d: ",j, i);
            numerr = getint();
            if (numerr.errors == 1){
                matr.errors = 1;
                return matr;
            }
            a = numerr.number;
            matr.arr[i][j] = a;
        }
    }
    return matr;
}

void printmatrix(int **arr, int m, int arrn[]){
    printf("\nВведённая матрица:\n");
    for (int i = 0; i < m; i++){
        for (int j = 0; j < arrn[i]; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int identicalchar(int *pa, int len){
    int i, j;
    int maxvalue = 0;
    int localvalue;
    if (len == 1){
        return 1;
    }
    else {
        for (i = 0; i < len - 1; i++){
            localvalue = 0;
            for (j = i; j < len; j++){
                if (pa[i] == pa[j]){ //pa++ ctrl + d отрицательные длины
                    localvalue++;
                }
            }
            if (localvalue > maxvalue){
                maxvalue = localvalue;
            }
        }
        return maxvalue;
    }
}

int *getvectorB(int m, int *arrn, int **arr){
    int *vectorb;
    vectorb = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++){
        vectorb[i] = identicalchar(arr[i], arrn[i]);
    }
    return vectorb;
}

void printvector(int *vect, int len){
    for (int i = 0; i < len; i++){
        printf("%d ", vect[i]);
    }
    printf("\n");
    free(vect);
}
void clean_matrix(int **matr, int m){
    for (int i = 0; i < m; i++){
        free(matr[i]);
    }
    free(matr);
}
