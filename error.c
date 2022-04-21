/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youskim <youskim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:24:33 by youskim           #+#    #+#             */
/*   Updated: 2022/04/21 18:24:35 by youskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_stdin()
{
	write (2, strerror(errno), ft_strlen(strerror(errno)));
	write (2, "\n", 1);
	exit (errno);
}
