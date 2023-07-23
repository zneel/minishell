/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:37:21 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/23 09:52:13 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"
# include "libft.h"
# include "minishell.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

char		**get_cmd(char *raw_cmd, char **env);
int   		prep_exec(t_node *node, t_minishell *minishell);
void	here_doc(char *limiter);

void		execute_command(t_command *cmd, t_minishell *minishell);
int		execute_first(t_command *cmd, t_minishell *minishell, int pipefd[2][2]);
int		execute_middle(t_command *cmd, t_minishell *minishell, int pipefd[2][2]);
int		execute_last(t_command *cmd, t_minishell *minishell, int pipefd[2][2]);
int		execute_pipeline(t_node *root, t_node *node, t_minishell *minishell,
			int pipefd[2][2]);

void		init_pipes(int pipefd[2][2]);
void		close_if(int fd);
void		wait_all(int nb_cmd);
t_command	*node_to_command(t_node *node, char **env);
int			msg_error(char *str);
void	free_cmd(t_command *cmd);
void	free_minishell(t_minishell *minishell);

#endif