/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:37:55 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/23 20:07:31 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <stdio.h>

int	exec(t_node *node, t_minishell *minishell);

int	exec_more(t_node *node, t_minishell *minishell)
{
	t_command	*command;
	char		**env;

	if (node->type == OR)
	{
	    exec(node->left, minishell);
	}
	else if (node->type == AND)
	{
	    exec(node->left, minishell);
	    exec(node->right, minishell);
	}
	else if (node->type == COMMAND)
	{
		env = convert_env(minishell->env);
		if (!env)
			return (1);
		command = node_to_command(node, env);
		free_mat(env);
		execute_command(command, minishell);
		free_cmd(command);
	}
	return (0);
}

int	exec(t_node *node, t_minishell *minishell)
{
	int		pipefd[2][2];

	init_pipes(pipefd);
	if (!node)
		return (0);
	if (node->type == PIPE)
	{
		if (execute_pipeline(node, node, minishell, pipefd) == 1)
			return (1);
	}
	return (exec_more(node, minishell));
}

int	prep_exec(t_node *node, t_minishell *minishell)
{
	if (exec(node, minishell) == 1)
		return (1);
	wait_all(4);
	// unlink(file_heredoc);
	return (0);
}