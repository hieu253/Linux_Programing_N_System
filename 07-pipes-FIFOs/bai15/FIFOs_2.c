#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define FIFO_FILE "./myfifo"
#define BUFF_SIZE 1024

int main(int argc, char *argv[])
{
    char buffer[BUFF_SIZE];
    int fd;
    mkfifo(FIFO_FILE, 0666);
    while (1)
    {
        fd = open(FIFO_FILE, O_RDONLY);
        read(fd, buffer, BUFF_SIZE);
        printf("FIFOs_2 message: %s", buffer);
        close(fd);
    }
    return 0;
}