/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:20:08 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/04 14:01:05 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	print_env(t_minishell *minishell)
{
	t_kv	*env;

	env = minishell->env;
	while (env)
	{
		if (env->value[0])
			ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
