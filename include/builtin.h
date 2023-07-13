/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:01:45 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/26 21:35:37 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "exec.h"
# include "ft_printf.h"
# include "libft.h"
# include "minishell.h"
# include <stdio.h>
# include <stdlib.h>

typedef enum s_builtin_type
{
	NONE,
	ECHO,
	EXPORT,
	ENV,
	PWD,
	UNSET,
	CD,
}	t_builtin_type;

int	check_builtin(t_command *cmd);
int	echo(int argc, char **argv);
int	pwd(int argc, char **argv, t_minishell minishell);
int	print_env(int argc, char **argv, t_minishell minishell);
int	export(int argc, char **argv, t_minishell *minishell);
int	unset(int argc, char **argv, t_minishell *minishell);
int	cd(int argc, char **argv, t_minishell *minishell);

#endif