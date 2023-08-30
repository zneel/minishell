/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:51:16 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/30 18:51:53 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_strncmp_back(char *str, char *ex, int size)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0 && size >= 0 && str[i] == ex[size])
	{
		i--;
		size--;
	}
	if (size == -1 && i != -1 && str[i] == '/')
		return (0);
	return (1);
}

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
	return (0);
}

t_builtin_type	check_wpath(char *cmd)
{
	if (!cmd)
		return (NONE);
	if (ft_strncmp_back(cmd, "echo", ft_strlen("echo")) == 0)
		return (W_PATH);
	if (ft_strncmp_back(cmd, "export", ft_strlen("export")) == 0)
		return (W_PATH);
	if (ft_strncmp_back(cmd, "env", ft_strlen("env")) == 0)
		return (W_PATH);
	if (ft_strncmp_back(cmd, "pwd", ft_strlen("pwd")) == 0)
		return (W_PATH);
	if (ft_strncmp_back(cmd, "unset", ft_strlen("unset")) == 0)
		return (W_PATH);
	if (ft_strncmp_back(cmd, "cd", ft_strlen("cd")) == 0)
		return (W_PATH);
	if (ft_strncmp_back(cmd, "exit", ft_strlen("exit")) == 0)
		return (W_PATH);
	return (0);
}

t_builtin_type	check_builtin(char *str)
{
	int	builtin;

	builtin = check_npath(str);
	if (builtin)
		return (builtin);
	return (check_wpath(str));
}
