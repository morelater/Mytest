#include<stdio.h>
#include<unistd.h>

int count = 200;
int main()
{
    pid_t pid;
    int i = 0;
    for(i = 0;i < 3;i++)
    {
        pid = fork();
        sleep(1);
        if(pid == 0)
        {
            break;
        }
    }
    if(i == 0)
    {
        count+=200;
        printf("first process pid = %d\n",getpid());
        printf("first count = %d\n",count);
    }
    if(i == 1)
    {
        count += 200;
        printf("scend process pid = %d\n",getpid());
        printf("scend count = %d\n",count);
    }
    if(i == 2)
    {
        count += 200;
        printf("third process pid = %d\n",getpid());
        printf("third child count = %d\n",count);
    }
    if(i == 3)
    {
        count += 500;
        printf("parent process pid = %d\n",getpid());
        printf("parent count = %d\n",count);
    }
    return 0;
}
