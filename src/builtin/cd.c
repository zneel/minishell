/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 09:23:02 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/26 21:50:00 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	arg_len(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (0);
	while (arg[i])
		i++;
	return (i);
}

int	go_home(t_minishell *minishell)
{
	char	*home;
	char	*old_pwd;

	home = get_env(*minishell, "HOME");
	if (!home)
		return (1);
	old_pwd = get_env(*minishell, "PWD");
	modif_env(minishell, "OLDPWD", old_pwd);
	chdir(home);
	modif_env(minishell, "PWD", home);
	return (0);
}

char	*alloc_pwd(char *argv)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	if (argv && argv[0] == '/' && argv[1] == '/' && argv[2] != '/')
	{
		free(pwd);
		pwd = ft_strdup(argv);
		if (!pwd)
			return (NULL);
	}
	return (pwd);
}

int	cd(t_command *cmd, t_minishell *minishell)
{
	char	*old_pwd;
	char	*pwd;

	if (arg_len(cmd->command) > 2)
		return (1);
	if (arg_len(cmd->command) == 1)
		return (go_home(minishell));
	if (access(cmd->command[1], F_OK) == -1)
		return (1);
	old_pwd = ft_strdup(get_env(*minishell, "PWD"));
	if (!old_pwd)
		return (1);
	if (chdir(cmd->command[1]))
		return (1);
	pwd = alloc_pwd(cmd->command[1]);
	if (!pwd)
		return (free(old_pwd), 1);
	if (modif_env(minishell, "PWD", pwd) || modif_env(minishell, "OLDPWD",
			old_pwd))
		return (free(pwd), free(old_pwd), 1);
	free(pwd);
	free(old_pwd);
	return (0);
}
