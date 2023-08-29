/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 09:54:16 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/29 12:56:11 by mhoyer           ###   ########.fr       */
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
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->builtin = NONE;
	cmd->file_in = "/dev/stdin";
	cmd->file_out = "/dev/stdout";
	cmd->mode = M_NO_MODE;
	cmd->has_good_file = true;
	cmd->has_path = false;
	cmd->command = convert_arg(node->args);
	if (cmd->command)
		cmd->has_path = ft_strrchr(cmd->command[0], '/');
	else
		cmd->has_path = false;
	return (cmd);
}

t_bool	open_file(t_command *cmd, t_list *redir)
{
	t_redirect	*red;

	if (!redir)
		return (true);
	red = (t_redirect *)redir->content;
	while (redir)
	{
		if (!check_in(red, cmd))
			return (false);
		else if (!check_out(red, cmd))
			return (false);
		redir = redir->next;
		if (!redir)
			break ;
		red = (t_redirect *)redir->content;
	}
	return (true);
}

t_command	*node_to_command(t_node *node, char **env)
{
	t_command	*command;

	command = init_command(node);
	if (!command)
		return (NULL);
	if (command->command)
		command->builtin = check_builtin(command->command[0]);
	if (command->command && command->builtin == NONE && !command->has_path)
		command->command = get_cmd(command->command, env);
	command->has_good_file = open_file(command, node->redir);
	return (command);
}
