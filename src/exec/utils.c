/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:54:16 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/18 14:49:02 by ebouvier         ###   ########.fr       */
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

t_command	*init_file(t_command *command)
{
	command->file_in = "/dev/stdin";
	command->file_out = "/dev/stdout";
	command->has_heredoc = false;
	command->has_append = false;
	command->has_infile = false;
	command->has_outfile = false;
	return (command);
}

t_command	*node_to_command(t_node *node, char **env)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	if (!ft_strrchr(node->data[0], '/'))
		command->has_path = false;
	else
		command->has_path = true;
	command->builtin = check_builtin(node->data[0]);
	if (command->builtin == NONE && command->has_path == false)
	{
		free_mat(node->data);
		command->command = get_cmd(node->data, env);
	}
	else
		command->command = node->data;
	command = init_file(command);
	command = open_file(command, node);
	return (command);
}
