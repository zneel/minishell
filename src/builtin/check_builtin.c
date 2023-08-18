/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:51:16 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/18 21:49:19 by ebouvier         ###   ########.fr       */
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
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (ECHO);
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (EXPORT);
	if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (ENV);
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (PWD);
	if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (UNSET);
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (CD);
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
