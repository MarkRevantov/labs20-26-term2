#include <stdio.h>
#include <stdlib.h>

#include "lib24.cpp"

int main() {
    int size;
    char* infix;
    Deque in;
    Deque out;

    createDeque(&in);
    createDeque(&out);
    // Запоминаю вводимую строку
    char buffer;
    size = 0;
    unsigned long memSize = 1;
    infix = (char *) malloc(sizeof(char));
    while((buffer = getchar()) != EOF) {
        if (size >= memSize) {
            memSize *= 2;
            infix = (char*)realloc(infix, memSize * sizeof(char));
        }
        infix[size] = buffer;
        size++;
    };
    infix = (char *) realloc(infix, size * sizeof(char));
    // Запомнил
    //printf("%s", infix);
    // Ок!


    // Выделяю из строки узлы.
    DequeFromString(&in, infix, size);
    printf("Создан стек!\n");
    // Проверяю содержимое
    //printDeque(&in);
    // Сортировочная станция
    sortingStation(&in, &out);
    printf("Отсортировал\n");
    //printDeque(&out);
    
    // Строим дерево
    Tree tree;
    buildTree(&tree, &out);
    printf("Дерево построилось без ошибок\n");
    //printTree(&tree);

    // Заменяю узлы
    replaceNodes(&tree);
    //printTree(&tree);

    // Вывожу результат
    printInfixTree(&tree);
    return 0;
}