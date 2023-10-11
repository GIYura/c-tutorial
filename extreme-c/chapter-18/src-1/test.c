#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <pthread.h>

#define SHARED_MEMORY_SIZE 4

/* Разделяемый файловый дескриптор, с помощью которого
мы ссылаемся на объект в разделяемой памяти */
static int m_sharedFd = -1;

/* Разделяемый файловый дескриптор для обращения
к объекту в разделяемой памяти мьютекса */
static int m_mutexShmFd = -1;

/* Указатель на разделяемый счетчик */
static int32_t* m_counter = NULL;

/* Указатель на разделяемый мьютекс */
static pthread_mutex_t* m_mutex = NULL;

/* Функции синхронизации */
void SyncInit(void) 
{
    /* Открываем разделяемую память мьютекса */
    m_mutexShmFd = shm_open("/mutex0", O_CREAT | O_RDWR, 0600);
    if (m_mutexShmFd < 0)
    {
        fprintf(stderr, "ERROR: Failed to create shared memory: %s\n", strerror(errno));
        exit(1);
    }

    /* Выделяем и усекаем разделяемую область памяти мьютекса */
    if (ftruncate(m_mutexShmFd, sizeof(pthread_mutex_t)) < 0)
    {
        fprintf(stderr, "ERROR: Truncation of mutex failed: %s\n", strerror(errno));
        exit(1);
    }

    /* Отображаем разделяемую память мьютекса */
    void* map = mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, m_mutexShmFd, 0);
    if (map == MAP_FAILED)
    {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        exit(1);
    }
    m_mutex = (pthread_mutex_t*)map;

    /* Инициализируем объект мьютекса */
    int ret = -1;
    pthread_mutexattr_t attr;

    if ((ret = pthread_mutexattr_init(&attr)))
    {
        fprintf(stderr, "ERROR: Failed to init mutex attrs: %s\n", strerror(ret));
        exit(1);
    }

    if ((ret = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED)))
    {
        fprintf(stderr, "ERROR: Failed to set the mutex attr: %s\n", strerror(ret));
        exit(1);
    }

    if ((ret = pthread_mutex_init(m_mutex, &attr)))
    {
        fprintf(stderr, "ERROR: Initializing the mutex failed: %s\n", strerror(ret));
        exit(1);
    }

    if ((ret = pthread_mutexattr_destroy(&attr)))
    {
        fprintf(stderr, "ERROR: Failed to destroy mutex attrs : %s\n", strerror(ret));
        exit(1);
    }
}

void SyncDeinit(void)
{
    int ret = -1;
    if ((ret = pthread_mutex_destroy(m_mutex)))
    {
        fprintf(stderr, "ERROR: Failed to destroy mutex: %s\n", strerror(ret));
        exit(1);
    }

    if (munmap(m_mutex, sizeof(pthread_mutex_t)) < 0)
    {
        fprintf(stderr, "ERROR: Unmapping the mutex failed: %s\n", strerror(errno));
        exit(1);
    }

    if (close(m_mutexShmFd) < 0) 
    {
        fprintf(stderr, "ERROR: Closing the mutex failed: %s\n", strerror(errno));
        exit(1);
    }

    if (shm_unlink("/mutex0") < 0)
    {
        fprintf(stderr, "ERROR: Unlinking the mutex failed: %s\n", strerror(errno));
        exit(1);
    }
}

static void SharedResourceOpen(void)
{
    /* Открываем объект в разделяемой памяти */
    m_sharedFd = shm_open("/shm0", O_CREAT | O_RDWR, 0600);
    if (m_sharedFd < 0)
    {
        fprintf(stderr, "ERROR: Failed to create shared memory: %s\n", strerror(errno));
        exit(1);
    }
    fprintf(stdout, "Shared memory is created with fd: %d\n", m_sharedFd);
}

static void SharedResourceClose(void)
{
    if (shm_unlink("/shm0") < 0)
    {
        fprintf(stderr, "ERROR: Unlinking shared memory failed: %s\n", strerror(errno));
        exit(1);
    }
}

static void CounterIncrement(void)
{
    usleep(1);
    int ret = pthread_mutex_lock(m_mutex);
    if (ret < 0)
    {
        fprintf(stderr, "ERROR: mutex lock: %s\n", strerror(errno));
        exit(1);
    }

    int32_t temp = *m_counter;
    usleep(1);
    temp++;
    usleep(1);
    *m_counter = temp;

    ret = pthread_mutex_unlock(m_mutex);
    if (ret < 0)
    {
        fprintf(stderr, "ERROR: mutex unlock: %s\n", strerror(errno));
        exit(1);
    }

    usleep(1);
}

int main(int argc, char* argv[])
{
    /* Родительский процесс должен инициализировать разделяемый ресурс */
    SharedResourceOpen();
    
    SyncInit();

    /* Выделяем и усекаем разделяемую область памяти */
    if (ftruncate(m_sharedFd, SHARED_MEMORY_SIZE * sizeof(char)) < 0) 
    {
        fprintf(stderr, "ERROR: Truncation failed: %s\n", strerror(errno));
        exit(1);
    }

    fprintf(stdout, "The memory region is truncated.\n");

    /* Отражаем разделяемую память и инициализируем счетчик */
    void* map = mmap(0, SHARED_MEMORY_SIZE, PROT_WRITE, MAP_SHARED, m_sharedFd, 0);
    if (map == MAP_FAILED)
    {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        exit(2);
    }
    m_counter = (int32_t*)map;
    *m_counter = 0;

    /* Создаем новый процесс из текущего */
    pid_t pid = fork();

    if (pid)
    { 
        /* Родительский процесс */
        /* Инкрементируем счетчик */
        CounterIncrement();
        fprintf(stdout, "The parent process sees the m_counter as %d.\n", *m_counter);
        /* Ждем завершения дочернего процесса */
        int status = -1;
        wait(&status);
        fprintf(stdout, "The child process finished with status %d.\n", status);
    }
    else
    {
        /* Инкрементируем счетчик */
        CounterIncrement();
        fprintf(stdout, "The child process sees the m_counter as %d.\n", *m_counter);
    }

    /* Оба процесса должны уничтожить отражение в области памяти и закрыть свои файловые дескрипторы */
    if (munmap(m_counter, SHARED_MEMORY_SIZE) < 0)
    {
        fprintf(stderr, "ERROR: Unmapping failed: %s\n", strerror(errno));
        exit(1);
    }

    if (close(m_sharedFd) < 0)
    {
        fprintf(stderr, "ERROR: Closing shared memory fd filed: %s\n", strerror(errno));
        exit(1);
    }
    
    /* Только родительскому процессу нужно закрывать разделяемый ресурс */
    if (pid)
    {
        SharedResourceClose();
        SyncDeinit();
    }

    return 0;
}
