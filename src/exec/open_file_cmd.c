/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:04:59 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/25 17:06:48 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	try_can_exec(t_command *command, t_node **parc_infile)
{
	while ((command->can_exec && (*parc_infile) && (*parc_infile)->left)
		|| (!command->can_exec && (*parc_infile)))
	{
		if ((*parc_infile)->type == HERE_DOC)
			here_doc((*parc_infile)->data[0]);
		if ((*parc_infile)->type == LESS)
		{
			if (access((*parc_infile)->data[0], F_OK | R_OK) == -1)
				return (msg_error("No such file or directory",
						(*parc_infile)->data[0]));
		}
		(*parc_infile) = (*parc_infile)->left;
	}
	return (0);
}

int	open_infile(t_command *command, t_node *node)
{
	t_node	*parc_infile;

	parc_infile = node->left;
	if (try_can_exec(command, &parc_infile))
		return (1);
	if (parc_infile && parc_infile->type == LESS)
	{
		command->file_in = parc_infile->data[0];
		command->has_infile = true;
	}
	else if (parc_infile && parc_infile->type == HERE_DOC)
	{
		command->file_in = parc_infile->data[0];
		command->has_heredoc = true;
	}
	return (0);
}

t_node	*try_access_out(t_node *parc_outfile, int *next_out, t_bool creat)
{
	int	fd;

	if (access(parc_outfile->data[0], F_OK | R_OK) == -1)
	{
		fd = open(parc_outfile->data[0], O_CREAT, 0644);
		if (fd == -1 && creat == false)
			return (msg_error("No such file or directory", parc_outfile->data[0]), NULL);
		close(fd);
	}
	if (parc_outfile->right)
		parc_outfile = parc_outfile->right;
	else
		*next_out = 0;
	return (parc_outfile);
}

void	creat_outfile(int next_out, t_node *parc_outfile)
{
	while (next_out && parc_outfile)
		parc_outfile = try_access_out(parc_outfile, &next_out, true);
}

int	open_outfile(t_command *command, t_node *node)
{
	int		next_out;
	t_node	*parc_outfile;

	parc_outfile = node->right;
	next_out = 1;
	creat_outfile(next_out, parc_outfile);
	while (next_out && parc_outfile)
	{
		parc_outfile = try_access_out(parc_outfile, &next_out, false);
		if (!parc_outfile)
			return (1);
	}
	if (parc_outfile && parc_outfile->type == GREAT)
	{
		command->file_out = parc_outfile->data[0];
		command->has_outfile = true;
	}
	else if (parc_outfile && parc_outfile->type == DGREAT)
	{
		command->file_out = parc_outfile->data[0];
		command->has_append = true;
	}
	return (0);
}
