/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:56:22 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/30 12:00:08 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**convert_arg(t_list *lst)
{
	char	**mat;
	int		i;

	i = 0;
	if (!lst)
		return (NULL);
	mat = ft_calloc(sizeof(char *), ft_lstsize(lst) + 1);
	if (!mat)
		return (NULL);
	while (lst)
	{
		mat[i] = ft_strdup(lst->content);
		if (!mat[i])
			return (free_before_return(mat, i), NULL);
		i++;
		lst = lst->next;
	}
	mat[i] = NULL;
	return (mat);
}
