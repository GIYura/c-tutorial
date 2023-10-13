#include <stdio.h>

#define CASE_1  0
#define CASE_2  0
#define CASE_3  0
#define CASE_4  1
#define CASE_5  0
#define CASE_6  0

static void PrintBytes(void* data, int size);

int main (int argc, char* argv[])
{
#if CASE_1
/*
NOTE: 

1. Precedence.
Postfix increment has a higher precedence than dereference / indirection.
Means, *p++ grouped *(p++).

Prefix increment and indirection has the same precedence. In this case 
'associativity' comes to play. In case of *++p it is right-to-left.

2. Post expression side effect.
By the time we reached 'printf', pointer looks on the next item in the buffer.

*p++ - dereferences the pointer, then increments the pointer: grouped *(p++);
*++p - increments the pointer, then dereferences the pointer: grouped *(++p);
++*p - dereferences the pointer, then increments dereferenced value: grouped ++(*p).
*/
    printf("======== CASE 1 ========\n");
    char message[] = "Hello";

    char* pMessage = message;

    while (*pMessage)
    {
        printf("%c ", *pMessage);
        pMessage++;
    }
    printf("\n");

#elif CASE_2
    printf("======== CASE 2 ========\n");
    char* p = "Hello";
    printf ("%c ", *p);     /* 'H' */
    printf ("%c ", *++p);   /* increment pointer, then dereference; 'e' */
    printf ("%c ", *p++);   /* direference pointer, then increment; 'e' */
    printf ("%c ", *p);     /* 'l' */
    printf("\n");

#elif CASE_3
/*
NOTE:
array name is not const pointer to a buffer, because pointer and array
have different size, moreover they are different type.
*/
    int buffer[] = { 1, 2, 3 };
    printf("sizeof buffer: %ld\n", sizeof(buffer));
    int* pBuffer = buffer;
    printf("sizeof pBuffer: %ld\n", sizeof(pBuffer));

#elif CASE_4
    int a = 0x12345678;
    double b = 3.14;

    PrintBytes(&a, sizeof(int));
    PrintBytes(&b, sizeof(double));

#endif

    return 0;
}

#if CASE_4
static void PrintBytes(void* data, int size)
{
    unsigned char* p = data;

    for (int i = 0; i < size; i++)
    {
        printf("%#x ", *p);
        p++;
    }
    printf("\n");
}
#endif



