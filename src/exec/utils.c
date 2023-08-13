/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:54:16 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/14 12:07:19 by ebouvier         ###   ########.fr       */
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
	char		**splited;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	splited = ft_split(node->data, " ");
	if (!splited)
		return (NULL);
	if (!ft_strrchr(splited[0], '/'))
		command->has_path = false;
	else
		command->has_path = true;
	command->builtin = check_builtin(splited[0]);
	if (command->builtin == NONE && command->has_path == false)
	{
		free_mat(splited);
		command->command = get_cmd(node->data, env);
	}
	else
		command->command = splited;
	command = init_file(command);
	command = open_file(command, node);
	return (command);
}
