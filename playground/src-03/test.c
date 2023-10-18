#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*NOTE:
NEVER DO THIS
*/
static char* RETURN_LOCAL_ADDRESS(void);

static char* ReturnStringLiteral(void);
static char* ReturnGlobalBuffer(void);
static char* ReturnStaticBuffer(void);
static char* ReturnDynamicallyAllocatedBuffer(void);
static void UseDynamicallyAllocatedBuffer(char* buffer, int size);

char message[] = "Hello WORLD";

int main(int argc, char* argv[])
{
    char* str;
    str = ReturnStringLiteral();
    printf("%s\n", str);

    ReturnGlobalBuffer();
    printf("%s\n", message);

    char* s;
    s = ReturnStaticBuffer();
    printf("%s\n", s);

    char* ptr;
    ptr = ReturnDynamicallyAllocatedBuffer();
    printf("%s\n", ptr);

/*
NOTE: this is the best solution
Caller is responsible for allocation and freeing memory.
*/
    char* pBuffer = (char*)malloc(20 * sizeof(char));
    if (!pBuffer)
        return -1;

    UseDynamicallyAllocatedBuffer(pBuffer, 20);
    printf("%s\n", pBuffer);

    free(pBuffer);

    return 0;
}

static char* ReturnStringLiteral(void)
{
/* NOTE: works for string ONLY */
    return "Hello World";
}

static char* ReturnGlobalBuffer(void)
{
    message[0] = 'A';
    return message;
}
 
static char* ReturnStaticBuffer(void)
{
    static char buffer[10];
    
    buffer[0] = 'A';
    buffer[1] = 'B';
    buffer[2] = 'C';
    buffer[3] = 'D';
    buffer[4] = 'E';

    return buffer;
}

static char* ReturnDynamicallyAllocatedBuffer(void)
{
    char* buffer = (char*)malloc(10 * sizeof(char));
    
    buffer[0] = 'F';
    buffer[1] = 'F';
    buffer[2] = 'F';
    buffer[3] = '\0';

    return buffer;
}

static void UseDynamicallyAllocatedBuffer(char* buffer, int size)
{
/* best solution */
    strncpy(buffer, "This is a string", size);
}

static char* RETURN_LOCAL_ADDRESS(void)
{
    char buffer[5] = {1,2,3,4,5};
    return buffer;
}

