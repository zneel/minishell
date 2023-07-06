/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:05:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 13:45:17 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_separate(char *str, char sep)
{
	char	**splited;
	int		i;

	splited = ft_calloc(sizeof(char *), 3);
	if (!splited)
		return (NULL);
	i = 0;
	while (str[i] != sep)
		i++;
	splited[0] = ft_calloc(sizeof(char), i + 1);
	if (!splited[0])
		return (free(splited), NULL);
	splited[1] = ft_calloc(sizeof(char), (ft_strlen(str) - (i + 1)) + 1);
	if (!splited[1])
		return (free(splited[0]), free(splited), NULL);
	ft_strlcpy(splited[0], str, i + 1);
	ft_strlcpy(splited[1], &str[i + 1], ft_strlen(str) - i);
	splited[2] = 0;
	return (splited);
}

t_kv	*env_cpy(char **env)
{
	t_kv	*lst_env;
	t_kv	*new;
	char	**tmp;
	int		i;

	if (!env || !*env)
		return (NULL);
	lst_env = NULL;
	i = -1;
	while (env[++i])
	{
		tmp = ft_separate(env[i], '=');
		if (!tmp || !tmp[0] || !tmp[1])
			return (ft_lstclear_env(&lst_env, free), NULL);
		new = ft_lstnew_env(tmp[0], tmp[1]);
		if (!new)
			return(free_mat(tmp), ft_lstclear_env(&lst_env, free), NULL);
		free(tmp);
		ft_lstadd_back_env(&lst_env, new);
	}
	return (lst_env);
}
