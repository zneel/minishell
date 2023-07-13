/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 09:44:17 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/13 11:47:09 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	modif_env(t_minishell *minishell, char *key_s, char *value_m)
{
	t_kv	*parc;
	
	parc = minishell->env;
	while (parc)
	{
		if (ft_strncmp(parc->key, key_s, ft_strlen(key_s)) == 0)
		{
			free(parc->value);
			parc->value = ft_strdup(value_m);
			if (!parc->value)
				return (1);
		}
		parc = parc->next;
	}
	return (0);
}
