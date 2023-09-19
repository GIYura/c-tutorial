#include <stdio.h>

#define CASE_1  0
#define CASE_2  0
#define CASE_3  0
#define CASE_4  1
#define CASE_5  0
#define CASE_6  0

#if CASE_3
void fun(int **p);
#endif

/*
---------------MAIN-------------------
*/
int main(int argc, char* argv[])
{
/*
1. What will be the output of the program?
*/
#if CASE_1
    printf("========= CASE 1 ==========\n");

    int a[5] = { 5, 1, 15, 20, 25 };

    printf("Initial array: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    int i, j, m;
    i = ++a[1]; /* i = 2 */
    j = a[1]++; /* j = 2 */
    m = a[i++]; /* m = 15; i = 3 */
    printf("Output: %d, %d, %d", i, j, m); /* 3, 2, 15 */
    printf("\n");

    printf("Modified array: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n\n");

#elif CASE_2

/*
2. What will be the output of the program?
*/
/*
NOTE: 
array - pointer to the first element of the array;
&array - pointer in an entire array.

array + 1 - increase the memory address by the size of array is pointing to.
sizeof (int) = 4 bytes.

&array + 1 - increase the memory address by the size of entire array.
With int array[4] the memory address will be increased 4 * 4 = 16 bytes.

NOTE: 
The name of 1-D array is the address of the first element.
The name of 2-D array is the address of the first 1-D array (the whole row).
*/
    printf("========= CASE 2 ==========\n");

    printf("sizeof int: %ld\n", sizeof(int));

    int buffer[4];
    printf("buffer:      %p\n", buffer);
    printf("&buffer:     %p\n", &buffer);
    printf("&buffer[0]:  %p\n", &buffer[0]);

    printf("buffer + 1:  %p\n", buffer + 1);
    printf("&buffer + 1: %p\n\n", &buffer + 1);

    int array[3][3] = { {1,2,3}, {4,5,6}, {7,8,9} };
    
    int i, j;
    int a, b, c, d;

    /* p is an array of pointers.
    It stores address of individual elements of the 0's row: 1, 2, 3 */
    int *p[] = { (int*)array, (int*)array + 1, (int*)array + 2 };

    printf("array base address:  %p\n", array);

    /* pointer to the first element in the first row */
    printf("array[1]:            %p\n", array[1]); /* pointer to 4 */
    printf("array[1] + 1:        %p\n", array[1] + 1); /* pointer to 5 */
    printf("*(array[1] + 1):     %d\n\n", *(array[1] + 1)); /* dereference pointer to 5 */

    /* pointer to the whole first row */
    printf("&array[1]:           %p\n", &array[1]); /* pointer to row 4,5,6 */
    printf("&array[1] + 1:       %p\n", &array[1] + 1); /* pointer to row 7,8,9 */
    printf("*(&array[1] + 1):    %p\n", *(&array[1] + 1)); /* pointer to 7 */
    printf("*(&array[1]) + 1:    %p\n", *(&array[1]) + 1); /* pointer to 5 */

    /* NOTE: parentheses does matter */
    printf("*(*(&array[1] + 1)): %d\n", *(*(&array[1] + 1))); /* dereference pointer to 7 */
    printf("*(*(&array[1]) + 1): %d\n", *(*(&array[1]) + 1)); /* dereference pointer to 5 */

    /* mixing of types:
    NOTE: compiler generates warning.
    &array[1] + 1 - its type is pointer to an array of 3 ints;
    whereas pointer - is a pointer to an int.
    To get rid of the warning, we need to type-cast */
    int* pointer = (int*)(&array[1] + 1);
    printf("pointer:             %p; value: %d\n\n", pointer, *pointer);

    printf("size of matrix 3x3 of int in bytes: %ld\n", sizeof(array));

    printf("base address of row 0: %p\n", &array[0] + 0);
    printf("base address of row 1: %p\n", &array[0] + 1);
    printf("base address of row 2: %p\n", &array[0] + 2);

    printf("p0: %p[0]\n", p[0]);
    printf("p1: %p[1]\n", p[1]);
    printf("p2: %p[2]\n", p[2]);

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            a = p[i][j]; //*(*(p + i) + j);
            b = p[j][i]; //*(*(j + p) + i);
            c = p[i][j]; //*(*(i + p) + j);
            d = p[j][i]; //*(*(p + j) + i);

            printf("%d, %d, %d, %d\n", a, b, c, d);
        }
    }
#elif CASE_3
/*
4. 
Q: What will be the output of the program?
*/
    printf("========= CASE 3 ==========\n");
    int a[3][4] = { {1, 2, 3, 4}, {4, 3, 2, 8}, {7, 8, 9, 0} };
    int* ptr;
    ptr = &a[0][0];
    fun(&ptr);
/*
NOTE: print 2-D array within single for loop.
*/
    printf("Print 2-D array within single for loop:\n");
    for (int* p = &a[0][0]; p <= &a[2][3]; p++)
    {
        printf("%d ", *p);
    }
    printf("\n");
#elif CASE_4

/*
5.
Q: What will be the output of the program? 
*/
    printf("========= CASE 4 ==========\n");
    int arr[] = { 0, 1, 2, 3, 4 };

    int* p[] = { arr, arr + 1, arr + 2, arr + 3, arr + 4 };
    int** ptr = p;

    ptr++;

    printf("sizeof pointer: %ld\n", sizeof(int*));

    printf("%ld, %ld, %d\n", ptr-p, *ptr-arr, **ptr);

    *ptr++; /* dereference ptr, then increment ptr */

    printf("%ld, %ld, %d\n", ptr-p, *ptr-arr, **ptr);

    *++ptr; /* increment ptr, then dereference ptr */
    printf("%ld, %ld, %d\n", ptr-p, *ptr-arr, **ptr);

    ++*ptr; /* dereference ptr, then increment the value */
    printf("%ld, %ld, %d\n", ptr-p, *ptr-arr, **ptr);
#endif

    return 0;
}

/**/
#if CASE_3
void fun(int **p)
{
    printf("Output: %d\n", **p);
}
#endif



