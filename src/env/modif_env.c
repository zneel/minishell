/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 09:44:17 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/01 12:15:24 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	modif_env(t_minishell *minishell, char *key_s, char *value_m)
{
	t_kv	*env;

	env = minishell->env;
	if (!value_m)
		return (1);
	while (env)
	{
		if (ft_strncmp(env->key, key_s, ft_strlen(key_s)) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value_m);
			if (!env->value)
				return (1);
		}
		env = env->next;
	}
	return (0);
}
