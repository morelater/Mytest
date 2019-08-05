#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

//父子进程间是否可以用文件通讯
int main()
{
    int fd = open("temp",O_CREAT | O_RDWR,0600);
    if(fd == -1)
    {
        perror("open failed\n");
        exit(1);
    }

    pid_t pid = fork();
    if(pid == -1)
    {
        perror("fork failed\n");
        exit(1);
    }
    
    if(pid > 0)
    {
        char *p = "nihao,I'm here!";
        write(fd,p,strlen(p) + 1);
        close(fd);
    }
    if(pid == 0)
    {
        sleep(1);
        char buff[1024] = {0};
        lseek(fd,0,SEEK_SET);
        int len = read(fd,buff,sizeof(buff));
        printf("%s\n",buff);
    }
    return 0;
}

