#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* ThreadBody_1(void* context)
{
    /* Получаем указатель на разделяемую переменную */
    int* shared_var_ptr = (int*)context;
    /* Инкрементируем разделяемую переменную на 1, выполняя запись
    непосредственно по ее адресу в памяти */
    (*shared_var_ptr)++;
    printf("%d\n", *shared_var_ptr);
    return NULL;
}

void* ThreadBody_2(void* context)
{
    /* Получаем указатель на разделяемую переменную */
    int* shared_var_ptr = (int*)context;
    /* Инкрементируем разделяемую переменную на 2, выполняя запись
    непосредственно по ее адресу в памяти */
    *shared_var_ptr += 2;
    printf("%d\n", *shared_var_ptr);
    return NULL;
}

int main(int argc, char* argv[])
{
    /* Разделяемая переменная */
    int sharedVar = 0;

    /* Обработчики потоков */
    pthread_t m_thread1;
    pthread_t m_thread2;

    /* Создаем новые потоки */
    int result1 = pthread_create(&m_thread1, NULL, ThreadBody_1, &sharedVar);
    int result2 = pthread_create(&m_thread2, NULL, ThreadBody_2, &sharedVar);
    
    if (result1 || result2)
    {
        printf("The threads could not be created.\n");
        exit(1);
    }

    /* Ждем, пока потоки не завершат работу */
    result1 = pthread_join(m_thread1, NULL);
    result2 = pthread_join(m_thread2, NULL);

    if (result1 || result2)
    {
        printf("The threads could not be joined.\n");
        exit(2);
    }

    return 0;
}

