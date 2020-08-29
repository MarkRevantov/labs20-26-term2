#include <stdio.h>
#include <stdlib.h>

int main() {
    char buffer;
    while((buffer = getchar()) != EOF) {
        printf("%c", buffer);
    }

    return 0;
}