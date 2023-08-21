/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:47:47 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/21 16:03:01 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_command	*prep_cmd_pipe(t_node *node, t_minishell *minishell)
{
	t_command	*command;
	char		**env;

	env = convert_env(minishell->env);
	if (!env)
		return (NULL);
	command = node_to_command(node, env);
	free_mat(env);
	return (command);
}

int	check_middle(t_node *root, t_node *node)
{
	if (node->parent && node->parent->type == PIPE
		&& node->parent->right == node && node->parent != root)
		return (1);
	return (0);
}

int	exec_cmd_pipe(t_node *root, t_node *node, t_minishell *minishell,
		int pipefd[2][2])
{
	t_command	*command;

	command = prep_cmd_pipe(node, minishell);
	if (!command)
		return (1);
	if (node->parent && node->parent->type == PIPE
		&& node->parent->left == node)
	{
		if (pipe(pipefd[1]) == -1 || execute_first(command, minishell,
				pipefd) == 1)
			return (free(command), 1);
	}
	else if (check_middle(root, node))
	{
		if (pipe(pipefd[1]) == -1 || execute_middle(command, minishell,
				pipefd) == 1)
			return (free(command), 1);
	}
	else if (node->parent && node->parent == root
		&& node->parent->right == node)
	{
		if (execute_last(command, minishell, pipefd) == 1)
			return (free(command), 1);
	}
	return (free(command), 0);
}

int	execute_pipeline(t_node *root, t_node *node, t_minishell *minishell,
		int pipefd[2][2])
{
	if (!node)
		return (0);
	if (node->type == PIPE)
	{
		if (execute_pipeline(root, node->left, minishell, pipefd) == 1)
			return (1);
		if (execute_pipeline(root, node->right, minishell, pipefd) == 1)
			return (1);
	}
	if (node->type == COMMAND)
	{
		if (exec_cmd_pipe(root, node, minishell, pipefd) == 1)
			return (1);
	}
	return (0);
}
