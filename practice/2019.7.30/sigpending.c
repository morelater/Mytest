#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>


int main()
{
    //创建自定义信号集合
    sigset_t myset;
    //将set集合致空
    sigemptyset(&myset);
    //将所有信号加入set集合
    sigfillset(&myset);
    //给自定义集合设置需要屏蔽的信号
    sigaddset(&myset,SIGINT);
    sigaddset(&myset,SIGQUIT);
    sigaddset(&myset,SIGKILL);
    //将自定义的信号集设置给内核的阻塞信号集
    sigprocmask(SIG_BLOCK,&myset,NULL);

    while(1)
    {
        //读取当前信号的未决信号集
        sigset_t pendset;
        sigpending(&pendset);
        
        //循环监听1-32号信号，看是否存在，存在打印1，不存在打印0
        int i = 1;
        for(;i < 32;i++)
        {
            if(sigismember(&pendset,i))
            {
                printf("1");
            }
            else
            {
                printf("0");
            }
        
        }

            printf("\n");
            sleep(1);
    }
    return 0;
}
