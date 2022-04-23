/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:24:38 by youskim           #+#    #+#             */
/*   Updated: 2022/04/23 20:36:36 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	do_cmd(char *cmd, char **envp, int fd, pid_t *pid)
{
	int	fd_in[2];

	if (pipe (fd_in) == -1)
		error_stdin();
	*pid = fork();
	if (*pid == -1)
		error_stdin();
	if (*pid == 0)
	{
		if (dup2 (fd_in[1], 1) == -1)
			error_stdin();
		if (dup2 (fd, 0) == -1)
			error_stdin();
		close (fd);
		close (fd_in[0]);
		path_check(cmd, envp);
		exit (127);
	}
	close (fd);
	close (fd_in[1]);
	return (fd_in[0]);
}

int	open_file(char *file)
{
	int	fd;

	fd = open (file, O_RDONLY);
	if (fd < 0)
		error_stdin();
	return (fd);
}

int	write_file(char *file)
{
	int	fd;

	if (access(file, F_OK) == 0)
	{
		if (unlink(file) < 0)
			error_stdin();
	}
	fd = open (file, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		error_stdin();
	return (fd);
}

void	pid_check(void)
{
	int	status;
	int	now_pid;

	now_pid = 0;
	while (1)
	{
		now_pid = waitpid(0, &status, 0);
		if (now_pid == -1)
			break ;
		if (WEXITSTATUS(status) == 127)
			exit(WEXITSTATUS(status));
	}
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd;
	int		fd2;
	char	*temp;
	pid_t	pid[2];

	if (argc != 5)
		exit (1);
	fd = open_file(argv[1]);
	fd2 = do_cmd(argv[2], envp, fd, &pid[0]);
	fd2 = do_cmd(argv[3], envp, fd2, &pid[1]);
	pid_check();
	fd = write_file(argv[argc - 1]);
	temp = get_next_line(fd2);
	while (temp != NULL)
	{
		write (fd, temp, ft_strlen(temp));
		free (temp);
		temp = get_next_line(fd2);
	}
	free (temp);
	close (fd2);
	close (fd);
	return (0);
}
