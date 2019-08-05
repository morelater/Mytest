#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void * myfun()
{
    
    //打印子线程的ID
    printf("child pthid = %lu\n",pthread_self()); 
    
}

int main()
{
    //‘定义一个线程的ID
    pthread_t pthid[5];
    int i = 0;
    //创建5个线程，并且创建的时候设置线程分离
    //初始化线程分离
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

    for(;i<5;i++)
    {
        pthread_create(&pthid[i],&attr,myfun,NULL);
    }
    
    //打印主进程的ID
    printf("parent pthid = %lu\n",pthread_self());
    
    //释放线程资源
    pthread_attr_destroy(&attr);
    return 0;
}
