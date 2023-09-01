/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:05:16 by ebouvier          #+#    #+#             */
/*   Updated: 2023/09/01 15:31:03 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	free_exit(t_command *cmd, t_minishell *minishell,
		long long exit_code)
{
	free_command(cmd);
	free_minishell(minishell);
	if (exit_code < 0)
		exit(156);
	else
		exit(exit_code);
}

static t_bool	overflow_check(char *str, long long exit_code)
{
	t_bool	overflow;
	char	*value;
	int		i;

	i = 0;
	overflow = false;
	value = ft_lltoa_base(exit_code, "0123456789");
	if (!value)
		return (false);
	while (str[i] && (ft_isspace(str[i]) || str[i] == '+'))
		i++;
	if (ft_strncmp(value, str + i, ft_strlen(value)) != 0)
		overflow = true;
	free(value);
	return (overflow);
}

int	ft_exit(t_command *cmd, t_minishell *minishell)
{
	long long	exit_code;

	if (arg_len(cmd->command) > 2)
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		free_exit(cmd, minishell, 1);
	}
	if (arg_len(cmd->command) == 1)
	{
		if (isatty(0) == 1)
			ft_printf("exit\n");
		free_exit(cmd, minishell, minishell->last_status);
	}
	exit_code = ft_atoll(cmd->command[1]);
	if (overflow_check(cmd->command[1], exit_code))
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
			cmd->command[1]);
		free_exit(cmd, minishell, 2);
	}
	if (isatty(0) == 1)
		ft_printf("exit\n");
	free_exit(cmd, minishell, exit_code);
	return (0);
}
