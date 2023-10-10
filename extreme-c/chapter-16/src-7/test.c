#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static char* m_sharedBuffer = NULL;
static size_t m_sharedBufferSize = 20;

static pthread_barrier_t m_allocBarrier;
static pthread_barrier_t m_fillBarrier;
static pthread_barrier_t m_doneBarrier;

static void* AllocBufferThread(void* context)
{
    unsigned int bufferSize = *((unsigned int*)context);

    m_sharedBuffer = (char*)malloc(sizeof(char) * bufferSize);
    if (m_sharedBuffer == NULL)
    {
        printf("Can't allocate buffer\n");
        exit(2);
    }
    pthread_barrier_wait(&m_allocBarrier);
    return NULL;
}

static void* FreeBufferThread(void* context)
{
    pthread_barrier_wait(&m_doneBarrier);
    free(m_sharedBuffer);
    pthread_barrier_destroy(&m_allocBarrier);
    pthread_barrier_destroy(&m_fillBarrier);
    pthread_barrier_destroy(&m_doneBarrier);
    return NULL;
}

static void* PrintBufferThread(void* context)
{
    pthread_barrier_wait(&m_fillBarrier);
    printf(">>> ");
    for(size_t i = 0; i < m_sharedBufferSize; i++)
    {
        printf("%c ", m_sharedBuffer[i]);
    }
    
    printf("\n");
    pthread_barrier_wait(&m_doneBarrier);
    return NULL;
}

static void* FillBufferThread(void* context)
{
    pthread_barrier_wait(&m_allocBarrier);

    bool even = *((int*)context);

    char c = 'a';
    size_t startIndex = 1;
    if (even)
    {
        c = 'Z';
        startIndex = 0;
    }
    
    for (size_t i = startIndex; i < m_sharedBufferSize; i += 2)
    {
        m_sharedBuffer[i] = even ? c-- : c++;
    }
    m_sharedBuffer[m_sharedBufferSize - 1] = '\0';

    pthread_barrier_wait(&m_fillBarrier);
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t m_allocThread, m_evenThread, m_oddThread, m_printThread, m_deallocThread;
    int res1, res2, res3, res4, res5;

    pthread_barrier_init(&m_allocBarrier, NULL, 3);
    pthread_barrier_init(&m_fillBarrier, NULL, 3);
    pthread_barrier_init(&m_doneBarrier, NULL, 2);

    res1 = pthread_create(&m_allocThread, NULL, AllocBufferThread, &m_sharedBufferSize);
    res2 = pthread_create(&m_deallocThread, NULL, FreeBufferThread, NULL);
    bool isEven = true;
    res3 = pthread_create(&m_evenThread, NULL, FillBufferThread, &isEven);
    isEven = false;
    res4 = pthread_create(&m_oddThread, NULL, FillBufferThread, &isEven);
    res5 = pthread_create(&m_printThread, NULL, PrintBufferThread, NULL);

    if (res1 || res2 || res3 || res4 || res5)
    {
        printf("Can't create threads\n");
        exit(3);
    }

    res1 = pthread_join(m_allocThread, NULL);
    res2 = pthread_join(m_deallocThread, NULL);
    res3 = pthread_join(m_evenThread, NULL);
    res4 = pthread_join(m_oddThread, NULL);
    res5 = pthread_join(m_printThread, NULL);
    
    if (res1 || res2 || res3 || res4 || res5)
    {
        printf("Can't join thread\n");
        exit(4);
    }
    pthread_exit(NULL);

    return 0;
}
