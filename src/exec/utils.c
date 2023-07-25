/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:54:16 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/25 11:29:20 by mhoyer           ###   ########.fr       */
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

void	wait_all(t_minishell *minishell)
{
	t_list	*parc;

	parc = minishell->pids;
	while (parc)
	{
		waitpid(-1, &minishell->last_status, 0);
		parc = parc->next;
	}
}

t_command	*open_file(t_command *command, t_node *node)
{
	int	fd;

	if (node->right && node->right->type == GREAT)
		command->file_out = node->right->data;
	else if (node->right && node->right->type == DGREAT)
	{
		command->file_out = node->right->data;
		command->has_append = 1;
	}
	if (access(command->file_out, F_OK | R_OK) == -1)
	{
		fd = open(command->file_out, O_CREAT, 0644);
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
	command->command = get_cmd(node->data, env);
	command->builtin = check_builtin(command);
	command->file_in = "/dev/stdin";
	command->file_out = "/dev/stdout";
	command->has_heredoc = 0;
	command->has_append = 0;
	if (node->left && node->left->type == LESS)
		command->file_in = node->left->data;
	else if (node->left && node->left->type == HERE_DOC)
	{
		command->file_in = node->left->data;
		command->has_heredoc = 1;
	}
	command = open_file(command, node);
	return (command);
}
