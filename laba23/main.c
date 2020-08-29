#include <stdio.h>
#include <stdlib.h>

typedef float T;
typedef struct Tree {
    T value;
    int size;
    struct Tree* left;
    struct Tree* right;
} Tree;
typedef struct {
    T value;
    int depth;
} ValDepth;

void create(Tree* tree, T value) {
    tree->value = value;
    tree->left = NULL;
    tree->right = NULL;
    tree->size = 1;
    return;
}
void push(Tree* base_tree, Tree* new_tree) {
    base_tree->size += new_tree->size;
    // Если левое поддерево пустое - занять левое поддерево 
    if(base_tree->left == NULL) {
        base_tree->left = new_tree;
    }
    // Тогда попробуем занять правое поддерево
    else if(base_tree->right == NULL) {
        base_tree->right = new_tree;
    }
    // Ага, деревья и слева, и справа уже есть. Тогда пристроимся к ним
    else if(base_tree->left->size <= base_tree->right->size) {
        push(base_tree->left, new_tree);
    }
    else {
        push(base_tree->right, new_tree);
    }
}
void delete_node(Tree* tree) {
    if((tree->left != NULL && tree->right == NULL) ||tree->left->size > tree->right->size){
        if(tree->left->size == 1) {
            free(tree->left);
            tree->left = NULL;
            tree->size--;
        }
        else {
            delete_node(tree->left);
            tree->size--;
        }
    }
    else {
        if(tree->right->size == 1) {
            free(tree->right);
            tree->right = NULL;
            tree->size--;
        }
        else {
            delete_node(tree->right);
            tree->size--;
        }
    }

    return;
}
void print(Tree* tree, int tabs) {
    for(int i=0; i < tabs; i++) {
        printf("\t");
    }
    printf("%f\n", tree->value);
    if(tree->left != NULL) print(tree->left, tabs+1);
    if(tree->right != NULL) print(tree->right, tabs+1);
    return; 
}
short is_in_range(Tree* tree, T l, T r) {
    short result = 1;
    if(tree->left != NULL) {
        result = is_in_range(tree->left, l, r);
    }
    if(tree->right != NULL) {
        result = is_in_range(tree->right, l, r);
    }
    if (tree->size == 1 || (tree->value < l || r < tree->value)) {
        result = 0;
        return result;
    }
    return result;
}

ValDepth valDepOfDeepLeaf(Tree* tree, int depth) {
    ValDepth vdleft, vdright;
    if(tree->left != NULL) {
        vdleft = valDepOfDeepLeaf(tree->left, depth+1);
    }
    else {
        vdleft.value = tree->value;
        vdleft.depth = depth;
    }
    if(tree->right != NULL) {
        vdright = valDepOfDeepLeaf(tree->right, depth+1);
    }
    else {
        vdright.value = tree->value;
        vdright.depth = depth;
    }

    return (vdleft.depth >= vdright.depth) ? vdleft : vdright;
}
T valueOfDeepLeaf(Tree* tree) {
    return valDepOfDeepLeaf(tree, 0).value;
}

int main() {
    Tree tree;
    char action;
    float value;
    
    while(scanf("%c", &action) != EOF) {
        if(action == 'c') {
            scanf("%f", &value);
            create(&tree, value);
            printf("The Tree has been created!\n");
            continue;
        }
        if(action == 'a') {
            scanf("%f", &value);
            Tree* new_tree = malloc(sizeof(Tree));
            create(new_tree, value);
            push(&tree, new_tree);
            continue;
        }
        if(action == 'p') {
            print(&tree, 0);
            continue;
        }
        if(action == 'd') {
            delete_node(&tree);
            continue;
        }
        if(action == 's') {
            printf("size: %d\n", tree.size);
            continue;
        }
        if(action == 'r') {
            T value2;
            scanf("%f%f", &value, &value2);
            if(is_in_range(&tree, value, value2)) {
                printf("Yes, values are in the range\n");
            }
            else {
                printf("No, values aren't in the range\n");
            }
            continue;
        }
        if(action == 'v') {
            printf("Значение наиболее глубокого узла: %f\n", valueOfDeepLeaf(&tree));
            continue;
        }
    }

    return 0;
}