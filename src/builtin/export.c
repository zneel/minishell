/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 10:54:01 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/31 23:28:08 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	valid_name(t_kv *env, char *new)
{
	int	i;

	i = -1;
	if (!ft_isalpha(new[0]) && new[0] != '_')
		return (2);
	while (new[++i])
	{
		if (!ft_isalnum(new[i]) && new[i] != '_')
			return (2);
	}
	while (env)
	{
		if (is_same(env->key, new))
			return (1);
		env = env->next;
	}
	return (0);
}

int	new_env(t_kv **env, char **tmp)
{
	t_kv	*new;

	new = ft_lstnew_env(tmp[0], tmp[1]);
	if (!new)
		return (1);
	ft_lstadd_back_env(env, new);
	return (0);
}

int	export_annexe(int i, char **cmd, t_minishell *minishell)
{
	char	**tmp;
	int		error;

	error = 1;
	tmp = ft_separate(cmd[i], '=');
	if (!tmp)
		return (valid_name(minishell->env, cmd[i]));
	if (!tmp || !tmp[0] || !tmp[1])
		return (error);
	if (tmp && (!tmp[0] || !tmp[1]))
		return (free(tmp), free(tmp[0]), free(tmp[1]), 1);
	if (valid_name(minishell->env, tmp[0]) == 1)
		error = replace_env(minishell->env, tmp);
	else if (valid_name(minishell->env, tmp[0]) == 0)
		error = new_env(&minishell->env, tmp);
	else
		error = 2;
	if (error == 2)
	{
		free(tmp[0]);
		free(tmp[1]);
	}
	free(tmp);
	return (error);
}

int	test_export(t_command *cmd, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (cmd->command && *cmd->command && cmd->command[++i])
	{
		if (export_annexe(i, cmd->command, minishell) == 2)
		{
			ft_dprintf(2, "minishell: ");
			ft_dprintf(2, "`%s\":", cmd->command[i]);
			ft_dprintf(2, " not a valid identifier\n");
			return (1);
		}
	}
	return (0);
}

int	export(t_command *cmd, t_minishell *minishell)
{
	t_kv	*parc;
	t_kv	*mem_parc;

	if (cmd->command && *cmd->command && cmd->command[1] == NULL)
	{
		parc = ft_lstcpy_env(minishell->env);
		if (!parc)
			return (1);
		mem_parc = parc;
		ft_lstsort_env(parc);
		while (parc)
		{
			ft_printf("export %s=%s\n", parc->key, parc->value);
			parc = parc->next;
		}
		return (ft_lstclear_env(&mem_parc, free), 0);
	}
	return (test_export(cmd, minishell));
}
