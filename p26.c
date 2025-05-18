//26.	WAP to implement following by using stack. A. Factorial of a given number B. Generation of Fibonacci series.

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

// Factorial using stack (iterative)
int factorial(int n) {
    Stack s;
    init(&s);
    int res = 1;
    while (n > 1) {
        push(&s, n);
        n--;
    }
    while (!isEmpty(&s)) {
        res *= pop(&s);
    }
    return res;
}

// Fibonacci series generation using stack (iterative)
void fibonacci(int n) {
    Stack s;
    init(&s);
    int a = 0, b = 1, i;
    printf("Fibonacci series: ");
    if (n >= 1) printf("%d ", a);
    if (n >= 2) printf("%d ", b);
    for (i = 3; i <= n; i++) {
        int c = a + b;
        push(&s, c);
        printf("%d ", c);
        a = b;
        b = c;
    }
    printf("\n");
}

int main() {
    int choice, num;
    printf("1. Factorial\n2. Fibonacci Series\nEnter choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("Enter number: ");
            scanf("%d", &num);
            printf("Factorial of %d is %d\n", num, factorial(num));
            break;
        case 2:
            printf("Enter number of terms: ");
            scanf("%d", &num);
            fibonacci(num);
            break;
        default:
            printf("Invalid choice\n");
    }
    return 0;
}