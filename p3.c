/*
3.	Write a Program to create a Binary Search Tree holding numeric keys and perform following nonrecursive operations on it. a. Levelwise display, b. Mirror image, c. Display height of a tree.
*/

#include <stdio.h>
#include <stdlib.h>

// Definition of a node in BST
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Queue for level order traversal
typedef struct QueueNode {
    Node *treeNode;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front, *rear;
} Queue;

// Queue functions
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

int isEmpty(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, Node *treeNode) {
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    temp->treeNode = treeNode;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
}

Node* dequeue(Queue *q) {
    if (isEmpty(q)) return NULL;
    QueueNode *temp = q->front;
    Node *treeNode = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return treeNode;
}

// BST insertion (non-recursive)
Node* insert(Node *root, int key) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    if (root == NULL) return newNode;

    Node *parent = NULL, *curr = root;
    while (curr != NULL) {
        parent = curr;
        if (key < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (key < parent->key)
        parent->left = newNode;
    else
        parent->right = newNode;
    return root;
}

// a. Levelwise display (non-recursive)
void levelOrder(Node *root) {
    if (root == NULL) return;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    while (!isEmpty(&q)) {
        Node *curr = dequeue(&q);
        printf("%d ", curr->key);
        if (curr->left) enqueue(&q, curr->left);
        if (curr->right) enqueue(&q, curr->right);
    }
    printf("\n");
}

// b. Mirror image (non-recursive)
void mirror(Node *root) {
    if (root == NULL) return;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    while (!isEmpty(&q)) {
        Node *curr = dequeue(&q);
        // Swap left and right
        Node *temp = curr->left;
        curr->left = curr->right;
        curr->right = temp;
        if (curr->left) enqueue(&q, curr->left);
        if (curr->right) enqueue(&q, curr->right);
    }
}

// c. Display height of a tree (non-recursive)
int treeHeight(Node *root) {
    if (root == NULL) return 0;
    Queue q;
    initQueue(&q);
    enqueue(&q, root);
    int height = 0;
    while (1) {
        int nodeCount = 0;
        QueueNode *temp = q.front;
        while (temp) {
            nodeCount++;
            temp = temp->next;
        }
        if (nodeCount == 0)
            return height;
        height++;
        while (nodeCount > 0) {
            Node *curr = dequeue(&q);
            if (curr->left) enqueue(&q, curr->left);
            if (curr->right) enqueue(&q, curr->right);
            nodeCount--;
        }
    }
}

// Main function to demonstrate operations
int main() {
    Node *root = NULL;
    int choice, key;
    while (1) {
        printf("\n1. Insert\n2. Levelwise Display\n3. Mirror Image\n4. Display Height\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Levelwise display: ");
                levelOrder(root);
                break;
            case 3:
                mirror(root);
                printf("Mirror image created.\n");
                break;
            case 4:
                printf("Height of tree: %d\n", treeHeight(root));
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}