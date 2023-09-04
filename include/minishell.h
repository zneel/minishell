/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:31:13 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/04 13:09:00 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "lists.h"
# include "structs.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

# define FILE_HEREDOC "/tmp/here_doc.tmp"

typedef enum e_mode
{
	M_HERE_DOC = (1 << 0),
	M_APPEND = (1 << 2),
	M_IN = (1 << 3),
	M_OUT = (1 << 4),
	M_NO_MODE = (1 << 5),
}			t_mode;

typedef enum e_err
{
	ERR_NO_ERR = 0,
	ERR_BASIC = 1,
	ERR_NOT_FOUND = 127,
	ERR_IS_DIR = 126,
}			t_err;

typedef struct s_command
{
	char	**command;
	char	*file_in;
	char	*file_out;
	t_bool	has_good_file;
	t_mode	mode;
	t_err	error;
	t_bool	has_path;
	int		builtin;
}			t_command;

char		**ft_separate(char *str, char sep);
void		free_mat(char **mat);
t_kv		*ft_lstnew_env(char *key, char *value);
void		ft_lstadd_back_env(t_kv **lst, t_kv *new_node);
void		ft_lstclear_env(t_kv **lst, void (*del)(void *));
int			ft_lstsize_env(t_kv *lst);
void		ft_lstdelone_env(t_kv *lst, void (*del)(void *));
void		ft_lstsort_env(t_kv *top);
t_kv		*ft_lstcpy_env(t_kv *top);

void		free_minishell(t_minishell *minishell);
void		free_before_return(char **mat, int i);
void		close_if(int fd);

t_kv		*env_cpy(char **env);
char		**convert_env(t_kv *lst);
t_kv		*env_cpy(char **env);
char		*get_env(t_minishell *minishell, char *to_search);
int			modif_env(t_minishell *minishell, char *key_s, char *value_m);
char		**convert_env(t_kv *lst);
t_bool		is_same(char *s1, char *s2);
char		*prompt(void);
void		init_minishell(t_minishell *minishell, char **env);
int			str_all_space(char *str);
void		dup_minishell(t_minishell *ms);
void		close_minishell_dup(t_minishell *ms);
void		set_shlevel(t_minishell *minishell);
#endif