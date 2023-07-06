/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoyer <mhoyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 07:41:40 by mhoyer            #+#    #+#             */
/*   Updated: 2023/07/06 11:02:29 by mhoyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_pwd(t_list *env)
{
	int		i;
	
	i = -1;
	while (env)
	{
		if (ft_strncmp((char *)env->content, "PWD=", 4) == 0)
			return ((char *)env->content);
		env = env->next;
	}
	return (NULL);
}

int	pwd(int argc, char **argv, t_minishell minishell)
{
	char	*dir;

	(void)argc;
	(void)argv;
	dir = get_pwd(minishell.env);
	if (dir == NULL)
		return (1);
	printf("%s\n", dir);
	return (0);
}
