/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:04:11 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/24 19:18:37 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_failed(t_command *cmd, char **env, t_minishell *minishell)
{
	msg_error("command not found", cmd->command[0]);
	free_cmd(cmd);
	free_mat(env);
	free_minishell(minishell);
	exit(1);
}

int	msg_error(char *str, char *error)
{
	ft_dprintf(2, "minishell: %s: %s\n", error, str);
	return (1);
}

void	free_cmd(t_command *cmd)
{
	free_mat(cmd->command);
	free(cmd);
}

void	nothing(void *x)
{
	(void)x;
}

void	free_minishell(t_minishell *minishell)
{
	ft_lstclear(&minishell->pids, nothing);
	ft_lstclear_env(&minishell->env, free);
}
