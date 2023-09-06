/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlevel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:02:52 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/06 11:05:44 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include <stdint.h>

void	set_shlevel(t_minishell *minishell)
{
	char		*shlevel;
	char		**shlevel_arr;
	char		*sh_value;
	long long	atoll_value;

	shlevel = get_env(minishell, "SHLVL");
	if (!shlevel)
	{
		shlevel_arr = ft_split("SHLVL=1", "=");
		if (!shlevel_arr)
			return ;
		if (new_env(&minishell->env, shlevel_arr))
			return (free_mat(shlevel_arr));
		return (free(shlevel_arr));
	}
	atoll_value = ft_atoll(shlevel);
	if (atoll_value == LLONG_MAX || atoll_value == LLONG_MIN)
		minishell->shlevel = 0;
	else
		minishell->shlevel = atoll_value;
	minishell->shlevel++;
	sh_value = ft_itoa(minishell->shlevel);
	if (modif_env(minishell, "SHLVL", sh_value))
		return ;
	free(sh_value);
}
