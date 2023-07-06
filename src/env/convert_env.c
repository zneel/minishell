/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:30:28 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 09:47:22 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**convert_env(t_list *lst)
{
	char	**mat;
	int		i;

	mat = ft_calloc(sizeof(char *), ft_lstsize(lst) + 1);
	if (!mat)
		return (NULL);
	i = 0;
	while (lst)
	{
		mat[i] = ft_calloc(sizeof(char), ft_strlen(lst->content) + 1);
		if (!mat[i])
		{
			while (--i >= 0)
				free(mat[i - 1]);
			free(mat);
			return (NULL);
		}
		ft_strlcpy(mat[i], lst->content, ft_strlen(lst->content) + 1);
		i++;
		lst = lst->next;
	}
	mat[i] = NULL;
	return (mat);
}
