/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:18:45 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/31 14:18:43 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_command	*init_command(t_node *node, t_minishell *minishell)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->builtin = NONE;
	cmd->file_in = "/dev/stdin";
	cmd->file_out = "/dev/stdout";
	cmd->mode = M_NO_MODE;
	cmd->error = ERR_NO_ERR;
	cmd->has_good_file = true;
	cmd->has_path = false;
	if (node->args)
		expand_args(&node->args, minishell);
	if (node->redirs)
		expand_redirs(&node->redirs, minishell);
	cmd->command = convert_arg(node->args);
	if (cmd->command)
		cmd->has_path = ft_strrchr(cmd->command[0], '/');
	else
		cmd->has_path = false;
	return (cmd);
}

t_bool	open_file(t_command *cmd, t_list *redirs)
{
	t_redirect	*red;

	if (!redirs)
		return (1);
	red = (t_redirect *)redirs->content;
	while (redirs)
	{
		if (!check_in(red, cmd))
			return (false);
		if (!check_out(red, cmd))
			return (false);
		redirs = redirs->next;
		if (!redirs)
			break ;
		red = (t_redirect *)redirs->content;
	}
	return (true);
}

t_command	*node_to_command(t_node *node, char **env, t_minishell *ms)
{
	t_command	*command;

	command = init_command(node, ms);
	if (!command)
		return (NULL);
	if (command->command)
		command->builtin = check_builtin(command->command[0]);
	if (command->command && command->builtin == NONE && !command->has_path)
		command->command = get_cmd(command->command, env);
	command->has_good_file = open_file(command, node->redirs);
	return (command);
}
