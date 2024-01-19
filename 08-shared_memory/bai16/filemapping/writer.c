#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

#define SHARED_MEM_SIZE 1024
#define SHARED_MEM_OBJ_NAME "share_mem_obj_mmap"

int main(int argc, char *argv[])
{
    // create a shared memory fd
    int shm_fd = shm_open(SHARED_MEM_OBJ_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0)
    {
        printf("shm_open() is failed\n");
        exit(1);
    }

    // set size
    ftruncate(shm_fd, SHARED_MEM_SIZE);

    // map
    char data[100] = "data from writer";
    mmap(0, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    printf("%s: Write data: %s\n", __FILE__, data);

    // unmmap
    munmap(data, SHARED_MEM_SIZE);
    close(shm_fd);
    return 0;
}