#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

void * myfun(void* arg)
{
    //int num = *(int *)arg;
    int num = (int)arg;
    //打印子线程的ID
    printf("%dth,child pthid = %lu\n",num,pthread_self()); 
    
    return NULL;   
}

int main()
{
    //‘定义一个线程的ID
    pthread_t pthid[5];
    int i = 0,w = 0;
    //int fd[5] = {1,2,3,4,5};
  
    for(;i < 5;i++)
    {
        //pthread_create(&pthid[i],NULL,myfun,(void*)&fd[w++]);
        pthread_create(&pthid[i],NULL,myfun,(void*)i);

    }
    //打印主进程的ID
    printf("parent pthid = %lu\n",pthread_self());
    int j = 0;
    for(j;j < 4;j++)
    {
        printf("j = %d\n",j);
    }
    sleep(1);
    return 0;
}
