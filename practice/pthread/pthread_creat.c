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
    pthread_t pthid;
    pthread_create(&pthid,NULL,myfun,NULL);
    //打印主进程的ID
    printf("parent pthid = %lu\n",pthread_self());
    int i = 0;
    for(i;i < 4;i++)
    {
        printf("i = %d\n",i);
    }
    sleep(2);
    return 0;
}
