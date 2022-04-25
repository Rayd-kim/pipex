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

int	do_cmd(char *cmd, char **envp, int fd, int *pid)
{
	int		fd_in[2];

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

void	pid_check(int *check, int *pid)
{
	int	status;
	int	now_pid;

	*check = 0;
	now_pid = 0;
	while (1)
	{
		now_pid = waitpid(0, &status, 0);
		if (now_pid == -1)
			break ;
		if (now_pid == pid[1])
			*check = status;
	}
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd;
	int		fd2;
	char	*temp;
	int		check;
	int		pid[2];

	if (argc != 5)
		exit (1);
	fd = open_file(argv[1]);
	fd2 = do_cmd(argv[2], envp, fd, &pid[0]);
	fd2 = do_cmd(argv[3], envp, fd2, &pid[1]);
	pid_check(&check, pid);
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
	check = check >> 8;
	return (check);
}
