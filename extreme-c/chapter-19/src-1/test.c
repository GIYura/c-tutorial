/*
Прежде чем записывать в канал, дочерний процесс ждет 2 секунды.
А родительский процесс тем временем заблокирован на функции read. 
Поэтому, когда в канал ничего не записывается, читающий процесс блокируется.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    int fds[2];
    pipe(fds);

    int childPID = fork();

    if (childPID == -1)
    {
        fprintf(stderr, "fork error!\n");
        exit(1);
    }

    if (childPID == 0)
    {
        /* Потомок закрывает файловый дескриптор для чтения */
        close(fds[0]);

        char message[] = "Hello World!";

        /* Потомок записывает в файловый дескриптор, открытый для записи */
        fprintf(stdout, "CHILD: Waiting for 2 seconds ...\n");
        sleep(2);
        fprintf(stdout, "CHILD: Writing to parent...\n");
        write(fds[1], message, strlen(message) + 1);
    }
    else
    {
        /* Родитель закрывает файловый дескриптор для записи */
        close(fds[1]);

        char buffer[32];

        /* Родитель читает из файлового дескриптора, открытого для чтения */
        fprintf(stdout, "PARENT: Reading from child ...\n");
        int numberBytes = read(fds[0], buffer, 32);
        fprintf(stdout, "PARENT: Received from child: %d bytes\n", numberBytes);
        fprintf(stdout, "PARENT: Received from child: %s\n", buffer);
    }

    return 0;
}

