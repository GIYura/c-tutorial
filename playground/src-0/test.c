#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#if CASE_3
void fun(int **p);
#endif

#if CASE_7
void foo(int p[3][4]);
#endif

#if CASE_20
void foo(int b[][3]);
#endif

#if CASE_22
void foo(char *a);
#endif

#if CASE_24
int* fun(void);
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
Q: What will be the output of the program?
NOTE:
distance between pointers = (pointer - pointer) / sizeof(element pointer points to)
int* p = 0x100;
int* q = 0x104;
q - p = (0x104 - 0x100)/4 = 1.
*/
    printf("========= CASE 4 ==========\n");
    int arr[] = { 0, 1, 2, 3, 4 };

    int* p[] = { arr, arr + 1, arr + 2, arr + 3, arr + 4 };
    int** ptr = p;

    for (int i = 0; i < 4; i++)
    {
        printf("address of p[%d]: %p\n", i, p[i]);
    }

    ptr++;

    printf("sizeof pointer: %ld\n", sizeof(int*));

    printf("%ld, %ld, %d\n", ptr-p, *ptr-arr, **ptr);

    *ptr++; /* dereference ptr, then increment ptr */

    printf("%ld, %ld, %d\n", ptr-p, *ptr-arr, **ptr);

    *++ptr; /* increment ptr, then dereference ptr */
    printf("%ld, %ld, %d\n", ptr-p, *ptr-arr, **ptr);

    ++*ptr; /* dereference ptr, then increment the value */
    printf("%ld, %ld, %d\n", ptr-p, *ptr-arr, **ptr);

#elif CASE_5
/*
Q: What will be the output of the program?
*/
    printf("========= CASE 5 ==========\n");

    int a[3][4] = {{1, 2, 3, 4}, {4, 3, 2, 1}, {7, 8, 9, 0}};
    printf("sizeof a: %ld\n", sizeof(a));
/*
NOTE: 
a + 1 = next row
&a + 1 = next after the whole matrix
*/
    printf("%p\n%p\n", a + 1, &a + 1);

#elif CASE_6
/*
Q: What will be the output of the program?
*/
    printf("========= CASE 6 ==========\n");
    int arr[1] = {10};
    printf("%d\n", 0[arr]);
    printf("sizeof arr: %ld\n", sizeof(arr));

#elif CASE_7
/*
Q. Which of the following is correct way to define the function fun() in the below program?
*/
    printf("========= CASE 7 ==========\n");
    int a[3][4];
    foo(a);

#elif CASE_8
/*
Q. What will be the output of the program ?
*/
    printf("========= CASE 8 ==========\n");
    char s[25] = "The cocaine man";
    int i = 0;
    char ch;
    ch = *(s + ++i);    /* s[++i]; */
    printf("%c", ch);   /* 'h' */
    ch = *(s + i++);    /* s[i++]; */
    printf("%c", ch);   /* 'h' */
    ch = *(i++ + s);    /* i++[s]; */
    printf("%c", ch);   /* 'e' */
    ch = ++*(i + s);    /* ++i[s]; */
    printf("%c\n", ch); /* '!' */

#elif CASE_9
/*
Q. What will be the output of the program?
*/
    printf("========= CASE 9 ==========\n");
    char ch = 'A';
    printf("%ld, %ld, %ld\n", sizeof(ch), sizeof('a'), sizeof(3.14f));

#elif CASE_10
/*
Q. What will be the output of the program?
A: Error.
NOTE: str = "ababa"; // illigal
*/
    printf("========= CASE 10 ==========\n");
    char str[] = "Nagpur";
    str[0]='K';
    printf("%s, ", str);
    //str = "Kanpur";
    printf("%s\n", str + 1);

#elif CASE_11
/*
Q. What is the output of this program?
*/
    printf("========= CASE 11 ==========\n");
    char *ptr;
    char string[] = "How are you?";
    ptr = string;
    ptr += 4;
    printf("%s\n", ptr);

#elif CASE_12
/*
Q. What is the output of this program?
*/
    printf("========= CASE 12 ==========\n");
    int a[10][20][30] = {0};
    a[5][2][1] = 2;
    printf("%d\n", *(*(*(a + 5) + 2) + 1));

#elif CASE_13
/*
Q. What is the output of this program?
A: Undefined behaviour.
*/
    printf("========= CASE 13 ==========\n");
    int a = 5;
    int b = ++a * a++;
    printf("%d\n", b);

#elif CASE_14
/*
Q. What is the output of the following program?
A: output 5.
NOTE: there is no break, case 5 and case 1 works
*/
    printf("========= CASE 14 ==========\n");
    int a = 5;
    switch(a)
    {
        default:
            a = 4;
        case 6:
            a--;
        case 5:
            a = a + 1;
        case 1:
            a = a - 1;
    }
    printf("%d\n",a);

