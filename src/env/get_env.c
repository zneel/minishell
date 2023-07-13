/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 09:34:27 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/13 09:37:42 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(t_minishell minishell, char *to_search)
{
	while (minishell.env)
	{
		if (strncmp(minishell.env->key, to_search, ft_strlen(to_search)) == 0)
			return (minishell.env->value);
		minishell.env = minishell.env->next;
	}
	return (NULL);
}