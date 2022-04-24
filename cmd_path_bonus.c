/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 19:38:12 by youskim           #+#    #+#             */
/*   Updated: 2022/04/24 19:38:14 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*path_split(char **envp)
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

void	do_execve(char *ret, char **command, char **envp)
{
	if (execve(ret, command, envp) == -1)
		error_stdin();
}

void	path_check(char *cmd, char **envp)
{
	int		i;
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
		if (access(ret, X_OK) == 0)
			do_execve(ret, command, envp);
		else
			i++;
	}
	write (2, "zsh: command not found: ", 24);
	write (2, command[0], ft_strlen(command[0]));
	write (2, "\n", 1);
	free(command);
	free(ret);
}
