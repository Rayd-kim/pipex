/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:24:33 by youskim           #+#    #+#             */
/*   Updated: 2022/04/23 16:47:43 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_stdin(void)
{
	write (2, strerror(errno), ft_strlen(strerror(errno)));
	write (2, "\n", 1);
	exit (errno);
}
