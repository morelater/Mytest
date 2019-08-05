#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>


int main()
{
    pid_t pid;
    
    
    pid = fork();
    if(pid < 0)
    {
        printf("fork failed!\n");
        return 0;
    }

    //wait回收子进程的id
    if(pid == 0)
    {
        sleep(1);
        printf("child pid = %d,ppid = %d\n",getpid(),getppid());
        //printf("parent pid = %d\n",getpid());
    }
    if(pid > 0)
    {
        printf("parent pid = %d\n",getpid());
        pid_t wpid = wait(NULL);
        printf("child died pid = %d\n",wpid);   
    }
    
    if(pid > 0)
        printf("father\n");
    else if(pid == 0)
        printf("son\n");

    return 0;
}
