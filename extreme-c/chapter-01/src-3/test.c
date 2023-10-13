#include <stdio.h>

/*
NOTE:
sizeof sample_t gives us 6 bytes, however it looks like 
it should be 5 bytes. 
This is called padding.
*/
#if 0
typedef struct
{
    unsigned char one;      /* 1 */
    unsigned char two;      /* 1 */
    unsigned char three;    /* 1 */
    /* unsigned char pad;   1 padding; insert by the compiler */
    unsigned short four;    /* 2 */
} sample_t;
#else
typedef struct __attribute__((__packed__))
{
    unsigned char one;      /* 1 */
    unsigned char two;      /* 1 */
    unsigned char three;    /* 1 */
    unsigned short four;    /* 2 */
} sample_t;
#endif

void PrintStructSize(const sample_t* const s);
void PrintArrSize(const int* const arr);
void PrintIntSize(const int* const value);
void PrintBytesInHex(const sample_t* const s);

int main(int argc, char* argv[])
{
    sample_t sample;

    sample.one = 0x01;
    sample.two = 0x02;
    sample.three = 0x03;
    sample.four = 0xaabb;

    PrintBytesInHex(&sample);
    PrintStructSize(&sample);

    int buff[] = { 1, 2, 3 };
    PrintArrSize(buff);

    int value = 10;
    PrintIntSize(&value);

    return 0;
}

void PrintStructSize(const sample_t* const s)
{
    printf("Struct Size: %ld in bytes\n", sizeof(*s));
}

void PrintArrSize(const int* const arr)
{
/*
NOTE:
It is not possible to get buffer size on its pointer.
sizeof(arr) - will give size of pointer (depends on architecture)
sizeof(*arr) - will give size of first element of the array
*/
    printf("Arr Size: %ld in bytes\n", sizeof(arr));
}

void PrintIntSize(const int* const value)
{
    printf("Int Size: %ld in bytes\n", sizeof(*value));
}

void PrintBytesInHex(const sample_t* const s)
{
    unsigned char* p = (unsigned char*)s;
    
    for (int i = 0; i < sizeof(*s); i++)
    {
        printf("%#x ", *p);
        p++;
    }
    printf("\n");
}