#elif CASE_15
/*
Q: What is the output of the following program?
*/
    printf("========= CASE 15 ==========\n");
    int a = 2, b = 5;
    a = a^b;
    b = b^a;
    printf("%d %d", a, b);

#elif CASE_16
/*
Q. What is the output of the following program?
*/
    printf("========= CASE 16 ==========\n");
    int a[][3] = {{1, 2, 3}, {4, 5, 6}};
    int (*ptr)[3] = a;
    printf("%d %d ", (*ptr)[1], (*ptr)[2]);
    ++ptr;
    printf("%d %d\n", (*ptr)[1], (*ptr)[2]);

#elif CASE_17
/*
Q. What is the output of the following program?
NOTE: by default char is signed in range -128 ... +127.

Rule 1 (unsigned):
If number is X where X is greater than 255 then
    New value = X % 256
If number is Y where Y is less than 0 then
    New value = 256 – (Y % 256)

Rule 2 (signed):
If number is X where X is greater than 127 then
    p = X % 256
if p <=127
    New value = p
else
    New value = p – 256

If number is Y where Y is less than -128 then
    p = Y % 256
If p <= 127
    New value = -p
else
    New value = 256 -p 
*/
    printf("========= CASE 17 ==========\n");
    char c = 125;
    c = c + 10;
    printf("%d\n",c);

#elif CASE_18
/*
Q. What is the output of the following program?
*/
    printf("========= CASE 18 ==========\n");
struct node
{
    int a;
    int b;
    int c;
};
    struct node s = { 3, 5, 6 };
    struct node *pt = &s;
    printf("%d\n", *((int*)pt + 1));

#elif CASE_19
/*
Q. What is the output of the following program?
NOTE: 
ptr - stores address of the element behind array a.
*/
    printf("========= CASE 19 ==========\n");
    char a[5] = { 1, 2, 3, 4, 5 };
    char *ptr = (char*)(&a + 1);

    printf("%ld\n", sizeof(char));
    printf("%p\n", a);
    printf("%p\n", ptr);
    printf("%d %d\n", *(a + 1), *(ptr - 1));

#elif CASE_20
/*
Q. What is the output of the following program?
A: 9
*/
    printf("========= CASE 20 ==========\n");
    int a[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    foo(a);
    printf("%d\n", a[2][1]);

#elif CASE_21
TODO:
    int a = 2;
    if(a == (1,2))
        printf("Hello");
    if(a == 1,2)
        printf("World");

#elif CASE_22
/*
Q. What is the output of the following program?
A: segmantation fault
NOTE: 
string - is a pointer to string. It is located in read-only memory
Inside foo we try to modify read-only memory.
*/
    printf("========= CASE 22 ==========\n");
    char *string = "Hello";
    foo(string);
    printf("%s",string);

#elif CASE_23
/*
Q. What is the output of the following program?
A: compilation error
NOTE:
s - is an array of characters.
inside while we try to modify array base address.
it is not allowed, it is not lvalue.
*/
    printf("========= CASE 23 ==========\n");
    char s[] = "Opendays2012";
    int i = 0;
    while(*(s++))
        i++;
    printf("%d",i);

#elif CASE_24
#elif CASE_25
#elif CASE_26
#elif CASE_27
#elif CASE_28
#elif CASE_29
#elif CASE_30
#elif CASE_31
#elif CASE_32
#elif CASE_33
#elif CASE_34
#elif CASE_35
#elif CASE_36
#elif CASE_37
#elif CASE_38
#elif CASE_39
#elif CASE_40
#elif CASE_41
#elif CASE_42
#elif CASE_43
#elif CASE_44
#elif CASE_45
#elif CASE_46
#elif CASE_47
#elif CASE_48
#elif CASE_49
#elif CASE_50

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

/**/
#if CASE_7
void foo(int p[3][4])
{

}
#endif

/**/
#if CASE_20
/*
NOTE: 
b - stores address of 1-D array.
++b - increments address and stores address to the next 1-D array
b[1][1] - equivalent to *(*(b + 1) + 1) increment the address and 
points to the next 1-D array.
*/
void foo(int b[][3])
{
    ++b;
    b[1][1] = 9;
}
#endif

/**/
#if CASE_22
void foo(char *a)
{
    while(*a)
    {
        *a += 1;
        a++;
    }
}
#endif

/**/
#if CASE_24
int* fun(void)
{
    int *a = (int*)malloc(sizeof(int));
    *a = 10;
    return a;
}

int foo(int a, int b)
{
    int c = a - b;
    printf("%d\n", c);
    c = c&(0x80000000);
    printf("%d\n", c);
    printf("%d\n", !c);
    printf("%d\n", !!c);
    return (!c)*a +(!!c)*b;
}

int func123(int a, int b)
{
    unsigned int i;
    unsigned j = 0;
    for (i = 0; i < 32; i++)
    {
        j <<= 1;
        j += !!(a & 0x80000000);
        a <<= 1;
        if (j >= b)
        {
            j -= b;
            a++;
        }
    }
    return a;
}

#endif


