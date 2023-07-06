/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:41:40 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 12:16:15 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	pwd(int argc, char **argv, t_minishell minishell)
{
	char	*dir;

	(void)argc;
	(void)argv;
	dir = get_env(minishell.env, "PWD=");
	if (dir == NULL)
	{
		dir = getcwd(NULL, 0);
		if (dir == NULL)
			return (1);
		printf("%s\n", dir);
		free(dir);
		return (0);
	}
	printf("%s\n", &dir[4]);
	return (0);
}
