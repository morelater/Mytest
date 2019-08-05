#include<stdio.h>
#include<signal.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    pid_t pid = fork();

    if(pid > 0)
    {
        while(1)
        {
            printf("parent process = %d\n",getpid());
            sleep(1);
        }

    }
    else if(pid == 0)
    {

        sleep(2);
        kill(getppid(),SIGKILL);
    }
    return 0;
}
