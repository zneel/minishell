/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:32:11 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/15 14:32:37 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_minishell(t_minishell *minishell)
{
	rl_clear_history();
	ast_delete(minishell->root);
	ft_lstclear(&minishell->pids, nothing);
	ft_lstclear_env(&minishell->env, free);
	close(minishell->std[0]);
	close(minishell->std[1]);
}