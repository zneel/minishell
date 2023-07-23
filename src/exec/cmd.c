/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:52:56 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/23 10:12:33 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	dup_in(t_command *cmd)
{
	int fdin;

	if (cmd->has_heredoc == 0)
		fdin = open(cmd->file_in, O_RDONLY);
	else
	{
		here_doc(cmd->file_in);
		fdin = open(file_heredoc, O_RDONLY);
	}
	if (fdin == -1)
		exit(msg_error("Infile not found"));
	dup2(fdin, STDIN_FILENO);
	close(fdin);
}

void	dup_out(t_command *cmd)
{
	int	fdout;

	if (cmd->has_append == 0)
		fdout = open(cmd->file_out, O_WRONLY | O_TRUNC);
	else
		fdout = open(cmd->file_out, O_WRONLY | O_APPEND);
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
}

void	execute_command(t_command *cmd, t_minishell *minishell)
{
	pid_t pid;
	char	**env;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		dup_in(cmd);
		dup_out(cmd);
		env = convert_env(minishell->env);
		if (!env)
			exit (1);
		if ((cmd->command == NULL || cmd->command[0] == NULL) || (execve(cmd->command[0], cmd->command, env) == -1))
		{
			free_cmd(cmd);
			free_mat(env);
			free_minishell(minishell);
			exit(msg_error("Cmd not found"));
		}
	}
	unlink(file_heredoc);
}
