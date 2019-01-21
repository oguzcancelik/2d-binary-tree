#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct n {
    int key1;
    int key2;
    int dph;
    struct n *left;
    struct n *right;
} node;

node *insert(node *tree, int data1, int data2, int depth) {
    if (tree == NULL) {
        node *root = (node *) malloc(sizeof(node));
        root->left = NULL;
        root->right = NULL;
        root->key1 = data1;
        root->key2 = data2;
        root->dph = depth;
        return root;
    }
    if (depth % 2 == 0) {
        if (tree->key1 < data1) {
            tree->right = insert(tree->right, data1, data2, ++depth);
            return tree;
        }
        tree->left = insert(tree->left, data1, data2, ++depth);
        return tree;
    }
    if (tree->key2 < data2) {
        tree->right = insert(tree->right, data1, data2, ++depth);
        return tree;
    }
    tree->left = insert(tree->left, data1, data2, ++depth);
    return tree;
}

int maxDepth(node *tree) {
    int maxDpt = tree->dph;
    if (tree->left != NULL) {
        if (maxDpt < maxDepth(tree->left)) {
            maxDpt = maxDepth(tree->left);
        }
    }
    if (tree->right != NULL) {
        if (maxDpt < maxDepth(tree->right)) {
            maxDpt = maxDepth(tree->right);
        }
    }
    return maxDpt;
}

void print(node *tree) {
    if (tree == NULL) {
        return;
    }
    print(tree->right);
    int i;
    for (i = 0; i < tree->dph; i++) {
        printf("       |");
    }
    printf("       +");
    printf("%d,%d", tree->key1, tree->key2);
    if (tree->left != NULL && tree->right != NULL) {
        printf("<");
    } else if (tree->left != NULL) {
        printf("\\");
    } else if (tree->right != NULL) {
        printf("/");
    }
    printf("\n");
    print(tree->left);
}

void printAll(node *tree) {
    printf("\n\n");
    print(tree);
    printf("\n");

    int i;
    for (i = 0; i <= maxDepth(tree); i++) {
        printf("-------%d", i);
    }
    printf("\n\n");
}

node *maxKey1(node *tree) {
    if (tree->right != NULL) {
        if (tree->key1 < maxKey1(tree->right)->key1) {
            tree = maxKey1(tree->right);
        }
    }
    if (tree->left != NULL) {
        if (tree->key1 < maxKey1(tree->left)->key1) {
            tree = maxKey1(tree->left);
        }
    }
    return tree;
}

node *maxKey2(node *tree) {
    if (tree->right != NULL) {
        if (tree->key2 < maxKey2(tree->right)->key2) {
            tree = maxKey2(tree->right);
        }
    }
    if (tree->left != NULL) {
        if (tree->key2 < maxKey2(tree->left)->key2) {
            tree = maxKey2(tree->left);
        }
    }
    return tree;
}

node *minKey1(node *tree) {
    if (tree->left != NULL) {
        if (tree->key1 > minKey1(tree->left)->key1) {
            tree = minKey1(tree->left);
        }
    }
    if (tree->right != NULL) {
        if (tree->key1 > minKey1(tree->right)->key1) {
            tree = minKey1(tree->right);
        }
    }
    return tree;
}

node *minKey2(node *tree) {
    if (tree->left != NULL) {
        if (tree->key2 > minKey2(tree->left)->key2) {
            tree = minKey2(tree->left);
        }
    }
    if (tree->right != NULL) {
        if (tree->key2 > minKey2(tree->right)->key2) {
            tree = minKey2(tree->right);
        }
    }
    return tree;
}

node *search(node *tree, int data1, int data2) {
    if (tree != NULL) {
        if (tree->key1 == data1 && tree->key2 == data2) {
            return tree;
        } else {
            if (search(tree->left, data1, data2) == NULL) {
                return search(tree->right, data1, data2);
            }
            return search(tree->left, data1, data2);
        }
    }
    return NULL;
}

node *find(node *tree, int data, int check) {
    if (tree != NULL) {
        if (check == 1 && tree->key1 == data) {
            return tree;
        } else if (check == 2 && tree->key2 == data) {
            return tree;
        } else {
            if (find(tree->left, data, check) == NULL) {
                return find(tree->right, data, check);
            }
            return find(tree->left, data, check);
        }
    }
    return NULL;
}

