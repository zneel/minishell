/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:01:45 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/24 23:15:30 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include "ft_printf.h"
# include "exec.h"
# include <stdlib.h>
# include <stdio.h>
# include "minishell.h"

typedef enum s_builtin_type
{
	NONE,
	ECHO,
	EXPORT,
	ENV,
	PWD,
	UNSET,
	CD,
}						t_builtin_type;

int	check_builtin(t_command *cmd);
int	echo(t_command *cmd);
int	pwd(t_minishell minishell);
int	print_env(t_minishell minishell);
int	export(t_command *cmd, t_minishell *minishell);
int	unset(t_command *cmd, t_minishell *minishell);

#endif