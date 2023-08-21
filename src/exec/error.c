/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:04:11 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/19 14:57:28 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_failed(t_command *cmd, char **env, t_minishell *minishell,
		int status)
{
	if ((cmd->builtin && cmd->has_path == true) || cmd->builtin == NONE)
	{
		if (cmd->has_path == false)
			msg_error("command not found", cmd->command[0]);
		else
			msg_error("No such file or directory", cmd->command[0]);
	}
	free_mat(env);
	free_minishell(minishell);
	if (cmd->builtin)
	{
		free(cmd);
		if (status == 1)
			exit(126);
		exit(0);
	}
	free(cmd);
	exit(127);
}

int	msg_error(char *str, char *error)
{
	ft_dprintf(2, "minishell: %s: %s\n", error, str);
	return (1);
}

void	nothing(void *x)
{
	(void)x;
}

void	free_minishell(t_minishell *minishell)
{
	rl_clear_history();
	ast_delete(minishell->root);
	ft_lstclear(&minishell->pids, nothing);
	ft_lstclear_env(&minishell->env, free);
	close(minishell->std[0]);
	close(minishell->std[1]);
}
