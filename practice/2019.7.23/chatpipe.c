#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1)
    {
        perror("pipe failed!");
        exit(1);
    }
    
    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork error!");
        exit(1);
    }

    if(pid > 0)
    {
        close(fd[0]);
        dup2(fd[1],1);
        execlp("ps","ps","aux",NULL);

        perror("execlp error!");
        exit(1);
    }

    if(pid == 0)
    {
        close(fd[1]);
        dup2(fd[0],0);
        execlp("grep","grep","bash",NULL);
        perror("grep error!");
        exit(1);
    }


    close(fd[0]);
    close(fd[1]);
    return 0;
}
