/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:10:38 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 12:10:49 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_list *env, char *var)
{
	int		i;

	i = -1;
	while (env)
	{
		if (ft_strncmp((char *)env->content, var, ft_strlen(var)) == 0)
			return ((char *)env->content);
		env = env->next;
	}
	return (NULL);
}
