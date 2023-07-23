/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:31:13 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/23 09:41:59 by mhoyer           ###   ########.fr       */
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
typedef struct s_kv
{
	char		*key;
	char		*value;
	struct s_kv	*next;
}				t_kv;

typedef struct s_minishell
{
	t_kv		*env;
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
}				t_command;

char			**ft_separate(char *str, char sep);
void			free_mat(char **mat);

t_kv			*ft_lstnew_env(char *key, char *value);
void			ft_lstadd_back_env(t_kv **lst, t_kv *new_node);
void			ft_lstclear_env(t_kv **lst, void (*del)(void *));
int				ft_lstsize_env(t_kv *lst);
void			ft_lstdelone_env(t_kv *mem, t_kv *lst, void (*del)(void *));

t_kv			*env_cpy(char **env);
char			**convert_env(t_kv *lst);

#endif