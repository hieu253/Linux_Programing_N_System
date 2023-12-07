#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

pthread_t thread_id1, thread_id2;

typedef struct
{
    char name[30];
    char birth[30];
    char phone_number[30];
    char home_town[30];

} human;

static void *thr_handler(void *args)
{
    pthread_t tid = pthread_self();
    human *data = (human *)args;
    if (pthread_equal(tid, thread_id1))
    {
        printf("Im thread_id1\n");
    }
    else if (pthread_equal(tid, thread_id2))
    {
        printf("Im thread_id2\n");
        printf("Thong tin:\n%s\n%s\n%s\n%s\n", data->name, data->birth, data->phone_number, data->home_town);
    }
}
int main()
{
    human data = {0};
    strncpy(data.name, "Ngo Trung Hieu", sizeof(data.name));
    strncpy(data.birth, "25/03/2002", sizeof(data.birth));
    strncpy(data.phone_number, "0332543444", sizeof(data.phone_number));
    strncpy(data.home_town, "Ha Nam", sizeof(data.home_town));

    if (pthread_create(&thread_id1, NULL, &thr_handler, NULL) != 0)
    {
        printf("pthread_create() error\n");
        return -1;
    }
    sleep(1);
    if (pthread_create(&thread_id2, NULL, &thr_handler, &data) != 0)
    {
        printf("pthread_create() error\n");
        return -1;
    }
    sleep(3);
    return 0;
}