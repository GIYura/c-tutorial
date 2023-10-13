#include <stdio.h>

#define CASE_1 0
#define CASE_2 1
#define CASE_3 0
#define CASE_4 0

#if CASE_1
void func(int* a);
#endif

#if CASE_2
int sum(int a, int b);
int subtract(int a, int b);
typedef int (*funcPtr)(int a, int b);
#endif

int main (int argc, char* argv[])
{
#if CASE_1
    int x = 5;
    int* px = &x;
    
    printf("x value before call: %d\n", x);
    printf("x address before call: %p\n", (void*)px);

    func(px);

    printf("x value before call: %d\n", x);
    printf("x address before call: %p\n", (void*)px);

#elif CASE_2
    funcPtr fp = &sum;
    int result = fp(1, 2);
    printf("Sum result: %d\n", result);

    fp = &subtract;
    result = fp(5, 2);
    printf("Subtract result: %d\n", result);

#elif CASE_3



#elif CASE_4


#endif


    return 0;
}

#if CASE_1
void func(int* a)
{
    int b = 10;
    *a = 3;
    a = &b;
    printf("b address inside 'func': %p\n", (void*)&b);
}
#endif

#if CASE_2
int sum(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}
#endif

