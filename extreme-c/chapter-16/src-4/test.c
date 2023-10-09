#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

static pthread_barrier_t waterBarrier;
static pthread_mutex_t oxygenMutex;
static sem_t hydrogenSem;
static unsigned int moleculNumber = 0;

/* поток водорода */
static void* HydrogenThread(void* context)
{
    /* На этот критический участок может зайти два потока водорода */
    sem_wait(&hydrogenSem);
    
    /* Когда количество потоков, ожидающих перед объектом барьера, достигает двух, это
    означает, что у нас имеется один атом кислорода и два атома водорода; */

    /* Ждем присоединения другого потока водорода */
    pthread_barrier_wait(&waterBarrier);
    
    sem_post(&hydrogenSem);

    return NULL;
}

/* поток кислорода */
static void* OxygenThread(void* context)
{
    /* Поток кислорода ждет пока к нему не присоединится 2 потока водорода.
    Как только 2 потока водорода присоединились к одному потоку кислорода, 
    это означает что молекула создана. */
    pthread_mutex_lock(&oxygenMutex);

    pthread_barrier_wait(&waterBarrier);
    moleculNumber++;

    pthread_mutex_unlock(&oxygenMutex);

    return NULL;
}

int main(int argc, char* argv[])
{
    /* Инициализируем мьютекс кислорода */
    pthread_mutex_init(&oxygenMutex, NULL);
    
    /* Инициализируем семафор водорода */
    sem_init(&hydrogenSem, 0, 2);

    /* Инициализируем барьер воды */
    pthread_barrier_init(&waterBarrier, 0, 3);

    pthread_t thread[150];
    /* Создаем потоки кислорода */
    for (int i = 0; i < 50; i++)
    {
        if (pthread_create(thread + i, NULL, OxygenThread, NULL))
        {
            printf("Couldn't create an oxygen thread.\n");
            exit(1);
        }
    }
    /* Создаем потоки водорода */
    for (int i = 50; i < 150; i++)
    {
        if (pthread_create(thread + i, NULL, HydrogenThread, NULL))
        {
            printf("Couldn't create an hydrogen thread.\n");
            exit(2);
        }
    }

    printf("Waiting for hydrogen and oxygen atoms to react ...\n");
    /* Ждем завершения всех потоков */
    for (int i = 0; i < 150; i++)
    {
        if (pthread_join(thread[i], NULL))
        {
            printf("The thread could not be joined.\n");
            exit(3);
        }
    }

    printf("Number of made water molecules: %d\n", moleculNumber);
    
    sem_destroy(&hydrogenSem);

    return 0;
}

