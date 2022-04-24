/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:24:38 by youskim           #+#    #+#             */
/*   Updated: 2022/04/23 20:37:01 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	pid_check(int *check, int *pid, int argc)
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
		if (now_pid == pid[argc - 4])
			*check = status;
	}
	free (pid);
}

void	write_to_outfile(int outfile_fd, int pipe_fd)
{
	char	*temp;

	temp = get_next_line(pipe_fd);
	while (temp != NULL)
	{
		write (outfile_fd, temp, ft_strlen(temp));
		free (temp);
		temp = get_next_line(pipe_fd);
	}
}

int	*pid_arr(int argc)
{
	int	*ret;

	ret = (int *)malloc(sizeof(pid_t) * (argc - 3));
	ft_memset(ret, 0, argc - 3);
	return (ret);
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd;
	int		fd2;
	int		i;
	int		check;
	int		*pid;

	if (argc < 3)
		exit (1);
	i = 2;
	fd = open_file(argv[1]);
	fd2 = fd;
	pid = pid_arr(argc);
	while (i < argc -1)
	{
		fd2 = do_cmd(argv[i], envp, fd2, &pid[i - 2]);
		i++;
	}
	pid_check(&check, pid, argc);
	fd = write_file(argv[argc - 1]);
	write_to_outfile(fd, fd2);
	close (fd2);
	close (fd);
	exit(WEXITSTATUS(check));
}
