#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>

int main()
{
    pid_t pid;
    int i = 0;
    for(;i < 3;i++)
    {
        pid = fork();
        //如果是子进程的话，就不在产生子进程
        if(pid == 0)
        {
            break;
        }
    }

    if(i == 0)
    {
        execl("/home/zcd/practice/2019.7.23/hello","hello",NULL);
        perror("execl error!");
        exit(1);
    }

    if(i == 1)
    {
        execlp("ls","ls",NULL);
        perror("execlp error!");
        exit(1);
    }
    if(i == 2)
    {
        execl("/bin/ps","ps",NULL);
        perror("execl2 error!");
        exit(1);
    }
    if( i == 3)
    {
        int status;
        pid_t wpid;
        while((wpid = waitpid(-1,&status,WNOHANG)) != -1 )
        {
            if(wpid == 0)
            {
                continue;
            }
            printf("child died pid = %d\n",getpid());
            if(WIFEXITED(status))
            {
                printf("return value %d\n",WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status))
            {
                printf("died by signal :%d\n",WTERMSIG(status));

            }
        }
    }

    return 0;
}
