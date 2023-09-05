/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:04:08 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/05 10:37:25 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_minishell(t_minishell *minishell, char **env)
{
	minishell->env = env_cpy(env);
	minishell->pids = NULL;
	minishell->root = NULL;
	minishell->last_status = 0;
	minishell->shlevel = 0;	
	minishell->m_fd[0] = -1;
	minishell->m_fd[1] = -1;
}

int	str_all_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isspace(str[i]))
			return (0);
	}
	return (1);
}

void	dup_minishell(t_minishell *ms)
{
	ms->m_fd[0] = dup(0);
	ms->m_fd[1] = dup(1);
}

void	close_minishell_dup(t_minishell *ms)
{
	close_if(ms->m_fd[0]);
	close_if(ms->m_fd[1]);
}

void	close_if(int fd)
{
	if (fd >= 0)
		close(fd);
}
