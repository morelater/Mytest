#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>

int main()
{
    pid_t pid = fork();
    //创建出子进程，让父进程死
    if(pid > 0)
    {
        exit(0);
        //kill(getpid(),SIGKILL);
        //raise(SIGKILL);
        //abort();    
    }
    else
    {
        //获取会话id，成为新进程组的组长
        setsid();
        while(1);
    }

    return 0;
}
