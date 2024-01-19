#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define buff_size 256
#define BACK_LOG 50
#define handler_error(msg)  \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

void chat_func(int client_fd)
{
    int num_read, num_write;
    char sendbuff[buff_size];
    char recvbuff[buff_size];
    while (1)
    {
        memset(sendbuff, '0', buff_size);
        memset(recvbuff, '0', buff_size);

        // doc du lieu tu socket
        num_read = read(client_fd, recvbuff, buff_size);
        if (num_read == -1)
        {
            handler_error("read()");
        }
        if (strncmp("exit", recvbuff, 4) == 0)
        {
            system("clear");
            break;
        }
        printf("\nMessage from client: %s", recvbuff);
        printf("\nMessage respond the message: ");
        fgets(sendbuff, buff_size, stdin);

        // ghi du lieu toi client thong qua ham write
        num_write = write(client_fd, sendbuff, sizeof(sendbuff));
        if (num_write == -1)
        {
            handler_error("write()");
        }
        if (strncmp("exit", sendbuff, 4) == 0)
        {
            system("clear");
            break;
        }
        sleep(1);
    }
    close(client_fd);
}

int main(int argc, char *argv[])
{
    int opt, port_no;
    int server_fd, client_fd;
    struct sockaddr_in serv_addr, client_addr;

    if (argc < 2)
    {
        printf("No port provided\ncommand: ./server <port number>\n");
        exit(1);
    }
    port_no = atoi(argv[1]);
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    // tao socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
        handler_error("socket()");

    /* Ngăn lỗi : “address already in use” */
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        handler_error("setsockopt()");

    // khoi tao dia chi cho server
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // gan socket voi dia chi cua server
    if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        handler_error("bind()");
    }

    // Nghe toi da 50 ket noi trong hang doi
    if (listen(server_fd, BACK_LOG) == -1)
    {
        handler_error("listen()");
    }
    int len = sizeof(client_addr);

    while (1)
    {
        printf("Server is listening at port: %d\n", port_no);
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&len);
        if (client_fd == -1)
        {
            handler_error("accept()");
        }
        system("clear");
        printf("Server: got connection \n");
        chat_func(client_fd);
    }
    close(server_fd);
    return 0;
}