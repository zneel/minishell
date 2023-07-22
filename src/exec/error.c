/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:04:11 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/22 17:10:11 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	msg_error(char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	return (1);
}

void	free_cmd(t_command *cmd)
{
	free_mat(cmd->command);
	free(cmd);
}