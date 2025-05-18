//22.	WAP to convert a given Infix expression into its equivalent Postfix expression and evaluate it using stack.

#include <stdio.h>

#define MAX 100

// Stack for operators
char stack[MAX];
int top = -1;

// Stack for evaluation
int evalStack[MAX];
int evalTop = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    if (top == -1) return -1;
    return stack[top--];
}

char peek() {
    if (top == -1) return -1;
    return stack[top];
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

void evalPush(int val) {
    evalStack[++evalTop] = val;
}

int evalPop() {
    return evalStack[evalTop--];
}

int isdigit(char c) {
    return (c >= '0' && c <= '9');
}

void infixToPostfix(char* infix, char* postfix) {
    int i = 0, k = 0;
    char c;
    while ((c = infix[i++]) != '\0') {
        if (isdigit(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && peek() != '(')
                postfix[k++] = pop();
            pop(); // remove '('
        } else if (isOperator(c)) {
            while (top != -1 && precedence(peek()) >= precedence(c))
                postfix[k++] = pop();
            push(c);
        }
    }
    while (top != -1)
        postfix[k++] = pop();
    postfix[k] = '\0';
}

int evaluatePostfix(char* postfix) {
    int i = 0;
    char c;
    while ((c = postfix[i++]) != '\0') {
        if (isdigit(c)) {
            evalPush(c - '0');
        } else if (isOperator(c)) {
            int b = evalPop();
            int a = evalPop();
            switch (c) {
                case '+': evalPush(a + b); break;
                case '-': evalPush(a - b); break;
                case '*': evalPush(a * b); break;
                case '/': evalPush(a / b); break;
            }
        }
    }
    return evalPop();
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression (single digit operands): ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("Evaluation result: %d\n", result);

    return 0;
}