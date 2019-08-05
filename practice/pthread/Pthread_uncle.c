#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


#define MAX 2000
//数数需要创建一个全局变量
int num;

void *fun1(void * arg)
{
    int i = 0;
    for(;i < MAX;i++)
    {
        int tmp = num;
        tmp++;
        num = tmp;

        printf("first pthread = %lu,num = %d\n",pthread_self,num);
        usleep(10);
    }

    return NULL;
}

void *fun2(void *arg)
{
    int i = 0;
    for(;i < MAX;i++)
    {
        int tmp = num;
        tmp++;
        num = tmp;;

        printf("scend pthread = %lu,num = %d\n",pthread_self(),num);
        usleep(10);
    }

    return NULL;
}
int main()
{
    //定义两个线程ID
    pthread_t p1,p2;
    //创建两个线程
    pthread_create(&p1,NULL,fun1,NULL);
    pthread_create(&p2,NULL,fun2,NULL);


    //等待线程结束，获取线程的退出状态
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);

    return 0;
}
