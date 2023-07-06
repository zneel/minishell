/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 21:31:13 by ebouvier          #+#    #+#             */
/*   Updated: 2023/07/06 13:28:54 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "lists.h"

typedef struct s_kv
{
	char		*key;
	char		*value;
	struct s_kv	*next;
}	t_kv;

typedef struct s_minishell
{
	t_kv	*env;
}	t_minishell;

void	free_mat(char **mat);

t_kv	*ft_lstnew_env(char *key, char *value);
void	ft_lstadd_back_env(t_kv **lst, t_kv *new_node);
void	ft_lstclear_env(t_kv **lst, void (*del)(void *));
int		ft_lstsize_env(t_kv *lst);

t_kv	*env_cpy(char **env);
char	**convert_env(t_kv *lst);

#endif