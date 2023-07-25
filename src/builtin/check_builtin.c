/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:51:16 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/25 09:23:20 by mhoyer           ###   ########.fr       */
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
	if (size == -1)
		return (0);
	return (1);
}

int	check_builtin(t_command *cmd)
{
	if (!cmd->command)
		return (NONE);
	if (ft_strncmp_back(cmd->command[0], "echo", ft_strlen("echo")) == 0)
		return (ECHO);
	if (ft_strncmp_back(cmd->command[0], "export", ft_strlen("export")) == 0)
		return (EXPORT);
	if (ft_strncmp_back(cmd->command[0], "env", ft_strlen("env")) == 0)
		return (ENV);
	if (ft_strncmp_back(cmd->command[0], "pwd", ft_strlen("pwd")) == 0)
		return (PWD);
	if (ft_strncmp_back(cmd->command[0], "unset", ft_strlen("unset")) == 0)
		return (UNSET);
	if (ft_strncmp_back(cmd->command[0], "cd", ft_strlen("cd")) == 0)
		return (CD);
	return (0);
}
