/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:20:08 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/25 11:47:38 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	print_env(t_minishell minishell)
{
	while (minishell.env)
	{
		printf("%s=%s\n", minishell.env->key, minishell.env->value);
		minishell.env = minishell.env->next;
	}
	return (0);
}
