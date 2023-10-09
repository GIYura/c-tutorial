#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Объект барьера */
static pthread_barrier_t m_barrier;

void* ThreadBody_1(void* context)
{
    printf("Thread 1 output: A\n");
    /* Ждем присоединения другого потока */
    pthread_barrier_wait(&m_barrier);
    return NULL;
}

void* ThreadBody_2(void* context)
{
    /* Ждем присоединения другого потока */
    pthread_barrier_wait(&m_barrier);
    printf("Thread 2 output: B\n");
    return NULL;
}

int main(int argc, char* argv[]) 
{
    /* Инициализируем объект барьера */
    pthread_barrier_init(&m_barrier, NULL, 2);

    /* Обработчики потоков */
    pthread_t m_thread1;
    pthread_t m_thread2;

    /* Создаем новые потоки */
    int result1 = pthread_create(&m_thread1, NULL, ThreadBody_1, NULL);
    int result2 = pthread_create(&m_thread2, NULL, ThreadBody_2, NULL);

    if (result1 || result2)
    {
        printf("Can't creat threads\n");
        exit(1);
    }

    /* Ждем, пока потоки не завершат работу */
    result1 = pthread_join(m_thread1, NULL);
    result2 = pthread_join(m_thread2, NULL);
    
    if (result1 || result2)
    {
        printf("Can't join threads\n");
        exit(2);
    }

    /* Уничтожаем объект барьера */
    pthread_barrier_destroy(&m_barrier);

    return 0;
}

