#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SHARED_MEM_SIZE 1024
int main(int argc, char *argv[])
{
    // map
    char *data = mmap(0, SHARED_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (data == MAP_FAILED)
    {
        printf("Creating shared memory error!\n");
        exit(1);
    }

    // create child process
    pid_t child_pid;
    child_pid = fork();
    if (child_pid >= 0)
    {
        if (child_pid == 0)
        {
            printf("This is child process, My ID: %d\n", getpid());
            strcat(data, "Haha");
            printf("Child started, data in child process: %s\n", data);
            if (munmap(data, sizeof(int)) == -1)
            {
                printf("munmap fail\n");
            }
            exit(1);
        }
        else
        {
            printf("This is parent process, My ID: %d\n", getpid());
            strcat(data, "Hehe");
            printf("Parent started, data in parent process: %s\n", data);
            if (munmap(data, sizeof(int)) == -1)
            {
                printf("munmap fail\n");
            }
            exit(1);
        }
    }
    else
    {
        printf("fork() unsuccessfull\n");
    }

    return 0;
}