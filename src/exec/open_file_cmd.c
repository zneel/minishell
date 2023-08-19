/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:04:59 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/21 15:56:01 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	try_can_excec(t_command *command, t_node **parc_infile)
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
	if (try_can_excec(command, &parc_infile))
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

void	open_outfile(t_command *command, t_node *node)
{
	int		next_out;
	t_node	*parc_outfile;

	parc_outfile = node->right;
	next_out = 1;
	while (next_out && parc_outfile)
		parc_outfile = try_access_out(parc_outfile, &next_out);
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
}

void	open_file(t_command *command, t_node *node)
{
	if (open_infile(command, node))
	{
		command->can_exec = false;
		return ;
	}
	open_outfile(command, node);
}
