#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


void* fun()
{
    printf("child pthid = %lu\n",pthread_self());  
    
    //单个线程退出，如果没有单个线程推出函数，那就只有跟随主线程的退出才能退出
    pthread_exit(NULL);  
}

int main()
{
    //定义一个线程ID
    pthread_t pthid;
    //创建线程
    pthread_create(&pthid,NULL,fun,NULL);
    //打印线程的线程ID
    printf("parent pthid = %lu\n",pthread_self());
    
    int i = 0;
    for(;i < 3;i++)
    {
        printf("nihao!\n");
    }
    
    //阻塞等待线程退出，获取子线程的退出状态
    pthread_join(pthid,NULL);
    return 0;
}
