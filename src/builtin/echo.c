/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:37:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 08:09:55 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	echo(int argc, char **argv)
{
	int	i;
	int	endl;

	if (argc < 1 || argv[0] == NULL)
		return (1);
	endl = 0;
	if (argv[1] && ft_strncmp(argv[1], "-n", 2) == 0)
		endl = 1;
	i = endl;
	while (argv[++i])
	{
		if (i - 1 != endl)
			printf(" ");
		printf("%s", argv[i]);	
	}
	if (!endl)
		printf("\n");
	return (0);
}
