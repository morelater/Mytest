#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>


int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1)
    {
        perror("pipe is error!");
        exit(0);
    }
    int i = 0;
    for(;i < 2;i++)
    {
        pid_t pid = fork();
        if(pid == -1)
        {
            perror("fork error!");
            exit(1);
        }
        if(pid == 0)
        {
            break;
        }
    }
    
    //子进程1负责写，关闭读端，执行ps -aux
    //0输入 读段  1输出 写段
    if(i == 0)
    {
        close(fd[0]);
        dup2(fd[1],1);
        execlp("ps","ps","au",NULL);
        perror("execlp error!");
        exit(1);
    }
    //子进程2负责读，关闭写端，执行grep “bash”
    else if(i == 1)
    {
        close(fd[1]);
        dup2(fd[0],0);
        execlp("grep","grep","bash",NULL);
        //perror("execlp error!");
        //exit(1);
    }
    else if(i == 2)
    {
        close(fd[0]);
        close(fd[1]);
        pid_t wpid;
        while((wpid = waitpid(-1,NULL,WNOHANG)) != -1)
        {
            if(wpid == 0)
            {
                continue;
            }
            printf("child died pid = %d\n",wpid);
        }

    }

    return 0;
}
