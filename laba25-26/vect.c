#include <stdio.h>

typedef long T;

typedef struct {
    int count;
    T* data;
} vect;

// Инициализация вектора
void create(vect* vct, int size) {
    vct->count = 0;
    vct->data = malloc(sizeof(T)*size);
}
void push(vect* vct, T val) {
    vct->data[vct->count] = val;
    vct->count+=1;
}


int main() {
    vect vct;
    int size;
    scanf("%d", &size);
    create(&vct, size);
    for(int i=0; i < size - 3; i++) {
        push(&vect, i*i);
    }
    for(int i=0; i < vct.count; i++) {
        printf("%d\n", vct.data[i]);
    }

    return 0;
}