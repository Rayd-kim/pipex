#include "pipex.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	fd1[2];
	int	fd2[2];
	pid_t	pid;
	pid_t	pid2;
	char	*file1;

	if (pipe(fd1) == -1 || pipe(fd2) == -1)
	{
		write (2, "error\n", 6);
		return (1);
	}
	/*	
	pid = fork();

	if (pid == 0)
	{
		pid2 = fork();

		if (pid2 == 0)
		{
			dup2 (fd2[1], 1);
			close (fd2[0]);
			file1 = file1_size(argv[1]);
			write (fd2[1], file1, ft_strlen(file1));
		}
		else
		{
			wait (NULL);
			dup2 (fd2[0], 0);
			dup2 (fd1[1], 1);
			char *exe[3];
			exe[0] = "/usr/bin/grep";
			exe[1] = "2";
			exe[2] = NULL;
			execve (exe[0], exe, NULL);
		}
	}
	else
	{
		wait(NULL);
		dup2 (fd1[0], 0);
		dup2 (fd1[1], 1);
		char	temp[100];
		read (fd2[0], temp, 100);
		printf("%s", temp);
	}
	*/
	pid2 = fork();

	if (pid2 == 0)
	{
		dup2 (fd2[1], 1);
		close (fd2[0]);
		file1 = file1_size(argv[1]);
		write (fd2[1], file1, ft_strlen(file1));
	}
	else
	{
		wait (NULL);
		write (1, "ok\n", 3);
		dup2 (fd2[0], 0);
		close (fd2[1]);
		char *exe[3];
		exe[0] = "/usr/bin/grep";
		exe[1] = "3";
		exe[2] = NULL;
		execve (exe[0], exe, NULL);
	}
	
	return (0);
}
