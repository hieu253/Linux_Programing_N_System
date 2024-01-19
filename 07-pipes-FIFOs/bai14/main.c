#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MSG_SIZE 20

int main(int argc, char *argv[])
{
    int num_read = 0;
    char in_buff[MSG_SIZE];
    int fds[2];
    char *msg = "Data from parent !!";
    if (pipe(fds) < 0)
    {
        printf("pipe() unsuccessfully()\n");
        exit(EXIT_FAILURE);
    }
    pid_t child_pid;
    child_pid = fork();
    if (child_pid >= 0)
    {
        if (child_pid == 0)
        {

            printf("Im child process\n");
            printf("Child process ID is: %d\n", getpid());
            num_read = read(fds[0], in_buff, MSG_SIZE);

            printf("Child is reading from pipe - Message is: %s\n", in_buff);

            if (close(fds[1] == -1))
            {
                printf("close(fds[1]) failed\n");
            }
        }

        else
        {
            if (close(fds[0]) == -1)
            {
                printf("close(fds[0]) failed\n");
            }

            printf("Im parent process\n");
            printf("Parent process ID is: %d\n", getpid());
            write(fds[1], msg, MSG_SIZE);
        }
    }
    else
    {
        printf("fork() initialization unsuccessfully\n");
    }
    return 0;
}