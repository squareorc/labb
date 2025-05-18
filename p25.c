//25.	A person is living in house having 5 rooms. These rooms are adjacent to each other. There is a treasure which is electronically locked and to unlock it we need a code. In last room there is a box in which some decimal number is written. We need to convert that number into binary to open treasure which is kept in room no.1. We need to move from room no.1 to 2 to 3 and so on and follow the reverse way to come back i.e. from 5 to 4 to 3 etc. Apply suitable logic to implement this scenario by using stacks.

#include <stdio.h>
#define MAX 100

// Stack implementation
typedef struct {
    int data[MAX];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int val) {
    if (!isFull(s)) {
        s->data[++(s->top)] = val;
    }
}

int pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->data[(s->top)--];
    }
    return -1;
}

int main() {
    int rooms[5] = {0}; // Simulate 5 rooms
    int i, decimal, temp;
    Stack path;
    init(&path);

    printf("Moving from Room 1 to Room 5...\n");
    for (i = 0; i < 5; i++) {
        printf("Entered Room %d\n", i + 1);
        push(&path, i + 1);
    }

    printf("You found a box in Room 5!\n");
    printf("Enter the decimal number written in the box: ");
    scanf("%d", &decimal);

    // Convert decimal to binary using stack
    Stack binStack;
    init(&binStack);
    temp = decimal;
    if (temp == 0) {
        push(&binStack, 0);
    } else {
        while (temp > 0) {
            push(&binStack, temp % 2);
            temp /= 2;
        }
    }

    printf("Returning from Room 5 to Room 1...\n");
    while (!isEmpty(&path)) {
        printf("Exited Room %d\n", pop(&path));
    }

    printf("Binary code to unlock the treasure in Room 1: ");
    while (!isEmpty(&binStack)) {
        printf("%d", pop(&binStack));
    }
    printf("\n");

    return 0;
}