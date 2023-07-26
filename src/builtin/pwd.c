/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:41:40 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/27 11:01:36 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	pwd(t_minishell minishell)
{
	char	*dir;

	while (minishell.env)
	{
		if (get_env(minishell, "PWD="))
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
