/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 13:31:06 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/31 13:13:21 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "signals.h"

int		g_sigint = 0;

void	sig_handler_minishell(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
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

void	sig_handler_here_doc(int sig)
{
	close(0);
	if (sig == SIGINT)
		g_sigint = 1;
}
