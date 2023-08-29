/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:04:59 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/29 14:05:34 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	check_in(t_redirect *red, t_command *cmd)
{
	if (red->type == LESS)
	{
		if (access(red->file, F_OK | R_OK) == -1)
			return (msg_error("No such file or directory", red->file), false);
		cmd->file_in = red->file;
		cmd->mode &= ~M_HERE_DOC;
	}
	else if (red->type == HERE_DOC)
	{
		here_doc(red->file);
		cmd->mode &= ~M_NO_MODE;
		cmd->mode |= M_HERE_DOC;
	}
	return (true);
}

t_bool	check_out(t_redirect *red, t_command *cmd)
{
	int	fd;

	if (red->type == GREAT)
	{
		fd = open(red->file, O_CREAT | O_WRONLY, 0644);
		if (fd == -1)
			return (msg_error("No such file or directory", red->file), false);
		close(fd);
		cmd->file_out = red->file;
		cmd->mode &= ~M_APPEND;
	}
	else if (red->type == DGREAT)
	{
		fd = open(red->file, O_CREAT | O_WRONLY, 0644);
		if (fd == -1)
			return (msg_error("No such file or directory", red->file), false);
		close(fd);
		cmd->file_out = red->file;
		cmd->mode &= ~M_NO_MODE;
		cmd->mode |= M_APPEND;
	}
	return (true);
}
