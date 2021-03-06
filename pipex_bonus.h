/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:03:54 by youskim           #+#    #+#             */
/*   Updated: 2022/04/25 13:03:56 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

int			*pid_arr(int argc);
void		pid_check(int *check, int *pid, int argc);
int			open_heredoc(char *file);
int			write_file_app(char *file);
int			open_file(char *file);
int			write_file(char *file);
void		error_stdin(void);
void		path_check(char *cmd, char **envp);
#endif
