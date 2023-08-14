/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 08:17:44 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/14 14:48:16 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echanger_valeurs(t_kv *a, t_kv *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	ft_lstsort_env(t_kv *top)
{
	t_kv	*current;
	t_kv	*parc;

	current = top;
	while (current != NULL)
	{
		parc = current->next;
		while (parc != NULL)
		{
			if (ft_strncmp(current->key, parc->key,
					ft_strlen(current->key)) > 0)
			{
				echanger_valeurs(current, parc);
			}
			parc = parc->next;
		}
		current = current->next;
	}
}
