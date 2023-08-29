/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:56:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/29 13:16:06 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	dup_out(t_command *cmd)
{
	int	fdout;

	if (cmd->mode & ~M_APPEND)
		fdout = open(cmd->file_out, O_WRONLY | O_TRUNC);
	else
		fdout = open(cmd->file_out, O_WRONLY | O_APPEND);
	if (!fdout)
		return (msg_error("No such file or directory", cmd->file_out));
	dup2(fdout, STDOUT_FILENO);
	close(fdout);
	return (0);
}

int	dup_in(t_command *cmd)
{
	int	fdin;

	if (cmd->mode & ~M_HERE_DOC)
		fdin = open(cmd->file_in, O_RDONLY, 0644);
	else
		fdin = open(FILE_HEREDOC, O_RDONLY, 0644);
	if (fdin == -1)
	{
		if (cmd->mode & ~M_HERE_DOC)
			return (msg_error("No such file or directory", cmd->file_in));
		else
			return (msg_error("No such file or directory", FILE_HEREDOC));
	}
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	return (0);
}