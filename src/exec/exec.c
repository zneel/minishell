/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:37:55 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/25 11:52:09 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <stdio.h>

int	exec(t_node *node, t_minishell *minishell)
{
	int	pipefd[2][2];

	if (init_exec(node, pipefd) == 0)
		return (0);
	if (node->type == PIPE)
	{
		if (exec_pipe(node, minishell, pipefd))
			return (1);
	}
	else if (node->type == OR)
	{
		if (exec_or(node, minishell))
			return (1);
	}
	else if (node->type == AND)
	{
		if (exec_and(node, minishell))
			return (1);
	}
	else if (node->type == COMMAND)
	{
		if (exec_cmd(node, minishell))
			return (1);
	}
	return (0);
}

int	prep_exec(t_node *node, t_minishell *minishell)
{
	if (exec(node, minishell) == 1)
		return (1);
	ft_lstclear(&minishell->pids, nothing);
	unlink(FILE_HEREDOC);
	return (0);
}
