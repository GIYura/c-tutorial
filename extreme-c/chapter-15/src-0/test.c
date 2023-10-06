#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
Поток становится завершенным только после возвращения функции-компаньона.
Порожденный поток завершается, когда функция-компаньон ThreadBody возвращает NULL. 
Затем главный поток, заблокированный вызовом pthread_join, освобождается и получает 
возможность продолжить работу, что в конечном счете приводит к успешному завершению программы.
*/

static void* ThreadBody(void* context)
{
    printf("Hello from thread\n");
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

    res = pthread_join(m_thread, NULL);
    if (res)
    {
        printf("Can't join thread. Error: %d\n", res);
        exit(2);
    }

    return 0;
}

