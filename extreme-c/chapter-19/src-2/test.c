#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <mqueue.h>

int main(int argc, char* argv[])
{
    /* Обработчик очереди сообщений */
//    mqd_t m_queue;

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 32;
    attr.mq_curmsgs = 0;

    int childpid = fork();

    if (childpid == -1)
    {
        fprintf(stderr, "fork error!\n");
        exit(1);
    }

    if (childpid == 0)
    {
        /* Потомок ждет, пока родитель создает очередь */
        sleep(1);
        mqd_t m_queue = mq_open("/mq0", O_WRONLY);

        char message[] = "Hello Parent!";

        /* Потомок записывает в файловый дескриптор, открытый для записи */
        fprintf(stdout, "CHILD: Waiting for 2 seconds ...\n");

        sleep(2);

        fprintf(stdout, "CHILD: Writing to daddy ...\n");
        mq_send(m_queue, message, strlen(message) + 1, 0);

        mq_close(m_queue);
    } 
    else 
    {
        mqd_t m_queue = mq_open("/mq0", O_RDONLY | O_CREAT, 0644, &attr);
        char buffer[32];

        fprintf(stdout, "PARENT: Reading from child ...\n");
        int numberOfBytes = mq_receive(m_queue, buffer, 32, NULL);
        fprintf(stdout, "PARENT: Received from child: %d bytes\n", numberOfBytes);
        fprintf(stdout, "PARENT: Received from child: %s\n", buffer);

        mq_close(m_queue);

        mq_unlink("/mq0");
    }

    return 0;
}

