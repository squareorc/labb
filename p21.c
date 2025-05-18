//21.	WAP to implement Heap sort and Merge Sort on 1D array of Student structure (contains student_name, student_roll_no, total_marks), with key as student_roll_no. And count the number of swap performed.

#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char student_name[50];
    int student_roll_no;
    int total_marks;
} Student;

// Swap function and swap counter
int swap_count = 0;
void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
    swap_count++;
}

// Heapify function for Heap Sort
void heapify(Student arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l].student_roll_no > arr[largest].student_roll_no)
        largest = l;
    if (r < n && arr[r].student_roll_no > arr[largest].student_roll_no)
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap Sort
void heapSort(Student arr[], int n) {
    swap_count = 0;
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n-1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Merge function for Merge Sort
void merge(Student arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Student L[n1], R[n2];
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].student_roll_no <= R[j].student_roll_no) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            swap_count++; // Counting as a swap when elements from right subarray are placed before left
        }
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

// Merge Sort
void mergeSort(Student arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Function to print array
void printArray(Student arr[], int n) {
    printf("Name\tRoll No\tMarks\n");
    for (int i = 0; i < n; i++)
        printf("%s\t%d\t%d\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
}

int main() {
    int n, choice;
    Student arr[MAX], arr_copy[MAX];

    printf("Enter number of students: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter name, roll no, total marks for student %d: ", i+1);
        scanf("%s %d %d", arr[i].student_name, &arr[i].student_roll_no, &arr[i].total_marks);
    }

    do {
        printf("\n1. Heap Sort\n2. Merge Sort\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            memcpy(arr_copy, arr, n * sizeof(Student));
            heapSort(arr_copy, n);
            printf("\nSorted array (Heap Sort):\n");
            printArray(arr_copy, n);
            printf("Number of swaps: %d\n", swap_count);
        } else if (choice == 2) {
            memcpy(arr_copy, arr, n * sizeof(Student));
            swap_count = 0;
            mergeSort(arr_copy, 0, n-1);
            printf("\nSorted array (Merge Sort):\n");
            printArray(arr_copy, n);
            printf("Number of swaps: %d\n", swap_count);
        }
    } while (choice != 3);

    return 0;
}