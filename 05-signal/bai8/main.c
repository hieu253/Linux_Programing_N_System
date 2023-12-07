#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// BT8. Viết chương trình in ra thông điệp bất kì khi nhấn tổ hợp phím Ctrl+C. Đăng ký action cho SIGUSR1 và SIGUSR2.
int cnt = 0;
void sig_handler(int signum)
{
    printf("\nIm signal handler: %d,cnt: %d\n", signum, cnt++);
}
void usr1_handler(int signum)
{
    printf("Received SIGUSR1\n");
}
void usr2_handler(int signum)
{
    printf("Received SIGUSR2\n");
}
int main()
{
    signal(SIGINT, sig_handler);
    signal(SIGUSR1, usr1_handler);
    signal(SIGUSR2, usr2_handler);

    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "Can't handle SIGINT\n");
    }
    if (signal(SIGUSR1, usr1_handler) == SIG_ERR)
    {
        fprintf(stderr, "Can't handle SIGUSR1\n");
    }
    if (signal(SIGUSR2, usr2_handler) == SIG_ERR)
    {
        fprintf(stderr, "Can't handle SIGUSR1\n");
    }
    else
        printf("Process ID: %d\n", getpid());
    while (1)
    {
        sleep(1);
    };
    return 0;
}