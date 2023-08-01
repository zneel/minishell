/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 09:34:27 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/01 10:54:49 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_minishell *minishell, char *to_search)
{
	t_kv	*env;

	env = minishell->env;
	while (env)
	{
		if (strncmp(env->key, to_search, ft_strlen(to_search)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
