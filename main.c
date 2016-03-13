#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include "main.h"

int main() 
{
    char command[256] = "\0";
    
    printf("maiterm > ");
    scanf("%s", command);
    
    printf("exit %d\n", exec_command(command));
    _exit(0);
}

pid_t exec_command(char * command)
{
    printf("command: %s\n", command);
    
    pid_t pID = fork();
    if (pID == 0)
    {
      printf("Child Process\n");
      int res = system(command);
      if (res != 0)
      {
        printf("command not found\n");
        _exit(1);
      }
    }
    else if (pID < 0)
    {
        printf("Failed to fork\n");
        _exit(1);
    }
    else
    {
      printf("Parent Process\n");
    }

    return pID;
}
