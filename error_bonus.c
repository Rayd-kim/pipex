/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 19:38:22 by youskim           #+#    #+#             */
/*   Updated: 2022/04/24 19:38:23 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_stdin(void)
{
	write (2, strerror(errno), ft_strlen(strerror(errno)));
	write (2, "\n", 1);
	exit (errno);
}
