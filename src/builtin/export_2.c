/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:27:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/31 23:28:22 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	replace_env(t_kv *env, char **tmp)
{
	while (env)
	{
		if (is_same(env->key, tmp[0]))
		{
			free(env->value);
			free(tmp[0]);
			env->value = ft_calloc(sizeof(char), ft_strlen(tmp[1]) + 1);
			if (!env->value)
				return (1);
			ft_strlcpy(env->value, tmp[1], ft_strlen(tmp[1]) + 1);
			free(tmp[1]);
			return (0);
		}
		env = env->next;
	}
	return (0);
}
