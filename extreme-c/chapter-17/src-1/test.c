#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char* argv[])
{
    printf("Parent process ID: %d\n", getpid());

    pid_t ret = fork();

    if (ret)
    {
        for (int i = 0; i < 5; i++)
        {
            printf("AAA\n");
            usleep(5000);
        }
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            printf("BBBBBB\n");
            usleep(5000);
        }
    }

    return 0;
}

