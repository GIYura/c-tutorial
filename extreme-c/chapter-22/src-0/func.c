#include "func.h"

int32_t NextEvenNumber(void)
{
    static int feed = -2;
    feed += 2;
    if (feed >= 10) 
    {
        feed = 0;
    }
    return feed;
}

int32_t CalcFactorial(handler_t handler)
{
    int32_t fact = 1;
    int32_t number = handler();
    for (int32_t i = 1; i <= number; i++)
    {
        fact *= i;
    }
    return fact;
}

