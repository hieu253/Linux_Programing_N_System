#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<stdlib.h>


void signal_hanlder(int signum){
    printf("Im signal_hanlder()\n");
    wait(NULL);
}
int main(){
    pid_t child_pid = fork();
    if(child_pid == 0){
        printf("Im child, My PID = %d\n",getpid());
        while(1);
    }
    else{
        signal(SIGCHLD,signal_hanlder);
        printf("Im Parent, My PID = %d\n",getpid());
    }
    return 0;
}