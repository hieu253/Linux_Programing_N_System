#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2, thread_id3;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct
{
    char name[30];
    char birth[30];
    char home_town[30];
} student;

int cnt = 0;
int con_var = 1;

static void *inputThread(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        while (con_var != 1)
        {
            pthread_cond_wait(&cond, &lock);
        }

        student *infor = (student *)args;
        printf("Nhap ho va ten cua ban:\n");
        fgets(infor->name, sizeof(infor->name), stdin);
        printf("Nhap ngay thang nam sinh cua ban:\n");
        fgets(infor->birth, sizeof(infor->birth), stdin);
        printf("Nhap que quan cua ban:\n");
        fgets(infor->home_town, sizeof(infor->home_town), stdin);

        con_var = 2;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

static void *writeThread(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        while (con_var != 2)
        {
            pthread_cond_wait(&cond, &lock);
        }
        int fd;
        fd = open("thongtinsinhvien.txt", O_APPEND | O_RDWR | O_CREAT);
        if (fd == -1)
        {
            printf("open thongtinsinhvien.txt failed\n");
        }

        student *infor = (student *)args;
        char buffer[100];
        sprintf(buffer, "%s%s%s\n", infor->name, infor->birth, infor->home_town);
        write(fd, buffer, strlen(buffer));
        close(fd);

        con_var = 3;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

static void *readThread(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&lock);
        while (con_var != 3)
        {
            pthread_cond_wait(&cond, &lock);
        }

        student *infor = (student *)args;
        int fd;
        fd = open("thongtinsinhvien.txt", O_APPEND | O_RDWR | O_CREAT);
        if (fd == -1)
        {
            printf("open thongtinsinhvien.txt failed\n");
        }

        char buffer[100];
        int bytesRead;
        while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0)
        {
            write(STDOUT_FILENO, buffer, bytesRead);
        }
        close(fd);
        con_var = 1;
        printf("Nhap thong tin sinh vien tiep theo:\n");
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main()
{
    student studentinfor;
    if (pthread_create(&thread_id1, NULL, &inputThread, &studentinfor) != 0)
    {
        perror("pthread_create() error\n");
        return 1;
    }
    if (pthread_create(&thread_id2, NULL, &writeThread, &studentinfor) != 0)
    {
        perror("pthread_create() error\n");
        return 1;
    }
    if (pthread_create(&thread_id3, NULL, &readThread, &studentinfor) != 0)
    {
        perror("pthread_create() error\n");
        return 1;
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);

    return 0;
}