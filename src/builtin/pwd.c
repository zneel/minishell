/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:41:40 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 08:07:43 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	pwd(int argc, char **argv, t_minishell minishell)
{
	char	*dir;

	(void)argc;
	(void)argv;
	while (minishell.env)
	{
		if (strncmp(minishell.env->key, "PWD", ft_strlen("PWD")) == 0)
			return (printf("%s\n", minishell.env->value), 0);
		minishell.env = minishell.env->next;
	}
	dir = getcwd(NULL, 0);
	if (dir == NULL)
		return (1);
	printf("%s\n", dir);
	free(dir);
	return (0);
}
