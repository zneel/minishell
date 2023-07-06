/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 11:20:08 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 11:26:53 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	print_env(int argc, char **argv, t_minishell minishell)
{
	(void)argc;
	(void)argv;
	while (minishell.env)
	{
		printf("%s\n", (char *)minishell.env->content);
		minishell.env = minishell.env->next;
	}
	return (0);
}