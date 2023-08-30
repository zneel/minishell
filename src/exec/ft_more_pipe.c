/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_more_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:30:40 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/30 13:57:31 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	builtin_pipe(t_command *cmd, char **env, t_minishell *minishell)
{
	int	status;

	signal(SIGPIPE, sig_handler_job);
	status = exec_builtin(cmd, minishell, false);
	exec_failed(cmd, env, minishell, status);
}

void	close_all_pipe_free(int pipefd[2][2], t_minishell *ms, t_command *cmd)
{
	free_command(cmd);
	free_minishell(ms);
	close_if(pipefd[0][1]);
	close_if(pipefd[0][0]);
	close_if(pipefd[1][0]);
	close_if(pipefd[1][1]);
	exit(127);
}
