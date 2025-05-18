//38.	Write a Program to create Inorder Threaded Binary Tree and Traverse it in Postorder way.

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

Node* rightMost(Node* n) {
    if (n == NULL) return NULL;
    while (n->rthread == 0)
        n = n->right;
    return n;
}

// Helper function to find parent in threaded binary tree
Node* findParent(Node* root, Node* child) {
    if (root == NULL || root == child)
        return NULL;
    Node* parent = NULL;
    Node* curr = root;
    while (curr != NULL && curr != child) {
        parent = curr;
        if (child->data < curr->data) {
            if (curr->lthread == 0)
                curr = curr->left;
            else
                break;
        } else {
            if (curr->rthread == 0)
                curr = curr->right;
            else
                break;
        }
    }
    if (curr == child)
        return parent;
    return NULL;
}

// Postorder traversal using parent finding (not efficient, but works for threaded trees)
void postorder(Node* root) {
    if (root == NULL) return;
    Node* curr = leftMost(root);
    Node* last = NULL;
    Node* stack[100];
    int top = -1;
    curr = root;
    while (curr != NULL || top != -1) {
        while (curr != NULL) {
            stack[++top] = curr;
            if (curr->lthread == 0)
                curr = curr->left;
            else
                break;
        }
        while (top != -1 && (stack[top]->rthread == 1 || stack[top]->right == last)) {
            last = stack[top--];
            printf("%d ", last->data);
        }
        if (top != -1)
            curr = stack[top]->right;
        else
            curr = NULL;
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
    printf("Postorder Traversal: ");
    postorder(root);
    printf("\n");
    return 0;
}