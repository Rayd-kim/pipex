#include "pipex.h"
#include <stdio.h>

char	*path_split(char **envp)
{
	char	*ret;
	int		i;

	i = 0;
	ret = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{	
			ret = ft_strdup(envp[i] + 5);
			return (ret);
		}
		i++;
	}
	return (NULL);
}

void	path_check(char *cmd, char **envp)
{
	int 	i;
	char	**split;
	char	*ret;
	char	*temp;
	char	**command;

	i = 0;
	split = ft_split(path_split(envp), ':');
	command = ft_split(cmd, ' ');
	while (split[i])
	{
		ret = ft_strjoin(split[i], "/");
		temp = ret;
		ret = ft_strjoin(temp, command[0]);
		free(temp);
		if (access(ret, F_OK) == 0)
		{
			//write (1, "ok\n", 3);
			execve (ret, command, NULL);
			//exit(0);
		}
		else
			i++;
	}
	free(command);
	free(ret);
}


int main(int argc, char *argv[], char **envp)
{
	int		fd;
	char	*buffer;
	int		fd1[2], fd2[2];
	pid_t	pid;
	pid_t	pid2;

	if (pipe(fd2) == -1)
	{
		write (2, "error\n", 6);
		return (-1);
	}
	buffer = file1_size(argv[1]);

	pid = fork();


	if (pid == 0)
	{
		if (pipe(fd1) == -1)
		{
			write (2, "error\n", 6);
			return (-1);
		}
		pid2 = fork();

		
		if (pid2 == 0)
		{
			dup2 (fd1[1], 1);
			close (fd1[0]);
			write (fd1[1], buffer, ft_strlen(buffer));
		}
		else
		{
			wait(NULL);
			dup2 (fd2[1], 1);
			close (fd2[0]);
			close (fd1[1]);
			dup2 (fd1[0], 0);
			path_check(argv[2], envp);
		}
	}
	else
	{
		wait(NULL);
		//dup2 (fd2[0], 0);
		//close (fd2[1]);
		char	temp[100];
		read (fd2[0], temp, 100);
		printf("%s", temp);
	}


	/*
	if (access(argv[2], F_OK) == 0)
	{
		if (unlink(argv[2]) < 0)
		{
			printf("%s\n", strerror(errno));
			return (0);
		}
	}
	
	fd = open (argv[2], O_WRONLY | O_CREAT, 00600 | 00040 | 00004);
	write (fd, buffer, ft_strlen(buffer));
	free (buffer);
	close (fd);
	*/
	return (0);
}