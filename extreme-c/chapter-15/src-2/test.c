#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* ThreadBody(void* context) 
{
    char* str = (char*)context;
    printf("%s\n", str);
    return NULL;
}

int main(int argc, char* argv[])
{
    /* Обработчики потоков */
    pthread_t m_thread1;
    pthread_t m_thread2;
    pthread_t m_thread3;

    int result1 = pthread_create(&m_thread1, NULL, ThreadBody, "Apple");
    int result2 = pthread_create(&m_thread2, NULL, ThreadBody, "Orange");
    int result3 = pthread_create(&m_thread3, NULL, ThreadBody, "Lemon");
    if (result1 || result2 || result3)
    {
        printf("The threads could not be created.\n");
        exit(1);
    }

    /* Ждем, пока потоки не завершат работу */
    result1 = pthread_join(m_thread1, NULL);
    result2 = pthread_join(m_thread2, NULL);
    result3 = pthread_join(m_thread3, NULL);

    if (result1 || result2 || result3)
    {
        printf("The threads could not be joined.\n");
        exit(2);
    }
    
    return 0;
}

