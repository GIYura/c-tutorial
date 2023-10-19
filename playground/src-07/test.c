/*
NOTE:
https://www.geeksforgeeks.org/multiline-macros-in-c/
*/
#include <stdio.h>

#define LIST    10,\
                20,\
                30,\
                40

#define PRINT(MSG)  do{\
                        printf(MSG "Multi\n");\
                        printf(MSG "Line\n");\
                        printf(MSG "Macro\n");\
                    } while(0)


static void BufferPrint(const int* const buffer, int size);

int main(int argc, char* argv[])
{
    int buffer[] = { LIST };
    
    BufferPrint(buffer, sizeof(buffer) / sizeof(buffer[0]));

    PRINT("hello");
    printf("-------\n");
    PRINT("hello");
    printf("-------\n");
    PRINT("hello");
    printf("-------\n");

    int i = 3;
    while (i--)
        PRINT("bye-");

    if (1)
        PRINT("nnnn");
    else
        PRINT("aaaa");

    return 0;
}

static void BufferPrint(const int* const buffer, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("buffer[%d]: %d\n", i, buffer[i]);
    }
}

