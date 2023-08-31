/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:37:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/30 20:02:12 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	echo(t_command *cmd)
{
	int	i;
	int	endl;

	if (!cmd->command || !cmd->command[0])
		return (1);
	endl = 0;
	if (cmd->command[1] && is_same(cmd->command[1], "-n"))
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