node *delete_node(node *tree, int data1, int data2) {
    if (tree == NULL) {
        return NULL;
    }
    if (tree->key1 == data1 && tree->key2 == data2) {
        if (tree->left == NULL && tree->right == NULL) {
            return NULL;
        }
        if (tree->dph % 2 == 0) {
            if (tree->right != NULL) {
                tree->key1 = minKey1(tree->right)->key1;
                tree->key2 = minKey1(tree->right)->key2;
                tree->right = delete_node(tree->right, tree->key1, tree->key2);
                return tree;
            }
            tree->key1 = maxKey1(tree->left)->key1;
            tree->key2 = maxKey1(tree->left)->key2;
            tree->left = delete_node(tree->left, tree->key1, tree->key2);
            return tree;
        }
        if (tree->right != NULL) {
            tree->key1 = minKey2(tree->right)->key1;
            tree->key2 = minKey2(tree->right)->key2;
            tree->right = delete_node(tree->right, tree->key1, tree->key2);
            return tree;
        }
        tree->key1 = maxKey2(tree->left)->key1;
        tree->key2 = maxKey2(tree->left)->key2;
        tree->left = delete_node(tree->left, tree->key1, tree->key2);
        return tree;
    }
    if (tree->dph % 2 == 0) {
        if (tree->key1 < data1) {
            tree->right = delete_node(tree->right, data1, data2);
            return tree;
        }
        tree->left = delete_node(tree->left, data1, data2);
        return tree;
    }
    if (tree->key2 < data2) {
        tree->right = delete_node(tree->right, data1, data2);
        return tree;
    }
    tree->left = delete_node(tree->left, data1, data2);
    return tree;
}

int main() {
    node *tree = NULL;
    FILE *fptr = fopen("input.txt", "r+");
    if (fptr == NULL) {
        printf("input.txt not found.");
        return 0;
    }
    char buf[2];
    int key1, key2;
    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) == 0) {
        printf("\ninput.txt is empty.\n");
    } else {
        fseek(fptr, 0, SEEK_SET);
        fscanf(fptr, "%d,%d", &key1, &key2);
        tree = insert(tree, key1, key2, 0);
        while (fgets(buf, sizeof(buf), fptr) != NULL) {
            fscanf(fptr, "%d,%d", &key1, &key2);
            if (find(tree, key1, 1) == NULL && find(tree, key2, 2) == NULL) {
                tree = insert(tree, key1, key2, 0);
            }
        }
        fclose(fptr);
        printAll(tree);
    }

    char input[15];
    printf("\nType 'print' to print. Type 'insert' to insert. Type 'delete' to delete. Type 'quit' to quit. ");
    scanf("%s", input);

    while (1) {
        if (strcmp(input, "quit") == 0) {
            printf("\n\nBreaking..\n");
            break;
        } else if (strcmp(input, "print") == 0) {
            if (tree != NULL) {
                printAll(tree);
            } else {
                printf("\n->Tree is empty. Nothing to print.\n");
            }
        } else if (strcmp(input, "insert") == 0) {
            printf("\nWhich numbers will be inserted?  ");
            if (scanf("%d, %d", &key1, &key2) == 2) {
                if (find(tree, key1, 1) == NULL && find(tree, key2, 2) == NULL) {
                    tree = insert(tree, key1, key2, 0);
                    printAll(tree);
                    printf("\n->%d, %d is inserted to tree.\n", key1, key2);
                } else if (find(tree, key1, 1) != NULL && find(tree, key2, 2) != NULL) {
                    printf("\n->Invalid input. key1: %d and key2: %d are already in the tree.\n", key1, key2);
                } else if (find(tree, key1, 1) != NULL) {
                    printf("\n->Invalid input. key1: %d is already in the tree.\n", key1);
                } else {
                    printf("\n->Invalid input. key2: %d is already in the tree.\n", key2);
                }
            } else {
                printf("\n->Invalid input.\n");
            }
        } else if (strcmp(input, "delete") == 0) {
            if (tree == NULL) {
                printf("\n->Tree is empty. Nothing to delete.\n");
            } else {
                printf("\nWhich node will be removed?  ");
                if (scanf("%d, %d", &key1, &key2) == 2) {
                    if (search(tree, key1, key2) == NULL) {
                        printf("\n->Invalid input. This node doesn't exist in the tree.\n");
                    } else {
                        tree = delete_node(tree, key1, key2);
                        if (tree != NULL) {
                            printAll(tree);
                            printf("\n->%d, %d is removed from tree.\n", key1, key2);
                        } else {
                            printf("\n->%d, %d is removed from tree.\n", key1, key2);
                            printf("\n->Tree is empty now.\n");
                        }
                    }
                } else {
                    printf("\n->Invalid input.\n");
                }
            }
        }
        printf("\nType 'print' to print. Type 'insert' to insert. Type 'delete' to delete. Type 'quit' to quit. ");
        scanf("%s", input);
    }
    return 0;
}