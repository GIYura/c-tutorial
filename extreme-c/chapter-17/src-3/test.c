#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

#define SHARED_MEMORY_SIZE 16

int main(int argc, char* argv[])
{
    int shm_fd = shm_open("/shm0", O_RDONLY, 0600);
    if (shm_fd < 0)
    {
        fprintf(stderr, "ERROR: Failed to open shared memory: %s\n", strerror(errno));
        exit(1);
    }

    fprintf(stdout, "Shared memory is opened with fd: %d\n", shm_fd);
    void* map = mmap(0, SHARED_MEMORY_SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (map == MAP_FAILED) 
    {
        fprintf(stderr, "ERROR: Mapping failed: %s\n", strerror(errno));
        exit(2);
    }
    char* ptr = (char*)map;
    fprintf(stdout, "The contents of shared memory object: %s\n", ptr);

    if (munmap(ptr, SHARED_MEMORY_SIZE) < 0)
    {
        fprintf(stderr, "ERROR: Unmapping failed: %s\n", strerror(errno));
        exit(3);
    }

    if (close(shm_fd) < 0)
    {
        fprintf(stderr, "ERROR: Closing shared memory fd filed: %s\n", strerror(errno));
        exit(4);
    }

    if (shm_unlink("/shm0") < 0)
    {
        fprintf(stderr, "ERROR: Unlinking shared memory failed: %s\n", strerror(errno));
        exit(5);
    }

    return 0;
}

