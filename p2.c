/*
2.	Write a Program to create a Binary Tree and perform following nonrecursive operations on it. a. inorder Traversal; b. Count no. of nodes on longest path; c. display tree levelwise; d. Display height of a tree.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE 100

// Binary Tree Node
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Stack for non-recursive inorder
typedef struct {
    Node* arr[MAX_QUEUE];
    int top;
} Stack;

// Queue for level order traversal
typedef struct {
    Node* arr[MAX_QUEUE];
    int front, rear;
} Queue;

// Stack functions
void initStack(Stack* s) { s->top = -1; }
int isEmptyStack(Stack* s) { return s->top == -1; }
void push(Stack* s, Node* node) { s->arr[++(s->top)] = node; }
Node* pop(Stack* s) { return s->arr[(s->top)--]; }

// Queue functions
void initQueue(Queue* q) { q->front = q->rear = 0; }
int isEmptyQueue(Queue* q) { return q->front == q->rear; }
void enqueue(Queue* q, Node* node) { q->arr[(q->rear)++] = node; }
Node* dequeue(Queue* q) { return q->arr[(q->front)++]; }

// Create new node
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Insert node (level order for simplicity)
Node* insertLevelOrder(Node* root, int data) {
    Node* newNode = createNode(data);
    if (!root) return newNode;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    while (!isEmptyQueue(&q)) {
        Node* temp = dequeue(&q);
        if (!temp->left) {
            temp->left = newNode;
            break;
        } else enqueue(&q, temp->left);
        if (!temp->right) {
            temp->right = newNode;
            break;
        } else enqueue(&q, temp->right);
    }
    return root;
}

// a. Non-recursive Inorder Traversal
void inorderNonRecursive(Node* root) {
    Stack s;
    initStack(&s);
    Node* curr = root;
    printf("Inorder Traversal: ");
    while (curr || !isEmptyStack(&s)) {
        while (curr) {
            push(&s, curr);
            curr = curr->left;
        }
        curr = pop(&s);
        printf("%d ", curr->data);
        curr = curr->right;
    }
    printf("\n");
}

// b. Count nodes on longest path (height)
int longestPathNodes(Node* root) {
    if (!root) return 0;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    int height = 0;
    while (!isEmptyQueue(&q)) {
        int nodeCount = q.rear - q.front;
        if (nodeCount == 0) break;
        height++;
        while (nodeCount--) {
            Node* node = dequeue(&q);
            if (node->left) enqueue(&q, node->left);
            if (node->right) enqueue(&q, node->right);
        }
    }
    return height;
}

// c. Display tree levelwise
void displayLevelwise(Node* root) {
    if (!root) return;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    printf("Levelwise display:\n");
    while (!isEmptyQueue(&q)) {
        int nodeCount = q.rear - q.front;
        while (nodeCount--) {
            Node* node = dequeue(&q);
            printf("%d ", node->data);
            if (node->left) enqueue(&q, node->left);
            if (node->right) enqueue(&q, node->right);
        }
        printf("\n");
    }
}

// d. Display height of tree
void displayHeight(Node* root) {
    int h = longestPathNodes(root);
    printf("Height of tree: %d\n", h);
}

int main() {
    Node* root = NULL;
    int n, val, ch;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter node values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insertLevelOrder(root, val);
    }
    do {
        printf("\nMenu:\n1. Inorder Traversal\n2. Count nodes on longest path\n3. Display tree levelwise\n4. Display height of tree\n5. Exit\nEnter choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: inorderNonRecursive(root); break;
            case 2: printf("Nodes on longest path: %d\n", longestPathNodes(root)); break;
            case 3: displayLevelwise(root); break;
            case 4: displayHeight(root); break;
        }
    } while (ch != 5);
    return 0;
}