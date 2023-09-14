#include <stdio.h>

#define C89 0
#define C99 1

void PrintMsg(const char* const message);


int main(int argc, char* argv[])
{

/*
The following code can't be compiled in C89
*/
#if C89
    // This type of comments should not be used. Instead use /* */

    /* It is not allowed to declare a variable inside for loop.
    It should be declared before.
     */
    for (int i = 0; i < 5; i++)
    {
        PrintMsg("Hello World");
    }
#endif

/*

*/
    if (__STDC_VERSION__ >= 201710L)
    {
        printf("C18\n");
    }
    else if (__STDC_VERSION__ >= 201112L)
    {
        printf("C11\n");
    }
    else if (__STDC_VERSION__ >= 199901L)
    {   
        printf("C99\n");
    }
    else
    {
        printf("C89\n");
    }

    return 0;
}

void PrintMsg(const char* const message)
{
    printf("%s\n", message);
}
