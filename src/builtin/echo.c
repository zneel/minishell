/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:37:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/30 18:52:13 by mhoyer           ###   ########.fr       */
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
			printf(" ");
		printf("%s", cmd->command[i]);
	}
	if (!endl)
		printf("\n");
	return (0);
}
