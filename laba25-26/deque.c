#include <stdio.h>

#define START_SIZE 3

typedef long T;
typedef char bool;
typedef struct {
    int rhead;
    int lhead;
    int count;
    int size;
    T* data;
} deque;
void create(deque* dq) {
    dq->count = 0;
    dq->rhead = -1;
    dq->lhead = -1;
    dq->size = START_SIZE;
    dq->data = malloc(sizeof(T)*dq->size);
}
bool is_empty(deque* dq) {
    if(dq->count == 0) {
        return 1;
    }
    else if(dq->count > 0) {
        return 0;
    }

    printf("Error! Count is lower than 0!\n");
    return -1;
}
void push_left(deque* dq, T val) {
    if(dq->count == dq->size) {
        // Зарезервировать ещё память.
    }
    if(is_empty(dq)) {
        dq->rhead = 0;
        dq->lhead = 1;
    }
    dq->lhead = (dq->lhead-1 + dq->size) % dq->size;
    dq->data[dq->lhead] = val;
    dq->count+=1;
    
    return;
}

int main() {
}