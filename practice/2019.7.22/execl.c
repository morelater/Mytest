#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    int i = 0;
    for(;i < 4;i++)
    {
        printf("i = %d\n",i);
    }

    sleep(1);
    pid_t pid = fork();
    if(pid == 0)
    {
        execlp("ps","ps","ef",NULL);
        perror("execlp");
        exit(0);
    }

    int j = 0;
    for(;j < 3;j++)
    {
        printf("j = %d\n",j);
    }

    return 0;
}

