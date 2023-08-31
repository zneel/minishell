/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:54:16 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/31 11:26:24 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_pipes(int pipefd[2][2])
{
	pipefd[0][0] = -1;
	pipefd[0][1] = -1;
	pipefd[1][0] = -1;
	pipefd[1][1] = -1;
}

void	close_if(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	nothing(void *x)
{
	(void)x;
}

t_bool	is_same(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (false);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (false);
	return (ft_strncmp(s1, s2, ft_strlen(s1)) == 0);
}
