#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Семафоры недоступны в заголовке pthread.h */
#include <semaphore.h>

/* Объект семафора, применяемый
для синхронизации доступа к разделяемому состоянию. */
static sem_t m_semaphore;

void* ThreadBody_1(void* context)
{
    /* Получаем указатель на разделяемую переменную */
    int* sharedVar = (int*)context;

    /* Ждем семафор */
    /*
    sem_wait() позволяет заходить на критический участок нескольким потокам,
    в отличии от pthread_mutex_lock()
    */
    sem_wait(&m_semaphore);

    /* Инкрементируем разделяемую переменную на 1,
    выполняя запись непосредственно по ее адресу в памяти */

    (*sharedVar)++;
    printf("Thread 1 output: %d\n", *sharedVar);

    /* Освобождаем семафор */
    sem_post(&m_semaphore);

    return NULL;
}

void* ThreadBody_2(void* context)
{
    /* Получаем указатель на разделяемую переменную */
    int* sharedVar = (int*)context;

    /* Ждем семафор */
    sem_wait(&m_semaphore);

    /* Инкрементируем разделяемую переменную на 1,
    выполняя запись непосредственно по ее адресу в памяти */

    (*sharedVar) += 2;
    printf("Thread 2 output: %d\n", *sharedVar);

    /* Освобождаем семафор */
    sem_post(&m_semaphore);

    return NULL;
}

int main(int argc, char* argv[])
{
    /* Разделяемая переменная */
    int sharedVar = 0;

    /* Обработчики потоков */
    pthread_t m_thread1;
    pthread_t m_thread2;

    /* Инициализируем семафор как мьютекс (двоичный семафор).
    В данном случае, семафор подобен мьютексу, т.к. количество потоков, которые могут заходить
    на критическую секцию = 1 */
    sem_init(&m_semaphore, 0, 1);

    /* Создаем новые потоки */
    int result1 = pthread_create(&m_thread1, NULL, ThreadBody_1, &sharedVar);
    int result2 = pthread_create(&m_thread2, NULL, ThreadBody_2, &sharedVar);
    if (result1 || result2)
    {
        printf("Can't creat threads\n");
        exit(1);
}

    /* Ждем, пока потоки не завершат работу*/
    result1 = pthread_join(m_thread1, NULL);
    result2 = pthread_join(m_thread2, NULL);
    if (result1 || result2)
    {
        printf("Can't join threads\n");
        exit(2);
    }

    sem_destroy(&m_semaphore);

    return 0;
}

