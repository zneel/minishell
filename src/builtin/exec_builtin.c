/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 22:14:40 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/01 11:00:03 by ebouvier         ###   ########.fr       */
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
	else if (cmd->builtin == EXIT)
	{
		if (ft_exit(cmd, minishell))
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
		if (pwd(minishell))
			return (1);
	}
	else if (cmd->builtin == EXPORT)
	{
		if (export(cmd, minishell))
			return (1);
	}
	else if (cmd->builtin == ENV)
	{
		if (print_env(minishell))
			return (1);
	}
	return (annexe_search(cmd, minishell));
}

int	prep_exec_builtin(t_command *cmd)
{
	return (dup_in(cmd) || dup_out(cmd));
}

int	end_builtin(int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	return (0);
}

int	exec_builtin(t_command *cmd, t_minishell *minishell, int prep)
{
	if (prep && prep_exec_builtin(cmd))
		return (1);
	if (search_builtin(cmd, minishell))
		return (1);
	if (prep && end_builtin(minishell->m_fd))
		return (1);
	return (0);
}
