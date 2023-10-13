#include <stdio.h>

#define MAX(a, b)   ((a) > (b) ? (a) : (b))

int main (int argc, char* argv[])
{
    int a = 10;
    int b = 5;

    int c = MAX(a, b);
    
    printf("MAX value %d among %d and %d\n", c, a, b);

    return 0;
}
