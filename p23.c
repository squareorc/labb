//23.	WAP to convert a given Infix expression into its equivalent Prefix expression and evaluate it using stack.

#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top < MAX - 1)
        stack[++top] = c;
}

char pop() {
    if (top >= 0)
        return stack[top--];
    return '\0';
}

char peek() {
    if (top >= 0)
        return stack[top];
    return '\0';
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int precedence(char c) {
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

void reverse(char *exp) {
    int l = 0, r = strlen(exp) - 1;
    while (l < r) {
        char t = exp[l];
        exp[l] = exp[r];
        exp[r] = t;
        l++; r--;
    }
}

// Check if character is a digit (0-9)
int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

// Check if character is an alphabet (A-Z or a-z)
int is_alpha(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// Check if character is alphanumeric
int is_alnum(char c) {
    return is_digit(c) || is_alpha(c);
}

void infixToPrefix(char infix[], char prefix[]) {
    int i, j = 0;
    int len = strlen(infix);
    char exp[MAX];
    strcpy(exp, infix);
    reverse(exp);

    for (i = 0; i < len; i++) {
        if (exp[i] == '(')
            exp[i] = ')';
        else if (exp[i] == ')')
            exp[i] = '(';
    }

    for (i = 0; i < len; i++) {
        char c = exp[i];
        if (is_alnum(c)) {
            prefix[j++] = c;
        } else if (c == '(') {
            push(c);
        } else if (c == ')') {
            while (top != -1 && peek() != '(')
                prefix[j++] = pop();
            pop();
        } else if (isOperator(c)) {
            while (top != -1 && precedence(peek()) > precedence(c))
                prefix[j++] = pop();
            push(c);
        }
    }
    while (top != -1)
        prefix[j++] = pop();
    prefix[j] = '\0';
    reverse(prefix);
}

int evalPrefix(char prefix[]) {
    int i, len = strlen(prefix);
    int stack2[MAX], top2 = -1;
    for (i = len - 1; i >= 0; i--) {
        char c = prefix[i];
        if (is_digit(c)) {
            stack2[++top2] = c - '0';
        } else if (isOperator(c)) {
            int op1 = stack2[top2--];
            int op2 = stack2[top2--];
            int res;
            switch (c) {
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/': res = op1 / op2; break;
                case '^': {
                    int r = 1, j;
                    for (j = 0; j < op2; j++)
                        r *= op1;
                    res = r;
                    break;
                }
                default: res = 0;
            }
            stack2[++top2] = res;
        }
    }
    return stack2[top2];
}

int main() {
    char infix[MAX], prefix[MAX];
    printf("Enter infix expression (single digit operands): ");
    scanf("%s", infix);

    infixToPrefix(infix, prefix);
    printf("Prefix expression: %s\n", prefix);

    int result = evalPrefix(prefix);
    printf("Evaluation result: %d\n", result);

    return 0;
}