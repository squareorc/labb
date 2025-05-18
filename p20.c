//20.	WAP to implement Heap sort and Quick Sort on 1D array of Student structure (contains student_name, student_roll_no, total_marks), with key as student_roll_no. And count the number of swap performed

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

// Heapify function for Heap Sort
void heapify(Student arr[], int n, int i, int *swap_count) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l].student_roll_no > arr[largest].student_roll_no)
        largest = l;
    if (r < n && arr[r].student_roll_no > arr[largest].student_roll_no)
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest], swap_count);
        heapify(arr, n, largest, swap_count);
    }
}

void heapSort(Student arr[], int n, int *swap_count) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i, swap_count);

    for (int i = n-1; i > 0; i--) {
        swap(&arr[0], &arr[i], swap_count);
        heapify(arr, i, 0, swap_count);
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
    swap(&arr[i+1], &arr[high], swap_count);
    return i+1;
}

void quickSort(Student arr[], int low, int high, int *swap_count) {
    if (low < high) {
        int pi = partition(arr, low, high, swap_count);
        quickSort(arr, low, pi - 1, swap_count);
        quickSort(arr, pi + 1, high, swap_count);
    }
}

void printStudents(Student arr[], int n) {
    printf("Name\tRoll No\tTotal Marks\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
    }
}

int main() {
    Student arr[MAX];
    int n, i;
    int heap_swaps = 0, quick_swaps = 0;

    printf("Enter number of students: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter name, roll no, total marks for student %d: ", i+1);
        scanf("%s %d %d", arr[i].student_name, &arr[i].student_roll_no, &arr[i].total_marks);
    }

    Student heap_arr[MAX], quick_arr[MAX];
    memcpy(heap_arr, arr, n * sizeof(Student));
    memcpy(quick_arr, arr, n * sizeof(Student));

    heapSort(heap_arr, n, &heap_swaps);
    printf("\nHeap Sort Result:\n");
    printStudents(heap_arr, n);
    printf("Heap Sort Swaps: %d\n", heap_swaps);

    quickSort(quick_arr, 0, n-1, &quick_swaps);
    printf("\nQuick Sort Result:\n");
    printStudents(quick_arr, n);
    printf("Quick Sort Swaps: %d\n", quick_swaps);

    return 0;
}