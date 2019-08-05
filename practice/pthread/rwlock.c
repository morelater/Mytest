#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

//线程间通信需要创建一个全局变量
int num;

//创建读写锁
pthread_rwlock_t lock;

void* write_fun(void *arg)
{
    while(1)
    {
        //在对全局变量执行写操作之前加写锁
        pthread_rwlock_wrlock(&lock);
        num++;
        printf("write pthid = %lu,num = %d\n",pthread_self(),num);
        //在使用完全局变量之后解锁
        pthread_rwlock_unlock(&lock);
        usleep(500);
    }

    return NULL;
}

void* read_fun(void *arg)
{
    while(1)
    {
        //在对全局变量执行读操作之前加读锁
        pthread_rwlock_rdlock(&lock);
        printf("read pthid = %lu,num = %d\n",pthread_self(),num);
        //在用完全局变量之后解锁
        pthread_rwlock_unlock(&lock);
        usleep(500);
    }
}

int main()
{
    //创建8个线程ID
    pthread_t pthid[8];

    //初始化读写锁
    pthread_rwlock_init(&lock,NULL);
    //创建3个写线程
    int i = 0;
    for(;i < 3;i++)
    {
        pthread_create(&pthid[i],NULL,write_fun,NULL);
    }
    //创建5个读锁
    int j = 3;
    for(;j < 8;j++)
    {
        pthread_create(&pthid[j],NULL,read_fun,NULL);
    }


    //对这8个线程进行回收
    int w = 0;
    for(;w < 8;w++)
    {
        pthread_join(pthid[w],NULL);
    }

    //在使用完锁之后一定要释放锁
    pthread_rwlock_destroy(&lock);
    return 0;
}


