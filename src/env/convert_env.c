/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:30:28 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 13:36:27 by mhoyer           ###   ########.fr       */
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

	i = 0;
	mat = ft_calloc(sizeof(char *), ft_lstsize_env(lst) + 1);
	if (!mat)
		return (NULL);
	while (lst)
	{
		tmp = ft_strjoin(lst->key, "=");
		if (!tmp)
			return (free_before_return(mat, i), NULL);
		mat[i] = ft_strjoin(tmp, lst->value);
		free(tmp);
		if (!mat[i])
			return (free_before_return(mat, i), NULL);
		i++;
		lst = lst->next;
	}
	mat[i] = NULL;
	return (mat);
}
