/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:01:45 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/31 23:28:20 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "exec.h"
# include "ft_printf.h"
# include "libft.h"
# include "minishell.h"
# include "signals.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_builtin_type
{
	NONE,
	ECHO,
	EXPORT,
	ENV,
	PWD,
	UNSET,
	CD,
	EXIT,
	W_PATH,
}				t_builtin_type;

t_builtin_type	check_npath(char *cmd);
int				replace_env(t_kv *env, char **tmp);
int				echo(t_command *cmd);
int				pwd(t_minishell *minishell);
int				print_env(t_minishell *minishell);
int				export(t_command *cmd, t_minishell *minishell);
int				unset(t_command *cmd, t_minishell *minishell);
int				cd(t_command *cmd, t_minishell *minishell);
int				ft_exit(t_command *cmd, t_minishell *minishell);
#endif