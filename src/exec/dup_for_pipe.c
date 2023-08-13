/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_for_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:56:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/13 17:09:44 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	dup_for_out(t_command *cmd)
{
	int	fdout;

	if (cmd->has_append == false)
		fdout = open(cmd->file_out, O_WRONLY | O_TRUNC);
	else
		fdout = open(cmd->file_out, O_WRONLY | O_APPEND);
	if (!fdout)
		exit(msg_error("No such file or directory", cmd->file_out));
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
}

void	dup_for_in(t_command *cmd)
{
	int	fdin;

	if (cmd->has_heredoc == false)
		fdin = open(cmd->file_in, O_RDONLY, 0644);
	else
		fdin = open(FILE_HEREDOC, O_RDONLY, 0644);
	if (fdin == -1)
	{
		if (cmd->has_heredoc == false)
			exit(msg_error("No such file or directory", cmd->file_in));
		else
			exit(msg_error("No such file or directory", FILE_HEREDOC));
	}
	dup2(fdin, STDIN_FILENO);
	close(fdin);
}
