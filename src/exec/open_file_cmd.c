/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:04:59 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/31 11:28:07 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	check_in(t_redirect *red, t_command *cmd)
{
	if (red->type == LESS && red->file)
	{
		if (access(red->file, F_OK) == -1)
			return (msg_error("No such file or directory", red->file), false);
		if (access(red->file, R_OK) == -1)
			return (msg_error("Permission denied", red->file), false);
		cmd->file_in = red->file;
		cmd->mode |= M_IN;
		cmd->mode &= ~M_HERE_DOC;
	}
	else if (red->type == HERE_DOC && red->file)
	{
		here_doc(red->file);
		cmd->mode &= ~M_NO_MODE;
		cmd->mode &= M_IN;
		cmd->mode |= M_HERE_DOC;
	}
	return (1);
}

t_bool	check_out(t_redirect *red, t_command *cmd)
{
	int	fd;

	if (red->type == GREAT && red->file)
	{
		fd = open(red->file, O_CREAT | O_WRONLY, 0644);
		close(fd);
		if (access(red->file, F_OK) == -1)
			return (msg_error("No such file or directory", red->file), false);
		if (access(red->file, R_OK) == -1)
			return (msg_error("Permission denied", red->file), false);
		cmd->file_out = red->file;
		cmd->mode |= M_OUT;
		cmd->mode &= ~M_APPEND;
	}
	else if (red->type == DGREAT && red->file)
	{
		fd = open(red->file, O_CREAT | O_WRONLY, 0644);
		close(fd);
			if (access(red->file, F_OK) == -1)
			return (msg_error("No such file or directory", red->file), false);
		if (access(red->file, R_OK) == -1)
			return (msg_error("Permission denied", red->file), false);
		cmd->file_out = red->file;
		cmd->mode &= ~M_OUT;
		cmd->mode |= M_APPEND;
	}
	return (1);
}
