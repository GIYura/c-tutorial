#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void UserSignalHandler(int signal)
{
    switch (signal)
    {
        case SIGUSR1:
            printf("SIGUSR1 received!\n");
        break;

        case SIGUSR2:
            printf("SIGUSR2 received!\n");
        break;

        default:
            printf("Unsupported signal is received!\n");
        break;
    }
}

void SigIntHandler(int signal)
{
    printf("Interrupt signal is received!\n");
}

void SigKillHandler(int signal)
{
    printf("Kill signal is received! Bye.\n");
    exit(0);
}

int main(int argc, char* argv[])
{
    signal(SIGUSR1, UserSignalHandler);
    signal(SIGUSR2, UserSignalHandler);
    signal(SIGINT, SigIntHandler);
    signal(SIGKILL, SigKillHandler);
    while (1);
    return 0;
}

