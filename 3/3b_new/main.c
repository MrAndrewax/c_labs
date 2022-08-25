#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//просматриваемая таблица, организованная списком;
//если мы прожимаем ctrl+c, то результат не должен сохраняться.
//В пространстве не может быть двух элементов с одинаковыми ключами.
/*• поиск элементов, заданных диапазоном ключей; в таблице могут отсутствовать элементы с
ключами, задающими диапазон; результатом поиска должна быть новая таблица, содержащая
найденные элементы.*/
//table->info_offset не нужен
//написать нормальный getint +
//Имя файла вводится по запросу из программы и хранится в описателе таблицы.
//порядок добавления не тот

typedef struct KeySpace{
    char* key; //сам ключ
    int key_len;
    int next_key; //позиция следующего ключа
    int info_offset; //отступ до нужной информации в info_file
    int info_len; //длина информации
    //int deleted; // удалили ли мы этот ключ
} KeySpace;

typedef struct Node{
    KeySpace* KS;
    struct Node* next;
} Node;

typedef struct Table{
    char* name;
    int count_of_elements;
    int key_offset;
    int info_offset;
    int first_KS;
    Node* head;
} Table;



Table* getTable(char* name){
    //выделили место под таблицу.
    Table* table = malloc(sizeof(Table));
    table->count_of_elements = 0;//количество элементов в таблице.
    table->key_offset = -1;//cur key_offset
    table->info_offset = 0;
    table->first_KS = -1;//-1 - это значит, что ключей в таблице нет
    table->head = NULL;

    FILE* table_file = fopen(name, "rb");//открываем табличку, чтобы получить её размер

    if (table_file == NULL){//если такого файлика нет, то создаём новый
        printf("The new table was created\n");
        return table;
    }
    else{
        fread(&(table->count_of_elements), sizeof(int), 1, table_file);//получаемся табличку
        fread(&(table->key_offset), sizeof(int), 1, table_file);
        fread(&(table->info_offset), sizeof(int), 1, table_file);
        fread(&(table->first_KS), sizeof(int), 1, table_file);
        if (table->first_KS == -1){
            fclose(table_file);
            return table;
        }

        int KeySeek = table->first_KS;

        for (int i = 0; i < table->count_of_elements; i++){
            //fseek(table_file, KeySeek, SEEK_SET);

            KeySpace* KS = malloc(sizeof(KeySpace));
            fread( &(KS->key_len), sizeof(int), 1, table_file);
            fread( &(KS->next_key), sizeof(int), 1, table_file);
            fread( &(KS->info_offset), sizeof(int), 1, table_file);
            fread( &(KS->info_len), sizeof(int), 1, table_file);
            KS->key = malloc(sizeof(char) * (KS->key_len + 1));
            fread( (KS->key), sizeof(char) * (KS->key_len + 1), 1, table_file);

            Node* newNode = malloc(sizeof(Node));
            newNode->KS = KS;
            newNode->next = table->head;
            table->head = newNode;

            KeySeek = KS->next_key;
        }


        fclose(table_file);
        return table;
    }//значит сейчас есть табличка
}
char* getString(){
    char *str = NULL, c;
    int len = 1;
    str = (char*) malloc(sizeof(char));
    while((c = getchar()) != '\n') {
        str[len - 1] = c;
        len++;
        str = (char*) realloc(str, len);
    }
    str[len - 1] = '\0';
    return str;
}
int get_int(){

    char* string;
    int num;
    int is_num_integer = 0;

    while (is_num_integer != 1){
        string = getString();
        if ( strcmp(string, "0") == 0 ){
            num = 0;
            free(string);
            return num;
        }

        else{
            num = atoi(string);
            free(string);
            if (num  == 0){
                is_num_integer = 0;
                printf("Введённая строка не является числом. Попробуйте ещё раз.\n");
            }
            else{
                return num;
            }
        }
    }

}
int getInt(int *a)
{
    int n;
    do{
        n = scanf("%d", a);
        if (n < 0) // обнаружен конец файла
            return 0;
        if (n == 0){ // обнаружен некорректный символ - ошибка
            printf("%s\n", "Error! Repeat input");
            scanf("%*c");
        }
    } while (n == 0);
    return 1;
}

