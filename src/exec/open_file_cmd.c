/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:04:59 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/18 14:48:27 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_command	*open_infile(t_command *command, t_node *node)
{
	t_node	*parc_infile;

	parc_infile = node->left;
	while (parc_infile && parc_infile->left)
	{
		if (parc_infile->type == HERE_DOC)
			here_doc(parc_infile->data[0]);
		parc_infile = parc_infile->left;
	}
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
	return (command);
}

t_node	*try_access_out(t_node *parc_outfile, int *next_out)
{
	int	fd;

	if (access(parc_outfile->data[0], F_OK | R_OK) == -1)
	{
		fd = open(parc_outfile->data[0], O_CREAT, 0644);
		if (fd == -1)
			return (NULL);
		close(fd);
	}
	if (parc_outfile->right)
		parc_outfile = parc_outfile->right;
	else
		*next_out = 0;
	return (parc_outfile);
}

t_command	*open_outfile(t_command *command, t_node *node)
{
	int		next_out;
	t_node	*parc_outfile;

	parc_outfile = node->right;
	next_out = 1;
	while (next_out && parc_outfile)
	{
		parc_outfile = try_access_out(parc_outfile, &next_out);
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
	return (command);
}

t_command	*open_file(t_command *command, t_node *node)
{
	command = open_infile(command, node);
	command = open_outfile(command, node);
	return (command);
}
