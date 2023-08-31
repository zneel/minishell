/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 09:23:02 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/31 18:47:50 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	arg_len(char **arg)
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

	home = get_env(minishell, "HOME");
	if (!home || ft_strlen(home) == 0)
		return (1);
	old_pwd = get_env(minishell, "PWD");
	if (old_pwd)
		modif_env(minishell, "OLDPWD", old_pwd);
	if (chdir(home) == -1)
		return (1);
	if (get_env(minishell, "PWD"))
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

int	do_cd(t_command *cmd, t_minishell *minishell)
{
	char	*path_to_go;

	if (is_same(cmd->command[1], "-"))
	{
		path_to_go = get_env(minishell, "OLDPWD");
		if (!path_to_go)
			return (1);
		if (chdir(path_to_go))
			return (1);
	}
	else
	{
		if (chdir(cmd->command[1]))
			return (1);
	}
	return (1);
}

int	cd(t_command *cmd, t_minishell *minishell)
{
	char	*pwd;

	if (arg_len(cmd->command) > 2)
		return (msg_error("too many arguments", "cd"));
	if (arg_len(cmd->command) == 1)
		return (go_home(minishell));
	if (ft_strncmp(cmd->command[1], "-", ft_strlen(cmd->command[1])) == 1
		&& access(cmd->command[1], F_OK) == -1)
		return (msg_error_more("No such file or directory", cmd->command[1], "cd"));
	if (access(cmd->command[1], F_OK) == -1)
		return (msg_error_more("No such file or directory", cmd->command[1], "cd"));
	do_cd(cmd, minishell);
	pwd = alloc_pwd(cmd->command[1]);
	if (!pwd)
		return (1);
	if (modif_env(minishell, "OLDPWD", get_env(minishell, "PWD"))
		|| modif_env(minishell, "PWD", pwd))
		return (free(pwd), 1);
	free(pwd);
	return (0);
}
