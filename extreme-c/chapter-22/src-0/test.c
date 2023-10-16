#include <stdio.h>

#include "func.h"

int main(int argc, char* argv[])
{
    for (size_t i = 1; i <= 12; i++)
    {
        printf("%lu\n", CalcFactorial(NextEvenNumber));
    }

    return 0;
}

