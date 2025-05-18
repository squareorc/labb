//27.	We Fly Anywhere Airlines (WFAA) is considering redesigning their ticket counters for airline passengers. They would like to have two separate waiting lines, one for regular customers and one for frequent flyers. Assuming there is only one ticket agent available to serve all passengers, they would like to determine the average waiting time for both types of passengers using various strategies for taking passengers from the waiting lines. WAP to simulate this situation.

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int arrival_time;
    int service_time;
    int start_service_time;
    int finish_time;
} Passenger;

typedef struct {
    Passenger queue[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return (q->rear + 1) % MAX == q->front;
}

void enqueue(Queue *q, Passenger p) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX;
    }
    q->queue[q->rear] = p;
}

Passenger dequeue(Queue *q) {
    Passenger p = q->queue[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    return p;
}

int main() {
    int n_regular, n_frequent, i, time = 0, served = 0;
    Queue regular, frequent;
    Passenger regulars[MAX], frequents[MAX];
    int total_regular_wait = 0, total_frequent_wait = 0;
    int served_regular = 0, served_frequent = 0;

    initQueue(&regular);
    initQueue(&frequent);

    printf("Enter number of regular customers: ");
    scanf("%d", &n_regular);
    printf("Enter arrival and service times for regular customers:\n");
    for (i = 0; i < n_regular; i++) {
        scanf("%d %d", &regulars[i].arrival_time, &regulars[i].service_time);
        regulars[i].start_service_time = -1;
        regulars[i].finish_time = -1;
    }

    printf("Enter number of frequent flyers: ");
    scanf("%d", &n_frequent);
    printf("Enter arrival and service times for frequent flyers:\n");
    for (i = 0; i < n_frequent; i++) {
        scanf("%d %d", &frequents[i].arrival_time, &frequents[i].service_time);
        frequents[i].start_service_time = -1;
        frequents[i].finish_time = -1;
    }

    int idx_regular = 0, idx_frequent = 0;
    int agent_free_time = 0;
    int total_passengers = n_regular + n_frequent;

    // Strategy: Serve frequent flyers first if both queues are non-empty
    while (served < total_passengers) {
        // Enqueue arriving passengers at current time
        while (idx_regular < n_regular && regulars[idx_regular].arrival_time <= time) {
            enqueue(&regular, regulars[idx_regular]);
            idx_regular++;
        }
        while (idx_frequent < n_frequent && frequents[idx_frequent].arrival_time <= time) {
            enqueue(&frequent, frequents[idx_frequent]);
            idx_frequent++;
        }

        // If agent is free, serve next passenger
        if (time >= agent_free_time) {
            if (!isEmpty(&frequent)) {
                Passenger p = dequeue(&frequent);
                p.start_service_time = time;
                p.finish_time = time + p.service_time;
                total_frequent_wait += (p.start_service_time - p.arrival_time);
                agent_free_time = p.finish_time;
                served_frequent++;
                served++;
            } else if (!isEmpty(&regular)) {
                Passenger p = dequeue(&regular);
                p.start_service_time = time;
                p.finish_time = time + p.service_time;
                total_regular_wait += (p.start_service_time - p.arrival_time);
                agent_free_time = p.finish_time;
                served_regular++;
                served++;
            } else {
                // No one to serve, advance time
                time++;
                continue;
            }
        }
        time++;
    }

    printf("\nAverage waiting time for regular customers: %.2f\n",
           served_regular ? (float)total_regular_wait / served_regular : 0.0);
    printf("Average waiting time for frequent flyers: %.2f\n",
           served_frequent ? (float)total_frequent_wait / served_frequent : 0.0);

    return 0;
}