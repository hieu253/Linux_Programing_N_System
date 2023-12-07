#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>

typedef struct
{
    int counter;
} Data;

void increaseCounterSingle(Data *data)
{
    for (int i = 0; i < 1000000; i++)
    {
        data->counter++;
    }
}

int main()
{
    Data data;
    data.counter = 0;

    clock_t start = clock();
    increaseCounterSingle(&data);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Single-threading time: %f seconds\n", time_spent);

    printf("Counter value: %d\n", data.counter);

    return 0;
}