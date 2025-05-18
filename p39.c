//39.	Implement following problems based on Arrays. A. a. i/p- { 2,2,3,4} o/p: 1 b. i/p: {1,3,2,5,4,9} o/p: 3 c. i/p: { 1,5,3,4,6,2,12} o/p: 5 B. Find saddle point in the Matrix. C. Magic square Matrix. (Check) D. Represent given matrix in its Sparse form.

#include <stdio.h>

// A. Find the smallest missing positive integer in an array
int smallest_missing_positive(int arr[], int n) {
    int present[n+1];
    for (int i = 0; i <= n; i++) present[i] = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0 && arr[i] <= n)
            present[arr[i]] = 1;
    }
    for (int i = 1; i <= n; i++) {
        if (!present[i]) return i;
    }
    return n+1;
}

// B. Find saddle point in the matrix
void find_saddle_point(int mat[10][10], int r, int c) {
    int found = 0;
    for (int i = 0; i < r; i++) {
        int min_row = mat[i][0], col_idx = 0;
        for (int j = 1; j < c; j++) {
            if (mat[i][j] < min_row) {
                min_row = mat[i][j];
                col_idx = j;
            }
        }
        int k;
        for (k = 0; k < r; k++) {
            if (mat[k][col_idx] > min_row)
                break;
        }
        if (k == r) {
            printf("Saddle point at (%d,%d): %d\n", i, col_idx, min_row);
            found = 1;
        }
    }
    if (!found)
        printf("No saddle point found.\n");
}

// C. Check if a matrix is a magic square
int is_magic_square(int mat[10][10], int n) {
    int sum = 0, diag1 = 0, diag2 = 0;
    for (int j = 0; j < n; j++)
        sum += mat[0][j];
    for (int i = 0; i < n; i++) {
        int row = 0, col = 0;
        for (int j = 0; j < n; j++) {
            row += mat[i][j];
            col += mat[j][i];
        }
        if (row != sum || col != sum)
            return 0;
        diag1 += mat[i][i];
        diag2 += mat[i][n-i-1];
    }
    return (diag1 == sum && diag2 == sum);
}

// D. Represent matrix in sparse form
void sparse_form(int mat[10][10], int r, int c) {
    int count = 0;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (mat[i][j] != 0)
                count++;
    printf("Sparse matrix representation:\n");
    printf("Row Col Value\n");
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (mat[i][j] != 0)
                printf("%d   %d   %d\n", i, j, mat[i][j]);
}

int main() {
    // A. Test cases
    int arr1[] = {2,2,3,4};
    int arr2[] = {1,3,2,5,4,9};
    int arr3[] = {1,5,3,4,6,2,12};
    printf("A.a Output: %d\n", smallest_missing_positive(arr1, 4));
    printf("A.b Output: %d\n", smallest_missing_positive(arr2, 6));
    printf("A.c Output: %d\n", smallest_missing_positive(arr3, 7));

    // B. Saddle point
    int mat1[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    printf("\nB. Saddle point:\n");
    find_saddle_point(mat1, 3, 3);

    // C. Magic square
    int magic[3][3] = {{2,7,6},{9,5,1},{4,3,8}};
    printf("\nC. Magic Square: ");
    if (is_magic_square(magic, 3))
        printf("Yes\n");
    else
        printf("No\n");

    // D. Sparse form
    int mat2[3][3] = {{0,0,3},{4,0,0},{0,8,0}};
    printf("\nD. Sparse form:\n");
    sparse_form(mat2, 3, 3);

    return 0;
}
