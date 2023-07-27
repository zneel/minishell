/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:14:40 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/27 11:02:41 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	annexe_search(t_command *cmd, t_minishell *minishell)
{
	if (cmd->builtin == UNSET)
	{
		if (unset(cmd, minishell))
			return (1);
	}
	else if (cmd->builtin == CD)
	{
		if (cd(cmd, minishell))
			return (1);
	}
	return (0);
}

int	search_builtin(t_command *cmd, t_minishell *minishell)
{
	if (cmd->builtin == ECHO)
	{
		if (echo(cmd))
			return (1);
	}
	else if (cmd->builtin == PWD)
	{
		if (pwd(*minishell))
			return (1);
	}
	else if (cmd->builtin == EXPORT)
	{
		if (export(cmd, minishell))
			return (1);
	}
	else if (cmd->builtin == ENV)
	{
		if (print_env(*minishell))
			return (1);
	}
	return (annexe_search(cmd, minishell));
}

int	prep_exec_builtin(t_command *cmd)
{
	int	fdin;
	int	fdout;

	if (cmd->has_heredoc == true)
		here_doc(cmd->file_in);
	if (cmd->has_append == false)
		fdout = open(cmd->file_out, O_WRONLY | O_TRUNC, 0644);
	else
		fdout = open(cmd->file_out, O_WRONLY | O_APPEND, 0644);
	if (cmd->has_heredoc == false)
		fdin = open(cmd->file_in, O_RDONLY, 0644);
	else
		fdin = open(FILE_HEREDOC, O_RDONLY, 0644);
	if (fdin == -1)
	{
		if (cmd->has_heredoc == false)
			return (msg_error("No such file or directory", cmd->file_in));
		else
			return (msg_error("No such file or directory", FILE_HEREDOC));
	}
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
	close(fdin);
	close(fdout);
	return (0);
}

int	end_builtin(int stdin, int stdout)
{
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
	return (0);
}

int	exec_builtin(t_command *cmd, t_minishell *minishell, int prep)
{
	int	stdin;
	int	stdout;

	stdin = minishell->std[0];
	stdout = minishell->std[1];
	if (prep && prep_exec_builtin(cmd))
		return (1);
	if (search_builtin(cmd, minishell))
		return (1);
	if (prep && end_builtin(stdin, stdout))
		return (1);
	return (0);
}
