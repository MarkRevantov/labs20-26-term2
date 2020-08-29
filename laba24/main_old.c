#include <stdio.h>
#include <stdlib.h>

typedef int T;
typedef struct Node {
    // n - number; l - liter; +, *, ^, (,), 0 - operators 
    char type;
    short priority;
    T value;
    struct Node* left;
    struct Node* right;
    struct Node* parrent;
} Node;
typedef struct {
    int size;
    Node* root;
} Tree;
typedef struct {
    int size;
    Node* first;
    Node* last;
} Deque;



void push_front(Deque* dq, Node* node) {
    if(dq->size == 0) {
        dq->first = node;
        dq->last = node;
        dq->size++;
        return;
    }
    else {
        node->right = dq->first;
        dq->first = node;
        dq->first->left = node;
        dq->size++;
        return;
    }
}
void push_back(Deque* dq, Node* node) {
    if(dq->size == 0) {
        dq->last = node;
        dq->first = node;
        dq->size++;
        return;
    }
    else {
        node->left = dq->last;
        dq->last = node;
        dq->last->right = node;
        dq->size++;
        return;
    }
}
Node* pop_front(Deque* dq) {
    if(dq->size == 0) { 
        printf("Error! There is no Nodes. Get this kek\n");
        return NULL;
    }
    else if (dq->size == 1) {
        Node* node;
        node = dq->first;
        dq->first = NULL;
        dq->last = NULL;
        dq->size--;

        return node;
    }
    else {
        Node* node;
        node = dq->first;
        dq->first = node->right;
        dq->size--;
        
        return node;
    }
}
Node* pop_back(Deque* dq) {
    if(dq->size == 0) { 
        printf("Error! There is no Nodes. Get this kek\n");
        return NULL;
    }
    else if (dq->size == 1) {
        Node* node;
        node = dq->last;
        dq->first = NULL;
        dq->last = NULL;
        dq->size--;

        return node;
    }
    else {
        Node* node;
        node = dq->last;
        dq->last = node->left;
        dq->size--;
        
        return node;
    }
}
long char_to_number(char c) {
    return c - '0';
}
long str_to_number(char* str, int size) {
    long result = 0;
    for(int i=0; i < size; i++) {
        result *= 10;
        result += char_to_number(str[i]);
    }

    return result;
}

unsigned long get_string(char* result) {
    
    char buffer;
    unsigned long size = 0;
    unsigned long memSize = 1;

    do {
        buffer = getchar();
        size++;
        if (result == NULL) {
            result = (char *) malloc(sizeof(char));
        } else if (size > memSize) {
            memSize *= 2;
            result = (char *) realloc(result, memSize * sizeof(char));
        }
        result[size - 1] = buffer;
    } while (buffer != '\n');
    return size-1;
}

int main() {
    int size;
    char* infix;
    Deque in;
    Deque stack;
    Deque out;


    char buffer;
    unsigned long size = 0;
    unsigned long memSize = 1;

    do {
        buffer = getchar();
        size++;
        if (infix == NULL) {
            infix = (char *) malloc(sizeof(char));
        } else if (size > memSize) {
            memSize *= 2;
            infix = (char *) realloc(infix, memSize * sizeof(char));
        }
        infix[size - 1] = buffer;
    } while (buffer != '\n');
    //size = get_string(infix);
    printf("%s", infix);
    char* element = malloc(sizeof(char)*size);
    char buffer;
    int j=0;
    printf("Захожу в цикл i<size\n");
    for(int i=0; i < size; i++) {
        printf('%c', infix[i]);
        buffer = infix[i];
        if('0' <= buffer && buffer <= '9') {
            printf("О, цифра\n");
            element[j] = buffer;
            j++;

        }
        else if('a' <= buffer && buffer <= 'z') {
            printf("a-z\n");
            Node* node;
            node->type = 'l';
            node->value = (T)buffer;
            push_front(&in, node);
            free(node);
        } 
        else if((buffer == '+') || buffer == '-' ||
                buffer == '*' || buffer == '/' ||
                buffer == '^' || buffer == '%' || buffer == '(' || buffer == ')') {
            // Also, if last char is number
            if(j > 0) {
                long value = str_to_number(element, j);
                j = 0;
                Node* node;
                node->type = 'n';
                node->value = value;
                push_front(&in, node);
            }
            // Else last char is litter
            Node* node;
            if(buffer == '+' || buffer == '-') {
                node->type = '+';
                node->priority = 0;
            }
            else if(buffer == '*' || buffer == '/') {
                node->type = '*';
                node->priority = 1;
            }
            else if(buffer == '^') {
                node->type = '^';
                node->priority = 2;
            }
            else if(buffer == '(') {
                node->type = '(';
                node->priority = 3;
            }
            else if(buffer == ')') {
                node->type = ')';
                node->priority = 3;
            } 
            node->value = (T)buffer;
            push_front(&in, node);
        }
    }
    // Now We have input nodes

    // Sorting Station
    printf("Sorting Station\n");
    for(int i=0; i < in.size; i++) {
        Node* node_stack = NULL;
        Node* node_in = pop_front(&in);
        if(node_in->type == 'n' || node_in->type == 'l') {
            push_back(&out, node_in);
        }
        // Ifs Only for operators
        else if(stack.size > 0) {
            node_stack = pop_back(&stack);
        }
        else if(node_stack == NULL) {
            push_back(&stack, node_in);
        }
        else if(node_in->type == '(') {
            push_back(&stack, node_in);
        }
        else if(node_in->type == ')') {
            while(node_stack->type != '(') {
                push_back(&out, node_stack);
                node_stack = pop_back(&stack);
            }
            pop_back(&stack);
        }
        else {
            while((node_stack != NULL) && node_stack->priority >= node_in->priority) {
                push_back(&out, node_stack);
                if(stack.size > 0) {
                    node_stack = pop_back(&stack);
                }
            }
            push_back(&stack, node_in);
        }
    }
    for(int i=0; i < stack.size; i++) {
        Node* node_stack = pop_back(&stack);
        push_back(&out, node_stack);
    }    
    for(int i=0; i < out.size; i++) {
        Node* node = pop_front(&out);
        if(node->type == 'n') {
            printf("%d", node->value);
        }
        else {
            printf("%c", node->value);
        }
    }


    return 0;
}