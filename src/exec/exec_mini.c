/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:16:03 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/18 15:01:30 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_cmd(t_node *node, t_minishell *minishell)
{
	char		**env;
	t_command	*command;

	env = convert_env(minishell->env);
	if (!env)
		return (1);
	command = node_to_command(node, env);
	free_mat(env);
	if (command->builtin != NONE)
	{
		if (command->builtin != W_PATH)
			minishell->last_status = exec_builtin(command, minishell, true);
		else
			return (msg_error("No such file or directory",
								command->command[0]));
	}
	else
	{
		execute_command(command, minishell);
		wait_all(minishell);
	}
	free(command);
	return (0);
}

int	exec_or(t_node *node, t_minishell *minishell)
{
	if (exec(node->left, minishell) == 1)
		return (1);
	if (minishell->last_status != 0)
	{
		if (exec(node->right, minishell) == 1)
			return (1);
	}
	return (0);
}

int	exec_and(t_node *node, t_minishell *minishell)
{
	if (exec(node->left, minishell) == 1)
		return (1);
	if (minishell->last_status == 0)
	{
		if (exec(node->right, minishell) == 1)
			return (1);
	}
	return (0);
}

int	exec_pipe(t_node *node, t_minishell *minishell, int pipefd[2][2])
{
	if (execute_pipeline(node, node, minishell, pipefd) == 1)
		return (1);
	wait_all(minishell);
	return (0);
}

int	init_exec(t_node *node, int pipefd[2][2])
{
	init_pipes(pipefd);
	if (!node)
		return (0);
	return (1);
}
