#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "pipex.h"
int main(void)
{
    int fd;
    int fd1[2];

    pipe (fd1);
    fd = open ("file1", O_RDWR);
    dup2 (fd, 0);
    close (fd);

    int pid = fork ();

    if (pid == 0)
    {
        dup2 (fd1[1], 1);
        close (fd1[0]);
        execve("/usr/bin/wc", NULL, NULL);
    }
    else
    {
        wait(NULL);
        dup2 (1, fd1[0]);
        close (fd1[1]);
    }
    printf ("check\n");
    return (0);
}