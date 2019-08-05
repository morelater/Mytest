#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>

void myfun(int num)
{
    printf("catch signal = %d\n",num);
    sleep(4);
    printf("game over!\n");
}

int main()
{
    //设置struct sigaction *act结构体
    struct sigaction act;
    act.sa_flags = 0;

    //先清空信号的集合act.sa_mask,然后添加需要捕捉的信号
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGINT);
    act.sa_handler = myfun;
    sigaction(SIGQUIT,&act,NULL);

    while(1)
    {};

    return 0;
}
