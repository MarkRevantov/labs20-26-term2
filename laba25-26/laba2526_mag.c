#include "laba2526_mag.h"


int main() {
    Stack st;

    create(&st, 10);
    print(&st);
    push(&st, 150);
    print(&st);
    for(int i=0; i < 12; i++) {
        push(&st, i*i);
    } 
    
    print(&st);
    printf("Poped: %ld\n", pop(&st));
    print(&st);

    Stack st2;
    create(&st2, 2);
    for(int i=0; i < 4; i++) {
        push(&st2, i*i + 1);
    }
    print(&st2);
    Stack* st3;
    merge(&st, &st2);
    print(&st);
    sort(&st);
    print(&st);
    destroy(&st);
    print(&st);
    print(&st2);
    destroy(&st2);
    print(&st2);
    return 0;
}