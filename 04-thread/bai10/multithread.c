#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>

// chia thread thanh 4 de tinh tong 1tr
typedef struct
{
    int counter;
} Data;

void *increaseCounterMulti(void *arg)
{
    Data *data = (Data *)arg;
    for (int i = 0; i < 250000; i++)
    {
        data->counter++;
    }
    return NULL;
}

int main()
{
    Data data;
    data.counter = 0;

    pthread_t threads[4];

    clock_t start = clock();

    for (int i = 0; i < 4; i++)
    {
        pthread_create(&threads[i], NULL, increaseCounterMulti, (void *)&data);
    }

    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Multi-threading time: %f seconds\n", time_spent);

    printf("Counter value: %d\n", data.counter);

    return 0;
}