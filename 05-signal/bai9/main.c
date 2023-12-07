#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

// BT9. Kiểm tra SIGINT có bị block trong process hay không. Nếu không thực hiện block/ublock thử SIGINT.
void sig_handler(int signum)
{
    printf("Im signal handler\n");
}
int main()
{
    sigset_t new_set, old_set;
    if (signal(SIGINT, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "Can't handle SIGINT\n");
    }
    sigemptyset(&old_set);
    sigemptyset(&new_set);
    sigprocmask(SIG_SETMASK, &new_set, &old_set);
    if (!sigprocmask(SIG_SETMASK, &new_set, &old_set))
    {
        if (sigismember(&new_set, SIGINT) == 1)
        {
            printf("SIGINT exist in signal mask\n");
        }
        else
        {
            printf("SIGINT does'nt exist in signal mask\n");
            sigaddset(&new_set, SIGINT);
            if (!sigaddset(&new_set, SIGINT))
            {
                printf("add SIGINT successfully\n");
            }
            // block SIGINT
            sigprocmask(SIG_BLOCK, &new_set, &old_set);
            if (!sigprocmask(SIG_BLOCK, &new_set, &old_set))
            {
                printf("successfully blocked SIGINT, cant press Ctrl+C\n");
            }
            sleep(10);
            // unblock SIGINT
            sigprocmask(SIG_UNBLOCK, &new_set, &old_set);
            if (!sigprocmask(SIG_UNBLOCK, &new_set, &old_set))
            {
                printf("successfully unblocked SIGINT,call signal handler\n");
            }
        }
    }
    while (1)
    {
    }
    return 0;
}