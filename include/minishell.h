/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:31:13 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/26 21:36:25 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "lists.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
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
	int			std[2];
	int			last_status;
	int			stdin;
	int			stdout;
}				t_minishell;

typedef struct s_command
{
	char		**command;
	char		*file_in;
	char		*file_out;
	int			has_heredoc;
	int			has_append;
	int			builtin;
}				t_command;

char			**ft_separate(char *str, char sep);
void			free_mat(char **mat);
t_kv			*ft_lstnew_env(char *key, char *value);
void			ft_lstadd_back_env(t_kv **lst, t_kv *new_node);
void			ft_lstclear_env(t_kv **lst, void (*del)(void *));
int				ft_lstsize_env(t_kv *lst);
void			ft_lstdelone_env(t_kv *mem, t_kv *lst, void (*del)(void *));
void			ft_lstsort_env(t_kv *top);
t_kv			*ft_lstcpy_env(t_kv *top);

void			free_minishell(t_minishell *minishell);

t_kv			*env_cpy(char **env);
char			**convert_env(t_kv *lst);
t_kv			*env_cpy(char **env);
char			*get_env(t_minishell minishell, char *to_search);
int				modif_env(t_minishell *minishell, char *key_s, char *value_m);
char			**convert_env(t_kv *lst);

#endif