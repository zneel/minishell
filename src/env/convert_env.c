/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:30:28 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/01 16:29:24 by ebouvier         ###   ########.fr       */
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
	if (!lst)
		return (NULL);
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
		lst = lst->next;
		i++;
	}
	mat[i] = NULL;
	return (mat);
}
