#include <stdio.h>

#define MAX(a, b)   ((a) > (b) ? (a) : (b))

int main (int argc, char* argv[])
{
    int a = 10;
    int b = 5;

    int c = MAX(a, b);
    
    printf("%d\n", c);

    return 0;
}
