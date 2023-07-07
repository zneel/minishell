/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:20:08 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 13:01:21 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	print_env(int argc, char **argv, t_minishell minishell)
{
	(void)argc;
	(void)argv;
	while (minishell.env)
	{
		printf("%s=%s\n", minishell.env->key, minishell.env->value);
		minishell.env = minishell.env->next;
	}
	return (0);
}
