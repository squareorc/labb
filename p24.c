//24.	WAP to implement multiple stack i.e. More than two stacks using array and perform following operations on it. A. PUSH, B. POP, C. StackFull D. StackeEmpty E. Display Stack.

#include <stdio.h>
#define MAX 100
#define NSTACKS 3 // Number of stacks

int arr[MAX];
int top[NSTACKS];
int base[NSTACKS];
int size[NSTACKS] = {0}; // To keep track of each stack's size

// Initialize the stacks
void initStacks(int n, int totalSize) {
    int partition = totalSize / n;
    for (int i = 0; i < n; i++) {
        base[i] = i * partition;
        top[i] = base[i] - 1;
        size[i] = partition;
    }
    // Last stack gets any remaining space
    size[n-1] += totalSize % n;
}

// Check if stack is full
int isFull(int sn) {
    return (top[sn] == base[sn] + size[sn] - 1);
}

// Check if stack is empty
int isEmpty(int sn) {
    return (top[sn] < base[sn]);
}

// Push operation
void push(int sn, int val) {
    if (isFull(sn)) {
        printf("Stack %d is Full!\n", sn+1);
        return;
    }
    top[sn]++;
    arr[top[sn]] = val;
    printf("Pushed %d to Stack %d\n", val, sn+1);
}

// Pop operation
int pop(int sn) {
    if (isEmpty(sn)) {
        printf("Stack %d is Empty!\n", sn+1);
        return -1;
    }
    int val = arr[top[sn]];
    top[sn]--;
    printf("Popped %d from Stack %d\n", val, sn+1);
    return val;
}

// Display stack
void display(int sn) {
    if (isEmpty(sn)) {
        printf("Stack %d is Empty!\n", sn+1);
        return;
    }
    printf("Stack %d: ", sn+1);
    for (int i = base[sn]; i <= top[sn]; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n = NSTACKS, totalSize = MAX;
    initStacks(n, totalSize);

    int choice, stackNum, val;
    while (1) {
        printf("\n1. PUSH\n2. POP\n3. StackFull\n4. StackEmpty\n5. Display Stack\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 6) break;
        if (choice >= 1 && choice <= 5) {
            printf("Enter stack number (1-%d): ", n);
            scanf("%d", &stackNum);
            stackNum--;
            if (stackNum < 0 || stackNum >= n) {
                printf("Invalid stack number!\n");
                continue;
            }
        }
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &val);
                push(stackNum, val);
                break;
            case 2:
                pop(stackNum);
                break;
            case 3:
                if (isFull(stackNum))
                    printf("Stack %d is Full!\n", stackNum+1);
                else
                    printf("Stack %d is NOT Full!\n", stackNum+1);
                break;
            case 4:
                if (isEmpty(stackNum))
                    printf("Stack %d is Empty!\n", stackNum+1);
                else
                    printf("Stack %d is NOT Empty!\n", stackNum+1);
                break;
            case 5:
                display(stackNum);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}