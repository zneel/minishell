/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:05:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 09:37:41 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_cpy(char **env)
{
	t_list	*lst_env;
	t_list	*new;
	char	*tmp;
	int		i;

	if (!env || !*env)
		return (NULL);
	lst_env = NULL;
	i = -1;
	while (env[++i])
	{
		tmp = ft_calloc(sizeof(char), ft_strlen(env[i]) + 1);
		if (!tmp)
			return (ft_lstclear(&lst_env, &free), NULL);
		ft_strlcpy(tmp, env[i], ft_strlen(env[i]) + 1);
		new = ft_lstnew(tmp);
		if (!new)
			return (ft_lstclear(&lst_env, &free), NULL);
		ft_lstadd_back(&lst_env, new);
	}
	return (lst_env);
}
