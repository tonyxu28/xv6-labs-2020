#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  buf[strlen(p)] = 0;
  return buf;
}

void
find(char *path, char *object)
{
    char buf[512], *p;
    int fd;
    struct dirent lss;
    struct stat xc;
    if((fd = open(path, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    if(fstat(fd, &xc) < 0)
    {
        fprintf(2, "find cannot stat %s\n", path);
        close(fd);
        return;
    }
    switch(xc.type)
    {
        case T_FILE:
            if(strcmp(fmtname(path),object) == 0)
                fprintf(1, "%s\n", path);
            break;
        case T_DIR:
            strcpy(buf, path);
            p = buf + strlen(buf);
            *p++ = '/';
            while(read(fd, &lss, sizeof(lss)) == sizeof(lss))
            {
                if(lss.inum == 0 || strcmp(lss.name, ".") == 0 || strcmp(lss.name, "..") == 0)
                    continue;
                memmove(p, lss.name, DIRSIZ);
                p[DIRSIZ] = 0;
                find(buf, object);
            }
            break;
    }
    close(fd);
}

int
main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(2, "error invoke");
        exit(1);
    }
    find(argv[1], argv[2]);
    exit(0);
}