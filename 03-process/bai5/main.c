#include<stdio.h>
#include<unistd.h>

int main(){
    pid_t pid_A;
    int cnt = 0;
    pid_A = fork();
    if (pid_A >= 0) {
        if (0 == pid_A) {       
            /* Process con */
            printf("\nIm the child process, cnt: %d\n", ++cnt);
            printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
        } 
        else {                    
            /* Process cha */
            printf("\nIm the parent process, cnt: %d\n", cnt);
            printf("My PID is: %d\n", getpid());
        }
    }
    else {
        /*fork() return -1 nếu lỗi*/
        printf("fork() unsuccessfully\n");     
    }
    return 0;
}