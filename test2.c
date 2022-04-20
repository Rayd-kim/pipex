#include "pipex.h"
#include <stdio.h>
#include "gnl/get_next_line.h"

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
			execve (ret, command, NULL);
		else
			i++;
	}
	free(command);
	free(ret);
}

int	do_cmd(char *cmd, char **envp, int fd)
{
	int	pid;
	int	fd_in[2];

	pipe (fd_in);
	dup2 (fd, 0);
	pid  = fork();
	if (pid == 0)
	{
		dup2 (fd_in[1], 1);
		close (fd_in[0]);
		path_check(cmd, envp);
	}
	close (fd_in[1]);
	return (fd_in[0]);
}

int main(int argc, char *argv[], char **envp)
{
	int		fd;
	int		fd2;
	//int		fd3;
	int		i;
	char	*temp;

    fd = open (argv[1], O_RDONLY);
	fd2 = do_cmd(argv[2], envp, fd);
	close (fd);
	fd2 = do_cmd(argv[3], envp, fd2);

	if (access(argv[4], F_OK) == 0)
	{
		if (unlink(argv[4]) < 0)
		{
			printf("%s\n", strerror(errno));
			return (0);
		}
    }
    fd = open (argv[4], O_WRONLY | O_CREAT, 0644);
	temp = get_next_line(fd2);
	while (temp != NULL)
	{
		write (fd, temp, ft_strlen(temp));
		free (temp);
		temp = get_next_line(fd2);
	}
	free (temp);
    close (fd);
	return (0);
}