#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <stdbool.h>

#define MUTEX_SHM_NAME "/m_mutex0"
#define SHM_NAME "/shm0"

/* Разделяемый файловый дескриптор для обращения к объекту разделяемой
памяти, содержащему флаг отмены */
static int m_cancelFlagShmFd = -1;

/* Флаг, определяющий, владеет ли текущий процесс
объектом разделяемой памяти */
static bool m_cancelFlagShmOwner = false;

/* Разделяемый файловый дескриптор для обращения к объекту разделяемой
памяти мьютекса */
static int m_mutexShmFd = -1;

/* Разделяемый мьютекс */
static pthread_mutex_t* m_mutex = NULL;

/* Флаг, определяющий, владеет ли текущий процесс
объектом разделяемой памяти */
static bool m_mutexOwner = false;

/* Указатель на флаг отмены, хранящийся в разделяемой памяти */
static bool* m_cancelFlag = NULL;

static void SharedResourceOpen(void)
{
    /* Открываем объект разделяемой памяти */
    m_cancelFlagShmFd = shm_open(SHM_NAME, O_RDWR, 0600);

    if (m_cancelFlagShmFd >= 0)
    {
        m_cancelFlagShmOwner = false;
        fprintf(stdout, "The shared memory object is opened.\n");
    }
    else if (errno == ENOENT)
    {
        fprintf(stderr, "WARN: The shared memory object doesn't exist.\n");
        fprintf(stdout, "Creating the shared memory object ...\n");
        m_cancelFlagShmFd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0600);

        if (m_cancelFlagShmFd >= 0)
        {
            m_cancelFlagShmOwner = true;
            fprintf(stdout, "The shared memory object is created.\n");
        }
        else
        {
            fprintf(stderr, "ERROR: Failed to create shared memory: %s\n", strerror(errno));
            exit(1);
        }
    } 
    else
    {
        fprintf(stderr, "ERROR: Failed to create shared memory: %s\n", strerror(errno));
        exit(1);
    }

    if (m_cancelFlagShmOwner) 
    {
        /* Выделяем и усекаем разделяемую область памяти */
        if (ftruncate(m_cancelFlagShmFd, sizeof(bool)) < 0)
        {
            fprintf(stderr, "ERROR: Truncation failed: %s\n", strerror(errno));
            exit(1);
        }
        fprintf(stdout, "The memory region is truncated.\n");
    }
    /* Отображаем разделяемую память и инициализируем флаг отмены */
    void* map = mmap(0, sizeof(bool), PROT_WRITE, MAP_SHARED, m_cancelFlagShmFd, 0);
    if (map == MAP_FAILED)
    {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        exit(1);
    }
    m_cancelFlag = (bool*)map;
    if (m_cancelFlagShmOwner)
    {
        *m_cancelFlag = false;
    }
}

static void SharedResourceClose(void) 
{
    if (munmap(m_cancelFlag, sizeof(bool)) < 0)
    {
        fprintf(stderr, "ERROR: Unmapping failed: %s\n", strerror(errno));
        exit(1);
    }

    if (close(m_cancelFlagShmFd) < 0)
    {
        fprintf(stderr, "ERROR: Closing the shared memory fd filed: %s\n", strerror(errno));
        exit(1);
    }
    
    if (m_cancelFlagShmOwner)
    {
        sleep(1);
        if (shm_unlink(SHM_NAME) < 0)
        {
            fprintf(stderr, "ERROR: Unlinking the shared memory failed: %s\n", strerror(errno));
            exit(1);
        }
    }
}

