/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:04:11 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/30 18:24:55 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_command(t_command *cmd)
{
	free_mat(cmd->command);
	free(cmd);
}

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
		free_command(cmd);
		if (status == 1)
			exit(126);
		exit(0);
	}
	free_command(cmd);
	exit(127);
}

int	msg_error(char *str, char *error)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", error, str);
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