int search(Table* table, char* key){
    Node* cur = table->head;
    while(cur!=NULL){
        if (strcmp(cur->KS->key, key) == 0){
            return 1;
        }
        cur=cur->next;
    }
    return 0;
}

int menu_search(Table* table, char* info_name, char* key){
    Node* cur = table->head;
    while(cur!=NULL){
        if (strcmp(cur->KS->key, key) == 0){

            FILE* info_file = fopen(info_name, "rb");
            if (info_file == NULL){
                printf("Файл с информацией ещё не был создан\n");
                return -1;
            }

            fseek(info_file, cur->KS->info_offset, SEEK_SET);

            char* info;
            info = malloc(sizeof(char) * (cur->KS->info_len + 1));
            fread(info, sizeof(char) * (cur->KS->info_len + 1), 1, info_file);
            printf("Элемент с ключом \"%s\" найден, ему соответствует информация \"%s\"\n", cur->KS->key, info);
            free(info);
            fclose(info_file);
            return 1;
        }
        cur=cur->next;
    }
    printf("Элемента с ключом \"%s\" в таблице нет\n", key);
    return 0;
}
int menu_search_shell(Table* table, char* info_name){
    char *key;

    printf("Введите ключ\n>");
    key = getString();

    menu_search(table, info_name, key);
    free(key);
}

int add(Table* table, char* info_name, char* key, char* info){

    if (search(table, key) == 1){
        printf("Элемент с ключом \"%s\" уже есть в таблице. Добавление не выполнено.\n", key);
        return -1;
    }
    else if (search(table, key) == 0){
        if (table->count_of_elements == 0){//если нет элементов, то мы задаём отступ на первый ключ
            table->first_KS = (int) (sizeof(int) * 4);
            table->key_offset = table->first_KS;
        }

        KeySpace* KS = malloc(sizeof(KeySpace));
        KS->key_len = (int) strlen(key);;
        KS->key = malloc(sizeof(char)*(KS->key_len + 1));
        strcpy(KS->key, key);
        KS->info_offset = table->info_offset;
        KS->info_len = (int) strlen(info);
        KS->next_key = table->key_offset + (int) (sizeof(int) * 4 + sizeof(char) * (KS->key_len + 1));

        Node* newNode = malloc(sizeof(Node));
        newNode->KS = KS;
        newNode->next = table->head;
        table->head = newNode;


        FILE* info_file = fopen(info_name, "ab");
        fwrite(info, sizeof(char) * (KS->info_len + 1), 1, info_file);
        fclose(info_file);


        table->info_offset += (int) sizeof(char) * (KS->info_len + 1);
        table->key_offset += (int) (sizeof(int) * 4 + sizeof(char) * (KS->key_len + 1));
        table->count_of_elements += 1;

        printf("Ключ \"%s\" c информацией \"%s\" успешно добавлен в табличку!\n", key, info);

        return 0;
    }
}
void add_shell(Table* table, char* info_name){
    char* key;
    char* info;

    printf("Введите ключ\n>");
    key = getString();
    printf("Введите информацию\n>");
    info = getString(table);

    add(table, info_name, key, info);

    free(key);
    free(info);
}

void free_table(Table* table){
    Node* cur = table->head;
    while (cur != NULL ){
        Node* temp = cur;
        cur=cur->next;
        free(temp->KS->key);
        free(temp->KS);
        free(temp);
    }
    free(table);
}

