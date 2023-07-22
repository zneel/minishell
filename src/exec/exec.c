/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:37:55 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/22 17:19:17 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <stdio.h>

int	exec_and_or(t_node *node, t_minishell *minishell)
{
	if (node->type == OR)
	{
	    exec(node->left, minishell);
	}
	else if (node->type == AND)
	{
	    exec(node->left, minishell);
	    exec(node->right, minishell);
	}
}

int	exec(t_node *node, t_minishell *minishell)
{
	t_command	*command;
	char		**env;
	int	pipefd[2][2];

	init_pipes(pipefd);
	if (!node)
		return (0);
	if (node->type == PIPE)
	{
		env = convert_env(minishell->env);
		if (!env)
			return (1);
		if (execute_pipeline(node, node, env, pipefd) == 1)
			return (1);
		free_mat(env);
	}
	else if (node->type == COMMAND)
	{
		command = node_to_command(node, convert_env(minishell->env));
		execute_command(command, convert_env(minishell->env));
		free_cmd(command);
	}
	else
		return (exec_and_or(node, minishell));
}

int	prep_exec(t_node *node, t_minishell *minishell)
{
	if (exec(node, minishell) == 1)
		return (1);
	wait_all(3);
	return (0);
}