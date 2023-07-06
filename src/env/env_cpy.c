/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:05:32 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 09:22:52 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_cpy(char **env)
{
	t_list	*lst_env;
	t_list	*new;
	char	*tmp;
	int		i;

	lst_env = NULL;
	i = -1;
	while (env[++i])
	{
		tmp = malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		if (!tmp)
		{
			ft_lstclear(&lst_env, &free);
			return (NULL);
		}
		ft_strlcpy(tmp, env[i], ft_strlen(env[i]) + 1);
		new = ft_lstnew(tmp);
		if (!new)
		{
			ft_lstclear(&lst_env, &free);
			return (NULL);
		}
		ft_lstadd_back(&lst_env, new);
	}
	return (lst_env);
}
