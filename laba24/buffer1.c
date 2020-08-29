#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer;
    unsigned long size = 0;


    char *result = NULL;

    do {
        buffer = getchar();
        size++;
        if (result == NULL)
            result = (char *) calloc(1, sizeof(char));
        else
            result = (char *) realloc(result, size * sizeof(char));


        result[size - 1] = buffer;
    } while (buffer != '\n');

    printf("%s\n", result);

    free(result);

    return 0;
}