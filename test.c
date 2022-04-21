#include "pipex.h"
#include <stdio.h>

int main(void)
{
    errno = 127;
    printf ("%s\n %d\n", strerror(errno), errno);
    return 0;
}