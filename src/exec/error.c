/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:04:11 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/24 18:08:41 by mhoyer           ###   ########.fr       */
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
