/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:18:49 by youskim           #+#    #+#             */
/*   Updated: 2022/04/24 15:18:52 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
