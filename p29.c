//Write a program which simulates the operation of a busy airport which has only two runways to handle all takeoffs and landings. You may assume that each takeoff or landing takes 15 minutes to complete. One runway request is made during each five minute time interval and likelihood of landing request is the same as for takeoff. Priority is given to planes requesting a landing. If a request cannot be honored it is added to a takeoff or landing queue. Your program should simulate 120 minutes of activity at the airport. Each request for runway clearance should be time-stamped and added to the appropriate queue. The output from your program should include the final queue contents, the number of take offs completed, the number of landings completed, and the average number of minutes spent in each queue.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIMULATION_TIME 120
#define REQUEST_INTERVAL 5
#define RUNWAY_TIME 15
#define RUNWAYS 2

typedef struct Node {
    int timestamp;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
    int count;
    int total_wait_time;
} Queue;

void enqueue(Queue* q, int timestamp) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->timestamp = timestamp;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
    q->count++;
}

int dequeue(Queue* q, int current_time) {
    if (q->front == NULL) return -1;
    Node* temp = q->front;
    int wait_time = current_time - temp->timestamp;
    q->total_wait_time += wait_time;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    q->count--;
    return wait_time;
}

void print_queue(Queue* q, const char* name) {
    printf("%s queue: ", name);
    Node* temp = q->front;
    while (temp) {
        printf("%d ", temp->timestamp);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Queue landing = {NULL, NULL, 0, 0};
    Queue takeoff = {NULL, NULL, 0, 0};
    int runway_free[RUNWAYS] = {0, 0}; // time when each runway becomes free
    int landings_completed = 0, takeoffs_completed = 0;
    srand((unsigned int)time(NULL));

    for (int t = 0; t < SIMULATION_TIME; t += REQUEST_INTERVAL) {
        // Generate request: 0 = landing, 1 = takeoff
        int req_type = rand() % 2;
        if (req_type == 0)
            enqueue(&landing, t);
        else
            enqueue(&takeoff, t);

        // Assign runways
        for (int r = 0; r < RUNWAYS; r++) {
            if (runway_free[r] <= t) {
                if (landing.count > 0) {
                    dequeue(&landing, t);
                    runway_free[r] = t + RUNWAY_TIME;
                    landings_completed++;
                } else if (takeoff.count > 0) {
                    dequeue(&takeoff, t);
                    runway_free[r] = t + RUNWAY_TIME;
                    takeoffs_completed++;
                }
            }
        }
    }

    // Process remaining planes in queues after simulation time
    int t = SIMULATION_TIME;
    while (landing.count > 0 || takeoff.count > 0) {
        for (int r = 0; r < RUNWAYS; r++) {
            if (runway_free[r] <= t) {
                if (landing.count > 0) {
                    dequeue(&landing, t);
                    runway_free[r] = t + RUNWAY_TIME;
                    landings_completed++;
                } else if (takeoff.count > 0) {
                    dequeue(&takeoff, t);
                    runway_free[r] = t + RUNWAY_TIME;
                    takeoffs_completed++;
                }
            }
        }
        t += REQUEST_INTERVAL;
    }

    printf("Final queue contents:\n");
    print_queue(&landing, "Landing");
    print_queue(&takeoff, "Takeoff");
    printf("Number of landings completed: %d\n", landings_completed);
    printf("Number of takeoffs completed: %d\n", takeoffs_completed);
    printf("Average wait time in landing queue: %.2f minutes\n",
           landings_completed ? (float)landing.total_wait_time / landings_completed : 0.0);
    printf("Average wait time in takeoff queue: %.2f minutes\n",
           takeoffs_completed ? (float)takeoff.total_wait_time / takeoffs_completed : 0.0);

    // Free any remaining nodes (shouldn't be any)
    while (landing.front) dequeue(&landing, t);
    while (takeoff.front) dequeue(&takeoff, t);

    return 0;
}