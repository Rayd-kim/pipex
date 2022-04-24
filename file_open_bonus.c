/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 19:38:31 by youskim           #+#    #+#             */
/*   Updated: 2022/04/24 19:38:33 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *file)
{
	int	fd;

	fd = open (file, O_RDONLY);
	if (fd < 0)
	{
		write (2, strerror(errno), ft_strlen(strerror(errno)));
		write (2, "\n", 1);
	}
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

int	write_file_app(char *file)
{
	int	fd;

	if (access(file, F_OK) == 0)
		fd = open (file, O_WRONLY | O_APPEND);
	else
		fd = open (file, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		error_stdin();
	return (fd);
}

int	open_heredoc(char *file)
{
	int		fd[2];
	char	*temp;
	int		check;

	if (pipe (fd) == -1)
		error_stdin();
	temp = get_next_line(0);
	check = ft_strncmp(temp, file, ft_strlen(file));
	while (check != 0)
	{
		write (fd[1], temp, ft_strlen(temp));
		free (temp);
		temp = get_next_line(0);
		check = ft_strncmp(temp, file, ft_strlen(file));
	}
	free (temp);
	close (fd[1]);
	return (fd[0]);
}
