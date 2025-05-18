// 39.	Implement following problems based on Arrays. A. a. i/p- { 2,2,3,4} o/p: 1 b. i/p: {1,3,2,5,4,9} o/p: 3 c. i/p: { 1,5,3,4,6,2,12} o/p: 5 B. Find saddle point in the Matrix. C. Magic square Matrix. (Check) D. Represent given matrix in its Sparse form.

#include <stdio.h>
#include <stdlib.h>

/* Problem A: Find the smallest positive number missing from an array
   The logic is to mark the presence of each number in a separate array
   and then find the first unmarked positive number */
int findSmallestMissingPositive(int arr[], int n)
{
    // Create a marker array and initialize it to 0
    int *present = (int *)calloc(n + 1, sizeof(int));

    // Mark the presence of each positive number in the array
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > 0 && arr[i] <= n)
        {
            present[arr[i]] = 1;
        }
    }

    // Find the first number that is not marked
    for (int i = 1; i <= n; i++)
    {
        if (present[i] == 0)
        {
            free(present);
            return i;
        }
    }

    // If all numbers from 1 to n are present, return n+1
    free(present);
    return n + 1;
}

/* Problem B: Find saddle point in a matrix
   A saddle point is an element that is minimum in its row and maximum in its column */
void findSaddlePoint(int matrix[][100], int rows, int cols)
{
    printf("\nProblem B: Finding Saddle Points\n");
    int foundSaddle = 0;

    for (int i = 0; i < rows; i++)
    {
        // Find the minimum element in the current row
        int min_col = 0;
        for (int j = 1; j < cols; j++)
        {
            if (matrix[i][j] < matrix[i][min_col])
            {
                min_col = j;
            }
        }

        // Check if the minimum element is also maximum in its column
        int isMaxInCol = 1;
        for (int k = 0; k < rows; k++)
        {
            if (matrix[k][min_col] > matrix[i][min_col])
            {
                isMaxInCol = 0;
                break;
            }
        }

        if (isMaxInCol)
        {
            printf("Saddle point found at position (%d, %d) with value %d\n",
                   i, min_col, matrix[i][min_col]);
            foundSaddle = 1;
        }
    }

    if (!foundSaddle)
    {
        printf("No saddle point found in the matrix.\n");
    }
}

/* Problem C: Check if a matrix is a Magic Square
   A magic square is a square matrix where the sum of each row, column,
   and the two main diagonals are all equal */
int isMagicSquare(int matrix[][100], int n)
{
    // Calculate the sum of the first row as the target sum
    int targetSum = 0;
    for (int j = 0; j < n; j++)
    {
        targetSum += matrix[0][j];
    }

    // Check rows
    for (int i = 1; i < n; i++)
    {
        int rowSum = 0;
        for (int j = 0; j < n; j++)
        {
            rowSum += matrix[i][j];
        }
        if (rowSum != targetSum)
        {
            return 0;
        }
    }

    // Check columns
    for (int j = 0; j < n; j++)
    {
        int colSum = 0;
        for (int i = 0; i < n; i++)
        {
            colSum += matrix[i][j];
        }
        if (colSum != targetSum)
        {
            return 0;
        }
    }

    // Check main diagonal (top-left to bottom-right)
    int diagSum1 = 0;
    for (int i = 0; i < n; i++)
    {
        diagSum1 += matrix[i][i];
    }
    if (diagSum1 != targetSum)
    {
        return 0;
    }

    // Check other diagonal (top-right to bottom-left)
    int diagSum2 = 0;
    for (int i = 0; i < n; i++)
    {
        diagSum2 += matrix[i][n - 1 - i];
    }
    if (diagSum2 != targetSum)
    {
        return 0;
    }

    return 1;
}

/* Problem D: Represent a matrix in sparse form
   Sparse form represents only the non-zero elements of a matrix */
void representSparseMatrix(int matrix[][100], int rows, int cols)
{
    printf("\nProblem D: Sparse Matrix Representation\n");

    // Count non-zero elements
    int nonZeroCount = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] != 0)
            {
                nonZeroCount++;
            }
        }
    }

    // Create sparse matrix representation (triplet form)
    // Format: [row, column, value]
    int sparse[nonZeroCount][3];
    int k = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] != 0)
            {
                sparse[k][0] = i;
                sparse[k][1] = j;
                sparse[k][2] = matrix[i][j];
                k++;
            }
        }
    }

    // Print the sparse matrix
    printf("Original Matrix (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nSparse Matrix Representation (Row, Column, Value):\n");
    printf("Total non-zero elements: %d\n", nonZeroCount);
    printf("Row\tColumn\tValue\n");
    for (int i = 0; i < nonZeroCount; i++)
    {
        printf("%d\t%d\t%d\n", sparse[i][0], sparse[i][1], sparse[i][2]);
    }
}

int main()
{
    // Problem A: Find the smallest positive number missing
    printf("Problem A: Find the smallest positive number missing\n");

    // Case a
    int arr1[] = {2, 2, 3, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("a. Input: {2, 2, 3, 4}, Output: %d\n",
           findSmallestMissingPositive(arr1, n1));

    // Case b
    int arr2[] = {1, 3, 2, 5, 4, 9};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("b. Input: {1, 3, 2, 5, 4, 9}, Output: %d\n",
           findSmallestMissingPositive(arr2, n2));

    // Case c
    int arr3[] = {1, 5, 3, 4, 6, 2, 12};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("c. Input: {1, 5, 3, 4, 6, 2, 12}, Output: %d\n",
           findSmallestMissingPositive(arr3, n3));

    // Problem B: Find saddle point in the Matrix
    int matrix1[100][100] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    findSaddlePoint(matrix1, 3, 3);

    // Problem C: Check if a matrix is a Magic Square
    printf("\nProblem C: Check Magic Square\n");

    // Example of a 3x3 magic square
    int magicSquare[100][100] = {
        {8, 1, 6},
        {3, 5, 7},
        {4, 9, 2}};

    int nonMagicSquare[100][100] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    printf("Example 1 is %sa magic square.\n",
           isMagicSquare(magicSquare, 3) ? "" : "not ");

    printf("Example 2 is %sa magic square.\n",
           isMagicSquare(nonMagicSquare, 3) ? "" : "not ");

    // Problem D: Represent a matrix in sparse form
    int sparseMatrix[100][100] = {
        {0, 0, 3, 0, 4},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 0}};

    representSparseMatrix(sparseMatrix, 4, 5);

    return 0;
}