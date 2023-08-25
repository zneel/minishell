/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:31:13 by ebouvier          #+#    #+#             */
/*   Updated: 2023/08/25 13:12:45 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "lists.h"
# include "parser.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

# define FILE_HEREDOC "/tmp/here_doc.tmp"

typedef struct s_kv
{
	char		*key;
	char		*value;
	struct s_kv	*next;
}				t_kv;

typedef struct s_minishell
{
	t_kv		*env;
	t_list		*pids;
	t_node		*root;
	int			last_status;
	int			std[2];
}				t_minishell;

typedef struct s_command
{
	char		**command;
	char		*file_in;
	char		*file_out;
	t_bool		has_good_infile;
	t_bool		has_good_outfile;
	t_bool		has_heredoc;
	t_bool		has_append;
	t_bool		has_infile;
	t_bool		has_outfile;
	t_bool		has_path;
	int			builtin;
	t_bool		can_exec;
}				t_command;

char			**ft_separate(char *str, char sep);
void			free_mat(char **mat);
t_kv			*ft_lstnew_env(char *key, char *value);
void			ft_lstadd_back_env(t_kv **lst, t_kv *new_node);
void			ft_lstclear_env(t_kv **lst, void (*del)(void *));
int				ft_lstsize_env(t_kv *lst);
void			ft_lstdelone_env(t_kv *lst, void (*del)(void *));
void			ft_lstsort_env(t_kv *top);
t_kv			*ft_lstcpy_env(t_kv *top);

void			free_minishell(t_minishell *minishell);

t_kv			*env_cpy(char **env);
char			**convert_env(t_kv *lst);
t_kv			*env_cpy(char **env);
char			*get_env(t_minishell *minishell, char *to_search);
int				modif_env(t_minishell *minishell, char *key_s, char *value_m);
char			**convert_env(t_kv *lst);

#endif