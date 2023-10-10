/*
Пример демонстрации использования heap в качастве стека процесса.
В примере есть два потока. В одном из них используется параметры стека по умолчанию, 
а в другом выделяется буфер в сегменте heap и назначается в качестве стека. 
ВАЖНО: для выделяемого буфера следует указывать минимальный размер, иначе его нельзя будет использовать
в качестве стека.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

void* ThreadBody_1(void* context)
{
    /* адрес локальной переменной находится в диапазоне сегмента стека, принадлежащего процессу */
    int value = 0;
    printf("Thread 1. Stack address: %p\n", (void*)&value);
    return NULL;
}

void* ThreadBody_2(void* context)
{
    /* адрес локальной переменной находится в диапазоне кучи */
    int value = 0;
    printf("Thread 2. Stack address: %p\n", (void*)&value);
    return NULL;
}

int main(int argc, char* argv[])
{
    size_t bufferSize = PTHREAD_STACK_MIN + 100;
    
    /* Буфер, выделенный из кучи и используемый как
    стек потока */
    char* buffer = (char*)malloc(bufferSize * sizeof(char));
    if (NULL == buffer)
    {
        printf("Can't allocate memory\n");
        exit(1);
    }

    /* Обработчики потоков */
    pthread_t m_thread1;
    pthread_t m_thread2;

    /* Создаем новый поток с атрибутами по умолчанию */
    int result1 = pthread_create(&m_thread1, NULL, ThreadBody_1, NULL);

    /* Создаем новый поток с нашим собственным стеком */
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    /* Задаем адрес и размер стека */
    if (pthread_attr_setstack(&attr, buffer, bufferSize))
    {
        printf("Failed to set stack attributes\n");
        exit(2);
    }

    int result2 = pthread_create(&m_thread2, &attr, ThreadBody_2, NULL);
    if (result1 || result2)
    {
        printf("Can't create threads\n");
        exit(3);
    }

    printf("Main Thread. Heap Address:  %p\n", (void*)buffer);
    printf("Main Thread. Stack Address: %p\n", (void*)&bufferSize);

    /* Ждем, пока потоки не завершат работу */
    result1 = pthread_join(m_thread1, NULL);
    result2 = pthread_join(m_thread2, NULL);

    if (result1 || result2)
    {
        printf("Can't join threads\n");
        exit(4);
    }

    free(buffer);

    return 0;
}

