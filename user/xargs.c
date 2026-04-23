#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int 
main(int argc, char* argv[])
{
    char buf[512];
    int i = 0, head = 0, pid;
    int copyargc = 0;
    char * copyargv[MAXARG];
    for(int j = 1; j < argc; j++)
    {
        copyargv[copyargc] = argv[j];
        copyargc++;
    }
    while(read(0, &buf[i] ,1) == 1)
    {
        if(buf[i] == '\n')
        {
            buf[i] = '\0';
            copyargv[copyargc] = &buf[head];
            copyargv[++copyargc] = '\0';
            pid = fork();
            if(pid == 0)
            {
                exec(copyargv[0], copyargv);
            }
            wait(0);
            i = 0; copyargc = 0; head = 0;
            for(int j = 1; j < argc; j++)
            {
                copyargv[copyargc] = argv[j];
                copyargc++;
            }
            continue;
        }
        if(buf[i] == ' ')
        {   
            buf[i] = '\0';
            copyargv[copyargc] = &buf[head];
            copyargc++;
            head = i + 1;
        }
        i++;
    }
    exit(0);
}