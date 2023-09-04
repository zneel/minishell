/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlevel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:02:52 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/04 13:09:32 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlevel(t_minishell *minishell)
{
	char	*shlevel;

	shlevel = get_env(minishell, "SHLVL");
	if (!shlevel)
		return ;
	minishell->shlevel = ft_atoi(shlevel);
	minishell->shlevel++;
	modif_env(minishell, "SHLVL", ft_itoa(minishell->shlevel));
}
