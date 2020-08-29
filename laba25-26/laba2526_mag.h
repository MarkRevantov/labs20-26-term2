#include <stdlib.h>
#include <stdio.h>

#define EXTRA 100

typedef long T;
typedef struct {
    int size;
    long index;
    T* data;
} Stack;
void create(Stack* s, int size) {
    s->index = -1;
    s->size = size;
    s->data = malloc(sizeof(T)*size);
}
int is_empty(Stack* s) {
    if(s->index < 0) {
        return 1;
    }
    else {
        return 0;
    }
}
void push(Stack* s, T val) {
    if(s->index >= s->size-1) {
        T* data = malloc(sizeof(T)*(s->size + EXTRA));
        for(int i=0; i < s->size; i++) {
            data[i] = s->data[i];
        }
        free(s->data);
        s->size += EXTRA;
        s->data = data;
    }
    s->index += 1;
    s->data[s->index] = val;
}
T pop(Stack* s) {
    if(is_empty(s) != 0) {
        printf("ERROR! Stack is Empty!");
        return -1;
    }
    s->index -= 1;
    return s->data[s->index+1];
}
void print(Stack* s) {
    if (is_empty(s) != 0) {
        printf("Stack is Empty!");
    }
    else {
        for(int i=0; i <= s->index; i++) {
            printf("%ld ", s->data[i]);
        }
    }
    printf("\n");
}
int get_size(Stack* s) {
    return s->index+1;
}
void destroy(Stack* s) {
    s->index = -1;
    s->size = 0;
    free(s->data);
}
void merge(Stack* s1, Stack* s2) {
    while(is_empty(s2) != 0) {
        push(s1, pop(s2));
    }
    return;
}
void data_sort(T data[], int left, int right) {
    if (left >= right) {
        return;
    }

    int ind = left;
    for(int i=left+1; i <= right; i++) {
        if(data[ind] >= data[i]) {
            T temp = data[ind];
            data[ind] = data[i];
            data[i] = temp;

            ind = i;
        }
    }
    data_sort(data, left, ind-1);
    data_sort(data, ind+1, right);
}
void sort(Stack* s) {
    if(is_empty(s)) {
        return;
    }
    data_sort(s->data, 0, s->index);
}
