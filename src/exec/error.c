/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:04:11 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/23 19:15:44 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	msg_error(char *str, char *error)
{
	ft_dprintf(2, "%s: %s\n", error, str);
	return (1);
}

void	free_cmd(t_command *cmd)
{
	free_mat(cmd->command);
	free(cmd);
}

void	free_minishell(t_minishell *minishell)
{
	ft_lstclear_env(&minishell->env, free);
}