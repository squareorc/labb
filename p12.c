//12.	Write a Program to create Inorder Threaded Binary Tree and Traverse it in Preorder way.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
    int lthread, rthread;
} Node;

Node* insert(Node* root, int key) {
    Node *ptr = root;
    Node *par = NULL;

    while (ptr != NULL) {
        if (key == ptr->data) {
            printf("Duplicate Key!\n");
            return root;
        }
        par = ptr;
        if (key < ptr->data) {
            if (ptr->lthread == 0)
                ptr = ptr->left;
            else
                break;
        } else {
            if (ptr->rthread == 0)
                ptr = ptr->right;
            else
                break;
        }
    }

    Node *tmp = (Node*)malloc(sizeof(Node));
    tmp->data = key;
    tmp->lthread = 1;
    tmp->rthread = 1;

    if (par == NULL) {
        tmp->left = tmp->right = NULL;
        root = tmp;
    } else if (key < par->data) {
        tmp->left = par->left;
        tmp->right = par;
        par->lthread = 0;
        par->left = tmp;
    } else {
        tmp->left = par;
        tmp->right = par->right;
        par->rthread = 0;
        par->right = tmp;
    }
    return root;
}

Node* leftMost(Node* node) {
    if (node == NULL)
        return NULL;
    while (node->lthread == 0)
        node = node->left;
    return node;
}

void preorder(Node* root) {
    Node* curr = root;
    while (curr != NULL) {
        printf("%d ", curr->data);
        if (curr->lthread == 0)
            curr = curr->left;
        else if (curr->rthread == 0)
            curr = curr->right;
        else {
            while (curr != NULL && curr->rthread == 1)
                curr = curr->right;
            if (curr != NULL)
                curr = curr->right;
        }
    }
}

int main() {
    Node* root = NULL;
    int n, val;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter node values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }
    printf("Preorder Traversal: ");
    preorder(root);
    printf("\n");
    return 0;
}