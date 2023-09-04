/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:37:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/04 13:07:45 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

#include "builtin.h"

t_bool	is_n(char *ext)
{
	int	i;

	i = 1;
	if (ext[0] != '-')
		return (false);
	while (ext[i] && ext[i] == 'n')
		i++;
	if (ext[i] == '\0')
		return (true);
	return (false);
}

int	echo(t_command *cmd)
{
	int	i;
	int	endl;

	if (!cmd->command || !cmd->command[0])
		return (1);
	endl = 0;
	if (cmd->command[1] && is_n(cmd->command[1]))
		endl = 1;
	i = endl;
	while (cmd->command[++i])
	{
		if (i - 1 != endl)
			ft_printf(" ");
		ft_printf("%s", cmd->command[i]);
	}
	if (!endl)
		ft_printf("\n");
	return (0);
}
