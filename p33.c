//33.	Given a list, split it into two sublists — one for the front half, and one for the back half. If the number of elements is odd, the extra element should go in the front list. So FrontBackSplit() on the list {2, 3, 5, 7, 11} should yield the two lists {2, 3, 5} and {7, 11}. Getting this right for all the cases is harder than it looks. You should check your solution against a few cases (length = 2, length = 3, length=4) to make sure that the list gets split correctly near the short-list boundary conditions. If it works right for length=4, it probably works right for length=1000. You will probably need special case code to deal with the (length <2) cases.

#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to print a linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to split the list into front and back halves
void FrontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef) {
    struct Node* slow;
    struct Node* fast;
    if (source == NULL || source->next == NULL) {
        // length < 2 cases
        *frontRef = source;
        *backRef = NULL;
        return;
    }
    slow = source;
    fast = source->next;
    // Advance 'fast' two nodes, and advance 'slow' one node
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    // 'slow' is before the midpoint in the list, so split it in two at that point.
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

// Helper function to push a node at the end
void append(struct Node** headRef, int new_data) {
    struct Node* node = newNode(new_data);
    if (*headRef == NULL) {
        *headRef = node;
        return;
    }
    struct Node* temp = *headRef;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = node;
}

int main() {
    struct Node* head = NULL;
    struct Node* front = NULL;
    struct Node* back = NULL;
    int n, val, i;

    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &val);
        append(&head, val);
    }

    printf("Original list: ");
    printList(head);

    FrontBackSplit(head, &front, &back);

    printf("Front half: ");
    printList(front);

    printf("Back half: ");
    printList(back);

    return 0;
}
