//WAP to merge two sorted Doubly linked lists and display their result.

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Function to insert node at the end
Node* insertEnd(Node* head, int data) {
    Node* newNode = createNode(data);
    if (!head)
        return newNode;
    Node* temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
    return head;
}

// Function to display the list
void display(Node* head) {
    Node* temp = head;
    while (temp) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Function to merge two sorted doubly linked lists
Node* mergeSortedLists(Node* head1, Node* head2) {
    Node* merged = NULL;
    Node* tail = NULL;

    while (head1 && head2) {
        Node* temp;
        if (head1->data <= head2->data) {
            temp = head1;
            head1 = head1->next;
        } else {
            temp = head2;
            head2 = head2->next;
        }
        temp->prev = temp->next = NULL;
        if (!merged) {
            merged = tail = temp;
        } else {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }
    while (head1) {
        Node* temp = head1;
        head1 = head1->next;
        temp->prev = temp->next = NULL;
        if (!merged) {
            merged = tail = temp;
        } else {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }
    while (head2) {
        Node* temp = head2;
        head2 = head2->next;
        temp->prev = temp->next = NULL;
        if (!merged) {
            merged = tail = temp;
        } else {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }
    }
    return merged;
}

int main() {
    Node* head1 = NULL;
    Node* head2 = NULL;
    int n1, n2, val, i;

    printf("Enter number of elements in first sorted list: ");
    scanf("%d", &n1);
    printf("Enter elements of first sorted list:\n");
    for (i = 0; i < n1; i++) {
        scanf("%d", &val);
        head1 = insertEnd(head1, val);
    }

    printf("Enter number of elements in second sorted list: ");
    scanf("%d", &n2);
    printf("Enter elements of second sorted list:\n");
    for (i = 0; i < n2; i++) {
        scanf("%d", &val);
        head2 = insertEnd(head2, val);
    }

    printf("First List: ");
    display(head1);
    printf("Second List: ");
    display(head2);

    Node* merged = mergeSortedLists(head1, head2);
    printf("Merged Sorted List: ");
    display(merged);

    return 0;
}