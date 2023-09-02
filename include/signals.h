/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:05:07 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/01 23:21:41 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

extern int	g_sigint;

void		sig_handler_minishell(int sig);
void		sig_handler_job(int sig);
void		sig_handler_here_doc(int sig);
void		set_signals(void);
#endif