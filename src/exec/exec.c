/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:37:55 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/04 14:49:09 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <stdio.h>

void	wait_all(t_minishell *minishell)
{
	t_list	*parc;

	parc = minishell->pids;
	while (parc)
	{
		waitpid(parc->n, &minishell->last_status, 0);
		parc = parc->next;
	}
	if (WIFEXITED(minishell->last_status))
		minishell->last_status = (WEXITSTATUS(minishell->last_status));
}

int	init_exec(t_node *node, int pipefd[2][2])
{
	init_pipes(pipefd);
	if (!node)
		return (0);
	return (1);
}

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

void	clear_exec(t_minishell *minishell)
{
	g_sigint = 0;
	set_signals();
	dup2(minishell->m_fd[1], 1);
	dup2(minishell->m_fd[0], 0);
	close_minishell_dup(minishell);
	ft_lstclear(&minishell->pids, nothing);
	unlink(FILE_HEREDOC);
}

int	prep_exec(t_minishell *minishell)
{
	dup_minishell(minishell);
	signal(SIGINT, sig_handler_job);
	signal(SIGQUIT, sig_handler_job);
	exec(minishell->root, minishell);
	clear_exec(minishell);
	return (0);
}
