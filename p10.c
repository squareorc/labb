//10.	Write a Program to create a Binary Search Tree and display its mirror image with and without disturbing the original tree. Also display height of a tree using nonrecursion.

#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct node {
    int data;
    struct node *left, *right;
} Node;

// Create a new node
Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Insert into BST
Node* insert(Node* root, int data) {
    if (root == NULL)
        return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

// Inorder traversal
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Mirror the tree (modifies original)
void mirror(Node* root) {
    if (root) {
        Node* temp = root->left;
        root->left = root->right;
        root->right = temp;
        mirror(root->left);
        mirror(root->right);
    }
}

// Copy a tree
Node* copy(Node* root) {
    if (root == NULL)
        return NULL;
    Node* new_root = newNode(root->data);
    new_root->left = copy(root->left);
    new_root->right = copy(root->right);
    return new_root;
}

// Display mirror image without disturbing original
void displayMirror(Node* root) {
    if (root) {
        displayMirror(root->right);
        printf("%d ", root->data);
        displayMirror(root->left);
    }
}

// Calculate height non-recursively (using level order traversal)
int height(Node* root) {
    if (root == NULL)
        return 0;
    int height = 0;
    Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        int nodeCount = rear - front;
        height++;
        while (nodeCount--) {
            Node* node = queue[front++];
            if (node->left)
                queue[rear++] = node->left;
            if (node->right)
                queue[rear++] = node->right;
        }
    }
    return height;
}

int main() {
    Node* root = NULL;
    int n, val, ch;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter node values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        root = insert(root, val);
    }
    while (1) {
        printf("\n1. Inorder Traversal\n2. Display Mirror (without disturbing original)\n3. Display Mirror (modifies original)\n4. Height (non-recursive)\n5. Exit\nEnter choice: ");
        scanf("%d", &ch);
        if (ch == 1) {
            printf("Inorder: ");
            inorder(root);
            printf("\n");
        } else if (ch == 2) {
            printf("Mirror Image (without disturbing original): ");
            displayMirror(root);
            printf("\n");
        } else if (ch == 3) {
            Node* mirrorRoot = copy(root);
            mirror(mirrorRoot);
            printf("Inorder of Mirrored Tree: ");
            inorder(mirrorRoot);
            printf("\n");
            // Freeing mirrorRoot is omitted for brevity
        } else if (ch == 4) {
            printf("Height of tree: %d\n", height(root));
        } else if (ch == 5) {
            break;
        } else {
            printf("Invalid choice\n");
        }
    }
    return 0;
}