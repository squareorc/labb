//41.	Implement a Polynomial addition and multiplication using Linked Lists.

#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode {
    int coeff;
    int pow;
    struct PolyNode* next;
} PolyNode;

// Function to create a new node
PolyNode* createNode(int coeff, int pow) {
    PolyNode* node = (PolyNode*)malloc(sizeof(PolyNode));
    node->coeff = coeff;
    node->pow = pow;
    node->next = NULL;
    return node;
}

// Function to insert a node at the end
void insertEnd(PolyNode** head, int coeff, int pow) {
    PolyNode* node = createNode(coeff, pow);
    if (*head == NULL) {
        *head = node;
        return;
    }
    PolyNode* temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = node;
}

// Function to display the polynomial
void displayPoly(PolyNode* head) {
    if (!head) {
        printf("0\n");
        return;
    }
    while (head) {
        printf("%dx^%d", head->coeff, head->pow);
        if (head->next && head->next->coeff >= 0)
            printf(" + ");
        else if (head->next)
            printf(" ");
        head = head->next;
    }
    printf("\n");
}

// Function to add two polynomials
PolyNode* addPoly(PolyNode* p1, PolyNode* p2) {
    PolyNode* res = NULL;
    while (p1 && p2) {
        if (p1->pow > p2->pow) {
            insertEnd(&res, p1->coeff, p1->pow);
            p1 = p1->next;
        } else if (p1->pow < p2->pow) {
            insertEnd(&res, p2->coeff, p2->pow);
            p2 = p2->next;
        } else {
            insertEnd(&res, p1->coeff + p2->coeff, p1->pow);
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while (p1) {
        insertEnd(&res, p1->coeff, p1->pow);
        p1 = p1->next;
    }
    while (p2) {
        insertEnd(&res, p2->coeff, p2->pow);
        p2 = p2->next;
    }
    return res;
}

// Function to multiply two polynomials
PolyNode* multiplyPoly(PolyNode* p1, PolyNode* p2) {
    PolyNode* res = NULL;
    for (PolyNode* t1 = p1; t1; t1 = t1->next) {
        for (PolyNode* t2 = p2; t2; t2 = t2->next) {
            int coeff = t1->coeff * t2->coeff;
            int pow = t1->pow + t2->pow;
            // Add to result, combine like terms
            PolyNode* temp = res, *prev = NULL;
            while (temp && temp->pow > pow) {
                prev = temp;
                temp = temp->next;
            }
            if (temp && temp->pow == pow) {
                temp->coeff += coeff;
            } else {
                PolyNode* newNode = createNode(coeff, pow);
                if (prev == NULL) {
                    newNode->next = res;
                    res = newNode;
                } else {
                    newNode->next = prev->next;
                    prev->next = newNode;
                }
            }
        }
    }
    return res;
}

// Function to free the polynomial linked list
void freePoly(PolyNode* head) {
    while (head) {
        PolyNode* temp = head;
        head = head->next;
        free(temp);
    }
}

// Example usage
int main() {
    PolyNode *poly1 = NULL, *poly2 = NULL, *sum = NULL, *prod = NULL;
    int n, coeff, pow, i;

    printf("Enter number of terms in first polynomial: ");
    scanf("%d", &n);
    printf("Enter coeff and power for each term (in descending order of power):\n");
    for (i = 0; i < n; i++) {
        scanf("%d%d", &coeff, &pow);
        insertEnd(&poly1, coeff, pow);
    }

    printf("Enter number of terms in second polynomial: ");
    scanf("%d", &n);
    printf("Enter coeff and power for each term (in descending order of power):\n");
    for (i = 0; i < n; i++) {
        scanf("%d%d", &coeff, &pow);
        insertEnd(&poly2, coeff, pow);
    }

    printf("First Polynomial: ");
    displayPoly(poly1);
    printf("Second Polynomial: ");
    displayPoly(poly2);

    sum = addPoly(poly1, poly2);
    printf("Sum: ");
    displayPoly(sum);

    prod = multiplyPoly(poly1, poly2);
    printf("Product: ");
    displayPoly(prod);

    freePoly(poly1);
    freePoly(poly2);
    freePoly(sum);
    freePoly(prod);

    return 0;
}