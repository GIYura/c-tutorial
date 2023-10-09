#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

/* Структура для хранения всех переменных, относящихся
к разделяемому состоянию */
typedef struct
{
    /* Флаг, показывающий, был выведен символ 'A' или нет */
    bool done;
    /* Объект мьютекса для защиты критического участка */
    pthread_mutex_t mutex;
    /* Условная переменная для синхронизации двух потоков */
    pthread_cond_t condVar;
} shared_state_t;

/* Инициализирует члены объекта shared_state_t */
void SharedStateInit(shared_state_t* shared_state)
{
    shared_state->done = false;
    pthread_mutex_init(&shared_state->mutex, NULL);
    pthread_cond_init(&shared_state->condVar, NULL);
}

/* Уничтожает члены объекта shared_state_t */
void SharedStateDestroy(shared_state_t* shared_state)
{
    pthread_mutex_destroy(&shared_state->mutex);
    pthread_cond_destroy(&shared_state->condVar);
}

void* ThreadBody_1(void* context)
{
    shared_state_t* ss = (shared_state_t*)context;
    pthread_mutex_lock(&ss->mutex);

    printf("Thread 1 output: A\n");
    ss->done = true;
    
    /* Шлем сигнал потокам, ожидающим условной переменной */
    pthread_cond_signal(&ss->condVar);

    pthread_mutex_unlock(&ss->mutex);

    return NULL;
}

void* ThreadBody_2(void* context)
{
    shared_state_t* ss = (shared_state_t*)context;
    pthread_mutex_lock(&ss->mutex);

    /* Ждем, пока флаг не станет равным TRUE */
    while (!ss->done) 
    {
        /* Ждем условную переменную */
        pthread_cond_wait(&ss->condVar, &ss->mutex);
    }
    printf("Thread 2 output: B\n");

    pthread_mutex_unlock(&ss->mutex);

    return NULL;
}

int main(int argc, char* argv[])
{
    /* Разделяемое состояние */
    shared_state_t m_sharedState;

    /* Инициализируем разделяемое состояние */
    SharedStateInit(&m_sharedState);

/* Обработчики потоков */
    pthread_t m_thread1;
    pthread_t m_thread2;

    /* Создаем новые потоки */
    int result1 = pthread_create(&m_thread1, NULL, ThreadBody_1, &m_sharedState);
    int result2 = pthread_create(&m_thread2, NULL, ThreadBody_2, &m_sharedState);

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

    /* Уничтожаем разделяемое состояние, освобождаем мьютекс
    и объекты условных переменных */
    SharedStateDestroy(&m_sharedState);
    
    return 0;
}

