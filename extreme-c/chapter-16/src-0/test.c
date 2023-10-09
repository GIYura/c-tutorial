#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
NOTE:
Заходя на критический участок, поток блокирует мьютекс, и остальные потоки
должны остановиться перед выражением pthread_mutex_lock(&m_mutex) и подождать,
пока мьютекс не будет разблокирован снова.
Поток, ожидающий разблокирования мьютекса, по умолчанию входит в спящий режим.
*/

/* Объект мьютекса для синхронизации доступа
 к разделяемому состоянию */
static pthread_mutex_t m_mutex;

void* ThreadBody_1(void* context)
{
    /* Получаем указатель на разделяемую переменную */
    int* sharedVar = (int*)context;

    /* Критический участок */
    pthread_mutex_lock(&m_mutex);

    /* Инкрементируем разделяемую переменную на 1, выполняя запись
    непосредственно по ее адресу в памяти */
    (*sharedVar)++;
    printf("%d\n", *sharedVar);

    pthread_mutex_unlock(&m_mutex);

    return NULL;
}

void* ThreadBody_2(void* context)
{
    /* Получаем указатель на разделяемую переменную */
    int* sharedVar = (int*)context;
    
    /* Критический участок */
    pthread_mutex_lock(&m_mutex);

    /* Инкрементируем разделяемую переменную на 2, выполняя запись
    непосредственно по ее адресу в памяти */
    *sharedVar += 2;
    printf("%d\n", *sharedVar);

    pthread_mutex_unlock(&m_mutex);

    return NULL;
}

int main(int argc, char* argv[])
{
    /* Разделяемая переменная */
    int sharedVar = 0;

    /* Обработчики потоков */
    pthread_t m_thread1;
    pthread_t m_thread2;

    /* Инициализирует мьютекс и его внутренние ресурсы */
    int result1 = pthread_mutex_init(&m_mutex, NULL);
    if (result1)
    {
        printf("Can't init mutex\n");
        exit(1);
    }

    /* Создаем новые потоки */
    int result2 = pthread_create(&m_thread1, NULL, ThreadBody_1, &sharedVar);
    int result3 = pthread_create(&m_thread2, NULL, ThreadBody_2, &sharedVar);
    
    if (result2 || result3)
    {
        printf("The threads could not be created.\n");
        exit(2);
    }

    /* Ждем, пока потоки не завершат работу */
    result2 = pthread_join(m_thread1, NULL);
    result3 = pthread_join(m_thread2, NULL);

    if (result2 || result3)
    {
        printf("The threads could not be joined.\n");
        exit(3);
    }

    /* Освобождение ресурсов мьютекса */
    pthread_mutex_destroy(&m_mutex);

    return 0;
}

