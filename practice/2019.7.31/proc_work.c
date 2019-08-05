#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>
#include<string.h>
#include<sys/time.h>

void dowork(int n)
{
    //获取当前时间，写到磁盘中去
    time_t curtime;
    time(&curtime);
    //格式化时间
    char *ptr = ctime(&curtime);
    //写到文件中去
    int fd = open("file",O_CREAT|O_WRONLY | O_APPEND,0664);
    write(fd,ptr,strlen(ptr) + 1);
    close(fd);
}

int main()
{
    pid_t pid = fork();
    if(pid > 0)
    {
        exit(0);
    }
    else if(pid == 0)
    {
        //子进程成为新的会长，脱离终端，成为守护进程
        setsid();
        //重新设置文件掩码
        umask(0);
        //关闭文件描述符
        close(0);
        close(1);
        close(2);

        //执行核心的工作
        
        //注册信号捕捉
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = dowork;
        sigemptyset(&act.sa_mask); 
        sigaction(SIGALRM,&act,NULL);


        //创建一个定时器
        struct itimerval val;
        //第一次触发的时间
        val.it_value.tv_usec = 0;
        val.it_value.tv_sec = 2;
        //循环周期
        val.it_interval.tv_usec = 0;
        val.it_interval.tv_sec = 1;
        setitimer(ITIMER_REAL,&val,NULL);
        

        while(1);

    }
    return 0;
}

