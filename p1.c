/*
1.	Write a Program to create a Binary Tree and perform following nonrecursive operations on it. a. Preorder Traversal, b. Postorder Traversal, c. Count total no. of nodes, d. Display height of a tree
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Stack for tree traversal
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

// Queue for tree creation
typedef struct Queue {
    Node* data[100];
    int front, rear;
} Queue;

void enqueue(Queue *q, Node *node) {
    q->data[++(q->rear)] = node;
}

Node* dequeue(Queue *q) {
    if (q->front > q->rear) return NULL;
    return q->data[(q->front)++];
}

int isQueueEmpty(Queue *q) {
    return q->front > q->rear;
}

// Create a new node
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Create tree level-wise
Node* createTree() {
    int data;
    printf("Enter root node data (-1 for NULL): ");
    scanf("%d", &data);
    if (data == -1) return NULL;

    Node* root = createNode(data);
    Queue q = {.front = 0, .rear = -1};
    enqueue(&q, root);

    while (!isQueueEmpty(&q)) {
        Node* curr = dequeue(&q);

        printf("Enter left child of %d (-1 for NULL): ", curr->data);
        scanf("%d", &data);
        if (data != -1) {
            curr->left = createNode(data);
            enqueue(&q, curr->left);
        }

        printf("Enter right child of %d (-1 for NULL): ", curr->data);
        scanf("%d", &data);
        if (data != -1) {
            curr->right = createNode(data);
            enqueue(&q, curr->right);
        }
    }
    return root;
}

// Non-recursive Preorder Traversal
void preorder(Node* root) {
    Stack s = {.top = -1};
    Node* curr = root;
    printf("Preorder: ");
    while (curr || !isEmpty(&s)) {
        if (curr) {
            printf("%d ", curr->data);
            push(&s, curr);
            curr = curr->left;
        } else {
            curr = pop(&s);
            curr = curr->right;
        }
    }
    printf("\n");
}

// Non-recursive Postorder Traversal
void postorder(Node* root) {
    Stack s1 = {.top = -1}, s2 = {.top = -1};
    if (!root) return;
    push(&s1, root);
    while (!isEmpty(&s1)) {
        Node* curr = pop(&s1);
        push(&s2, curr);
        if (curr->left) push(&s1, curr->left);
        if (curr->right) push(&s1, curr->right);
    }
    printf("Postorder: ");
    while (!isEmpty(&s2)) {
        printf("%d ", pop(&s2)->data);
    }
    printf("\n");
}

// Count total number of nodes (non-recursive)
int countNodes(Node* root) {
    if (!root) return 0;
    Stack s = {.top = -1};
    int count = 0;
    Node* curr = root;
    while (curr || !isEmpty(&s)) {
        if (curr) {
            count++;
            push(&s, curr);
            curr = curr->left;
        } else {
            curr = pop(&s);
            curr = curr->right;
        }
    }
    return count;
}

// Display height of tree (non-recursive, using level order)
int treeHeight(Node* root) {
    if (!root) return 0;
    Queue q = {.front = 0, .rear = -1};
    enqueue(&q, root);
    int height = 0;
    while (1) {
        int nodeCount = q.rear - q.front + 1;
        if (nodeCount == 0)
            return height;
        height++;
        while (nodeCount > 0) {
            Node* node = dequeue(&q);
            if (node->left) enqueue(&q, node->left);
            if (node->right) enqueue(&q, node->right);
            nodeCount--;
        }
    }
}

int main() {
    Node* root = createTree();
    int choice;
    do {
        printf("\n1. Preorder Traversal\n2. Postorder Traversal\n3. Count Nodes\n4. Display Height\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: preorder(root); break;
            case 2: postorder(root); break;
            case 3: printf("Total nodes: %d\n", countNodes(root)); break;
            case 4: printf("Height of tree: %d\n", treeHeight(root)); break;
            case 5: break;
            default: printf("Invalid choice\n");
        }
    } while (choice != 5);
    return 0;
}