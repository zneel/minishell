/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:37:21 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/21 15:57:50 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtin.h"
# include "ft_printf.h"
# include "libft.h"
# include "minishell.h"
# include "parser.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int			test_cmd(char *cmd);
char		**get_cmd(char **cmd, char **env);
int			prep_exec(t_minishell *minishell);
void		here_doc(char *limiter);

int			exec_builtin(t_command *cmd, t_minishell *minishell, int prep);
int			exec_cmd(t_node *node, t_minishell *minishell);
int			exec_or(t_node *node, t_minishell *minishell);
int			exec_and(t_node *node, t_minishell *minishell);
int			exec_pipe(t_node *node, t_minishell *minishell, int pipefd[2][2]);
int			exec(t_node *node, t_minishell *minishell);
void		execute_command(t_command *cmd, t_minishell *minishell);
int			execute_first(t_command *cmd, t_minishell *minishell,
				int pipefd[2][2]);
int			execute_middle(t_command *cmd, t_minishell *minishell,
				int pipefd[2][2]);
int			execute_last(t_command *cmd, t_minishell *minishell,
				int pipefd[2][2]);
int			execute_pipeline(t_node *root, t_node *node, t_minishell *minishell,
				int pipefd[2][2]);

void		init_pipes(int pipefd[2][2]);
void		close_if(int fd);
void		wait_all(t_minishell *minishell);
void		dup_for_out(t_command *cmd);
void		dup_for_in(t_command *cmd);
void		open_file(t_command *command, t_node *node);
t_command	*node_to_command(t_node *node, char **env);
int			msg_error(char *str, char *error);
void		free_minishell(t_minishell *minishell);
void		exec_failed(t_command *cmd, char **env, t_minishell *minishell,
				int status);
void		nothing(void *x);

#endif