int printTable(Table* table, char* info_name){

    if (table->count_of_elements == 0){
        printf("В таблице нет элементов\n");
        /*
        printf("table->count_of_elements: %d\n", table->count_of_elements);
        printf("table->first_KS: %d\n", table->first_KS);
        printf("table->key_offset: %d\n", table->key_offset);
        printf("table->info_offset: %d\n", table->info_offset);
*/

        return -1;
    }

    FILE* info_file = fopen(info_name, "rb");
    /*
    printf("table->count_of_elements: %d\n", table->count_of_elements);
    printf("table->first_KS: %d\n", table->first_KS);
    printf("table->key_offset: %d\n", table->key_offset);
    printf("table->info_offset: %d\n", table->info_offset);
     */
    Node* cur = table->head;
    while (cur != NULL){
        int info_seek = cur->KS->info_offset;

        fseek(info_file, info_seek, SEEK_SET);

        char* info;
        info = malloc(sizeof(char) * (cur->KS->info_len + 1));
        fread(info, sizeof(char) * (cur->KS->info_len + 1), 1, info_file);
        printf("Key: %s\tInfo: %s\n", cur->KS->key, info);
        free(info);

        cur=cur->next;
    }
    fclose(info_file);
    return 0;
}

void push_table(Table* table, char* table_name){
    FILE* table_file = fopen(table_name, "wb");

    fseek(table_file, 0, SEEK_SET);

    //сначала записываем основную информацию о таблице
    fwrite(&(table->count_of_elements), sizeof(int), 1, table_file);
    fwrite(&(table->key_offset), sizeof(int), 1, table_file);
    fwrite(&(table->info_offset), sizeof(int), 1, table_file);
    fwrite(&(table->first_KS), sizeof(int), 1, table_file);
    //теперь переходим к ключевому пространству.
    Node* cur = table->head;
    while (cur != NULL){
        fwrite( &(cur->KS->key_len), sizeof(int), 1, table_file);
        fwrite( &(cur->KS->next_key), sizeof(int), 1, table_file);
        fwrite( &(cur->KS->info_offset), sizeof(int), 1, table_file);
        fwrite( &(cur->KS->info_len), sizeof(int), 1, table_file);
        fwrite( (cur->KS->key), sizeof(char) * (cur->KS->key_len + 1), 1, table_file);
        cur=cur->next;
    }

    fclose(table_file);
}

int delete(Table* table, char* key){
    if (search(table, key) == 0){
        printf("Элемента с ключом \"%s\" в таблице нет. Удаление не выполнено.\n", key);
        return -1;
    }
    else{
        if (strcmp(table->head->KS->key, key) == 0){
            Node* temp = table->head;
            int key_len = temp->KS->key_len;

            table->head = table->head->next;
            free(temp->KS->key);
            free(temp->KS);
            free(temp);
            printf("Элемент1 с ключом \"%s\" успешно удалён\n", key);

            table->key_offset -= (int) (sizeof(int) * 4 + sizeof(char) * (key_len + 1));
            table->count_of_elements--;
            return 1;
        }
        else{
            Node* cur = table->head;
            while (cur != NULL){
                if (strcmp(cur->next->KS->key, key) == 0){
                    Node* temp = cur->next;
                    cur->next = cur->next->next;
                    free(temp->KS->key);
                    free(temp->KS);
                    free(temp);
                    printf("Элемент с ключом \"%s\" успешно удалён\n", key);
                    table->count_of_elements--;
                    return 1;
                }
                cur=cur->next;
            }
        }
    }
}
int delete_shell(Table* table){
    printf("Введите ключ\n>");
    char* key = getString();
    delete(table, key);
    free(key);
}

