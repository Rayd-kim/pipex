#include "pipex.h"
#include <stdio.h>

void	read_file1(char *buffer, char *file1, int size)
{
	int	fd;
	char	*ret;

	fd = open (file1, O_RDONLY);
	if (fd < 0)
	{
		write (2, strerror(errno), ft_strlen(strerror(errno)));
		write (2, "\n", 1);
		exit (0);
	}
	read (fd, buffer, size);
	close (fd);
}

char	*file1_size(char *str) //file1 읽어오고 그만큼 할당해서 읽기.
{
	int		size;
	int		read_size;
	char	*temp[10];
	char	*buffer;
	int		fd;

	fd = open (str, O_RDWR);
	if (fd < 0)
	{
		write (2, strerror(errno), ft_strlen(strerror(errno)));
		write (2, "\n", 1);
		exit (0);
	}
	read_size = read(fd, temp, 10);
	size = 0;
	while (read_size > 0)
	{
		size += read_size;
		read_size = read (fd, temp, 10);
	}
	buffer = (char *)malloc(sizeof(char) * (size + 1));
	if (buffer == 0)
		return (NULL);
	close (fd);
	read_file1(buffer, str, size);
	return (buffer);
}

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
			write (1, "ok\n", 3);
			execve (ret, command, NULL);
			exit(0);
		}
		else
			i++;
	}
	free(command);
	free(ret);
}

int main(int argc, char *argv[], char **envp)
{
	int		fd2;
	char	*buffer;
	int		file1_fd[2];
	pid_t	pid;

	buffer = file1_size(argv[1]);
	pipe(file1_fd);
	file1_fd[0] = buffer;
	
	pid = fork();

	if (pid == 0)
		path_check(argv[2], envp);
	else
	{
		wait(NULL);

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
	
	fd2 = open (argv[2], O_WRONLY | O_CREAT, 00600 | 00040 | 00004);
	write (fd2, buffer, ft_strlen(buffer));
	free (buffer);
	close (fd2);
	*/
	return (0);
}