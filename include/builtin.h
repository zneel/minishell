/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 08:01:45 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 10:56:14 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include "minishell.h"

int	echo(int argc, char **argv);
int	pwd(int argc, char **argv, t_minishell minishell);

#endif