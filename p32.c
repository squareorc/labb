//32.	       Write a Program to implement multiple queue i.e. two queues using array and perform following operations on it. A. Addq, B. Delq, C. Display Queue. 

#include <stdio.h>
#define MAX 50

int queue1[MAX], front1 = -1, rear1 = -1;
int queue2[MAX], front2 = -1, rear2 = -1;

void addq(int queue[], int *front, int *rear, int val) {
    if (*rear == MAX - 1) {
        printf("Queue Overflow\n");
        return;
    }
    if (*front == -1)
        *front = 0;
    (*rear)++;
    queue[*rear] = val;
}

int delq(int queue[], int *front, int *rear) {
    int val;
    if (*front == -1 || *front > *rear) {
        printf("Queue Underflow\n");
        return -1;
    }
    val = queue[*front];
    (*front)++;
    return val;
}

void display(int queue[], int front, int rear) {
    int i;
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
        return;
    }
    for (i = front; i <= rear; i++)
        printf("%d ", queue[i]);
    printf("\n");
}

int main() {
    int choice, qno, val, delval;
    while (1) {
        printf("\n1. Addq\n2. Delq\n3. Display Queue\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 4)
            break;
        printf("Enter queue number (1 or 2): ");
        scanf("%d", &qno);
        switch (choice) {
            case 1:
                printf("Enter value to add: ");
                scanf("%d", &val);
                if (qno == 1)
                    addq(queue1, &front1, &rear1, val);
                else if (qno == 2)
                    addq(queue2, &front2, &rear2, val);
                else
                    printf("Invalid queue number\n");
                break;
            case 2:
                if (qno == 1)
                    delval = delq(queue1, &front1, &rear1);
                else if (qno == 2)
                    delval = delq(queue2, &front2, &rear2);
                else {
                    printf("Invalid queue number\n");
                    break;
                }
                if (delval != -1)
                    printf("Deleted value: %d\n", delval);
                break;
            case 3:
                if (qno == 1)
                    display(queue1, front1, rear1);
                else if (qno == 2)
                    display(queue2, front2, rear2);
                else
                    printf("Invalid queue number\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}