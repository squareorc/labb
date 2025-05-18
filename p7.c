//7.	Write a Program to create a Binary Search Tree and perform following nonrecursive operations on it. a. Preorder Traversal b. Postorder Traversal c. Display total Number of Nodes d. Display Leaf nodes


#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Stack for non-recursive traversals
typedef struct Stack {
    Node* data[100];
    int top;
} Stack;

void push(Stack *s, Node *node) {
    s->data[++(s->top)] = node;
}

Node* pop(Stack *s) {
    return s->data[(s->top)--];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

// BST Insertion
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

// Non-recursive Preorder Traversal
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

// Non-recursive Postorder Traversal
void postorder(Node* root) {
    if (!root) return;
    Stack s1, s2;
    s1.top = s2.top = -1;
    push(&s1, root);
    while (!isEmpty(&s1)) {
        Node* curr = pop(&s1);
        push(&s2, curr);
        if (curr->left) push(&s1, curr->left);
        if (curr->right) push(&s1, curr->right);
    }
    while (!isEmpty(&s2)) {
        printf("%d ", pop(&s2)->data);
    }
}

// Count total nodes (non-recursive)
int countNodes(Node* root) {
    if (!root) return 0;
    Stack s; s.top = -1;
    int count = 0;
    push(&s, root);
    while (!isEmpty(&s)) {
        Node* curr = pop(&s);
        count++;
        if (curr->right) push(&s, curr->right);
        if (curr->left) push(&s, curr->left);
    }
    return count;
}

// Display leaf nodes (non-recursive)
void displayLeafNodes(Node* root) {
    if (!root) return;
    Stack s; s.top = -1;
    push(&s, root);
    while (!isEmpty(&s)) {
        Node* curr = pop(&s);
        if (!curr->left && !curr->right)
            printf("%d ", curr->data);
        if (curr->right) push(&s, curr->right);
        if (curr->left) push(&s, curr->left);
    }
}

int main() {
    Node* root = NULL;
    int choice, val;
    while (1) {
        printf("\n1. Insert\n2. Preorder Traversal\n3. Postorder Traversal\n4. Total Nodes\n5. Display Leaf Nodes\n6. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
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
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;
            case 4:
                printf("Total nodes: %d\n", countNodes(root));
                break;
            case 5:
                printf("Leaf nodes: ");
                displayLeafNodes(root);
                printf("\n");
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}