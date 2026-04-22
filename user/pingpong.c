#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// int 
// main(int argc, char* argv[])
// {
//     char buf1[20], buf2[20];
//     int p[2], q[2];
//     if (argc != 1)
//     {
//         fprintf(2,"error using");
//         exit(1);
//     }
//     pipe(p);
//     pipe(q);
//     int pid = fork();
//     if(pid == 0)
//     {
//         close(0);
//         close(q[0]);
//         dup(p[0]);
//         close(p[0]);
//         close(p[1]);
//         read(0, buf1, 20);
//         pid = getpid();
//         fprintf(1,"%d: received ping\n", pid);
//         write(q[1], "pong", 4);
//         exit(0);
//     }
//     close(p[0]);
//     write(p[1],"ping",4);
//     wait(0);
//     close(0);
//     dup(q[0]);
//     close(q[0]);
//     close(q[1]);
//     read(0, buf2, 20);
//     pid = getpid();
//     fprintf(1,"%d: received pong\n", pid);
//     exit(0);
// }
int 
main(int argc, char* argv[])
{
    int p[2], q[2];
    char buf[1];
    pipe(p); pipe(q);
    int pid = fork();
    if(pid == 0)
    {
        close(p[1]);
        read(p[0], buf, 1);
        close(p[0]);
        pid = getpid();
        fprintf(1, "%d: received ping\n", pid);
        close(q[0]);
        write(q[1], "z", 1);
        close(q[1]);
        exit(0);
    }
    close(p[0]);
    write(p[1], "f", 1);
    close(p[1]);
    wait(0);
    close(q[1]);
    read(q[0], buf, 1);
    close(q[0]);
    pid = getpid();
    fprintf(1, "%d: received pong\n", pid, buf[0]);
    exit(0);
}