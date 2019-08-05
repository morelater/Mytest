#include<stdio.h>
#include<unistd.h>

int main()
{
    pid_t pid;
    printf("nihao\n");
    char *message;
    pid = fork();
    int n = 0;
    
    if(pid < 0)
    {
        perror("fork is failed");
        return 0;
    }
    if(pid ==  0)
    {
        message = "this is chlid!\n";
        n = 4;
    }
    else
    {
        message = "this is parent!\n";
        n = 2;
       // sleep(1);
    }

    for(;n > 0;n--)
    {
        printf(message);
        //sleep(1);
    }



    return 0;
}
