/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:54:01 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/08 10:31:50 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_disp(t_kv *env, char *new)
{
	while (env)
	{
		if (ft_strncmp(env->key, new, ft_strlen(new)) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	replace_env(t_kv *env, char **tmp)
{
	while (env)
	{
		if (ft_strncmp(env->key, tmp[0], ft_strlen(tmp[0])) == 0)
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

int	new_env(t_kv **env, char **tmp)
{
	t_kv 	*new;

	new = ft_lstnew_env(tmp[0], tmp[1]);
	if (!new)
		return (1);
	ft_lstadd_back_env(env, new);
	return (0);
}

int	export(int argc, char **argv, t_minishell *minishell)
{
	char	**tmp;
	int		i;

	i = 0;
	(void)argc;
	while (argv[++i] && argv[i][0] != '=')
	{
		tmp = ft_separate(argv[i], '=');
		if (!tmp || !tmp[0] || !tmp[1])
			return (1);
		if (check_disp(minishell->env, tmp[0]))
		{
			if (replace_env(minishell->env, tmp))
				return (1);
		}
		else
		{
			if (new_env(&minishell->env, tmp))
				return (1);
		}
		free(tmp);
	}
	return (0);
}
