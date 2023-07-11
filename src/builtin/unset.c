/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 07:32:23 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/11 10:01:40 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	unset(int argc, char **argv, t_minishell *minishell)
{
	int		i;
	t_kv	*parc;

	i = 0;
	if (argc < 2)
		return (1);
	while (argv[++i])
	{
		parc = minishell->env; 
		while (parc)
		{
			if (ft_strncmp(argv[i], parc->key, ft_strlen(argv[i])) == 0)
			{
				ft_lstdelone_env(minishell->env, parc, free);
				parc = NULL;
			}
			if (parc)
				parc = parc->next;
		}
	}
	return (0);
}