int spec_search(Table* table, char* info_name, char* key1, char* key2){


    printf("Введите имя таблицы\n>");
    char* new_table_name = getString();
    printf("Введите имя файла\n>");
    char* new_info_name = getString();




    Node* cur = table->head;

    //создаём НОВУЮ ВРЕМЕННУЮ таблицу
    Table* temp_table = malloc(sizeof(Table));
    temp_table->count_of_elements = 0;//количество элементов в таблице.
    temp_table->key_offset = -1;//cur key_offset
    temp_table->info_offset = 0;
    temp_table->first_KS = -1;//-1 - это значит, что ключей в таблице нет
    temp_table->head = NULL;
    /////////////////////////////////


    //пробегаемся по всем элементам исходной таблицы
    while (cur != NULL){
        if ( (strcmp(cur->KS->key, key1) >= 0) && (strcmp(cur->KS->key, key2) <= 0) ){//если элемент входит в заданный диапазон, то мы добавляем его в новую таблицу

            if (temp_table->count_of_elements == 0){//если нет элементов
                temp_table->first_KS = (int) (sizeof(int) * 4);//то мы задаём отступ на первый ключ
                temp_table->key_offset = temp_table->first_KS;
            }

            //получаем информацию, которая хранится по данному ключу в исходной таблице.
            FILE* info_file = fopen(info_name, "rb");
            if (info_file == NULL){
                printf("Файл с информацией ещё не был создан\n");
                return -1;
            }
            fseek(info_file, cur->KS->info_offset, SEEK_SET);

            char* info;
            info = malloc(sizeof(char) * (cur->KS->info_len + 1));
            fread(info, sizeof(char) * (cur->KS->info_len + 1), 1, info_file);
            fclose(info_file);
            ///////////////////////////////////////////////////////////


            //создаём копию элемента исходной таблицы
            KeySpace* KS = malloc(sizeof(KeySpace));
            KS->key_len = cur->KS->key_len;
            KS->key = malloc(sizeof(char)*(KS->key_len + 1));
            strcpy(KS->key, cur->KS->key);
            KS->info_offset = temp_table->info_offset;
            KS->info_len = (int) strlen(info);
            KS->next_key = temp_table->key_offset + (int) (sizeof(int) * 4 + sizeof(char) * (KS->key_len + 1));

            Node* newNode = malloc(sizeof(Node));
            newNode->KS = KS;
            newNode->next = temp_table->head;
            temp_table->head = newNode;
            ///////////////////////////////////////////////////


            //теперь загрузим информацию в новую таблицу
            FILE* temp_info_file = fopen("temp_info_file.bin", "ab");
            fwrite(info, sizeof(char) * (KS->info_len + 1), 1, temp_info_file);
            fclose(temp_info_file);
            ////////////////////////////////////////////

            free(info);

            temp_table->info_offset += (int) sizeof(char) * (KS->info_len + 1);
            temp_table->key_offset += (int) (sizeof(int) * 4 + sizeof(char) * (KS->key_len + 1));
            temp_table->count_of_elements += 1;
        }
        cur=cur->next;
    }

    //осталось лишь вывести новую таблицу
    printTable(temp_table, info_name);


    remove("temp_info_file.bin");
    free_table(temp_table);
}

void spec_search_shell(Table* table, char* info_name){

    printf("Введите первый ключ\n>");
    char* key1 = getString();
    printf("Введите второй ключ\n>");
    char* key2 = getString();

    spec_search(table, info_name, key1, key2);

    free(key1);
    free(key2);
}

void printMenu(){
    printf("\nЧто изволите, сударь?\n");
    printf("1. включение нового элемента в таблицу\n");
    printf("2. поиск в таблице элемента\n");
    printf("3. удаление из таблицы элемента\n");
    printf("4. специальный поиск\n");
    printf("5. вывод содержимого таблицы на экран\n");
    printf("6. Записать таблицу в файл\n");
    printf("7. Прочитать таблицу из файла\n");
    //printf("404. Очистить экран\n");
    printf("0. Завершение программы\n");
    printf(">");
}
void Menu(Table* table, char* table_name, char* info_name){
    int choice = 0;

    do {
        printMenu();

        choice = get_int();

        if (choice == 1){
            add_shell(table, info_name);
        }
        else if(choice == 2) {
            menu_search_shell(table, info_name);
        }
        else if(choice == 3){
            delete_shell(table);
        }
        else if(choice == 4){
            spec_search_shell(table, info_name);
        }
        else if(choice == 5){
            printTable(table, info_name);
        }
        else if(choice == 404){
            printf("\033c");
        }
    } while (choice != 0);
    printf("The program was stopped\n");
}

int main(){
    printf("Введите имя таблицы\n>");
    char* table_name = getString();
    printf("Введите имя файла\n>");
    char* info_name = getString();
    Table* table = getTable(table_name);
    Menu(table, table_name, info_name);
    push_table(table, table_name);
    free_table(table);
    return 0;
}