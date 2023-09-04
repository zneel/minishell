/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlevel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:02:52 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/04 13:45:08 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

void	set_shlevel(t_minishell *minishell)
{
	char	*shlevel;
	char	**shlevel_arr;
	char	*sh_value;

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
	minishell->shlevel = ft_atoi(shlevel);
	minishell->shlevel++;
	sh_value = ft_itoa(minishell->shlevel);
	modif_env(minishell, "SHLVL", sh_value);
	free(sh_value);
}
