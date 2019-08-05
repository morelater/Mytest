#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<signal.h>


int main()
{
    pid_t pid = fork();
    if(pid > 0)
    {
        printf("parent process pid = %d\n",getpid());
        int s;
        pid_t wpid = wait(&s);

        printf("child died pid = %d\n",wpid);
        if(WIFSIGNALED(s))
        {
            printf("died by signal = %d\n", WTERMSIG(s));
        }

    }
    else if(pid == 0)
    {
        raise(SIGQUIT);
    }
    return 0;
}
