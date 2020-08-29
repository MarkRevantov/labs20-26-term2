#ifndef __lib24.c__
#define __lib24.c__

#include <stdio.h>
#include <stdlib.h>

#define NUM -3
#define LIT -2

typedef int T;
typedef struct Node {
    // priority: -3 - number; -2 - litter; 0 - +-; 1 - */; 2 - ^; 3 - ();
    short priority;
    T value;
    struct Node* left;
    struct Node* right;
    struct Node* parrent;
} Node;
typedef struct {
    Node* root;
} Tree;
typedef struct {
    int size;
    Node* first;
    Node* last;
} Deque;

Node* makeNode(T value, short priority) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->priority = priority;
    node->left = NULL;
    node->right = NULL;
    node->parrent = NULL;
    
    return node;
}
void destroyNode(Node* node) {
    if(node->left  != NULL) destroyNode(node->left);
    if(node->right != NULL) destroyNode(node->right);
    free(node);
    node = NULL;
    return;
}
void createDeque(Deque* dq) {
    dq->size = 0;
    dq->first = NULL;
    dq->last = NULL;
}
void push_front(Deque* dq, Node* node) {
    if(dq->size == 0) {
        dq->first = node;
        dq->last = node;
        dq->size++;
        return;
    }
    else {
        node->right = dq->first;
        dq->first->left = node;
        dq->first = node;
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
        dq->last->right = node;
        dq->last = node;
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
void printDeque(Deque* dq) {
    Node* node = dq->first;
    for(int i=0; i < dq->size; i++) {
        if (node->priority == NUM) {
            printf("%d|", node->value);
        }
        else {printf("%c|", node->value);}
        node = node->right;
    }
    printf("\n");
    return;
}

void sortingStation(Deque* input, Deque* output) {
    Deque* stack = malloc(sizeof(Deque));
    createDeque(stack);
    Node* node = NULL;
    while(input->size != 0){
        node = pop_front(input);
        if(node->priority == NUM || node->priority == LIT) {
            push_back(output, node);
            continue;
        }
        // That is operator
        if(node->value == '(') {
            push_back(stack, node);
            continue;
        }
        if(node->value == ')') {
            while(stack->last->value != '(') {
                push_back(output, pop_back(stack));
            }
            // Pop '('
            pop_back(stack);
            continue;
        }
        while(stack->size != 0 && stack->last->priority >= node->priority) {
            push_back(output, pop_back(stack));
        }
        if(stack->size == 0 || stack->last->priority < node->priority) {
            push_back(stack, node);
            continue;
        }
    }
    while(stack->size != 0) {
        push_back(output, pop_back(stack));
    }

    free(stack);
    return;
}
void buildPartTree(Node* node, Deque* dq) {
    if(node->right == NULL) {
        Node* dqnode = pop_back(dq);

        dqnode->right = NULL;
        dqnode->left = NULL;
        dqnode->parrent = node;

        node->right = dqnode;
        if(0 <= dqnode->priority && dqnode->priority <= 2) {
            buildPartTree(node->right, dq);
        }
    }
    if(node->left == NULL) {
        Node* dqnode = pop_back(dq);

        dqnode->right = NULL;
        dqnode->left = NULL;
        dqnode->parrent = node;

        node->left = dqnode;
        if(0 <= dqnode->priority && dqnode->priority <= 2) {
            buildPartTree(node->left, dq);
        }
    }
}
void buildTree(Tree* tree, Deque* dq) {
    Node* node = pop_back(dq);
    node->left = NULL;
    node->right = NULL;
    tree->root = node;
    buildPartTree(node, dq);
}
Node* getCopyNode(Node* node) {
    Node* new_node = malloc(sizeof(Node));
    if(node->right != NULL) new_node->right = getCopyNode(node->right);
    if(node->left  != NULL) new_node->left  = getCopyNode(node->left);
    new_node->parrent = NULL;
    new_node->value = node->value;
    new_node->priority = node->priority;

    return new_node;
}
void replaceNodesTree(Node* node) {
    if(node->left  != NULL) replaceNodesTree(node->left);
    else return;
    if(node->right != NULL) replaceNodesTree(node->right);
    else return;

    if(node->left->priority == NUM && node->right->priority == NUM) return;

    if(node->value == '*' && node->left->priority == NUM && node->right->priority != NUM) {
        Node* nodetmp = node->left;
        node->left = node->right;
        node->right = nodetmp;
    }
    // Здесь явно что-то плохо написано
    if(node->priority == 1 && node->value == '*') {
        if (node->right->priority == NUM) {
            if(node->right->value > 1) {
                Node* node_operation = makeNode('*', 1);
                Node* node_left = getCopyNode(node->left);
                Node* node_right = makeNode(node->right->value-1, NUM);
                node_left->parrent = node_operation;
                node_right->parrent = node_operation;

                node_operation->left = node_left;
                node_operation->right = node_right;

                destroyNode(node->right);
                node->right = node_operation;
                node_operation->parrent = node;

                node->value = '+';
                node->priority = 0;
                replaceNodesTree(node->right);
            }
            else if(node->right->value == 1) {
                Node* nodetmp = node->left;
                
                destroyNode(node->right);
                
                node->right = nodetmp->right;
                node->left = nodetmp->left;
                node->priority = nodetmp->priority;
                node->value = nodetmp->value;
                free(nodetmp);
                /*
                node->left = NULL;
                nodetmp->parrent = node->parrent;
                // Сын говорит отцу, что Сын - сын Отца
                if(nodetmp->parrent->right == node) nodetmp->parrent->right == nodetmp;
                else if(nodetmp->parrent->left == node) nodetmp->parrent->left == nodetmp;
                destroyNode(node);
                node = nodetmp;
                */
            }
            else if(node->right->value == 0) {
                destroyNode(node->right);
                destroyNode(node->left);
                node->right = NULL;
                node->left = NULL;

                node->priority = NUM;
                node->value = 0;
            }
        }
    }
}
void replaceNodes(Tree* tree) {
    replaceNodesTree(tree->root);
    return;
}
void printNode(Node* node, int tabs) {
    for(int i=0; i < tabs; i++) {
        printf("\t");
    }
    if ((0 <= node->priority && node->priority <= 2) || node->priority == LIT) {
        printf("%c\n", node->value);
    }
    else {
        printf("%d\n", node->value);
    }

    if(node->right != NULL) printNode(node->right, tabs+1);
    if(node->left  != NULL) printNode(node->left, tabs+1);
    return;
}
void printTree(Tree* tree) {
    printNode(tree->root, 0);
    return;
}
void printInfixNode(Node* node) {
    if(node->left != NULL && node->right != NULL) {
        printf("(");
        printInfixNode(node->left);
        printf("%c", node->value);
        printInfixNode(node->right);
        printf(")"); 
    }
    else {
        if (node->priority == NUM) printf("%d", node->value);
        if (node->priority == LIT) printf("%c", node->value);
    }
    return;
}
void printInfixTree(Tree* tree) {
    printInfixNode(tree->root);
    printf("\n");
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
void DequeFromString(Deque* in, char* infix, int size) {
    char* numbers = malloc(sizeof(char)*size);
    int j=0;
    Node* node;
    //printf("Захожу в цикл i<size\n");
    for(int i=0; i < size; i++) {
        //printf("Обработка символа %c\n", infix[i]);
        if(infix[i] == ' ') continue;
        
        if('0' <= infix[i] && infix[i] <= '9') {
            //printf("О, цифра\n");
            numbers[j] = infix[i];
            j++;
            continue;
        }
        else if('a' <= infix[i] && infix[i] <= 'z') {
            //printf("a-z\n");
            node = makeNode((T)infix[i], LIT);
            push_back(in, node);
        } 
        else if((infix[i] == '+') || infix[i] == '-' ||
                infix[i] == '*' || infix[i] == '/' ||
                infix[i] == '^' || infix[i] == '%' || infix[i] == '(' || infix[i] == ')') {
            // Also, if last char is number
            if(j > 0) {
                long value = str_to_number(numbers, j);
                j = 0;
                node = makeNode(value, NUM);
                push_back(in, node);
            }
            short priority = 4;
            switch(infix[i]) {
                case '+': priority = 0; break;
                case '-': priority = 0; break;
                case '*': priority = 1; break;
                case '/': priority = 1; break;
                case '^': priority = 2; break;
                // Почему при priority >=3 скобки в sortingStation обваливаются, а при <0 ничего плохого не происходит, и все работает?
                case '(': priority = -4; break;
                case ')': priority = -4; break;
                default: printf("Bad char in switch!!!\n");
            }
            node = makeNode((T)infix[i], priority);
            push_back(in, node);
        }
    }
    // Last char maybe is number
    if(j > 0) {
        long value = str_to_number(numbers, j);
        j = 0;
        node = makeNode(value, NUM);
        push_back(in, node);
    }
    free(numbers);
    free(infix);
}

#endif
