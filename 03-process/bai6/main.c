#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>
#include<stdlib.h>

int main(){
    pid_t pid_A;
    int status;
    int ret;
    pid_A = fork();
    if (pid_A >= 0) {
        if (0 == pid_A) {       
            /* Process con */
            printf("Im the child process, myPID: %d\nMy parent ID : %d\n", getpid(),getppid());
            exit(0);
        } 
        else {                    
            /* Process cha */;
            ret = wait(&status);
            if(ret == -1)
            {
                printf("wait() unsuccesfull");
            }
                if(WIFEXITED(status))
                {
                    printf("Normally termination, status = %d\n",WEXITSTATUS(status));
                }
                else
                {
                    printf("Abnormally termination, signal value = %d\n",WTERMSIG(status));
                }
        }
    }
    else 
        /*fork() return -1 nếu lỗi*/
        printf("fork() unsuccessfully\n"); 
    return 0;
}
