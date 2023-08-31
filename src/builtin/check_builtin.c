/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:51:16 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/31 15:58:44 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_builtin_type	check_npath(char *cmd)
{
	if (!cmd)
		return (NONE);
	if (is_same(cmd, "echo"))
		return (ECHO);
	if (is_same(cmd, "export"))
		return (EXPORT);
	if (is_same(cmd, "env"))
		return (ENV);
	if (is_same(cmd, "pwd"))
		return (PWD);
	if (is_same(cmd, "unset"))
		return (UNSET);
	if (is_same(cmd, "cd"))
		return (CD);
	if (is_same(cmd, "exit"))
		return (EXIT);
	return (NONE);
}
