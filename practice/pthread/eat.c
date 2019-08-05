#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>


//线程同步需要互斥锁
pthread_mutex_t mutex;

//阻塞线程需要条件变量
pthread_cond_t cond;
typedef struct Node
{
    int data;
    struct Node *next;
}Node;

Node* head = NULL;

void * producer()
{
    while(1)
    {
        
        Node *p = (Node *)malloc(sizeof(Node));
        p->data = rand()%1000;
        //开始枷锁,保护共享资源
        pthread_mutex_lock(&mutex);
        p->next = head;
        head = p;
        //开始解锁
        printf("producer pthid = %lu,%d\n",pthread_self(),p->data);
               
        pthread_mutex_unlock(&mutex);
        //通知阻塞的线程
        pthread_cond_signal(&cond);
        sleep(rand()%3);
    }
    
    return NULL;
}

void * customer()
{   
    while(1)
    {
        //枷锁
        pthread_mutex_lock(&mutex);
        if(head == NULL)
        {
            //continue;
            //阻塞线程,对互斥锁解锁
            pthread_cond_wait(&cond,&mutex);
            //对互斥锁继续枷锁

        }
            
        printf("sustomer pthid = %-lu,%d\n",pthread_self(),head->data);
        Node*p = head->next;
        free (head);
        head = p;
        //解锁      
        pthread_mutex_unlock(&mutex);
        
    }
    return NULL;
}
int main()
{
    //创建两个线程，一个生产，一个消费
    pthread_t p1,p2;
    pthread_create(&p1,NULL,producer,NULL);
    pthread_create(&p2,NULL,customer,NULL);
    //初始化条=条件变量和互斥锁
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);


    //回收子线程
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);

    //销毁条件变量和互斥锁
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return 0;
}
