//13.	Write a Program to create Inorder Threaded Binary Tree and Traverse it in Inorder way.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
    int lthread, rthread;
} Node;

Node* createNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    temp->lthread = temp->rthread = 1;
    return temp;
}

Node* insert(Node* root, int key) {
    Node *ptr = root, *par = NULL;
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
    Node* tmp = createNode(key);
    if (par == NULL) {
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

Node* leftMost(Node* n) {
    if (n == NULL) return NULL;
    while (n->lthread == 0)
        n = n->left;
    return n;
}

void inorder(Node* root) {
    Node* cur = leftMost(root);
    while (cur != NULL) {
        printf("%d ", cur->data);
        if (cur->rthread)
            cur = cur->right;
        else
            cur = leftMost(cur->right);
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
    printf("Inorder Traversal: ");
    inorder(root);
    printf("\n");
    return 0;
}