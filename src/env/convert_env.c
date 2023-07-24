/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:30:28 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/24 18:34:58 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_before_return(char **mat, int i)
{
	while (--i >= 0)
		free(mat[i]);
	free(mat);
}

char	**convert_env(t_kv *lst)
{
	char	**mat;
	char	*tmp;
	int		i;
	t_kv *copy;

	i = 0;
	copy = lst;
	mat = ft_calloc(sizeof(char *), ft_lstsize_env(copy) + 1);
	if (!mat)
		return (NULL);
	while (copy)
	{
		tmp = ft_strjoin(copy->key, "=");
		if (!tmp)
			return (free_before_return(mat, i), NULL);
		mat[i] = ft_strjoin(tmp, copy->value);
		free(tmp);
		if (!mat[i])
			return (free_before_return(mat, i), NULL);
		i++;
		copy = copy->next;
	}
	mat[i] = NULL;
	return (mat);
}
