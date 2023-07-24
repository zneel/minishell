/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:37:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/24 22:50:45 by mhoyer           ###   ########.fr       */
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
	if (cmd->command[1] && ft_strncmp(cmd->command[1], "-n", 2) == 0)
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
