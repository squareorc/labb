//6.	Write a Program to create a Binary Search Tree and perform following nonrecursive operations on it. a. Preorder Traversal b. Inorder Traversal c. Display Number of Leaf Nodes d. Mirror Image

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Stack for traversal
typedef struct Stack {
    Node* data[100];
    int top;
} Stack;

void push(Stack *s, Node *node) {
    s->data[++(s->top)] = node;
}

Node* pop(Stack *s) {
    if (s->top == -1) return NULL;
    return s->data[(s->top)--];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

// BST Insert
Node* insert(Node* root, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    if (!root) return newNode;
    Node *curr = root, *parent = NULL;
    while (curr) {
        parent = curr;
        if (data < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
    return root;
}

// Nonrecursive Inorder Traversal
void inorder(Node* root) {
    Stack s; s.top = -1;
    Node* curr = root;
    while (curr || !isEmpty(&s)) {
        while (curr) {
            push(&s, curr);
            curr = curr->left;
        }
        curr = pop(&s);
        printf("%d ", curr->data);
        curr = curr->right;
    }
}

// Nonrecursive Preorder Traversal
void preorder(Node* root) {
    if (!root) return;
    Stack s; s.top = -1;
    push(&s, root);
    while (!isEmpty(&s)) {
        Node* curr = pop(&s);
        printf("%d ", curr->data);
        if (curr->right) push(&s, curr->right);
        if (curr->left) push(&s, curr->left);
    }
}

// Nonrecursive Count Leaf Nodes
int countLeafNodes(Node* root) {
    if (!root) return 0;
    Stack s; s.top = -1;
    int count = 0;
    push(&s, root);
    while (!isEmpty(&s)) {
        Node* curr = pop(&s);
        if (!curr->left && !curr->right)
            count++;
        if (curr->right) push(&s, curr->right);
        if (curr->left) push(&s, curr->left);
    }
    return count;
}

// Nonrecursive Mirror Image
void mirror(Node* root) {
    if (!root) return;
    Stack s; s.top = -1;
    push(&s, root);
    while (!isEmpty(&s)) {
        Node* curr = pop(&s);
        Node* temp = curr->left;
        curr->left = curr->right;
        curr->right = temp;
        if (curr->left) push(&s, curr->left);
        if (curr->right) push(&s, curr->right);
    }
}

int main() {
    Node* root = NULL;
    int ch, val;
    while (1) {
        printf("\n1.Insert\n2.Preorder\n3.Inorder\n4.Count Leaf Nodes\n5.Mirror Image\n6.Exit\nEnter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                root = insert(root, val);
                break;
            case 2:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;
            case 3:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 4:
                printf("Number of leaf nodes: %d\n", countLeafNodes(root));
                break;
            case 5:
                mirror(root);
                printf("Mirror image created.\n");
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}