/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:31:06 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/01 19:35:56 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "signals.h"

void	sig_handler_minishell(int sig)
{
	if (sig == SIGINT)
	{
		ft_dprintf(1, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		ft_dprintf(1, "\33[2K\r");
		rl_on_new_line();
		rl_redisplay();
	}
}
void	sig_handler_job(int sig)
{
	(void)sig;
}
