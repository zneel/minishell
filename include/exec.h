/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:37:21 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/29 12:56:51 by mhoyer           ###   ########.fr       */
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
char		**convert_arg(t_list *lst);
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
int			try_can_exec(t_command *command, t_node **parc_infile);
int			open_infile(t_command *command, t_node *node);
t_node		*try_access_out(t_node *parc_outfile, int *next_out, t_bool creat);
void		creat_outfile(int next_out, t_node *parc_outfile);
int			open_outfile(t_command *command, t_node *node);
void		close_if(int fd);
void		wait_all(t_minishell *minishell);
void		dup_for_out(t_command *cmd);
void		dup_for_in(t_command *cmd);
t_bool		check_in(t_redirect *red, t_command *cmd);
t_bool		check_out(t_redirect *red, t_command *cmd);
t_command	*node_to_command(t_node *node, char **env);
int			msg_error(char *str, char *error);
void		free_minishell(t_minishell *minishell);
void		exec_failed(t_command *cmd, char **env, t_minishell *minishell,
				int status);
void		nothing(void *x);
void		free_command(t_command *cmd);
#endif