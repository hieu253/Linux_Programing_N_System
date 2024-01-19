#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define buff_size 256
#define handler_error(msg)  \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

void chat_func(int server_fd)
{
    int num_write, num_read;
    char sendbuff[buff_size];
    char recvbuff[buff_size];
    while (1)
    {
        memset(sendbuff, '0', buff_size);
        memset(recvbuff, '0', buff_size);
        printf("Please enter the message: ");
        fgets(sendbuff, buff_size, stdin);

        // Gui thong diep toi server bang ham write
        num_write = write(server_fd, sendbuff, sizeof(sendbuff));
        if (num_write < 0)
        {
            handler_error("read()");
        }
        if (strncmp("exit", sendbuff, 4) == 0)
        {
            printf("Client exit ...\n");
            break;
        }
        // Nhan thong diep tu server bang ham read
        num_read = read(server_fd, recvbuff, sizeof(recvbuff));
        if (num_read < 0)
        {
            handler_error("read()");
        }
        if (strncmp("exit", recvbuff, 4) == 0)
        {
            printf("Server exit ...\n");
            break;
        }
        printf("\nMessage form Server: %s\n", recvbuff);
    }
    close(server_fd);
}
int main(int argc, char *argv[])
{
    int port_no;
    int server_fd;
    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    if (argc < 3)
    {
        printf("command: ./client <server address> <port number>\n");
        exit(1);
    }
    port_no = atoi(argv[2]);

    // khoi tao dia chi server
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) == -1)
    {
        handler_error("inet_pton()");
    }

    // tao socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        handler_error("socket()");
    }

    // ket noi toi server
    if (connect(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
    {
        handler_error("connect()");
    }
    chat_func(server_fd);
    return 0;
}