//40.	WAP to implement Insertion sort, Merge Sort, Bubble Sort and Quick Sort on 1D array of Student structure (contains student_name, student_roll_no, total_marks ), with key as student_roll_no. and count the number of swap performed

#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char student_name[50];
    int student_roll_no;
    int total_marks;
} Student;

void swap(Student *a, Student *b, int *swap_count) {
    Student temp = *a;
    *a = *b;
    *b = temp;
    (*swap_count)++;
}

// Insertion Sort
void insertionSort(Student arr[], int n, int *swap_count) {
    for (int i = 1; i < n; i++) {
        Student key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].student_roll_no > key.student_roll_no) {
            arr[j + 1] = arr[j];
            (*swap_count)++;
            j--;
        }
        arr[j + 1] = key;
        if (j + 1 != i) (*swap_count)++;
    }
}

// Bubble Sort
void bubbleSort(Student arr[], int n, int *swap_count) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].student_roll_no > arr[j+1].student_roll_no) {
                swap(&arr[j], &arr[j+1], swap_count);
            }
        }
    }
}

// Merge function for Merge Sort
void merge(Student arr[], int l, int m, int r, int *swap_count) {
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
            (*swap_count)++;
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge Sort
void mergeSort(Student arr[], int l, int r, int *swap_count) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, swap_count);
        mergeSort(arr, m + 1, r, swap_count);
        merge(arr, l, m, r, swap_count);
    }
}

// Partition function for Quick Sort
int partition(Student arr[], int low, int high, int *swap_count) {
    int pivot = arr[high].student_roll_no;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].student_roll_no < pivot) {
            i++;
            swap(&arr[i], &arr[j], swap_count);
        }
    }
    swap(&arr[i + 1], &arr[high], swap_count);
    return i + 1;
}

// Quick Sort
void quickSort(Student arr[], int low, int high, int *swap_count) {
    if (low < high) {
        int pi = partition(arr, low, high, swap_count);
        quickSort(arr, low, pi - 1, swap_count);
        quickSort(arr, pi + 1, high, swap_count);
    }
}

// Function to print array
void printArray(Student arr[], int n) {
    printf("Name\tRoll No\tMarks\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
    }
}

int main() {
    Student arr[MAX];
    int n, choice, swap_count;
    printf("Enter number of students: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter name, roll no, total marks for student %d: ", i + 1);
        scanf("%s %d %d", arr[i].student_name, &arr[i].student_roll_no, &arr[i].total_marks);
    }
    do {
        printf("\n1. Insertion Sort\n2. Bubble Sort\n3. Merge Sort\n4. Quick Sort\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);
        Student temp[MAX];
        memcpy(temp, arr, n * sizeof(Student));
        swap_count = 0;
        switch (choice) {
            case 1:
                insertionSort(temp, n, &swap_count);
                printf("Sorted array (Insertion Sort):\n");
                printArray(temp, n);
                printf("Number of swaps: %d\n", swap_count);
                break;
            case 2:
                bubbleSort(temp, n, &swap_count);
                printf("Sorted array (Bubble Sort):\n");
                printArray(temp, n);
                printf("Number of swaps: %d\n", swap_count);
                break;
            case 3:
                mergeSort(temp, 0, n - 1, &swap_count);
                printf("Sorted array (Merge Sort):\n");
                printArray(temp, n);
                printf("Number of swaps: %d\n", swap_count);
                break;
            case 4:
                quickSort(temp, 0, n - 1, &swap_count);
                printf("Sorted array (Quick Sort):\n");
                printArray(temp, n);
                printf("Number of swaps: %d\n", swap_count);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);
    return 0;
}