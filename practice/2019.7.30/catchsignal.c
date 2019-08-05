#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

//设置回调函数
void function(int num)
{
    printf("catch signal = %d\n",num);
}

int main()
{
   // 捕捉信号
   //注册捕捉函数
   signal(SIGINT,function);

   while(1)
   {
       printf("hello, I'm here!\n");
       sleep(2);
    }
    return 0;   
}
