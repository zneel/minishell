/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:54:16 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/25 17:06:54 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_pipes(int pipefd[2][2])
{
	pipefd[0][0] = -1;
	pipefd[0][1] = -1;
	pipefd[1][0] = -1;
	pipefd[1][1] = -1;
}

void	close_if(int fd)
{
	if (fd >= 0)
		close(fd);
}

t_command	*init_command(t_node *node)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->builtin = NONE;
	command->file_in = "/dev/stdin";
	command->file_out = "/dev/stdout";
	command->has_heredoc = false;
	command->has_append = false;
	command->has_infile = false;
	command->has_good_infile = true;
	command->has_good_outfile = true;
	command->has_outfile = false;
	command->has_path = false;
	command->command = node->data;
	command->can_exec = node->data != NULL;
	command->has_path = command->can_exec && ft_strrchr(node->data[0], '/');
	return (command);
}

t_command	*node_to_command(t_node *node, char **env)
{
	t_command	*command;

	command = init_command(node);
	if (!command)
		return (NULL);
	if (command->can_exec)
		command->builtin = check_builtin(node->data[0]);
	if (command->can_exec && command->builtin == NONE && !command->has_path)
		command->command = get_cmd(node->data, env);
	open_file(command, node);
	return (command);
}

void	open_file(t_command *command, t_node *node)
{
	if (open_infile(command, node))
	{
		command->has_good_infile = false;
		return ;
	}
	if (open_outfile(command, node))
	{
		command->has_good_outfile = false;
		return ;
	}
}
