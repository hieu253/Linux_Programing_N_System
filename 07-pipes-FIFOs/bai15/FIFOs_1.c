#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFF_SIZE 1024
#define FIFO_FILE "./myfifo"
int main(int argc, char *argv[])
{
    char buffer[BUFF_SIZE];
    int fd;
    mkfifo(FIFO_FILE, 0666);
    while (1)
    {
        printf("Message to FIFOs_2: ");
        fflush(stdin);
        fgets(buffer, BUFF_SIZE, stdin);
        fd = open(FIFO_FILE, O_WRONLY);
        write(fd, buffer, sizeof(buffer));
        close(fd);
    }
    return 0;
}