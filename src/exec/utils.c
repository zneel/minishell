/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:54:16 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/23 09:44:13 by mhoyer           ###   ########.fr       */
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

void	wait_all(int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		wait(NULL);
		i++;
	}
}

t_command	*open_file(t_command *command, t_node *node)
{
	int	fd;

	if (node->right && node->right->type == GREAT)
	{
		command->file_out = node->right->raw_command;
		command->has_append = 0;
	}
	else if (node->right && node->right->type == DGREAT)
	{
		command->file_out = node->right->raw_command;
		command->has_append = 1;
	}
	if (access(command->file_out, F_OK | R_OK) == -1)
	{
		fd = open(command->file_out, O_CREAT, 0777);
		if (fd == -1)
			return (NULL);
		close(fd);
	}
	return (command);
}

t_command	*node_to_command(t_node *node, char **env)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->command = get_cmd(node->raw_command, env);
	command->file_in = "/dev/stdin";
	command->file_out = "/dev/stdout";
	if (node->left && node->left->type == LESS)
	{
		command->file_in = node->left->raw_command;
		command->has_heredoc = 0;
	}
	else if (node->left && node->left->type == DLESS)
	{
		command->file_in = node->left->raw_command;
		command->has_heredoc = 1;
	}
	command = open_file(command, node);
	return (command);
}
