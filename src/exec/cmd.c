/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:52:56 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/01 16:57:02 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signals.h"

void	sub_execute(t_command *cmd, t_minishell *minishell)
{
	char	**env;
	t_bool	ok;

	env = convert_env(minishell->env);
	ok = dup_in(cmd);
	dup_out(cmd);
	close_if(minishell->m_fd[1]);
	close_if(minishell->m_fd[0]);
	if (ok)
	{
		free_command(cmd);
		free_mat(env);
		free_minishell(minishell);
		exit(1);
	}
	if (execve(cmd->command[0], cmd->command, env) == -1)
		exec_failed(cmd, env, minishell, 1);
}

void	execute_command(t_command *cmd, t_minishell *minishell)
{
	pid_t	pid;

	if (g_sigint == 1)
		return ;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		sub_execute(cmd, minishell);
	else
	{
		signal(SIGINT, sig_handler_job);
		signal(SIGQUIT, sig_handler_job);
		ft_lstadd_back(&minishell->pids, ft_lstnew(&pid));
	}
}
