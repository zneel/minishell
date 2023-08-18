/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:57:05 by mhoyer            #+#    #+#             */
/*   Updated: 2023/08/18 14:50:58 by ebouvier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

int	test_cmd(char *cmd)
{
	return (access(cmd, F_OK | X_OK) == 0);
}

char	**split_paths(char *env)
{
	char	**paths;

	paths = ft_split(env, ":");
	if (!paths || !*paths)
		return (NULL);
	return (paths);
}

char	*get_good_cmd(char **paths, char *cmd)
{
	char	*good_cmd;
	char	*good_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		good_path = ft_strjoin(paths[i], "/");
		good_cmd = ft_strjoin(good_path, cmd);
		free(good_path);
		if (test_cmd(good_cmd))
			return (good_cmd);
		free(good_cmd);
		i++;
	}
	return (NULL);
}

char	*join_cmd(char *cmd, char **env)
{
	char	**paths;
	int		i;
	char	*good_cmd;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			paths = split_paths(&env[i][5]);
			if (!paths)
				return (NULL);
			good_cmd = get_good_cmd(paths, cmd);
			if (good_cmd)
				return (free_mat(paths), good_cmd);
			return (free_mat(paths), NULL);
		}
		i++;
	}
	return (NULL);
}

char	**get_cmd(char **cmd, char **env)
{
	char	*pathed_cmd;

	if (!cmd || !*cmd)
		return (NULL);
	if (test_cmd(cmd[0]))
		return (cmd);
	if (!env || !*env)
		return (free_mat(cmd), NULL);
	pathed_cmd = join_cmd(cmd[0], env);
	if (!pathed_cmd)
		return (cmd);
	free(cmd[0]);
	cmd[0] = pathed_cmd;
	return (cmd);
}
