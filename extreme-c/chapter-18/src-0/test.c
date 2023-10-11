#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

#define SHARED_MEMORY_SIZE 4

/* Разделяемый файловый дескриптор, с помощью которого
мы ссылаемся на объект в разделяемой памяти */
static int m_sharedFd = -1;

/* Указатель на разделяемый счетчик */
static int32_t* m_counter = NULL;

/* Указатель на разделяемый семафор */
static sem_t* m_semaphore = NULL;

/* Функции синхронизации */
void SyncInit(void) 
{
    m_semaphore = sem_open("/sem0", O_CREAT | O_EXCL, 0600, 1);
    if (m_semaphore == SEM_FAILED)
    {
        fprintf(stderr, "ERROR: Opening the semaphore failed: %s\n", strerror(errno));
    exit(1);
    }
}

void SyncDeinit(void)
{
    if (sem_close(m_semaphore) < 0)
    {
        fprintf(stderr, "ERROR: Closing the semaphore failed: %s\n", strerror(errno));
        exit(1);
    }
    if (sem_unlink("/sem0") < 0)
    {
        fprintf(stderr, "ERROR: Unlinking failed: %s\n", strerror(errno));
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
    int ret = sem_wait(m_semaphore);
    if (ret < 0)
    {
        fprintf(stderr, "ERROR: semaphore wait: %s\n", strerror(errno));
        exit(1);
    }

    int32_t temp = *m_counter;
    usleep(1);
    temp++;
    usleep(1);
    *m_counter = temp;

    ret = sem_post(m_semaphore);
    if (ret < 0)
    {
        fprintf(stderr, "ERROR: semaphore post: %s\n", strerror(errno));
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
