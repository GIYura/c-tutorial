#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
Сразу после создания новый поток отсоединяется от главного. Вслед за этим
главный поток завершает работу. Инструкция pthread_exit(NULL) нужна для того,
чтобы процесс дождался завершения другого, отсоединенного потока. Без разъединение, 
процесс завершился бы вместе с главным потоком.
*/

static void* ThreadBody(void* context)
{
    printf("Hello from thread!!!\n");
    return NULL;
}

int main (int argc, char* argv[])
{
    pthread_t m_thread;

    int res = pthread_create(&m_thread, NULL, ThreadBody, NULL);
    if (res)
    {
        printf("Can't create thread. Error: %d\n", res);
        exit(1);
    }

    res = pthread_detach(m_thread);
    if (res)
    {
        printf("Can't join thread. Error: %d\n", res);
        exit(2);
    }

    /* выход из главного потока */
    pthread_exit(NULL);

    return 0;
}

