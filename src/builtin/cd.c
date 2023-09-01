/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 09:23:02 by mhoyer            #+#    #+#             */
/*   Updated: 2023/09/01 17:37:59 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	msg_for_perm(char *file)
{
	struct stat	file_info;

	file_info.st_mode = 0;
	stat(file, &file_info);
	if (S_ISDIR(file_info.st_mode))
		return (msg_error("Permission denied", file, "cd"));
	else
		return (msg_error("Not a directory", file, "cd"));
}

int	go_home(t_minishell *minishell)
{
	char	*home;
	char	*old_pwd;

	home = get_env(minishell, "HOME");
	if (!home || ft_strlen(home) == 0)
		return (msg_error("HOME not set", "cd", NULL));
	old_pwd = get_env(minishell, "PWD");
	if (old_pwd)
		modif_env(minishell, "OLDPWD", old_pwd);
	if (chdir(home) == -1)
		return (msg_for_perm(home));
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
			return (msg_error("OLDPWD not set", "cd", NULL));
		if (chdir(path_to_go))
			return (msg_for_perm(path_to_go));
		printf("%s\n", path_to_go);
	}
	else if (is_same(cmd->command[1], "~"))
	{
		path_to_go = get_env(minishell, "HOME");
		if (!path_to_go)
			return (msg_error("HOME not set", "cd", NULL));
		if (chdir(path_to_go))
			return (msg_for_perm(path_to_go));
	}
	else
	{
		if (chdir(cmd->command[1]))
			return (msg_for_perm(cmd->command[1]));
	}
	return (0);
}

int	cd(t_command *cmd, t_minishell *minishell)
{
	char	*pwd;

	if (arg_len(cmd->command) > 2)
		return (msg_error("too many arguments", "cd", NULL));
	if (arg_len(cmd->command) == 1)
		return (go_home(minishell));
	if (access(cmd->command[1], F_OK) == -1 && !is_same("-", cmd->command[1])
		&& !is_same("~", cmd->command[1]))
		return (msg_error("No such file or directory", cmd->command[1], "cd"));
	if (do_cd(cmd, minishell))
		return (1);
	pwd = alloc_pwd(cmd->command[1]);
	if (!pwd)
		return (1);
	if (modif_env(minishell, "OLDPWD", get_env(minishell, "PWD"))
		|| modif_env(minishell, "PWD", pwd))
		return (free(pwd), 1);
	free(pwd);
	return (0);
}
