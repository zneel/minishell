/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_for_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:56:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/24 18:08:28 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	dup_for_out(t_command *cmd, t_minishell *minishell)
{
	int	fdout;

	if (cmd->has_append == false)
		fdout = open(cmd->file_out, O_WRONLY | O_TRUNC);
	else
		fdout = open(cmd->file_out, O_WRONLY | O_APPEND);
	if (!fdout)
		exit(free_and_msg("No such file or directory", cmd->file_out, minishell,
				cmd));
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
}

void	dup_for_in(t_command *cmd, t_minishell *minishell)
{
	int	fdin;

	if (cmd->has_heredoc == false)
		fdin = open(cmd->file_in, O_RDONLY, 0644);
	else
		fdin = open(FILE_HEREDOC, O_RDONLY, 0644);
	if (fdin == -1)
	{
		if (cmd->has_heredoc == false)
			exit(free_and_msg("No such file or directory", cmd->file_in,
					minishell, cmd));
		else
			exit(free_and_msg("No such file or directory", FILE_HEREDOC,
					minishell, cmd));
	}
	dup2(fdin, STDIN_FILENO);
	close(fdin);
}
