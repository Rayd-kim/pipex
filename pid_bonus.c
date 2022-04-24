/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 19:42:12 by youskim           #+#    #+#             */
/*   Updated: 2022/04/24 19:42:20 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	*pid_arr(int argc)
{
	int	*ret;

	ret = (int *)malloc(sizeof(pid_t) * (argc - 3));
	ft_memset(ret, 0, argc - 3);
	return (ret);
}
