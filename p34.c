//WAP to perform addition of two polynomials using singly linked list.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int pow;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int coeff, int pow) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->pow = pow;
    newNode->next = NULL;
    return newNode;
}

// Function to insert node at the end
void insert(Node** head, int coeff, int pow) {
    Node* newNode = createNode(coeff, pow);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}

// Function to display the polynomial
void display(Node* head) {
    if (!head) {
        printf("0\n");
        return;
    }
    while (head) {
        printf("%dx^%d", head->coeff, head->pow);
        if (head->next && head->next->coeff >= 0)
            printf(" + ");
        head = head->next;
    }
    printf("\n");
}

// Function to add two polynomials
Node* addPoly(Node* poly1, Node* poly2) {
    Node* result = NULL;
    while (poly1 && poly2) {
        if (poly1->pow > poly2->pow) {
            insert(&result, poly1->coeff, poly1->pow);
            poly1 = poly1->next;
        } else if (poly1->pow < poly2->pow) {
            insert(&result, poly2->coeff, poly2->pow);
            poly2 = poly2->next;
        } else {
            insert(&result, poly1->coeff + poly2->coeff, poly1->pow);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    while (poly1) {
        insert(&result, poly1->coeff, poly1->pow);
        poly1 = poly1->next;
    }
    while (poly2) {
        insert(&result, poly2->coeff, poly2->pow);
        poly2 = poly2->next;
    }
    return result;
}

int main() {
    Node *poly1 = NULL, *poly2 = NULL, *result = NULL;
    int n, coeff, pow, i;

    printf("Enter number of terms in first polynomial: ");
    scanf("%d", &n);
    printf("Enter terms in descending order of power (coeff pow):\n");
    for (i = 0; i < n; i++) {
        scanf("%d%d", &coeff, &pow);
        insert(&poly1, coeff, pow);
    }

    printf("Enter number of terms in second polynomial: ");
    scanf("%d", &n);
    printf("Enter terms in descending order of power (coeff pow):\n");
    for (i = 0; i < n; i++) {
        scanf("%d%d", &coeff, &pow);
        insert(&poly2, coeff, pow);
    }

    printf("First Polynomial: ");
    display(poly1);
    printf("Second Polynomial: ");
    display(poly2);

    result = addPoly(poly1, poly2);
    printf("Sum: ");
    display(result);

    // Free memory (optional)
    return 0;
}