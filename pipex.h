/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:25:10 by youskim           #+#    #+#             */
/*   Updated: 2022/04/23 16:47:16 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

void		error_stdin(void);
void		path_check(char *cmd, char **envp);
#endif
