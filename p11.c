//11.	Write a program to efficiently search a particular employee record by using Tree data structure. Also sort the data on emp-id in ascending order.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee {
    int emp_id;
    char name[50];
    float salary;
} Employee;

typedef struct Node {
    Employee data;
    struct Node *left, *right;
} Node;

// Create a new node
Node* createNode(Employee emp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = emp;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert employee into BST
Node* insert(Node* root, Employee emp) {
    if (root == NULL)
        return createNode(emp);
    if (emp.emp_id < root->data.emp_id)
        root->left = insert(root->left, emp);
    else if (emp.emp_id > root->data.emp_id)
        root->right = insert(root->right, emp);
    return root;
}

// Inorder traversal to sort by emp_id
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("Emp ID: %d, Name: %s, Salary: %.2f\n", root->data.emp_id, root->data.name, root->data.salary);
        inorder(root->right);
    }
}

// Search for an employee by emp_id
Node* search(Node* root, int emp_id) {
    if (root == NULL || root->data.emp_id == emp_id)
        return root;
    if (emp_id < root->data.emp_id)
        return search(root->left, emp_id);
    else
        return search(root->right, emp_id);
}

int main() {
    Node* root = NULL;
    int n, i, emp_id;
    Employee emp;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter Employee ID: ");
        scanf("%d", &emp.emp_id);
        printf("Enter Name: ");
        scanf("%s", emp.name);
        printf("Enter Salary: ");
        scanf("%f", &emp.salary);
        root = insert(root, emp);
    }

    printf("\nEmployees sorted by Emp ID:\n");
    inorder(root);

    printf("\nEnter Employee ID to search: ");
    scanf("%d", &emp_id);
    Node* found = search(root, emp_id);
    if (found) {
        printf("Record Found: Emp ID: %d, Name: %s, Salary: %.2f\n", found->data.emp_id, found->data.name, found->data.salary);
    } else {
        printf("Employee with ID %d not found.\n", emp_id);
    }

    return 0;
}