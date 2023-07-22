/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:47:47 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/22 17:11:41 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_cmd_pipe(t_node *root, t_node *node, char **env,
		int pipefd[2][2])
{
	t_command	*command;

	command = node_to_command(node, env);
	if (!command)
		return (free_cmd(command), 1);
	if (node->parent && node->parent->type == PIPE
		&& node->parent->left == node)
	{
		if (pipe(pipefd[1]) == -1 || execute_first(command, env, pipefd) == 1)
			return (free_cmd(command), 1);
	}
	else if (node->parent && node->parent->type == PIPE
			&& node->parent->right == node && node->parent != root)
	{
		if (pipe(pipefd[1]) == -1 || execute_middle(command, env, pipefd) == 1)
			return (free_cmd(command), 1);
	}
	else if (node->parent && node->parent == root
			&& node->parent->right == node)
	{
		if (execute_last(command, env, pipefd) == 1)
			return (free_cmd(command), 1);
	}
	return (free_cmd(command), 0);
}

int	execute_pipeline(t_node *root, t_node *node, char **env,
		int pipefd[2][2])
{
	if (!node)
		return (0);
	if (node->type == PIPE)
	{
		if (execute_pipeline(root, node->left, env, pipefd) == 1)
			return (1);
		if (execute_pipeline(root, node->right, env, pipefd) == 1)
			return (1);
	}
	if (node->type == COMMAND)
	{
		if (exec_cmd_pipe(root, node, env, pipefd) == 1)
			return (1);
	}
	return (0);
}
