#include <stdio.h>

#include "calc.h"

int main(int argc, char* argv[])
{
    int a = 10;
    int b = 3;

    printf("a = %d; b = %d\n", a, b);
    printf("Sum = %d\n", add(a, b));
    printf("Sub = %d\n", sub(a, b));
    printf("Mul = %d\n", mul(a, b));
    printf("Div = %d\n", div(a, b));

    return 0;
}


