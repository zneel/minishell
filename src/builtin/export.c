/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:54:01 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/11 11:45:37 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_disp(t_kv *env, char *new)
{
	int	i;

	i = -1;
	while (new[++i])
	{
		if (ft_isalpha(new[i]) == 0)
			return (2);
	}
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

int	export_annexe(int i, char **argv, t_minishell *minishell)
{
	char	**tmp;
	int		error;

	tmp = ft_separate(argv[i], '=');
	if (!tmp || !tmp[0] || !tmp[1])
		return (1);
	if (check_disp(minishell->env, tmp[0]) == 1)
		error = replace_env(minishell->env, tmp);
	else if (check_disp(minishell->env, tmp[0]) == 0)
		error = new_env(&minishell->env, tmp);
	else
		error = 1;
	if (error)
	{
		free(tmp[0]);
		free(tmp[1]);
	}
	free(tmp);
	return (error);
}

int	export(int argc, char **argv, t_minishell *minishell)
{
	int		i;
	t_kv	*parc;

	i = 0;
	(void)argc;
	if (argv && *argv && argv[1] == NULL)
	{
		parc = minishell->env;
		while (parc)
		{
			printf("export %s=%s\n", parc->key, parc->value);
			parc = parc->next;
		}
	}
	while (argv && *argv && argv[++i] && argv[i][0] != '=')
	{
		if (export_annexe(i, argv, minishell))
			return (1);
	}
	return (0);
}
