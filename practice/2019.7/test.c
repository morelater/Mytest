#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
    pid_t pid = fork();
    if(pid > 0)
        exit(-1);
    else if(pid ==  0)
    {
        sleep(2);
        printf("%d\n",getppid());
    }
    return 0;
}
