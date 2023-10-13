/*
This test demostrates difference in time between friendly and non-friendly matrix iteration.
Friendly - means friendly to cache
None friendly - means non-friendly to cache

To measure time execution use:
time ./test friendly-sum 10000 10000

There is a difference due to matrix stores in memory in consecutive order (row by row).
It takes less time to get access to element in one row then anoter.
It takes more time to get access to one element in one row then one element in another row.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        printf("Usage: %s [print|friendly-sum|none-friendly-sum] [number-of-rows] [number-of-columns]\n", argv[0]);
        exit(1);
    }
    char* operation = argv[1];
    int rows = atol(argv[2]);
    int columns = atol(argv[3]);

    int* matrix = (int*)malloc(rows * columns * sizeof(int));

    MatrixInit(matrix, rows, columns);

    if (strcmp(operation, "print") == 0)
    {
        MatrixPrint2D(matrix, rows, columns);
        MatrixPrint1D(matrix, rows, columns);
    }
    else if (strcmp(operation, "friendly-sum") == 0) 
    {
        int sum = MatrixFriendlySum(matrix, rows, columns);
        printf("Friendly sum: %d\n", sum);
    }
    else if (strcmp(operation, "none-friendly-sum") == 0)
    {
        int sum = MatrixNoneFriendlySum(matrix, rows, columns);
        printf("Not friendly sum: %d\n", sum);
    }
    else 
    {
        printf("FATAL: Not supported operation!\n");
        exit(1);
    }

    free(matrix);

    return 0;
}

