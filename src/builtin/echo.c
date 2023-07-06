/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:37:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 07:37:29 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strcmp(char *to_cmp, char *model)
{
	int	i;

	i = 0;
	while (to_cmp[i] && model[i] && to_cmp[i] == model[i])
		i++;
	return (to_cmp[i] - model[i]);
}

void	echo(char **param)
{
	int	i;
	int	endl;

	endl = 0;
	if (param[1] && ft_strcmp(param[1], "-n") == 0)
		endl = 1;
	i = endl;
	while (param[++i])
	{
		if (i - 1 != endl)
			printf(" ");
		printf("%s", param[i]);	
	}
	if (!endl)
		printf("\n");
}

/*#include <stdlib.h>
int	main(int ac, char **av)
{
	if (ac == 0)
		return (0);
	echo(av);
	return (0);
}*/