static void SyncInit(void) 
{
    /* Открываем разделяемую память мьютекса */
    m_mutexShmFd = shm_open(MUTEX_SHM_NAME, O_RDWR, 0600);
    if (m_mutexShmFd >= 0) 
    {
        /* Разделяемый объект мьютекса существует, и я теперь его владелец */
        m_mutexOwner = false;
        fprintf(stdout, "The m_mutex's shared memory object is opened.\n");
    } 
    else if(errno == ENOENT) 
    {
        fprintf(stderr, "WARN: Mutex's shared memory doesn't exist.\n");
        fprintf(stdout, "Creating the m_mutex's shared memory object ...\n");
        m_mutexShmFd = shm_open(MUTEX_SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
        if (m_mutexShmFd >= 0) 
        {
            m_mutexOwner = true;
            fprintf(stdout, "The m_mutex's shared memory object is created.\n");
        } 
        else 
        {
            fprintf(stderr, "ERROR: Failed to create m_mutex's shared memory: %s\n", strerror(errno));
            exit(1);
        }
    } 
    else 
    {
        fprintf(stderr, "ERROR: Failed to create m_mutex's shared memory: %s\n", strerror(errno));
        exit(1);
    }

    if (m_mutexOwner)
    {
        /* Выделяем и усекаем область разделяемой памяти мьютекса */
        if (ftruncate(m_mutexShmFd, sizeof(pthread_mutex_t)) < 0)
        {
            fprintf(stderr, "ERROR: Truncation of the m_mutex failed: %s\n", strerror(errno));
            exit(1);
        }
    }
    /* Отображаем разделяемую память мьютекса */
    void* map = mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE, MAP_SHARED, m_mutexShmFd, 0);
  
    if (map == MAP_FAILED)
    {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        exit(1);
    }
    m_mutex = (pthread_mutex_t*)map;
    if (m_mutexOwner)
    {
        int ret = -1;
        pthread_mutexattr_t attr;
        if ((ret = pthread_mutexattr_init(&attr)))
        {
            fprintf(stderr, "ERROR: Initializing m_mutex attributes failed: %s\n", strerror(ret));
            exit(1);
        }

        if ((ret = pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED)))
        {
            fprintf(stderr, "ERROR: Setting the m_mutex attribute failed: %s\n", strerror(ret));
            exit(1);
        }

        if ((ret = pthread_mutex_init(m_mutex, &attr)))
        {
            fprintf(stderr, "ERROR: Initializing the m_mutex failed: %s\n", strerror(ret));
            exit(1);
        }

        if ((ret = pthread_mutexattr_destroy(&attr))) 
        {
            fprintf(stderr, "ERROR: Destruction of m_mutex attributes failed: %s\n", strerror(ret));
            exit(1);
        }
    }
}

void SyncDeinit(void) 
{
    sleep(1);
    if (m_mutexOwner)
    {
        int ret = -1;
        if ((ret = pthread_mutex_destroy(m_mutex))) 
        {
            fprintf(stderr, "WARN: Destruction of the m_mutex failed: %s\n", strerror(ret));
        }
    }

    if (munmap(m_mutex, sizeof(pthread_mutex_t)) < 0)
    {
        fprintf(stderr, "ERROR: Unmapping the m_mutex failed: %s\n", strerror(errno));
        exit(1);
    }

    if (close(m_mutexShmFd) < 0)
    {
        fprintf(stderr, "ERROR: Closing the m_mutex failed: %s\n", strerror(errno));
        exit(1);
    }

    if (m_mutexOwner)
    {
        if (shm_unlink(MUTEX_SHM_NAME) < 0)
        {
            fprintf(stderr, "ERROR: Unlinking the m_mutex failed: %s\n", strerror(errno));
            exit(1);
        }
    }
}

static bool IsCanceled(void)
{
    pthread_mutex_lock(m_mutex);
    bool temp = *m_cancelFlag;
    pthread_mutex_unlock(m_mutex);
    return temp;
}

static void Cancel(void)
{
    pthread_mutex_lock(m_mutex);
    *m_cancelFlag = true;
    pthread_mutex_unlock(m_mutex);
}

static void SignalHandler(int signo)
{
    fprintf(stdout, "\nHandling INT signal: %d ...\n", signo);
    Cancel();
}

int main(int argc, char* argv[]) 
{
    signal(SIGINT, SignalHandler);

    /* Родительский процесс должен инициализировать разделяемый ресурс */
    SharedResourceOpen();

    /* Родительский процесс должен инициализировать механизм управления */
    SyncInit();

    while(!IsCanceled())
    {
        fprintf(stdout, "Working ...\n");
        sleep(1);
    }

    fprintf(stdout, "Cancel signal is received.\n");

    SharedResourceClose();
    SyncDeinit();

    return 0;
}

