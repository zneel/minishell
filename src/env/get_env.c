/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 09:34:27 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/24 13:23:47 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_minishell *minishell, char *to_search)
{
	t_kv	*env;
	size_t	to_search_len;

	if (!to_search)
		return (NULL);
	to_search_len = ft_strlen(to_search);
	env = minishell->env;
	while (env)
	{
		if (ft_strlen(env->key) == to_search_len && ft_strncmp(env->key,
				to_search, ft_strlen(env->key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
