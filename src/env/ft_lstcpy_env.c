/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 08:57:28 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/14 14:49:09 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_kv	*ft_lstcpy_env(t_kv *top)
{
	t_kv	*new_top;
	t_kv	*parc;
	char	*key_cpy;
	char	*value_cpy;

	new_top = NULL;
	parc = top;
	while (parc != NULL)
	{
		key_cpy = ft_strdup(parc->key);
		if (!key_cpy)
			return (NULL);
		value_cpy = ft_strdup(parc->value);
		if (!value_cpy)
			return (free(key_cpy), NULL);
		ft_lstadd_back_env(&new_top, ft_lstnew_env(key_cpy, value_cpy));
		parc = parc->next;
	}
	return (new_top);
}
