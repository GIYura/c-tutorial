#include <stdio.h>
#include "func.h"

void MatrixInit(int* matrix, int rows, int columns)
{
    int counter = 1;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            *(matrix + i * columns + j) = counter;
        }
        counter++;
    }
}

void MatrixPrint2D(int* matrix, int rows, int columns)
{
    printf("Matrix:\n");
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%d ", *(matrix + i * columns + j));
        }
    printf("\n");
    }
}

void MatrixPrint1D(int* matrix, int rows, int columns)
{
    printf("Flat matrix: ");
    for (int i = 0; i < (rows * columns); i++) 
    {
        printf("%d ", *(matrix + i));
    }
    printf("\n");
}

int MatrixFriendlySum(int* matrix, int rows, int columns)
{
    int sum = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            sum += *(matrix + i * columns + j);
        }
  }
  return sum;
}

int MatrixNoneFriendlySum(int* matrix, int rows, int columns)
{
    int sum = 0;
    for (int j = 0; j < columns; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            sum += *(matrix + i * columns + j);
        }
  }
  return sum;
}

