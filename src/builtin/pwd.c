/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:41:40 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/01 10:50:53 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	pwd(t_minishell *minishell)
{
	char	*dir;
	t_kv	*env;

	env = minishell->env;
	while (env)
	{
		if (get_env(minishell, "PWD="))
			return (printf("%s\n", env->value), 0);
		env = env->next;
	}
	dir = getcwd(NULL, 0);
	if (dir == NULL)
		return (1);
	printf("%s\n", dir);
	free(dir);
	return (0);
}
