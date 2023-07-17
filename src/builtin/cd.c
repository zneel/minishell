/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 09:23:02 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/17 11:06:33 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int go_home(t_minishell *minishell)
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

int	cd(int argc, char **argv, t_minishell *minishell)
{
	char	*old_pwd;
	char	*pwd;

	if (argc > 2)
		return (1);
	if (argc == 1)
		return (go_home(minishell));
	if (access(argv[1], F_OK) == -1)
		return (1);
	old_pwd = ft_strdup(get_env(*minishell, "PWD"));
	if (!old_pwd)
		return (1);
	if (chdir(argv[1]))
		return (1);
	pwd = alloc_pwd(argv[1]);
	if (!pwd)
		return (free(old_pwd), 1);
	if (modif_env(minishell, "PWD", pwd) || modif_env(minishell, "OLDPWD", old_pwd))
		return (free(pwd), free(old_pwd), 1);
	free(pwd);
	free(old_pwd);
	return (0);
}
