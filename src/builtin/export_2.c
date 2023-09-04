/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:27:45 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/04 14:31:47 by mhoyer           ###   ########.fr       */
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

int	export_no_value(char **cmd, int i, t_minishell *minishell)
{
	char	*swap;
	char	**tmp;
	int		error;

	swap = ft_strjoin(cmd[i], "=");
	tmp = ft_separate(swap, '=');
	if (valid_name(minishell->env, tmp[0]) == 0)
		error = new_env(&minishell->env, tmp);
	else
		error = 2;
	free(swap);
	free(tmp);
	return (error);
}
